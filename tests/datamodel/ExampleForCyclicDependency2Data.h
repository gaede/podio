#ifndef ExampleForCyclicDependency2DATA_H
#define ExampleForCyclicDependency2DATA_H

#include <type_traits>

/** @class ExampleForCyclicDependency2Data
 *  Type for cyclic dependency
 *  @author: Benedikt Hegner
 */

class ExampleForCyclicDependency2Data {
public:
};

static_assert(
    std::is_trivially_copyable<ExampleForCyclicDependency2Data>::value,
    "Please check your definition of ExampleForCyclicDependency2 in the yaml "
    "file.");

#endif
