cmake_minimum_required(VERSION 3.17)
project(FEUP_AEDA_proj)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(libs/googletest)

include_directories(libs/googletest/googletest libs/googletest/googlemock)

include_directories(src/Exceptions src/Streams src/Users src/Utils)


add_executable(FEUP_AEDA_proj main.cpp src/Users/User.cpp src/Users/User.h src/Streams/Stream.cpp src/Streams/Stream.h src/Manager.cpp src/Manager.h src/Utils/Date.cpp src/Utils/Date.h src/Exceptions/RestrictedAgeException.cpp src/Exceptions/RestrictedAgeException.h src/Users/Viewer.cpp src/Users/Viewer.h)

target_link_libraries(FEUP_AEDA_proj gtest gtest_main)


# Doxygen Build
find_package(Doxygen)
if(DOXYGEN_FOUND)
    set(BUILD_DOC_DIR "${CMAKE_SOURCE_DIR}/docs/output")
    if(NOT EXISTS "${BUILD_DOC_DIR}")
        file(MAKE_DIRECTORY "${BUILD_DOC_DIR}")
    endif()

    set(DOXYGEN_IN "${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile")
    set(DOXYGEN_OUT "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile")
    configure_file("${DOXYGEN_IN}" "${DOXYGEN_OUT}" @ONLY)

    message("Doxygen build started")
    add_custom_target(Doxygen ALL
            COMMAND "${DOXYGEN_EXECUTABLE}" "${DOXYGEN_OUT}"
            WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM)
else(DOXYGEN_FOUND)
    message("Doxygen needs to be installed to generate the documentation.")
endif(DOXYGEN_FOUND)