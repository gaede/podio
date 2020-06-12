#ifndef DATAMODEL_UserDataOBJ_H
#define DATAMODEL_UserDataOBJ_H

// std includes
#include <atomic>
#include <iostream>

// data model specific includes
#include "podio/ObjBase.h"
#include "podio/UserDataData.h"



// forward declarations




//class UserData;
//class ConstUserData;


template<size_t I, size_t F, size_t D>
class UserDataObj : public podio::ObjBase {
public:
  /// constructor
  UserDataObj();
  /// copy constructor (does a deep-copy of relation containers)
  UserDataObj(const UserDataObj<I,F,D>&);
  /// constructor from ObjectID and UserDataData
  /// does not initialize the internal relation containers
  UserDataObj(const podio::ObjectID id, UserDataData<I,F,D> data);
  virtual ~UserDataObj();

public:
  UserDataData<I,F,D> data;


};



#endif
