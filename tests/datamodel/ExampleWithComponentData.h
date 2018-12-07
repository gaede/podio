#ifndef ExampleWithComponentDATA_H
#define ExampleWithComponentDATA_H

#include "NotSoSimpleStruct.h"
#include <type_traits>

/** @class ExampleWithComponentData
 *  Type with one component
 *  @author: Benedikt Hegner
 */

class ExampleWithComponentData {
public:
  NotSoSimpleStruct component; ///< a component
};

static_assert(
    std::is_trivially_copyable<ExampleWithComponentData>::value,
    "Please check your definition of ExampleWithComponent in the yaml file.");

#endif
