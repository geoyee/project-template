# ------------------------------------------------------------------------

function(update_cached name value)
    set("${name}" "${value}" CACHE INTERNAL "*** Internal ***" FORCE)
endfunction()

function(update_cached_list name)
    set(_tmp_list "${${name}}")
    list(APPEND _tmp_list "${ARGN}")
    list(REMOVE_DUPLICATES _tmp_list)
    update_cached(${name} "${_tmp_list}")
endfunction()

# ------------------------------------------------------------------------

function(set_work_dirs_force bin_dir)
    list(APPEND CMAKE_BUILD_TYPE_LIST "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
    foreach(BUILD_TYPE_CONFIG ${CMAKE_BUILD_TYPE_LIST})
        string(TOUPPER ${BUILD_TYPE_CONFIG} BUILD_TYPE_CONFIG_UP)
        set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${BUILD_TYPE_CONFIG_UP} "${bin_dir}/lib/${CMAKE_BUILD_TYPE}" CACHE PATH "" FORCE)
        set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${BUILD_TYPE_CONFIG_UP} "${bin_dir}/lib/${CMAKE_BUILD_TYPE}" CACHE PATH "" FORCE)
        set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${BUILD_TYPE_CONFIG_UP} "${bin_dir}/bin/${CMAKE_BUILD_TYPE}" CACHE PATH "" FORCE)
        set(CMAKE_PDB_OUTPUT_DIRECTORY_${BUILD_TYPE_CONFIG_UP} "${bin_dir}/bin/${CMAKE_BUILD_TYPE}" CACHE PATH "" FORCE)
    endforeach()
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${bin_dir}/lib" CACHE PATH "Output directory for libraries" FORCE)
    message(STATUS "CMAKE_LIBRARY_OUTPUT_DIRECTORY: ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${bin_dir}/lib" CACHE PATH "Output directory for static libraries" FORCE)
    message(STATUS "CMAKE_ARCHIVE_OUTPUT_DIRECTORY: ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${bin_dir}/bin" CACHE PATH "Output directory for executables" FORCE)
    message(STATUS "CMAKE_RUNTIME_OUTPUT_DIRECTORY: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
    set(CMAKE_PDB_OUTPUT_DIRECTORY "${bin_dir}/bin" CACHE PATH "Output directory for PDB files" FORCE)
    message(STATUS "CMAKE_PDB_OUTPUT_DIRECTORY: ${CMAKE_PDB_OUTPUT_DIRECTORY}")
    set(CMAKE_INSTALL_PREFIX "${bin_dir}/install/${CMAKE_BUILD_TYPE}" CACHE PATH "Global install directory" FORCE)
    message(STATUS "CMAKE_INSTALL_PREFIX: ${CMAKE_INSTALL_PREFIX}")
endfunction()

# ------------------------------------------------------------------------