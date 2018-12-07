#ifndef ExampleReferencingTypeDATA_H
#define ExampleReferencingTypeDATA_H

#include <type_traits>

/** @class ExampleReferencingTypeData
 *  Referencing Type
 *  @author: B. Hegner
 */

class ExampleReferencingTypeData {
public:
  unsigned int Clusters_begin;
  unsigned int Clusters_end;
  unsigned int Refs_begin;
  unsigned int Refs_end;
};

static_assert(
    std::is_trivially_copyable<ExampleReferencingTypeData>::value,
    "Please check your definition of ExampleReferencingType in the yaml file.");

#endif
