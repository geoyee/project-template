file(GLOB_RECURSE CODE_FILES CONFIGURE_DEPENDS *.cpp *.c *.cc)

project(sample)

# 编译为可执行文件
add_executable(${PROJECT_NAME} ${CODE_FILES})
target_link_libraries(${PROJECT_NAME} PRIVATE libraryT)

# 安装
install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)