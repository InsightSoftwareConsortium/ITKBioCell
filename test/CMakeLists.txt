itk_module_test()
set(BioCellTests
itkBioCellTest.cxx
itkBioGenomeTest.cxx
itkBioCellularAggregateTest.cxx
itkBioGeneNetworkTest.cxx
itkBioGeneTest.cxx
)

CreateTestDriver(BioCell  "${BioCell-Test_LIBRARIES}" "${BioCellTests}")

itk_add_test(NAME itkBioCellTest
      COMMAND BioCellTestDriver itkBioCellTest 1.0 1.0 0.1 2.0 1.0 1.0 10 10 30 150 255 220)
itk_add_test(NAME itkBioGenomeTest
      COMMAND BioCellTestDriver itkBioGenomeTest)
itk_add_test(NAME itkBioCellularAggregateTest
      COMMAND BioCellTestDriver itkBioCellularAggregateTest)
itk_add_test(NAME itkBioGeneNetworkTest
      COMMAND BioCellTestDriver itkBioGeneNetworkTest)
itk_add_test(NAME itkBioGeneTest
      COMMAND BioCellTestDriver itkBioGeneTest)
