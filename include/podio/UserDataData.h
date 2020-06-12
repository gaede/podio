#ifndef DATAMODEL_UserDataDATA_H
#define DATAMODEL_UserDataDATA_H

#include <array>


/** @class UserDataData
 *  User data with int, float and double arrays
 *  @author: F.Gaede, DESY
 */

template<size_t I, size_t F, size_t D>
class UserDataData {
public:
  std::array<int, I> intvals;  ///<integer values
  std::array<float, F> floatvals;  ///<float   values
  std::array<double, D> doublevals;  ///<double  values
};


#endif
