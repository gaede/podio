// datamodel specific includes
#include "podio/UserData.h"
#include "podio/UserDataConst.h"
#include "podio/UserDataObj.h"
#include "podio/UserDataData.h"
#include "podio/UserDataCollection.h"
#include <iostream>




UserData::UserData() : m_obj(new UserDataObj()){
 m_obj->acquire();
}

UserData::UserData(std::array<int, 4201> intvals,std::array<float, 4202> floatvals,std::array<double, 4203> doublevals) : m_obj(new UserDataObj()) {
  m_obj->acquire();
    m_obj->data.intvals = intvals;  m_obj->data.floatvals = floatvals;  m_obj->data.doublevals = doublevals;
}


UserData::UserData(const UserData& other) : m_obj(other.m_obj) {
  m_obj->acquire();
}

UserData& UserData::operator=(const UserData& other) {
  if ( m_obj != nullptr) m_obj->release();
  m_obj = other.m_obj;
  return *this;
}

UserData::UserData(UserDataObj* obj) : m_obj(obj){
  if(m_obj != nullptr)
    m_obj->acquire();
}

UserData UserData::clone() const {
  return {new UserDataObj(*m_obj)};
}

UserData::~UserData(){
  if ( m_obj != nullptr) m_obj->release();
}

UserData::operator ConstUserData() const {return ConstUserData(m_obj);}

  const std::array<int, 4201>& UserData::intvals() const { return m_obj->data.intvals; }
  const int& UserData::intvals(size_t i) const { return m_obj->data.intvals.at(i); }
  const std::array<float, 4202>& UserData::floatvals() const { return m_obj->data.floatvals; }
  const float& UserData::floatvals(size_t i) const { return m_obj->data.floatvals.at(i); }
  const std::array<double, 4203>& UserData::doublevals() const { return m_obj->data.doublevals; }
  const double& UserData::doublevals(size_t i) const { return m_obj->data.doublevals.at(i); }

void UserData::intvals(std::array<int, 4201> value) { m_obj->data.intvals = value; }
void UserData::intvals(size_t i, int value) { m_obj->data.intvals.at(i) = value; }
void UserData::floatvals(std::array<float, 4202> value) { m_obj->data.floatvals = value; }
void UserData::floatvals(size_t i, float value) { m_obj->data.floatvals.at(i) = value; }
void UserData::doublevals(std::array<double, 4203> value) { m_obj->data.doublevals = value; }
void UserData::doublevals(size_t i, double value) { m_obj->data.doublevals.at(i) = value; }



bool  UserData::isAvailable() const {
  if (m_obj != nullptr) {
    return true;
  }
  return false;
}

const podio::ObjectID UserData::getObjectID() const {
  if (m_obj !=nullptr){
    return m_obj->id;
  }
  return podio::ObjectID{-2,-2};
}

bool UserData::operator==(const ConstUserData& other) const {
  return (m_obj==other.m_obj);
}

std::ostream& operator<<( std::ostream& o,const ConstUserData& value ){
  o << " id : " << value.id() << std::endl ;
  o << " intvals : " ;
  for(int i=0,N= 4201;i<N;++i)
      o << value.intvals()[i] << "|" ;
  o << std::endl ;
  o << " floatvals : " ;
  for(int i=0,N= 4202;i<N;++i)
      o << value.floatvals()[i] << "|" ;
  o << std::endl ;
  o << " doublevals : " ;
  for(int i=0,N= 4203;i<N;++i)
      o << value.doublevals()[i] << "|" ;
  o << std::endl ;
  return o ;
}


//bool operator< (const UserData& p1, const UserData& p2 ) {
//  if( p1.m_containerID == p2.m_containerID ) {
//    return p1.m_index < p2.m_index;
//  } else {
//    return p1.m_containerID < p2.m_containerID;
//  }
//}


