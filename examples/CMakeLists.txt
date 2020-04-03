cmake_minimum_required(VERSION 3.10.2)

project(BioCell_Examples CXX)

find_package(ITK REQUIRED
  COMPONENTS
    BioCell
    ITKSmoothing
    ITKIOImageBase
    ITKIOPNG
    ITKIOMeta
    )
include(${ITK_USE_FILE})

add_executable(CellularSegmentation1 CellularSegmentation1.cxx )
target_link_libraries(CellularSegmentation1 ${ITK_LIBRARIES})

add_executable(CellularSegmentation2 CellularSegmentation2.cxx )
target_link_libraries(CellularSegmentation2 ${ITK_LIBRARIES})


enable_testing()
set(INPUT_DIR ${BioCell_SOURCE_DIR}/examples/Data)
set(TEST_OUTPUT_DIR ${BioCell_BINARY_DIR}/Testing/Temporary)


add_test(NAME CellularSegmentation1Test
  COMMAND CellularSegmentation1
      ${INPUT_DIR}/BrainProtonDensitySlice.png
      100 115 200 255 3000
      ${TEST_OUTPUT_DIR}/CellularSegmentation1Test.vtk
  )

add_test(NAME CellularSegmentation2Test
  COMMAND CellularSegmentation2
      ${INPUT_DIR}/brainweb1e1a10f20.mha
      81 113 96 220 255 2000
      ${TEST_OUTPUT_DIR}/CellularSegmentation2Test.vtk
  )
