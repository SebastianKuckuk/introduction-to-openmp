program mc_pi
  use iso_fortran_env, only: real64
  use omp_lib
  implicit none

  integer :: n_sample, i, num_hits
  real(real64) :: x, y, pi, pi_ref, elapsed
  real(real64) :: t_start, t_end
  character(len=32) :: arg

  ! default parameters
  n_sample = 32 * 1024

  ! override with command line arguments
  if (command_argument_count() >= 1) then
    call get_command_argument(1, arg)
    read(arg, *) n_sample
  end if

  t_start = omp_get_wtime()

  num_hits = 0
  do i = 1, n_sample
    call random_number(x)
    call random_number(y)
    if (x*x + y*y <= 1.0_real64) num_hits = num_hits + 1
  end do

  t_end   = omp_get_wtime()
  elapsed = t_end - t_start

  pi     = 4.0_real64 * real(num_hits, real64) / real(n_sample, real64)
  pi_ref = 4.0_real64 * atan(1.0_real64)

  write(*, '(A,I0)')      '  #samples:        ', n_sample
  write(*, '(A,F0.3,A)') '  elapsed time:    ', 1.0e3_real64 * elapsed, ' ms'
  write(*, '(A,F0.3)')    '  MLUP/s:          ', &
    1.0e-6_real64 * real(n_sample, real64) / elapsed
  write(*, '(A,F0.6)')   '  Estimate for pi: ', pi
  write(arg, '(ES12.3)') abs(pi - pi_ref) / pi_ref
  write(*, '(A,A)')  '  Relative error:  ', trim(adjustl(arg))

end program mc_pi
