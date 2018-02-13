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
#ifndef itkBioCellularAggregate_h
#define itkBioCellularAggregate_h

#include "itkDefaultDynamicMeshTraits.h"
#include "itkMesh.h"
#include "itkImage.h"
#include "itkBioCell.h"
#include "itkPolygonCell.h"

#include <iostream>
#include <vector>

namespace itk
{
namespace bio
{
/** \class CellularAggregate
 * \brief Base class for different types of cellular groups,
 * including bacterial colonies and pluricellular organisms
 *
 * This class represents an aggregation of bio::Cell objects.
 *
 * \ingroup ITKBioCell
 */
template< unsigned int NSpaceDimension = 3 >
class ITK_TEMPLATE_EXPORT CellularAggregate:public CellularAggregateBase
{
public:
  /** Standard class type alias. */
  using Self = CellularAggregate;
  using Superclass = CellularAggregateBase;
  using Pointer = SmartPointer< Self >;
  using ConstPointer = SmartPointer< const Self >;

  /*** Run-time type information (and related methods). */
  itkTypeMacro(BioCellularAggregate, CellularAggregateBase);

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  static constexpr unsigned int SpaceDimension = NSpaceDimension;

  /*** Type to be used for data associated with each point in the mesh. */
  using BioCellType = Cell< NSpaceDimension >;
  using PointPixelType = BioCellType *;
  using CellPixelType = double;

  /** Mesh Traits */
  using MeshTraits = DefaultDynamicMeshTraits<
    PointPixelType,                     // PixelType
    NSpaceDimension,                    // Points Dimension
    NSpaceDimension,                    // Max.Topological Dimension
    double,                             // Type for coordinates
    double,                             // Type for interpolation
    CellPixelType                       // Type for values in the cells
    >;

  /** Mesh Traits */
  using MeshType = Mesh<  PointPixelType,
                 NSpaceDimension,
                 MeshTraits  >;

  /** Mesh Associated types */
  using MeshPointer = typename MeshType::Pointer;
  using MeshConstPointer = typename MeshType::ConstPointer;
  using PointType = typename MeshType::PointType;
  using VectorType = typename BioCellType::VectorType;

  using PointsContainer = typename MeshType::PointsContainer;
  using PointDataContainer = typename MeshType::PointDataContainer;
  using VoronoiRegionsContainer = typename MeshType::CellsContainer;
  using PointsIterator = typename PointsContainer::Iterator;
  using CellsIterator = typename PointDataContainer::Iterator;
  using VoronoiIterator = typename VoronoiRegionsContainer::Iterator;
  using PointsConstIterator = typename PointsContainer::ConstIterator;
  using CellsConstIterator = typename PointDataContainer::ConstIterator;
  using VoronoiConstIterator = typename VoronoiRegionsContainer::ConstIterator;
  using CellAutoPointer = typename MeshType::CellAutoPointer;

  /**   Voronoi region around a bio::Cell */
  using CellInterfaceType = CellInterface<
    typename MeshType::CellPixelType,
    typename MeshType::CellTraits >;

  using VoronoiRegionType = PolygonCell<  CellInterfaceType >;
  using VoronoiRegionAutoPointer = typename VoronoiRegionType::SelfAutoPointer;

  /** Convenient type alias. */
  using ImagePixelType = float;
  using SubstrateType = Image< ImagePixelType, NSpaceDimension >;
  using SubstratePointer = typename SubstrateType::Pointer;
  using SubstrateValueType = ImagePixelType;
  using SubstratesVector = std::vector< SubstratePointer >;

public:
  unsigned int GetNumberOfCells() const;

  static unsigned int GetDimension() { return SpaceDimension; }

  void SetGrowthRadiusLimit(double value);

  void SetGrowthRadiusIncrement(double value);

  itkGetModifiableObjectMacro(Mesh, MeshType);

  virtual void AdvanceTimeStep();

  virtual void SetEgg(BioCellType *cell, const PointType & position);

  virtual void Add(CellBase *cell);

  virtual void Add(CellBase *cell, const VectorType & perturbation);

  void Add(CellBase *cellA, CellBase *cellB, double perturbationLength) override;

  void Remove(CellBase *cell) override;

  virtual void GetVoronoi(IdentifierType cellId, VoronoiRegionAutoPointer &) const;

  void DumpContent(std::ostream & os) const;

  virtual void AddSubstrate(SubstrateType *substrate);

  virtual SubstratesVector & GetSubstrates();

  SubstrateValueType GetSubstrateValue(IdentifierType cellId,
                                               unsigned int substrateId) const override;

  virtual void KillAll();

protected:
  CellularAggregate();
  ~CellularAggregate() override;
  CellularAggregate(const Self &);
  void operator=(const Self &);

  void PrintSelf(std::ostream & os, Indent indent) const override;

  virtual void ComputeForces();

  virtual void UpdatePositions();

  virtual void ComputeClosestPoints();

  virtual void ClearForces();

private:

  MeshPointer      m_Mesh;
  SubstratesVector m_Substrates;
  double           m_FrictionForce;
  SizeValueType    m_Iteration;
  SizeValueType    m_ClosestPointComputationInterval;
};
} // end namespace bio
} // end namespace itk

#ifndef ITK_MANUAL_INSTANTIATION
#include "itkBioCellularAggregate.hxx"
#endif

#endif
