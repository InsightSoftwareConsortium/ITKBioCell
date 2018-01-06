set(BioCell_SRCS
  itkBioGenome.cxx
  itkBioGene.cxx
  itkBioGeneNetwork.cxx
  itkBioCellBase.cxx
  itkBioCellularAggregateBase.cxx
  )

itk_module_add_library(BioCell ${BioCell_SRCS})
