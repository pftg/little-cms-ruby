require "mkmf"

# Check for compiler. Extract first word so ENV['CC'] can be a program name with arguments.
cc = (ENV["CC"] or Config::CONFIG["CC"] or "gcc").split(' ').first
unless find_executable(cc)
  exit_failure "No C compiler found in ${ENV['PATH']}. See mkmf.log for details."
end


dir_config('lcms')
have_library('lcms2')

create_makefile("lcms")

