program stencil_2d
  use iso_fortran_env, only: real64
  use omp_lib
  implicit none

  integer :: nx, ny, nit, i, j, it
  real(real64), pointer :: u(:,:) => null(), u_new(:,:) => null(), tmp(:,:) => null()
  real(real64) :: res, local_res, elapsed
  real(real64) :: t_start, t_end
  character(len=32) :: arg

  ! default parameters
  nx  = 4096
  ny  = 4096
  nit = 64

  ! override with command line arguments
  if (command_argument_count() >= 1) then
    call get_command_argument(1, arg)
    read(arg, *) nx
  end if
  if (command_argument_count() >= 2) then
    call get_command_argument(2, arg)
    read(arg, *) ny
  end if
  if (command_argument_count() >= 3) then
    call get_command_argument(3, arg)
    read(arg, *) nit
  end if

  allocate(u(nx, ny), u_new(nx, ny))

  ! init fields: 0 at boundaries, 1 in the interior
  do j = 1, ny
    do i = 1, nx
      if (i == 1 .or. i == nx .or. j == 1 .or. j == ny) then
        u(i, j)     = 0.0_real64
        u_new(i, j) = 0.0_real64
      else
        u(i, j)     = 1.0_real64
        u_new(i, j) = 1.0_real64
      end if
    end do
  end do

  t_start = omp_get_wtime()

  do it = 1, nit
    res = 0.0_real64

    !$omp parallel do reduction(+ : res) private(local_res)
    do j = 2, ny - 1
      do i = 2, nx - 1
        u_new(i, j) = 0.25_real64 * (u(i-1, j) + u(i+1, j) + u(i, j-1) + u(i, j+1))

        local_res = 4 * u(i, j) - (u(i-1, j) + u(i+1, j) + u(i, j-1) + u(i, j+1))
        res = res + local_res * local_res
      end do
    end do
    !$omp end parallel do

    res = sqrt(res)
    write(arg, '(ES12.4)') res
    write(*, '(A,I0,A,A)') '  Residual for iteration ', it - 1, ' is ', trim(adjustl(arg))

    !  swap source and destination pointers
    tmp   => u
    u     => u_new
    u_new => tmp
  end do

  t_end   = omp_get_wtime()
  elapsed = t_end - t_start

  write(*, '(A,I0,A,I0)') '  #cells / #it:  ', nx * ny, ' / ', nit
  write(*, '(A,F0.3,A)') '  elapsed time:  ', 1.0e3_real64 * elapsed, ' ms'
  write(*, '(A,F0.3,A)') '  per iteration: ', 1.0e3_real64 * elapsed / nit, ' ms'
  write(*, '(A,F0.3)')    '  MLUP/s:        ', &
    1.0e-6_real64 * real(nx * ny, real64) * real(nit, real64) / elapsed

  ! compute the final residual
  res = 0.0_real64
  do j = 2, ny - 1
    do i = 2, nx - 1
      local_res = 4 * u(i, j) - (u(i-1, j) + u(i+1, j) + u(i, j-1) + u(i, j+1))
      res = res + local_res * local_res
    end do
  end do
  res = sqrt(res)
  write(arg, '(ES12.4)') res
  write(*, '(A,A)') '  Final residual is ', trim(adjustl(arg))

  deallocate(u, u_new)
end program stencil_2d
