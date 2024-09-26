cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

# C/C++配置
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(LINK_WHAT_YOU_USE ON)

# 设置CMake策略
if (POLICY CMP0078)
  cmake_policy(SET CMP0078 NEW)
endif ()
if (POLICY CMP0086)
  cmake_policy(SET CMP0086 NEW)
endif ()

# 项目
project(project-template LANGUAGES C CXX)

# 防止在源码目录下进行内部构建
if (PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
  message(FATAL_ERROR "Please create a build directory and run CMake from there")
endif ()

# 编译类型
if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif ()
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
if (CCACHE_FOUND)
  set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
  set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache)
endif ()

# 编译器选项
if (MSVC)
  add_compile_options($<$<CXX_COMPILER_ID:MSVC>:/utf-8>)
  add_compile_options($<$<CXX_COMPILER_ID:MSVC>:/W4$<SEMICOLON>/WX>)
  add_compile_options($<$<CXX_COMPILER_ID:MSVC>:/wd4566$<SEMICOLON>/wd4819>)
  add_compile_options($<$<CXX_COMPILER_ID:MSVC>:/EHsc>)
  # list(APPEND COMPILE_OPTIONS_DEFAULT "/nologo") list(APPEND CMAKE_STATIC_LINKER_FLAGS "/nologo")
else ()
  add_compile_options($<$<CXX_COMPILER_ID:GNU,Clang>:-fPIC>)
  add_compile_options($<$<CXX_COMPILER_ID:GNU,Clang>:-Wall$<SEMICOLON>-Wextra>)
  # add_compile_options($<$<CXX_COMPILER_ID:GNU,Clang>:-Werror>)
  add_compile_options($<$<CXX_COMPILER_ID:GNU,Clang>:-Wno-unknown-pragmas>)
  # add_compile_options($<$<CXX_COMPILER_ID:GNU,Clang>:-Werror=uninitialized$<SEMICOLON>-Werror=return-type$<SEMICOLON>-Wconversion$<SEMICOLON>-Wsign-compare$<SEMICOLON>-Werror=unused-result$<SEMICOLON>-Werror=suggest-override$<SEMICOLON>-Wzero-as-null-pointer-constant$<SEMICOLON>-Wmissing-declarations$<SEMICOLON>-Wold-style-cast$<SEMICOLON>-Wnon-virtual-dtor>)
  add_link_options($<$<CXX_COMPILER_ID:GNU,Clang>:-flto>)
  if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_options(-g3)
  else ()
    add_compile_options(-g0)
  endif ()
endif ()

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU"
    AND CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL 10.0.0
    AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS 11.0.0)
  add_compile_options(
    $<$<COMPILE_LANG_AND_ID:CXX,GNU>:-Wno-error$<SEMICOLON>-fcoroutines$<SEMICOLON>-D__cplusplus=202002L>)
  if (IS_DIRECTORY /usr/include/c++/10)
    include_directories($<$<COMPILE_LANG_AND_ID:CXX,GNU>:/usr/include/c++/10>)
  endif ()
endif ()

# 可选编译内容
option(BUILD_SAMPLE "Build sample" ON)
option(BUILD_TEST "Build test" ON)
option(BUILD_OLANGS "Build other languages" ON)
option(BUILD_DOC "Build doc" ON)

# 添加第三方库
add_definitions(-DDBG_MACRO_NO_WARNING)
if (CMAKE_BUILD_TYPE STREQUAL "Release")
  add_definitions(-DDBG_MACRO_DISABLE)
endif ()
add_subdirectory("${PROJECT_DEPENDS_DIR}/dbg-macro")
update_cached_list(DBG_LIBS dbg_macro)

add_definitions(-D_USE_MATH_DEFINES)

# 添加子目录
add_subdirectory(libraryT)
set(LIBRARYT_HEADER_DIR "${PROJECT_ROOT_DIR}/libraryT/include")

# 是否编译生成示例
if (BUILD_SAMPLE)
  add_subdirectory(sample)
endif ()

# 是否编译生成测试
if (BUILD_TEST)
  enable_testing()
  set(BUILD_GMOCK
      OFF
      CACHE BOOL "Build googletest's own googletest subproject." FORCE)
  if (MSVC)
    set(gtest_force_shared_crt
        ON
        CACHE BOOL "Prevent overriding the parent project's compiler/linker settings" FORCE)
  endif ()
  add_subdirectory("${PROJECT_DEPENDS_DIR}/googletest")
  update_cached_list(GTest_LIBS GTest::gtest)
  add_subdirectory(test)
endif ()

# 是否编译生成其他语言的接口
if (BUILD_OLANGS)
  add_subdirectory(swig)
endif ()

# 是否编译生成C/C++文档
if (BUILD_DOC)
  include(UseDoxygenDoc)

  add_doxygen_doc(
    BUILD_DIR
    ${CMAKE_CURRENT_BINARY_DIR}/docs
    DOXY_FILE
    ${PROJECT_ROOT_DIR}/Doxyfile.in
    TARGET_NAME
    docs
    COMMENT
    "HTML documentation")
endif ()
