function (add_doxygen_doc)
  find_package(Doxygen)
  if (DOXYGEN_FOUND)
    set(options)
    set(oneValueArgs BUILD_DIR DOXY_FILE TARGET_NAME COMMENT)
    set(multiValueArgs)
    cmake_parse_arguments(DOXY_DOC "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})
    configure_file(${DOXY_DOC_DOXY_FILE} ${DOXY_DOC_BUILD_DIR}/Doxyfile @ONLY)
    set(Doxyfile_Path "${DOXY_DOC_BUILD_DIR}/Doxyfile")
    message("-- Doxyfile_Path: ${Doxyfile_Path}")
    add_custom_target(
      ${DOXY_DOC_TARGET_NAME} ALL
      COMMAND ${DOXYGEN_EXECUTABLE} ${Doxyfile_Path}
      WORKING_DIRECTORY ${DOXY_DOC_BUILD_DIR}
      COMMENT "Building ${DOXY_DOC_COMMENT} with Doxygen"
      VERBATIM)
    install(DIRECTORY ${DOXY_DOC_BUILD_DIR}/doc DESTINATION share)
    message(STATUS "Added ${DOXY_DOC_TARGET_NAME} [Doxygen] target to build documentation")
  else ()
    message("Doxygen need to be installed to generate the doxygen documentation")
  endif ()
endfunction ()
