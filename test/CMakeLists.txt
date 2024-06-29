file(GLOB_RECURSE CODE_FILES CONFIGURE_DEPENDS *.cpp *.c *.cc)

project(test_main)

# 编译为可执行文件
add_executable(${PROJECT_NAME} ${CODE_FILES})
target_link_libraries(${PROJECT_NAME} PRIVATE libraryT ${GTest_LIBS})

# 测试
include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})

# 安装
install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)