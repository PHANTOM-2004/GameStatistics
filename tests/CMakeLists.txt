file(GLOB_RECURSE VARARRAY_SOURCES
${CMAKE_SOURCE_DIR}/include/dsa/*.hpp
)

set(TESTS_SOURCES
vararray_test.cc vararray_test.hpp
${VARARRAY_SOURCES}
)

message("Test Source files are listed below")
foreach(f IN LISTS TESTS_SOURCES)
  message("${f}")
endforeach()
message("Test Source files end")

qt_add_executable(VARARRAY_TEST
        MANUAL_FINALIZATION
        ${TESTS_SOURCES}
    )

# enable address sanitizer
target_compile_options(VARARRAY_TEST PRIVATE -fsanitize=address)
target_link_options(VARARRAY_TEST PRIVATE -fsanitize=address)

target_link_libraries(VARARRAY_TEST PRIVATE Qt6::Widgets)


qt_finalize_executable(VARARRAY_TEST)
