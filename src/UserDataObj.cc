#include "podio/UserDataObj.h"



UserDataObj::UserDataObj() :
    ObjBase{{podio::ObjectID::untracked,podio::ObjectID::untracked},0}, data()
{ }

UserDataObj::UserDataObj(const podio::ObjectID id, UserDataData data) :
    ObjBase{id,0}, data(data)
{ }

UserDataObj::UserDataObj(const UserDataObj& other) :
    ObjBase{{podio::ObjectID::untracked,podio::ObjectID::untracked},0}
    , data(other.data)
{

}

UserDataObj::~UserDataObj() {
  if (id.index == podio::ObjectID::untracked) {

  }

}

