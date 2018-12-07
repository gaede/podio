#ifndef ExampleWithNamespaceDATA_H
#define ExampleWithNamespaceDATA_H

#include "NamespaceStruct.h"
#include <type_traits>

namespace ex {
/** @class ExampleWithNamespaceData
 *  Type with namespace and namespaced member
 *  @author: Joschka Lingemann
 */

class ExampleWithNamespaceData {
public:
  ex2::NamespaceStruct data; ///< a component
};

static_assert(
    std::is_trivially_copyable<ExampleWithNamespaceData>::value,
    "Please check your definition of ExampleWithNamespace in the yaml file.");

} // namespace ex

#endif
