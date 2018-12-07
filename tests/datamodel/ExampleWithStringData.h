#ifndef ExampleWithStringDATA_H
#define ExampleWithStringDATA_H

#include <string>
#include <type_traits>

/** @class ExampleWithStringData
 *  Type with a string
 *  @author: Benedikt Hegner
 */

class ExampleWithStringData {
public:
  std::string theString; ///< the string
};

//static_assert(
//    std::is_trivially_copyable<ExampleWithStringData>::value,
//    "Please check your definition of ExampleWithString in the yaml file.");

#endif
