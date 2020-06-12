// standard includes
#include <stdexcept>


#include "podio/UserDataCollection.h"



UserDataCollection::UserDataCollection() : m_isValid(false), m_collectionID(0), m_entries() ,m_data(new UserDataDataContainer() ) {
  
}

UserDataCollection::~UserDataCollection() {
  clear();
  if (m_data != nullptr) delete m_data;
  
}

const UserData UserDataCollection::operator[](unsigned int index) const {
  return UserData(m_entries[index]);
}

const UserData UserDataCollection::at(unsigned int index) const {
  return UserData(m_entries.at(index));
}

UserData UserDataCollection::operator[](unsigned int index) {
  return UserData(m_entries[index]);
}

UserData UserDataCollection::at(unsigned int index) {
  return UserData(m_entries.at(index));
}

int  UserDataCollection::size() const {
  return m_entries.size();
}

UserData UserDataCollection::create(){
  auto obj = new UserDataObj();
  m_entries.emplace_back(obj);

  obj->id = {int(m_entries.size()-1),m_collectionID};
  return UserData(obj);
}

void UserDataCollection::clear(){
  m_data->clear();

  for (auto& obj : m_entries) { delete obj; }
  m_entries.clear();
}

void UserDataCollection::prepareForWrite(){
  auto size = m_entries.size();
  m_data->reserve(size);
  for (auto& obj : m_entries) {m_data->push_back(obj->data); }
  for (auto& pointer : m_refCollections) {pointer->clear(); } 

  for(int i=0, size = m_data->size(); i != size; ++i){

  }

}

void UserDataCollection::prepareAfterRead(){
  int index = 0;
  for (auto& data : *m_data){
    auto obj = new UserDataObj({index,m_collectionID}, data);
    
    m_entries.emplace_back(obj);
    ++index;
  }
  m_isValid = true;
}

bool UserDataCollection::setReferences(const podio::ICollectionProvider* collectionProvider){


  return true; //TODO: check success
}

void UserDataCollection::push_back(ConstUserData object){
  int size = m_entries.size();
  auto obj = object.m_obj;
  if (obj->id.index == podio::ObjectID::untracked) {
      obj->id = {size,m_collectionID};
      m_entries.push_back(obj);
      
  } else {
    throw std::invalid_argument( "Object already in a collection. Cannot add it to a second collection " );
  }
}

void UserDataCollection::setBuffer(void* address){
  if (m_data != nullptr) delete m_data;
  m_data = static_cast<UserDataDataContainer*>(address);
}


const UserData UserDataCollectionIterator::operator* () const {
  m_object.m_obj = (*m_collection)[m_index];
  return m_object;
}

const UserData* UserDataCollectionIterator::operator-> () const {
  m_object.m_obj = (*m_collection)[m_index];
  return &m_object;
}

const UserDataCollectionIterator& UserDataCollectionIterator::operator++() const {
  ++m_index;
  return *this;
}

std::ostream& operator<<( std::ostream& o,const UserDataCollection& v){
  std::ios::fmtflags old_flags = o.flags() ; 
  o << "id:          intvals:      floatvals:    doublevals:   " << std::endl ;
   for(int i = 0; i < v.size(); i++){
     o << std::scientific << std::showpos  << std::setw(12)  << v[i].id() << " "   << std::endl;
  }
o.flags(old_flags);
  return o ;
}



