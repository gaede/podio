#ifndef ExampleHitDATA_H
#define ExampleHitDATA_H

#include <type_traits>

/** @class ExampleHitData
 *  Example Hit
 *  @author: B. Hegner
 */

class ExampleHitData {
public:
  double x;      ///< x-coordinate
  double y;      ///< y-coordinate
  double z;      ///< z-coordinate
  double energy; ///< measured energy deposit
};

static_assert(std::is_trivially_copyable<ExampleHitData>::value,
              "Please check your definition of ExampleHit in the yaml file.");

#endif
