file(GLOB SOURCES_TEST ${CMAKE_CURRENT_SOURCE_DIR}/*.cc)

# include_directories(${GTEST_INCLUDE_DIRS})

message("Library: ${BASE_IMG_LIB}/lib/libmo815-3dvis.a")

foreach(local_file ${SOURCES_TEST})
  get_filename_component(local_filename ${local_file} NAME_WE)
  message("Compiling: ${local_file} ${SOURCES} ${TBB_LIBRARIES} ${GTEST_MAIN_LIBRARIES} ${GTEST_LIBRARIES}")
  add_executable(${local_filename} ${local_file} ${SOURCES})
#   cxx_test(${local_filename} ${local_file} ${GTEST_MAIN_LIBRARIES} ${GTEST_LIBRARIES})

  target_link_libraries(${local_filename} volimg)
endforeach()
