#ifndef ExampleWithOneRelationDATA_H
#define ExampleWithOneRelationDATA_H

#include <type_traits>

/** @class ExampleWithOneRelationData
 *  Type with one relation member
 *  @author: Benedikt Hegner
 */

class ExampleWithOneRelationData {
public:
};

static_assert(
    std::is_trivially_copyable<ExampleWithOneRelationData>::value,
    "Please check your definition of ExampleWithOneRelation in the yaml file.");

#endif
