//AUTOMATICALLY GENERATED - DO NOT EDIT
#ifndef ExampleForCyclicDependency1SIOBlock_H
#define ExampleForCyclicDependency1SIOBlock_H

#include "podio/SIOBlock.h"

#include <sio/api.h>
#include <sio/version.h>
#include <sio/io_device.h>
#include "ExampleForCyclicDependency1Collection.h"

#include  <typeindex>




class ExampleForCyclicDependency1SIOBlock: public podio::SIOBlock{
  
public:
  
  
  ExampleForCyclicDependency1SIOBlock() :
    SIOBlock( "ExampleForCyclicDependency1", sio::version::encode_version(0, 1) ){
    podio::SIOBlockFactory::instance().registerBlockForCollection( std::string("ExampleForCyclicDependency1"), this) ;
  }
  
  ExampleForCyclicDependency1SIOBlock(const std::string &nam ) :
    //SIOBlock( nam+std::string("__ExampleForCyclicDependency1"), sio::version::encode_version(0, 1) ){
    SIOBlock(nam , sio::version::encode_version(0, 1) ){
  }
  
  // Read the particle data from the device
  virtual void read( sio::read_device &device,
         sio::version_type vers ) override ;
  
  // Write the particle data to the device
  virtual void write( sio::write_device &device ) override ;
  
  virtual  void createCollection() override {
    setCollection(  new ExampleForCyclicDependency1Collection ) ;
  }

  SIOBlock* const create(const std::string name) override { return new ExampleForCyclicDependency1SIOBlock(name) ; }

};


static ExampleForCyclicDependency1SIOBlock _dummyExampleForCyclicDependency1SIOBlock ;



#endif
