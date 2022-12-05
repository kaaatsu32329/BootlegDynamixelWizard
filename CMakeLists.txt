cmake_minimum_required(VERSION 3.12)

file(GLOB cpp_src "src/*.cpp")
file(GLOB cpp_include "include")

file(GLOB dynamixel_sdk_src "dynamixel_sdk/src/dynamixel_sdk/*.cpp")
file(GLOB dynamixel_sdk_include "dynamixel_sdk/include/dynamixel_sdk")

project(BDWizard CXX)

if (NOT CMAKE_CONFIGURATION_TYPES AND
    NOT CMAKE_NO_BUILD_TYPE AND
    NOT CMAKE_BUILD_TYPE AND
    CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    message(STATUS "[!] Setting build type to 'Release' as none was specified.")
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

include_directories(
    ${dynamixel_sdk_include}
    ${cpp_include}
)

add_executable(Bootleg
  ${cpp_src}
  ${dynamixel_sdk_src}
)

find_package(Siv3D)
target_link_libraries(Bootleg PUBLIC Siv3D::Siv3D)

target_compile_features(Bootleg PRIVATE cxx_std_20)

if(BUILD_TESTING)
enable_testing()
add_test(
  NAME Test
  COMMAND Bootleg
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
  )
endif()
