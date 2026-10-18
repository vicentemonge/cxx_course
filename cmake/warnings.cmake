add_library(course_warnings INTERFACE)
target_compile_options(course_warnings INTERFACE
  $<$<CXX_COMPILER_ID:GNU,Clang,AppleClang>:
    -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -Wshadow
    -Wnon-virtual-dtor -Wold-style-cast -Wcast-align -Wnull-dereference
    -Wdouble-promotion -Wimplicit-fallthrough>
  $<$<CXX_COMPILER_ID:GNU>:-Wduplicated-cond -Wlogical-op -Wuseless-cast>)
