#ifndef DATAMODEL_ConstUserData_H
#define DATAMODEL_ConstUserData_H
#include "podio/UserDataData.h"
#include <array>
#include <vector>
#include "podio/ObjectID.h"

//forward declarations


#include "podio/UserDataObj.h"



template<size_t I, size_t F, size_t D>
class UserDataObj;
template<size_t I, size_t F, size_t D>
class UserData;
template<size_t I, size_t F, size_t D>
class UserDataCollection;
template<size_t I, size_t F, size_t D>
class UserDataCollectionIterator;

/** @class ConstUserData
 *  User data with int, float and double arrays
 *  @author: F.Gaede, DESY
 */

template<size_t I, size_t F, size_t D>
class ConstUserData {

  friend UserData<I,F,D>;
  friend UserDataCollection<I,F,D>;
  friend UserDataCollectionIterator<I,F,D>;

public:

  /// default constructor
  ConstUserData();
  ConstUserData(std::array<int, I> intvals,std::array<float, F> floatvals,std::array<double, D> doublevals);

  /// constructor from existing UserDataObj
  ConstUserData(UserDataObj<I,F,D>* obj);
  /// copy constructor
  ConstUserData(const ConstUserData& other);
  /// copy-assignment operator
  ConstUserData& operator=(const ConstUserData& other);
  /// support cloning (deep-copy)
  ConstUserData clone() const;
  /// destructor
  ~ConstUserData();


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



  /// check whether the object is actually available
  bool isAvailable() const;
  /// disconnect from UserDataObj instance
  void unlink(){m_obj = nullptr;}

  bool operator==(const ConstUserData& other) const {
       return (m_obj==other.m_obj);
  }

  bool operator==(const UserData<I,F,D>& other) const;

// less comparison operator, so that objects can be e.g. stored in sets.
//  friend bool operator< (const UserData& p1,
//       const UserData& p2 );
  bool operator<(const ConstUserData& other) const { return m_obj < other.m_obj  ; }

  unsigned int id() const { return getObjectID().collectionID * 10000000 + getObjectID().index  ;  } 

  const podio::ObjectID getObjectID() const;

private:
  UserDataObj<I,F,D>* m_obj;

};


#endif
