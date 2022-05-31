/*=========================================================================
 *
 *  Copyright NumFOCUS
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         https://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/

#ifndef itkBioCellularAggregateBase_h
#define itkBioCellularAggregateBase_h

#include "itkIntTypes.h"
#include "itkObject.h"
#include "itkObjectFactory.h"
#include "BioCellExport.h"

namespace itk
{
namespace bio
{
// Forward reference because of circular dependencies
class ITK_FORWARD_EXPORT CellBase;

/** \class CellularAggregateBase
 * \brief Base class for the CellularAggregates.
 *
 * This base class is not templated over the space dimension.
 *
 * \ingroup ITKBioCell
 */
class BioCell_EXPORT CellularAggregateBase : public Object
{
public:
  ITK_DISALLOW_COPY_AND_MOVE(CellularAggregateBase);

  /** Standard class type alias. */
  using Self = CellularAggregateBase;
  using Superclass = Object;
  using Pointer = SmartPointer<Self>;
  using ConstPointer = SmartPointer<const Self>;

  /*** Run-time type information (and related methods). */
  itkTypeMacro(BioCellularAggregateBase, Object);

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Convenient type alias. */
  using ImagePixelType = float;
  using SubstrateValueType = ImagePixelType;

public:
  virtual void
  Add(CellBase * cellA, CellBase * cellB, double perturbationLength);

  virtual void
  Remove(CellBase * cell);

  virtual SubstrateValueType
  GetSubstrateValue(IdentifierType cellId, unsigned int substrateId) const;

protected:
  CellularAggregateBase();
  ~CellularAggregateBase() override;
};
} // end namespace bio
} // end namespace itk

#endif
