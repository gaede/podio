#ifndef ExampleWithVectorMemberDATA_H
#define ExampleWithVectorMemberDATA_H

#include <type_traits>

/** @class ExampleWithVectorMemberData
 *  Type with a vector member
 *  @author: B. Hegner
 */

class ExampleWithVectorMemberData {
public:
  unsigned int count_begin;
  unsigned int count_end;
};

static_assert(std::is_trivially_copyable<ExampleWithVectorMemberData>::value,
              "Please check your definition of ExampleWithVectorMember in the "
              "yaml file.");

#endif
