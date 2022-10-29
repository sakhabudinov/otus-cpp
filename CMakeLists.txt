cmake_minimum_required(VERSION 3.12)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})

project(hw2 VERSION ${PROJECT_VERSION})

configure_file(version.h.in version.h)

add_executable(hw2 main.cpp)

set_target_properties(hw2 PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(hw2
    PRIVATE "${CMAKE_BINARY_DIR}"
)
 
if (MSVC)
    target_compile_options(hw2 PRIVATE /W4)
else ()
    target_compile_options(hw2 PRIVATE -Wall -Wextra -pedantic -Werror)
endif()

install(TARGETS hw2 RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT example@example.com)
include(CPack)
