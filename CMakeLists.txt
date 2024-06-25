cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

# 编译器/CMAKE配置
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(LINK_WHAT_YOU_USE ON)

# 项目
project(cmake-project-template LANGUAGES C CXX)

# 防止在源码目录下进行内部构建
if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
    message(FATAL_ERROR "Please create a build directory and run CMake from there")
endif()

# 编译类型
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()
message(STATUS "CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")

# 包含工具
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
include(Functions)

# 路径设置
set(PROJECT_ROOT_DIR "${PROJECT_SOURCE_DIR}")
message(STATUS "PROJECT_ROOT_DIR: ${PROJECT_ROOT_DIR}")
set(PROJECT_DEPENDS_DIR "${PROJECT_ROOT_DIR}/3rdparty")
message(STATUS "PROJECT_DEPENDS_DIR: ${PROJECT_DEPENDS_DIR}")
set_work_dirs_force("${PROJECT_BINARY_DIR}")

# 读取缓存
find_program(CCACHE_FOUND ccache)
if(CCACHE_FOUND)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache)
endif()

# 设置编译器
if(POLICY CMP0048)
    cmake_policy(SET CMP0048 NEW)
endif(POLICY CMP0048)
if(POLICY CMP0069)
    cmake_policy(SET CMP0069 NEW)
endif (POLICY CMP0069)
if(POLICY CMP0077)
    cmake_policy(SET CMP0077 NEW)
endif(POLICY CMP0077)

if(UNIX)
    add_compile_options(-fPIC 
                        -Wall -Wextra -Wpedantic -Werror=return-type 
                        -Wno-unused-function -Wno-unused-parameter -Wno-unused-variable 
                        -Wno-error=extra -Wno-error=missing-field-initializers -Wno-error=type-limits)
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        add_compile_options(-g3)
    else()
        add_compile_options(-g0)
    endif()
elseif(WIN32)
    if(MSVC)
        add_compile_options(/wd4566 /wd4819 /EHsc) # /source-charset:utf-8
        list(APPEND COMPILE_OPTIONS_DEFAULT "/nologo")
        list(APPEND CMAKE_STATIC_LINKER_FLAGS "/nologo")
    endif()
endif()
 
if(CMAKE_HOST_SYSTEM_NAME STREQUAL "Darwin")
  if(CMAKE_HOST_SYSTEM_PROCESSOR STREQUAL "arm64")
    include_directories(SYSTEM "/opt/homebrew/include")
  endif()
endif()

# 可选编译选项
option(BUILD_SAMPLE "Build sample" ON)
option(BUILD_TEST "Build test" ON)

# 添加子目录
add_subdirectory("${PROJECT_DEPENDS_DIR}/poco")
update_cached_list(Poco_LIBS Poco::Foundation Poco::Util Poco::JSON Poco::XML Poco::Net)

add_subdirectory(libraryT)

if(BUILD_SAMPLE)
    add_subdirectory(sample)
endif()

if(BUILD_TEST)
    enable_testing()
    add_subdirectory("${PROJECT_DEPENDS_DIR}/googletest")
    update_cached_list(GTest_LIBS GTest::gtest GTest::gtest_main)
    add_subdirectory(test)
endif()