# Fuzzers libFuzzer (solo Clang). Activar con -DCOURSE_BUILD_FUZZERS=ON:
#   cmake --preset host-clang -DCOURSE_BUILD_FUZZERS=ON
#   cmake --build --preset host-clang --target fuzz_frame_parser
#   ./build/host-clang/fuzz/fuzz_frame_parser -max_total_time=60
if(NOT CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  message(FATAL_ERROR "COURSE_BUILD_FUZZERS requiere Clang")
endif()

function(course_fuzzer name src)
  add_executable(${name} ${src})
  target_include_directories(${name} PRIVATE ${ARGN})
  target_compile_options(${name} PRIVATE -fsanitize=fuzzer,address,undefined -g)
  target_link_options(${name} PRIVATE -fsanitize=fuzzer,address,undefined)
  target_link_libraries(${name} PRIVATE course_common)
endfunction()

course_fuzzer(fuzz_frame_parser frame_parser_fuzz.cpp ${PROJECT_SOURCE_DIR}/modules/04-tipos-vocabulario)
