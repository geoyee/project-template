option(BUILD_JAVA "Build Java" ON)

find_package(SWIG REQUIRED)
if (NOT SWIG_FOUND)
  message(WARNING "SWIG not found")
  set(BUILD_OLANGS OFF)
endif ()

if (BUILD_OLANGS AND BUILD_JAVA)
  add_subdirectory(java)
endif ()
