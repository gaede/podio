#ifndef ConstExampleWithNamespace_H
#define ConstExampleWithNamespace_H
#include "NamespaceStruct.h"
#include "ExampleWithNamespaceData.h"
#include <vector>
#include "podio/ObjectID.h"

// Type with namespace and namespaced member
// author: Joschka Lingemann

//forward declarations


#include "ExampleWithNamespaceObj.h"

namespace ex {

class ExampleWithNamespaceObj;
class ExampleWithNamespace;
class ExampleWithNamespaceCollection;
class ExampleWithNamespaceCollectionIterator;

class ConstExampleWithNamespace {

  friend ExampleWithNamespace;
  friend ExampleWithNamespaceCollection;
  friend ExampleWithNamespaceCollectionIterator;

public:

  /// default constructor
  ConstExampleWithNamespace();
  ConstExampleWithNamespace(ex2::NamespaceStruct data);

  /// constructor from existing ExampleWithNamespaceObj
  ConstExampleWithNamespace(ExampleWithNamespaceObj* obj);
  /// copy constructor
  ConstExampleWithNamespace(const ConstExampleWithNamespace& other);
  /// copy-assignment operator
  ConstExampleWithNamespace& operator=(const ConstExampleWithNamespace& other);
  /// support cloning (deep-copy)
  ConstExampleWithNamespace clone() const;
  /// destructor
  ~ConstExampleWithNamespace();


public:

  const ex2::NamespaceStruct& data() const;



  /// check whether the object is actually available
  bool isAvailable() const;
  /// disconnect from ExampleWithNamespaceObj instance
  void unlink(){m_obj = nullptr;}

  bool operator==(const ConstExampleWithNamespace& other) const {
       return (m_obj==other.m_obj);
  }

  bool operator==(const ExampleWithNamespace& other) const;

// less comparison operator, so that objects can be e.g. stored in sets.
//  friend bool operator< (const ExampleWithNamespace& p1,
//       const ExampleWithNamespace& p2 );

  const podio::ObjectID getObjectID() const;

private:
  ExampleWithNamespaceObj* m_obj;

};
} // namespace ex

#endif
