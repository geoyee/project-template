file(GLOB_RECURSE CODE_FILES CONFIGURE_DEPENDS *.i)

project("jv${PROJ_LIB_NAME}")

find_package(JNI REQUIRED)
find_package(Java REQUIRED)

if (JNI_FOUND AND Java_FOUND)
  include(${SWIG_USE_FILE})
  include_directories(${JNI_INCLUDE_DIRS})
  include_directories(${LIBRARYT_HEADER_DIR})

  # SWIG编译选项
  set(CMAKE_INCLUDE_CURRENT_DIR ON)
  set_property(SOURCE ${CODE_FILES} PROPERTY CPLUSPLUS ON)
  set(CMAKE_SWIG_OUTDIR "${PROJECT_BINARY_DIR}/${PROJ_LIB_NAME}/scripts")
  set(SWIG_OUTFILE_DIR "${PROJECT_BINARY_DIR}/cpp")
  set(JAVADOC_OUTPUT_DIR "${PROJECT_BINARY_DIR}/javadoc")
  set(CMAKE_SWIG_FLAGS -package "${PROJ_LIB_NAME}.scripts")

  # 编译链接
  swig_add_library(
    ${PROJECT_NAME}
    TYPE MODULE
    LANGUAGE java
    SOURCES ${CODE_FILES})
  swig_link_libraries(${PROJECT_NAME} ${PROJ_LIB_NAME})
  # 文档导出
  set_property(TARGET ${PROJECT_NAME} PROPERTY SWIG_COMPILE_OPTIONS -doxygen)

  # 打包为jar包
  add_custom_command(
    TARGET ${PROJECT_NAME}
    WORKING_DIRECTORY "${PROJECT_BINARY_DIR}"
    POST_BUILD
    COMMAND "${Java_JAVADOC_EXECUTABLE}" -encoding UTF-8 -d "${JAVADOC_OUTPUT_DIR}" "${PROJ_LIB_NAME}/scripts/*.java"
    COMMAND "${Java_JAVAC_EXECUTABLE}" -encoding UTF-8 "${PROJ_LIB_NAME}/scripts/*.java"
    COMMAND "${Java_JAR_EXECUTABLE}" cf "${PROJ_LIB_NAME}.jar" "${PROJ_LIB_NAME}/scripts/*.class"
    COMMENT "Compile and package Java classes")
  set("${PROJ_LIB_NAME}_FILES" $<TARGET_FILE:"${SWIG_MODULE_${PROJECT_NAME}_REAL_NAME}">)

  # 安装
  set(PROJ_JAR_PAHT "${PROJECT_BINARY_DIR}/${PROJ_LIB_NAME}.jar")
  install(FILES "${PROJ_JAR_PAHT}" DESTINATION bin)
  install(DIRECTORY "${JAVADOC_OUTPUT_DIR}" DESTINATION share)
  install(TARGETS ${PROJECT_NAME} LIBRARY DESTINATION "${SHARED_BIN_DIR}")
else ()
  message(WARNING "JNI or Java not found")
endif ()
