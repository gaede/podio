#ifndef ExampleMCBlock_H
#define ExampleMCBlock_H

#include "SIOBlock.h"

#include <sio/api.h>
#include <sio/version.h>
#include <sio/io_device.h>
#include "ExampleMCCollection.h"

#include  <typeindex>



class ExampleMCBlock: public SIOBlock{
  
public:
  
  
  ExampleMCBlock() :
    SIOBlock( "ExampleMC", sio::version::encode_version(0, 1) ){
    BlockFactory::instance().registerBlockForCollection( std::type_index(typeid(ExampleMCCollection)), this) ;
  }
  
  ExampleMCBlock(const std::string &nam ) :
    SIOBlock( nam+std::string("__ExampleMC"), sio::version::encode_version(0, 1) ){
  }
  
  // Read the particle data from the device
  virtual void read( sio::read_device &device,
		     sio::version_type vers ) override ;
  
  // Write the particle data to the device
  virtual void write( sio::write_device &device ) override ;
  
  SIOBlock* const create(const std::string name) override { return new ExampleMCBlock(name) ; }

};


static ExampleMCBlock _dummyExampleMCBlock ;

#endif
