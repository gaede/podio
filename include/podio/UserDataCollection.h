//AUTOMATICALLY GENERATED - DO NOT EDIT

#ifndef DATAMODEL_UserDataCollection_H
#define DATAMODEL_UserDataCollection_H

#include <string>
#include <vector>
#include <deque>
#include <array>
#include <algorithm>
#include <iostream>
#include <iomanip>

// podio specific includes
#include "podio/ICollectionProvider.h"
#include "podio/CollectionBase.h"
#include "podio/CollectionIDTable.h"

// datamodel specific includes
#include "podio/UserDataData.h"
#include "podio/UserData.h"
#include "podio/UserDataObj.h"


template<size_t I, size_t F, size_t D>
using UserDataDataContainer = std::vector<UserDataData <I,F,D> >;

template<size_t I, size_t F, size_t D>
using UserDataObjPointerContainer  = std::deque<UserDataObj<I,F,D>*> ;

template<size_t I, size_t F, size_t D>
class UserDataCollectionIterator {

  public:
    UserDataCollectionIterator(int index, const UserDataObjPointerContainer<I,F,D>* collection) : m_index(index), m_object(nullptr), m_collection(collection) {}

    bool operator!=(const UserDataCollectionIterator& x) const {
      return m_index != x.m_index; //TODO: may not be complete
    }

    const UserData<I,F,D> operator*() const;
    const UserData<I,F,D>* operator->() const;
    const UserDataCollectionIterator& operator++() const;

  private:
    mutable int m_index;
    mutable UserData<I,F,D> m_object;
    const UserDataObjPointerContainer<I,F,D>* m_collection;
};

/**
A Collection is identified by an ID.
*/

template<size_t I, size_t F, size_t D>
class UserDataCollection : public podio::CollectionBase {

public:
  typedef const UserDataCollectionIterator<I,F,D> const_iterator;

  UserDataCollection();
//  UserDataCollection(const UserDataCollection& ) = delete; // deletion doesn't work w/ ROOT IO ! :-(
//  UserDataCollection(UserDataVector* data, int collectionID);
  ~UserDataCollection();

  void clear() override final;

  /// operator to allow pointer like calling of members a la LCIO  \n     
  UserDataCollection* operator->() { return (UserDataCollection*) this ; }

  /// Append a new object to the collection, and return this object.
  UserData<I,F,D> create();

  /// Append a new object to the collection, and return this object.
  /// Initialized with the parameters given
  template<typename... Args>
  UserData<I,F,D> create(Args&&... args){
    int size = m_entries.size();
    auto obj = new UserDataObj<I,F,D>({size,m_collectionID},{args...});
    m_entries.push_back(obj);
    return UserData<I,F,D>(obj);
  }


  /// number of elements in the collection
  int size() const override final ;

  /// fully qualified type name of elements - with namespace
  std::string getValueTypeName() const override { return std::string("UserData") ; } ;

  /// Returns the const object of given index
  const UserData<I,F,D> operator[](unsigned int index) const;
  /// Returns the object of a given index
  UserData<I,F,D> operator[](unsigned int index);
  /// Returns the const object of given index
  const UserData<I,F,D> at(unsigned int index) const;
  /// Returns the object of given index
  UserData<I,F,D> at(unsigned int index);


  /// Append object to the collection
  void push_back(ConstUserData<I,F,D> object);

  void prepareForWrite() override final;
  void prepareAfterRead() override final;
  void setBuffer(void* address) override final;
  bool setReferences(const podio::ICollectionProvider* collectionProvider) override final;

  podio::CollRefCollection* referenceCollections() override final { return &m_refCollections;};

  podio::VectorMembersInfo* vectorMembers() override {return &m_vecmem_info ; }

  void setID(unsigned ID) override final {
    m_collectionID = ID;
    std::for_each(m_entries.begin(),m_entries.end(),
                 [ID](UserDataObj<I,F,D>* obj){obj->id = {obj->id.index,static_cast<int>(ID)}; }
    );
  };

  unsigned getID() const override final {
    return m_collectionID ;
  }

  bool isValid() const override final {
    return m_isValid;
  }

  // support for the iterator protocol
  const const_iterator begin() const {
    return const_iterator(0, &m_entries);
  }
  const const_iterator end() const {
    return const_iterator(m_entries.size(), &m_entries);
  }

  /// returns the address of the pointer to the data buffer
  void* getBufferAddress() override final { return (void*)&m_data;};

  /// returns the pointer to the data buffer
  std::vector<UserDataData<I,F,D> >* _getBuffer() { return m_data;};

  template<size_t arraysize>
  const std::array<std::array<int, I>,arraysize> intvals() const{
    std::array<class std::array<int, I>,arraysize> tmp;
    auto valid_size = std::min(arraysize,m_entries.size());
    for (unsigned i = 0; i<valid_size; ++i){
      tmp[i] = m_entries[i]->data.intvals;
    }
    return tmp;
  }

  template<size_t arraysize>
  const std::array<std::array<float, F>,arraysize> floatvals() const{
    std::array<class std::array<float, F>,arraysize> tmp;
    auto valid_size = std::min(arraysize,m_entries.size());
    for (unsigned i = 0; i<valid_size; ++i){
      tmp[i] = m_entries[i]->data.floatvals;
    }
    return tmp;
  }

  template<size_t arraysize>
  const std::array<std::array<double, D>,arraysize> doublevals() const{
    std::array<class std::array<double, D>,arraysize> tmp;
    auto valid_size = std::min(arraysize,m_entries.size());
    for (unsigned i = 0; i<valid_size; ++i){
      tmp[i] = m_entries[i]->data.doublevals;
    }
    return tmp;
  }
  


private:
  bool m_isValid;
  int m_collectionID;
  UserDataObjPointerContainer<I,F,D> m_entries;
  // members to handle 1-to-N-relations

  //members to handle vector members

  // members to handle streaming
  podio::CollRefCollection m_refCollections;
  podio::VectorMembersInfo m_vecmem_info ;
  UserDataDataContainer<I,F,D>* m_data;
};

template<size_t I, size_t F, size_t D>
std::ostream& operator<<( std::ostream& o,const UserDataCollection<I,F,D>& v);


//template<size_t I, size_t F, size_t D, typename... Args>
// UserData<I,F,D>  UserDataCollection<I,F,D>::create(Args&&... args){
//   int size = m_entries.size();
//   auto obj = new UserDataObj<I,F,D>({size,m_collectionID},{args...});
//   m_entries.push_back(obj);
//   return UserData<I,F,D>(obj);
// }

// template<size_t arraysize>
// const std::array<class std::array<int, I>,arraysize> UserDataCollection<I,F,D>::intvals() const {
//   std::array<class std::array<int, I>,arraysize> tmp;
//   auto valid_size = std::min(arraysize,m_entries.size());
//   for (unsigned i = 0; i<valid_size; ++i){
//     tmp[i] = m_entries[i]->data.intvals;
//  }
//  return tmp;
// }
// template<size_t arraysize>
// const std::array<class std::array<float, F>,arraysize> UserDataCollection<I,F,D>::floatvals() const {
//   std::array<class std::array<float, F>,arraysize> tmp;
//   auto valid_size = std::min(arraysize,m_entries.size());
//   for (unsigned i = 0; i<valid_size; ++i){
//     tmp[i] = m_entries[i]->data.floatvals;
//  }
//  return tmp;
// }
// template<size_t arraysize>
// const std::array<class std::array<double, D>,arraysize> UserDataCollection<I,F,D>::doublevals() const {
//   std::array<class std::array<double, D>,arraysize> tmp;
//   auto valid_size = std::min(arraysize,m_entries.size());
//   for (unsigned i = 0; i<valid_size; ++i){
//     tmp[i] = m_entries[i]->data.doublevals;
//  }
//  return tmp;
// }


#endif
