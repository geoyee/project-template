cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

# C/C++配置
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(LINK_WHAT_YOU_USE ON)

# 设置CMake策略
if(POLICY CMP0048)
    cmake_policy(SET CMP0048 NEW)
endif()
if(POLICY CMP0069)
    cmake_policy(SET CMP0069 NEW)
endif ()
if(POLICY CMP0077)
    cmake_policy(SET CMP0077 NEW)
endif()
if(POLICY CMP0091)
    cmake_policy(SET CMP0091 NEW)
endif()

# 项目
project(project-template LANGUAGES C CXX)

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

# 编译器选项
if(MSVC)
    add_compile_options($<$<CXX_COMPILER_ID:MSVC>:/utf-8>)
    add_compile_options($<$<CXX_COMPILER_ID:MSVC>:/W4$<SEMICOLON>/WX>)
    add_compile_options($<$<CXX_COMPILER_ID:MSVC>:/wd4566$<SEMICOLON>/wd4819>)
    add_compile_options($<$<CXX_COMPILER_ID:MSVC>:/EHsc>)
    # list(APPEND COMPILE_OPTIONS_DEFAULT "/nologo")
    # list(APPEND CMAKE_STATIC_LINKER_FLAGS "/nologo")
else()
    add_compile_options($<$<CXX_COMPILER_ID:GNU,Clang>:-fPIC>)
    add_compile_options($<$<CXX_COMPILER_ID:GNU,Clang>:
        -Wall$<SEMICOLON>-Wextra$<SEMICOLON>-Wno-interference-size$<SEMICOLON>
        -Werror=return-type$<SEMICOLON>-Werror=unused-result$<SEMICOLON>
        -Werror=uninitialized$<SEMICOLON>-Werror=maybe-uninitialized$<SEMICOLON>
        -Wno-unused-parameter$<SEMICOLON>-Wunused-but-set-variable$<SEMICOLON>
        -Wunused-but-set-parameter$<SEMICOLON>-Wunused-function$<SEMICOLON>
        -Wunused-const-variable$<SEMICOLON>-Werror=use-after-free=3$<SEMICOLON>
        -Werror=invalid-memory-model$<SEMICOLON>-Wunused-value$<SEMICOLON>-Wexceptions$<SEMICOLON>
        -Werror=missing-declarations$<SEMICOLON>-Werror=missing-field-initializers$<SEMICOLON>
        -Wparentheses$<SEMICOLON>-Wconversion$<SEMICOLON>-Wsign-conversion$<SEMICOLON>
        -Wsign-compare$<SEMICOLON>-Wno-terminate$<SEMICOLON>-Werror=delete-non-virtual-dtor$<SEMICOLON>
        -Werror=suggest-override$<SEMICOLON>-Wsign-promo$<SEMICOLON>-Wold-style-cast$<SEMICOLON>
        -Wrange-loop-construct$<SEMICOLON>-Werror=reorder$<SEMICOLON>-Werror=class-memaccess$<SEMICOLON>
        -Werror=narrowing$<SEMICOLON>-Wenum-conversion$<SEMICOLON>
        -Wdeprecated-enum-enum-conversion$<SEMICOLON>-Werror=deprecated-copy-dtor$<SEMICOLON>
        -Werror=deprecated-copy$<SEMICOLON>-Wzero-as-null-pointer-constant$<SEMICOLON>
        -Wplacement-new=2$<SEMICOLON>-Wsuggest-final-types$<SEMICOLON>-Wsuggest-final-methods$<SEMICOLON>
        -Werror=conversion-null$<SEMICOLON>-Werror=mismatched-new-delete$<SEMICOLON>
        -Werror=address$<SEMICOLON>-Wlogical-op$<SEMICOLON>-Wlogical-not-parentheses$<SEMICOLON>
        -Wattributes$<SEMICOLON>-Wmissing-declarations$<SEMICOLON>-Werror=multichar$<SEMICOLON>
        -Werror=overflow$<SEMICOLON>-Werror=restrict$<SEMICOLON>-Werror=vla$<SEMICOLON>
        -Werror=strict-aliasing=1$<SEMICOLON>-Werror=string-compare$<SEMICOLON>
        -Werror=stringop-overflow=2$<SEMICOLON>-Wsuggest-attribute=const$<SEMICOLON>
        -Wsuggest-attribute=pure$<SEMICOLON>-Wsuggest-attribute=noreturn$<SEMICOLON>
        -Werror=alloca$<SEMICOLON>-Werror=array-bounds$<SEMICOLON>-Werror=bool-compare$<SEMICOLON>
        -Werror=bool-operation$<SEMICOLON>-Werror=zero-length-bounds$<SEMICOLON>
        -Werror=div-by-zero$<SEMICOLON>-Wno-shadow$<SEMICOLON>-Werror=format$<SEMICOLON>
        -Werror=pointer-arith$<SEMICOLON>-Werror=write-strings$<SEMICOLON>
        -Werror=dangling-pointer=2$<SEMICOLON>-Wempty-body$<SEMICOLON>-Wno-unknown-warning-option>)
    add_compile_options($<$<CXX_COMPILER_ID:GNU,Clang>:-Werror>)
    add_link_options($<$<CXX_COMPILER_ID:GNU,Clang>:-flto>)
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        add_compile_options(-g3)
    else()
        add_compile_options(-g0)
    endif()
endif()

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU" AND 
    CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL 10.0.0 AND 
    CMAKE_CXX_COMPILER_VERSION VERSION_LESS 11.0.0)
    add_compile_options(
        $<$<COMPILE_LANG_AND_ID:CXX,GNU>:-Wno-error$<SEMICOLON>
        -fcoroutines$<SEMICOLON>-D__cplusplus=202002L>)
    if (IS_DIRECTORY /usr/include/c++/10)
        include_directories($<$<COMPILE_LANG_AND_ID:CXX,GNU>:/usr/include/c++/10>)
    endif()
endif()

# 可选编译内容
option(BUILD_SAMPLE "Build sample" ON)
option(BUILD_TEST "Build test" ON)

# 添加子目录
add_subdirectory(libraryT)

if(BUILD_SAMPLE)
    add_subdirectory(sample)
endif()

if(BUILD_TEST)
    enable_testing()
    set(BUILD_GMOCK OFF CACHE BOOL "Build googletest's own googletest subproject." FORCE)
    if(MSVC)
        set(gtest_force_shared_crt ON CACHE BOOL "Prevent overriding the parent project's compiler/linker settings" FORCE)
    endif()
    add_subdirectory("${PROJECT_DEPENDS_DIR}/googletest")
    update_cached_list(GTest_LIBS GTest::gtest)
    add_subdirectory(test)
endif()