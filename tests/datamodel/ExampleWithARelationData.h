#ifndef ExampleWithARelationDATA_H
#define ExampleWithARelationDATA_H

#include <type_traits>

namespace ex {
/** @class ExampleWithARelationData
 *  Type with namespace and namespaced relation
 *  @author: Joschka Lingemann
 */

class ExampleWithARelationData {
public:
  float number; ///< just a number
  unsigned int refs_begin;
  unsigned int refs_end;
};

static_assert(
    std::is_trivially_copyable<ExampleWithARelationData>::value,
    "Please check your definition of ExampleWithARelation in the yaml file.");

} // namespace ex

#endif
