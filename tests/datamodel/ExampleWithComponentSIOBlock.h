//AUTOMATICALLY GENERATED - DO NOT EDIT
#ifndef ExampleWithComponentSIOBlock_H
#define ExampleWithComponentSIOBlock_H

#include "podio/SIOBlock.h"

#include <sio/api.h>
#include <sio/version.h>
#include <sio/io_device.h>
#include "ExampleWithComponentCollection.h"

#include  <typeindex>




class ExampleWithComponentSIOBlock: public podio::SIOBlock{
  
public:
  
  
  ExampleWithComponentSIOBlock() :
    SIOBlock( "ExampleWithComponent", sio::version::encode_version(0, 1) ){
    podio::SIOBlockFactory::instance().registerBlockForCollection( std::type_index(typeid(::ExampleWithComponentCollection)), this) ;
  }
  
  ExampleWithComponentSIOBlock(const std::string &nam ) :
    SIOBlock( nam+std::string("__ExampleWithComponent"), sio::version::encode_version(0, 1) ){
  }
  
  // Read the particle data from the device
  virtual void read( sio::read_device &device,
         sio::version_type vers ) override ;
  
  // Write the particle data to the device
  virtual void write( sio::write_device &device ) override ;
  
  SIOBlock* const create(const std::string name) override { return new ExampleWithComponentSIOBlock(name) ; }

};


static ExampleWithComponentSIOBlock _dummyExampleWithComponentSIOBlock ;



#endif
