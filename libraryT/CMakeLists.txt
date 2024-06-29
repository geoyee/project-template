file(GLOB_RECURSE CODE_FILES CONFIGURE_DEPENDS src/*.cpp src/*.c src/*.cc include/*.h include/*.hpp)

project(libraryT)

# 编译为动态库
add_library(${PROJECT_NAME} SHARED ${CODE_FILES})
target_include_directories(${PROJECT_NAME} PUBLIC include)
# target_link_libraries(${PROJECT_NAME} PUBLIC <other_libraries>)

# 安装
install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)
install(DIRECTORY include/ DESTINATION include)