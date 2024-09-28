file(
  GLOB_RECURSE
  CODE_FILES
  CONFIGURE_DEPENDS
  src/*.cpp
  src/*.c
  src/*.cc
  include/*.h
  include/*.hpp
  include/*/*.h
  include/*/*.hpp)

project(libraryT)

# 编译为动态库
add_library(${PROJECT_NAME} SHARED ${CODE_FILES})
target_include_directories(${PROJECT_NAME} PUBLIC include)
target_link_libraries(${PROJECT_NAME} PUBLIC ${DBG_LIBS} ${SPDLOG_LIBS})

set(PROJ_LIB_NAME
    ${PROJECT_NAME}
    CACHE STRING "library name")

# 安装
install(TARGETS ${PROJECT_NAME} LIBRARY DESTINATION ${SHARED_BIN_DIR})
install(DIRECTORY include/ DESTINATION include)
