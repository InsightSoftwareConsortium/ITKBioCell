/*=========================================================================
 *
 *  Copyright Insight Software Consortium
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/

#include <iostream>

#include "itkBioCell.h"
#include "itkTestingMacros.h"


/**
 *  This test exercises the functionality of the itk::bio::Cell class.
 *
 *
 */

template< unsigned int NSpaceDimension >
class BioCellHelper : public itk::bio::Cell< NSpaceDimension >
{

public:

  using Self = BioCellHelper;
  using Superclass = itk::bio::Cell<NSpaceDimension>;
  using Pointer = itk::SmartPointer<Self>;
  using ConstPointer = itk::SmartPointer<const Self>;

  using VectorType = typename itk::bio::Cell< NSpaceDimension >::VectorType;


  static int Exercise(VectorType forceVector,
    double itkNotUsed(radius),
    double defaultRadius,
    double growthRadiusIncrement,
    double growthRadiusLimit,
    double nutrientSelfRepairLevel,
    double energySelfRepairLevel,
    itk::SizeValueType growthMaximumLatencyTime,
    itk::SizeValueType divisionMaximumLatencyTime,
    itk::SizeValueType maximumGenerationLimit,
    double chemoAttractantLowThreshold,
    double chemoAttractantHighThreshold,
    double itkNotUsed(chemoAttractantLevel))
  {
    std::cout << "Testing " << NSpaceDimension << "D..." << std::endl;


    using CellType = itk::bio::Cell<NSpaceDimension>;

    CellType * egg = CellType::CreateEgg();

    // Test Set/Get methods
    //CellType::SetRadius( radius );
    //ITK_TEST_SET_GET_VALUE(radius, egg->GetRadius());
    egg->GetRadius();

    CellType::SetDefaultRadius( defaultRadius );
    //ITK_TEST_SET_GET_VALUE(defaultRadius, egg->GetDefaultRadius());

    CellType::SetGrowthRadiusIncrement( growthRadiusIncrement );
    //ITK_TEST_SET_GET_VALUE(growthRadiusIncrement, egg->GetGrowthRadiusIncrement());

    CellType::SetGrowthRadiusLimit( growthRadiusLimit );
    ITK_TEST_SET_GET_VALUE(growthRadiusLimit, egg->GetGrowthRadiusLimit());

    CellType::SetNutrientSelfRepairLevel( nutrientSelfRepairLevel );
    /*ITK_TEST_SET_GET_VALUE(nutrientSelfRepairLevel,
      egg->GetNutrientSelfRepairLevel());*/

    CellType::SetEnergySelfRepairLevel( energySelfRepairLevel );
    //ITK_TEST_SET_GET_VALUE(energySelfRepairLevel, egg->GetEnergySelfRepairLevel());

    CellType::SetGrowthMaximumLatencyTime( growthMaximumLatencyTime );
    ITK_TEST_SET_GET_VALUE(growthMaximumLatencyTime,
      egg->GetGrowthMaximumLatencyTime());

    CellType::SetDivisionMaximumLatencyTime( divisionMaximumLatencyTime );
    ITK_TEST_SET_GET_VALUE(divisionMaximumLatencyTime,
      egg->GetDivisionMaximumLatencyTime());

    CellType::SetMaximumGenerationLimit( maximumGenerationLimit );
    /*ITK_TEST_SET_GET_VALUE(maximumGenerationLimit,
      egg->GetMaximumGenerationLimit());*/

    CellType::SetChemoAttractantLowThreshold( chemoAttractantLowThreshold );
    /*ITK_TEST_SET_GET_VALUE(chemoAttractantLowThreshold,
      egg->GetChemoAttractantLowThreshold());*/

    CellType::SetChemoAttractantHighThreshold( chemoAttractantHighThreshold );
    /*ITK_TEST_SET_GET_VALUE(chemoAttractantHighThreshold,
      egg->GetChemoAttractantHighThreshold());*/

    //CellType::SetChemoAttractantLevel( chemoAttractantLevel );
    //ITK_TEST_SET_GET_VALUE(chemoAttractantLevel, egg->GetChemoAttractantLevel());

    egg->ClearForce();
    egg->AddForce(forceVector);

    typename CellType::VectorType forceVector2 = egg->GetForce();

    ITK_TEST_EXPECT_EQUAL(forceVector, forceVector2);

    egg->GetSelfIdentifier();
    egg->GetParentIdentifier();
    egg->GetColor();

    // Create a cellular aggregate base
    itk::bio::CellularAggregateBase::Pointer cell =
      itk::bio::CellularAggregateBase::New();
    cell->Clone();

    egg->SetCellularAggregate(cell);

    ITK_TEST_SET_GET_VALUE(cell, egg->GetCellularAggregate());

    // Complete the cell life cycle
    //while(egg->CheckPointApoptosis())
    egg->AdvanceTimeStep();

    delete egg;

    std::cout << "Test succeeded." << std::endl;
    return EXIT_SUCCESS;

  }

};


int itkBioCellTest( int argc, char * argv[] )
{

  if ( argc < 13 )
    {
    std::cout << "Usage: " << argv[0]
      << " Radius"
      << " DefaultRadius"
      << " GrowthRadiusIncrement"
      << " GrowthRadiusLimit"
      << " NutrientSelfRepairLevel"
      << " EnergySelfRepairLevel"
      << " GrowthMaximumLatencyTime"
      << " DivisionMaximumLatencyTime"
      << " MaximumGenerationLimit"
      << " ChemoAttractantLowThreshold"
      << " ChemoAttractantHighThreshold"
      << " ChemoAttractantLevel"
      << std::endl;
    return EXIT_FAILURE;
    }

  double radius = atof(argv[1]);
  double defaultRadius = atof(argv[2]);
  double growthRadiusIncrement = atof(argv[3]);
  double growthRadiusLimit = atof(argv[4]);
  double nutrientSelfRepairLevel = atof(argv[5]);
  double energySelfRepairLevel = atof(argv[6]);
  itk::SizeValueType growthMaximumLatencyTime = atoi(argv[7]);
  itk::SizeValueType divisionMaximumLatencyTime = atoi(argv[8]);
  itk::SizeValueType maximumGenerationLimit = atoi(argv[9]);
  double chemoAttractantLowThreshold = atof(argv[10]);
  double chemoAttractantHighThreshold = atof(argv[11]);
  double chemoAttractantLevel = atof(argv[12]);

  constexpr unsigned int dimension2D = 2;
  constexpr unsigned int dimension3D = 3;
  constexpr unsigned int dimension4D = 4;

  // Test for 2D
  BioCellHelper<dimension2D>::VectorType forceVector2D;
  forceVector2D[0] = 10.5;
  forceVector2D[1] = 20.5;

  BioCellHelper<dimension2D>::Exercise(forceVector2D,
    radius,
    defaultRadius,
    growthRadiusIncrement,
    growthRadiusLimit,
    nutrientSelfRepairLevel,
    energySelfRepairLevel,
    growthMaximumLatencyTime,
    divisionMaximumLatencyTime,
    maximumGenerationLimit,
    chemoAttractantLowThreshold,
    chemoAttractantHighThreshold,
    chemoAttractantLevel);

  // Test for 3D
  BioCellHelper<dimension3D>::VectorType forceVector3D;
  forceVector3D[0] = 10.5;
  forceVector3D[1] = 20.5;
  forceVector3D[2] = 30.5;

  BioCellHelper<dimension3D>::Exercise(forceVector3D,
    radius,
    defaultRadius,
    growthRadiusIncrement,
    growthRadiusLimit,
    nutrientSelfRepairLevel,
    energySelfRepairLevel,
    growthMaximumLatencyTime,
    divisionMaximumLatencyTime,
    maximumGenerationLimit,
    chemoAttractantLowThreshold,
    chemoAttractantHighThreshold,
    chemoAttractantLevel);

  // Test for 4D
  BioCellHelper<dimension4D>::VectorType forceVector4D;
  forceVector4D[0] = 10.5;
  forceVector4D[1] = 20.5;
  forceVector4D[2] = 30.5;
  forceVector4D[3] = 15.5;

  BioCellHelper<dimension4D>::Exercise(forceVector4D,
    radius,
    defaultRadius,
    growthRadiusIncrement,
    growthRadiusLimit,
    nutrientSelfRepairLevel,
    energySelfRepairLevel,
    growthMaximumLatencyTime,
    divisionMaximumLatencyTime,
    maximumGenerationLimit,
    chemoAttractantLowThreshold,
    chemoAttractantHighThreshold,
    chemoAttractantLevel);

  return EXIT_SUCCESS;
}
