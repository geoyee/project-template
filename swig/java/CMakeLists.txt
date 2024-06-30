file(GLOB_RECURSE CODE_FILES CONFIGURE_DEPENDS *.i)

project("jv_${PROJ_LIB_NAME}")

find_package(JNI REQUIRED)
find_package(Java REQUIRED)

if(JNI_FOUND AND Java_FOUND)
    include(${SWIG_USE_FILE})
    include_directories(${JNI_INCLUDE_DIRS})
    include_directories(${LIBRARYT_HEADER_DIR})

    set(CMAKE_INCLUDE_CURRENT_DIR ON)
    set_property(SOURCE ${CODE_FILES} PROPERTY CPLUSPLUS ON)
    set(CMAKE_SWIG_OUTDIR "${CMAKE_CURRENT_BINARY_DIR}/${PROJ_LIB_NAME}/scripts")
    set(SWIG_OUTFILE_DIR "${CMAKE_CURRENT_BINARY_DIR}/cpp")
    set(CMAKE_SWIG_FLAGS -package "${PROJ_LIB_NAME}.scripts")

    swig_add_library(${PROJECT_NAME} TYPE MODULE LANGUAGE java SOURCES ${CODE_FILES})
    swig_link_libraries(${PROJECT_NAME} ${PROJ_LIB_NAME})

    add_custom_command(TARGET ${PROJECT_NAME}
        WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
        POST_BUILD
        COMMAND "${Java_JAVAC_EXECUTABLE}" "${PROJ_LIB_NAME}/scripts/*.java"
        COMMAND "${Java_JAR_EXECUTABLE}" cf "${PROJ_LIB_NAME}.jar" "${PROJ_LIB_NAME}/scripts/*.class"
        COMMENT "Compile and package Java classes"
    )
    set("${PROJ_LIB_NAME}_FILES" $<TARGET_FILE:"${SWIG_MODULE_${PROJECT_NAME}_REAL_NAME}">)
else()
    message(WARNING "JNI or Java not found")
endif()