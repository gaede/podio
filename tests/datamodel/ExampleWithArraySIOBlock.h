//AUTOMATICALLY GENERATED - DO NOT EDIT
#ifndef ExampleWithArraySIOBlock_H
#define ExampleWithArraySIOBlock_H

#include "podio/SIOBlock.h"

#include <sio/api.h>
#include <sio/version.h>
#include <sio/io_device.h>
#include "ExampleWithArrayCollection.h"

#include  <typeindex>




class ExampleWithArraySIOBlock: public podio::SIOBlock{
  
public:
  
  
  ExampleWithArraySIOBlock() :
    SIOBlock( "ExampleWithArray", sio::version::encode_version(0, 1) ){
    podio::SIOBlockFactory::instance().registerBlockForCollection( std::type_index(typeid(::ExampleWithArrayCollection)), this) ;
  }
  
  ExampleWithArraySIOBlock(const std::string &nam ) :
    SIOBlock( nam+std::string("__ExampleWithArray"), sio::version::encode_version(0, 1) ){
  }
  
  // Read the particle data from the device
  virtual void read( sio::read_device &device,
         sio::version_type vers ) override ;
  
  // Write the particle data to the device
  virtual void write( sio::write_device &device ) override ;
  
  SIOBlock* const create(const std::string name) override { return new ExampleWithArraySIOBlock(name) ; }

};


static ExampleWithArraySIOBlock _dummyExampleWithArraySIOBlock ;



#endif
