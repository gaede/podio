// datamodel specific includes
#include "podio/UserData.h"
#include "podio/UserDataConst.h"
#include "podio/UserDataObj.h"
#include "podio/UserDataData.h"
#include "podio/UserDataCollection.h"
#include <iostream>




ConstUserData::ConstUserData() : m_obj(new UserDataObj()) {
 m_obj->acquire();
}

ConstUserData::ConstUserData(std::array<int, 4201> intvals,std::array<float, 4202> floatvals,std::array<double, 4203> doublevals) : m_obj(new UserDataObj()){
 m_obj->acquire();
   m_obj->data.intvals = intvals;  m_obj->data.floatvals = floatvals;  m_obj->data.doublevals = doublevals;
}


ConstUserData::ConstUserData(const ConstUserData& other) : m_obj(other.m_obj) {
  m_obj->acquire();
}

ConstUserData& ConstUserData::operator=(const ConstUserData& other) {
  if ( m_obj != nullptr) m_obj->release();
  m_obj = other.m_obj;
  return *this;
}

ConstUserData::ConstUserData(UserDataObj* obj) : m_obj(obj) {
  if(m_obj != nullptr)
    m_obj->acquire();
}

ConstUserData ConstUserData::clone() const {
  return {new UserDataObj(*m_obj)};
}

ConstUserData::~ConstUserData(){
  if ( m_obj != nullptr) m_obj->release();
}

  /// Access the integer values
  const int& ConstUserData::intvals(size_t i) const { return m_obj->data.intvals.at(i); }
  /// Access the integer values
  const std::array<int, 4201>& ConstUserData::intvals() const { return m_obj->data.intvals; }
  /// Access the float   values
  const float& ConstUserData::floatvals(size_t i) const { return m_obj->data.floatvals.at(i); }
  /// Access the float   values
  const std::array<float, 4202>& ConstUserData::floatvals() const { return m_obj->data.floatvals; }
  /// Access the double  values
  const double& ConstUserData::doublevals(size_t i) const { return m_obj->data.doublevals.at(i); }
  /// Access the double  values
  const std::array<double, 4203>& ConstUserData::doublevals() const { return m_obj->data.doublevals; }



bool  ConstUserData::isAvailable() const {
  if (m_obj != nullptr) {
    return true;
  }
  return false;
}

const podio::ObjectID ConstUserData::getObjectID() const {
  if (m_obj !=nullptr){
    return m_obj->id;
  }
  return podio::ObjectID{-2,-2};
}

bool ConstUserData::operator==(const UserData& other) const {
     return (m_obj==other.m_obj);
}

//bool operator< (const UserData& p1, const UserData& p2 ) {
//  if( p1.m_containerID == p2.m_containerID ) {
//    return p1.m_index < p2.m_index;
//  } else {
//    return p1.m_containerID < p2.m_containerID;
//  }
//}


