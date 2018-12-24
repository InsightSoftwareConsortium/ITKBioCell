cmake_minimum_required(VERSION 3.10.2)

project(BioCell_Examples CXX)

find_package(ITK REQUIRED
  COMPONENTS
    BioCell
    ITKSmoothing
    ITKIOImageBase
    ITKIONRRD
    )
include(${ITK_USE_FILE})

add_executable(CellularSegmentation1 CellularSegmentation1.cxx )
target_link_libraries(CellularSegmentation1 ${ITK_LIBRARIES})

add_executable(CellularSegmentation2 CellularSegmentation2.cxx )
target_link_libraries(CellularSegmentation2 ${ITK_LIBRARIES})


enable_testing()
find_path(INPUT_DATA_DIR
  NAMES BrainProtonDensitySlice.png
  HINTS ${ITK_SOURCE_DIR}/Examples/Data
  )
set(TEST_OUTPUT_DIR ${BioCell_Examples_BINARY_DIR}/Testing/Temporary)

if(INPUT_DATA_DIR)
  add_test(NAME CellularSegmentation1Test
    COMMAND CellularSegmentation1
        ${INPUT_DATA_DIR}/BrainProtonDensitySlice.png
        100 115 200 255 3000
        ${TEST_OUTPUT_DIR}/CellularSegmentation1Test.vtk
    )
  add_test(NAME CellularSegmentation2Test
    COMMAND CellularSegmentation2
        ${INPUT_DATA_DIR}/BrainWeb/brainweb1e1a10f20.mha}
        81 113 96 220 255 2000
        ${TEST_OUTPUT_DIR}/CellularSegmentation2Test.vtk
    )
endif()
