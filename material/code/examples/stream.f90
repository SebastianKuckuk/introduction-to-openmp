program stream
  use iso_fortran_env, only: real64
  use omp_lib
  implicit none

  integer :: nx, nit, i, j
  real(real64), pointer :: src(:) => null(), dest(:) => null(), tmp(:) => null()
  real(real64) :: t_start, t_end, t_it_start, t_it_end, elapsed, elapsed_it
  character(len=32) :: arg

  ! default parameters
  nx  = 64 * 1024 * 1024
  nit = 4

  ! override with command line arguments
  if (command_argument_count() >= 1) then
    call get_command_argument(1, arg)
    read(arg, *) nx
  end if
  if (command_argument_count() >= 2) then
    call get_command_argument(2, arg)
    read(arg, *) nit
  end if

  allocate(src(nx), dest(nx))

  ! init array elements with their index values (0-based to match C++ version)
  do j = 1, nx
    src(j)  = real(j - 1, real64)
    dest(j) = real(j - 1, real64)
  end do

  t_start = omp_get_wtime()

  do i = 1, nit
    write(*, '(A,I0)') 'Iteration ', i - 1
    t_it_start = omp_get_wtime()

    ! copy array elements and increase each by one
    do j = 1, nx
      dest(j) = src(j) + 1.0_real64
    end do

    !  swap source and destination pointers
    tmp => src
    src => dest
    dest => tmp

    t_it_end  = omp_get_wtime()
    elapsed_it = t_it_end - t_it_start

    write(*, '(A,F0.3,A)') '  elapsed time:  ', 1.0e3_real64 * elapsed_it, ' ms'
    write(*, '(A,F0.3,A)')  '  bandwidth:     ', &
      1.0e-9_real64 * 2 * 8 * real(nx, real64) / elapsed_it, ' GB/s'
    write(*, *)
  end do

  t_end   = omp_get_wtime()
  elapsed = t_end - t_start

  write(*, '(A)')          'Accumulated'
  write(*, '(A,I0,A,I0)') '  #cells / #it:  ', nx, ' / ', nit
  write(*, '(A,F0.3,A)') '  elapsed time:  ', 1.0e3_real64 * elapsed, ' ms'
  write(*, '(A,F0.3,A)') '  per iteration: ', 1.0e3_real64 * elapsed / nit, ' ms'
  write(*, '(A,F0.3)')    '  MLUP/s:        ', &
    1.0e-6_real64 * real(nx, real64) * real(nit, real64) / elapsed
  write(*, '(A,F0.3,A)')  '  bandwidth:     ', &
    1.0e-9_real64 * 2 * 8 * real(nx, real64) * real(nit, real64) / elapsed, ' GB/s'

  ! check solution: each element should be increased by nit
  do j = 1, nx
    if (nint(src(j)) /= (j - 1) + nit) then
      write(*, '(A,I0,A,I0,A,I0,A)') &
        '  Stream check failed for element ', j, &
        ' (expected ', (j - 1) + nit, ' but got ', nint(src(j)), ')'
      stop 1
    end if
  end do

  write(*, '(A)') '  Stream check completed'

  deallocate(src, dest)
end program stream
