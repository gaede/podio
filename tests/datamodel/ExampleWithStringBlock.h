#ifndef ExampleWithStringBlock_H
#define ExampleWithStringBlock_H

#include "podio/SIOBlock.h"

#include <sio/api.h>
#include <sio/version.h>
#include <sio/io_device.h>
#include "ExampleWithStringCollection.h"

#include  <typeindex>



class ExampleWithStringBlock: public podio::SIOBlock{
  
public:
  
  
  ExampleWithStringBlock() :
    SIOBlock( "ExampleWithString", sio::version::encode_version(0, 1) ){
    podio::SIOBlockFactory::instance().registerBlockForCollection( std::type_index(typeid(ExampleWithStringCollection)), this) ;
  }
  
  ExampleWithStringBlock(const std::string &nam ) :
    SIOBlock( nam+std::string("__ExampleWithString"), sio::version::encode_version(0, 1) ){
  }
  
  // Read the particle data from the device
  virtual void read( sio::read_device &device,
		     sio::version_type vers ) override ;
  
  // Write the particle data to the device
  virtual void write( sio::write_device &device ) override ;
  
  SIOBlock* const create(const std::string name) override { return new ExampleWithStringBlock(name) ; }

};


static ExampleWithStringBlock _dummyExampleWithStringBlock ;

#endif
