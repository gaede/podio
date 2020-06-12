#ifndef DATAMODEL_UserData_H
#define DATAMODEL_UserData_H
#include "podio/UserDataData.h"
#include <array>
#include <vector>
#include <iostream>
#include <iomanip>
#include "podio/ObjectID.h"

//forward declarations


#include "podio/UserDataConst.h"
#include "podio/UserDataObj.h"



template<size_t I, size_t F, size_t D>
class UserDataCollection;
template<size_t I, size_t F, size_t D>
class UserDataCollectionIterator;
template<size_t I, size_t F, size_t D>
class ConstUserData;

/** @class UserData
 *  User data with int, float and double arrays
 *  @author: F.Gaede, DESY
 */
template<size_t I, size_t F, size_t D>
class UserData {

  friend UserDataCollection<I,F,D>;
  friend UserDataCollectionIterator<I,F,D>;
  friend ConstUserData<I,F,D>;

public:

  /// default constructor
  UserData();
  UserData(std::array<int, I> intvals,std::array<float, F> floatvals,std::array<double, D> doublevals);

  /// constructor from existing UserDataObj
  UserData(UserDataObj<I,F,D>* obj);
  /// copy constructor
  UserData(const UserData& other);
  /// copy-assignment operator
  UserData& operator=(const UserData& other);
  /// support cloning (deep-copy)
  UserData clone() const;
  /// destructor
  ~UserData();

  /// conversion to const object
  operator ConstUserData<I,F,D>() const;

public:

  /// Access the integer values
  const std::array<int, I>& intvals() const;
  /// Access item i in the integer values
  const int& intvals(size_t i) const;
  /// Access the float   values
  const std::array<float, F>& floatvals() const;
  /// Access item i in the float   values
  const float& floatvals(size_t i) const;
  /// Access the double  values
  const std::array<double, D>& doublevals() const;
  /// Access item i in the double  values
  const double& doublevals(size_t i) const;

  /// Set the integer values
  void intvals(std::array<int, I> value);

  /// Set item i in integer values
  void intvals(size_t i, int value);

  /// Set the float   values
  void floatvals(std::array<float, F> value);

  /// Set item i in float   values
  void floatvals(size_t i, float value);

  /// Set the double  values
  void doublevals(std::array<double, D> value);

  /// Set item i in double  values
  void doublevals(size_t i, double value);




  /// check whether the object is actually available
  bool isAvailable() const;
  /// disconnect from UserDataObj instance
  void unlink(){m_obj = nullptr;}

  bool operator==(const UserData& other) const {
    return (m_obj==other.m_obj);
  }

  bool operator==(const ConstUserData<I,F,D>& other) const;

// less comparison operator, so that objects can be e.g. stored in sets.
//  friend bool operator< (const UserData& p1,
//       const UserData& p2 );
  bool operator<(const UserData& other) const { return m_obj < other.m_obj  ; }


  unsigned int id() const { return getObjectID().collectionID * 10000000 + getObjectID().index  ;  } 

  const podio::ObjectID getObjectID() const;

private:
  UserDataObj<I,F,D>* m_obj;

};

template<size_t I, size_t F, size_t D>
std::ostream& operator<<( std::ostream& o,const ConstUserData<I,F,D>& value );




#endif
