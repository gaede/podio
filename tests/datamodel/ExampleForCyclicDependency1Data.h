#ifndef ExampleForCyclicDependency1DATA_H
#define ExampleForCyclicDependency1DATA_H

#include <type_traits>

/** @class ExampleForCyclicDependency1Data
 *  Type for cyclic dependency
 *  @author: Benedikt Hegner
 */

class ExampleForCyclicDependency1Data {
public:
};

static_assert(
    std::is_trivially_copyable<ExampleForCyclicDependency1Data>::value,
    "Please check your definition of ExampleForCyclicDependency1 in the yaml "
    "file.");

#endif
