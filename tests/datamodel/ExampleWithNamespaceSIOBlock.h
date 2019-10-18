//AUTOMATICALLY GENERATED - DO NOT EDIT
#ifndef ExampleWithNamespaceSIOBlock_H
#define ExampleWithNamespaceSIOBlock_H

#include "podio/SIOBlock.h"

#include <sio/api.h>
#include <sio/version.h>
#include <sio/io_device.h>
#include "ExampleWithNamespaceCollection.h"

#include  <typeindex>


namespace ex42 {

class ExampleWithNamespaceSIOBlock: public podio::SIOBlock{
  
public:
  
  
  ExampleWithNamespaceSIOBlock() :
    SIOBlock( "ExampleWithNamespace", sio::version::encode_version(0, 1) ){
    podio::SIOBlockFactory::instance().registerBlockForCollection( std::string("ex42::ExampleWithNamespace"), this) ;
  }
  
  ExampleWithNamespaceSIOBlock(const std::string &nam ) :
    //SIOBlock( nam+std::string("__ExampleWithNamespace"), sio::version::encode_version(0, 1) ){
    SIOBlock(nam , sio::version::encode_version(0, 1) ){
  }
  
  // Read the particle data from the device
  virtual void read( sio::read_device &device,
         sio::version_type vers ) override ;
  
  // Write the particle data to the device
  virtual void write( sio::write_device &device ) override ;
  
  virtual  void createCollection() override {
    setCollection(  new ExampleWithNamespaceCollection ) ;
  }

  SIOBlock* const create(const std::string name) override { return new ExampleWithNamespaceSIOBlock(name) ; }

};


static ExampleWithNamespaceSIOBlock _dummyExampleWithNamespaceSIOBlock ;

} // namespace ex42

#endif
