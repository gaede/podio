//AUTOMATICALLY GENERATED - DO NOT EDIT
#ifndef ExampleMCSIOBlock_H
#define ExampleMCSIOBlock_H

#include "podio/SIOBlock.h"

#include <sio/api.h>
#include <sio/version.h>
#include <sio/io_device.h>
#include "ExampleMCCollection.h"

#include  <typeindex>




class ExampleMCSIOBlock: public podio::SIOBlock{
  
public:
  
  
  ExampleMCSIOBlock() :
    SIOBlock( "ExampleMC", sio::version::encode_version(0, 1) ){
    podio::SIOBlockFactory::instance().registerBlockForCollection( std::type_index(typeid(::ExampleMCCollection)), this) ;
  }
  
  ExampleMCSIOBlock(const std::string &nam ) :
    SIOBlock( nam+std::string("__ExampleMC"), sio::version::encode_version(0, 1) ){
  }
  
  // Read the particle data from the device
  virtual void read( sio::read_device &device,
         sio::version_type vers ) override ;
  
  // Write the particle data to the device
  virtual void write( sio::write_device &device ) override ;
  
  SIOBlock* const create(const std::string name) override { return new ExampleMCSIOBlock(name) ; }

};


static ExampleMCSIOBlock _dummyExampleMCSIOBlock ;



#endif
