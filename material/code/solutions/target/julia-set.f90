program julia_set
  use iso_fortran_env, only: real64
  use omp_lib
  implicit none

  integer :: nx, ny, max_it, i, j, it, k
  complex(real64) :: c, z
  real(real64) :: re, im, elapsed
  real(real64) :: t_start, t_end
  integer :: funit, julia_val, idx
  integer, allocatable :: raw(:)
  character(len=1), allocatable :: image(:)
  character(len=32) :: arg
  character(len=32) :: dims

  ! default parameters
  nx     = 1024
  ny     = 1024
  max_it = 256

  ! override with command line arguments
  if (command_argument_count() >= 1) then
    call get_command_argument(1, arg)
    read(arg, *) nx
  end if
  if (command_argument_count() >= 2) then
    call get_command_argument(2, arg)
    read(arg, *) ny
  end if

  allocate(raw(3 * nx * ny))

  ! Julia set parameter c
  c = cmplx(-0.7_real64, 0.27015_real64, real64)

  t_start = omp_get_wtime()

  ! compute the Julia set for each pixel on the device;
  ! use an integer array since char() is not available in target regions
  !$omp target teams distribute parallel do collapse(2) &
  !$omp&  map(from: raw(1:3*nx*ny)) map(to: c, nx, ny, max_it) &
  !$omp&  private(it, re, im, z, julia_val, idx)
  do j = 1, ny
    do i = 1, nx
      ! map pixel coordinates to [-1, 1] x [-1, 1]
      re = (real(i - 1, real64) - 0.5_real64 * nx) / (0.5_real64 * nx)
      im = (real(j - 1, real64) - 0.5_real64 * ny) / (0.5_real64 * ny)
      z  = cmplx(re, im, real64)

      ! iterate until escape or max iterations reached
      it = 0
      do while (it < max_it .and. abs(z) < 2.0_real64)
        z  = z * z + c
        it = it + 1
      end do

      julia_val = 255 * it / max_it

      ! store RGB channels in row-major order (matches PPM layout)
      idx = 3 * ((j - 1) * nx + (i - 1)) + 1
      raw(idx)   = julia_val
      raw(idx+1) = 0
      raw(idx+2) = 255 - julia_val
    end do
  end do
  !$omp end target teams distribute parallel do

  t_end   = omp_get_wtime()
  elapsed = t_end - t_start

  write(*, '(A,I0)')      '  #cells:       ', nx * ny
  write(*, '(A,F0.3,A)') '  elapsed time: ', 1.0e3_real64 * elapsed, ' ms'
  write(*, '(A,F0.3)')    '  MLUP/s:       ', &
    1.0e-6_real64 * real(nx * ny, real64) / elapsed

  ! convert integer pixel values to bytes for PPM output
  allocate(image(3 * nx * ny))
  do k = 1, 3 * nx * ny
    image(k) = char(raw(k))
  end do
  deallocate(raw)

  ! write P6 binary PPM: header as ASCII text, pixel data as raw bytes
  write(dims, '(I0,A,I0)') nx, ' ', ny
  open(newunit=funit, file='julia.ppm', access='stream', form='unformatted', status='replace')
  write(funit) 'P6' // char(10) // trim(dims) // char(10) // '255' // char(10)
  write(funit) image
  close(funit)

  write(*, '(A)') '  image saved as julia.ppm'

  deallocate(image)
end program julia_set
