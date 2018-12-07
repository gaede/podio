#ifndef EventInfoDATA_H
#define EventInfoDATA_H

#include <type_traits>

/** @class EventInfoData
 *  Event info
 *  @author: B. Hegner
 */

class EventInfoData {
public:
  int Number; ///< event number
};

static_assert(std::is_trivially_copyable<EventInfoData>::value,
              "Please check your definition of EventInfo in the yaml file.");

#endif
