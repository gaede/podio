//AUTOMATICALLY GENERATED - DO NOT EDIT
#ifndef ExampleHitSIOBlock_H
#define ExampleHitSIOBlock_H

#include "podio/SIOBlock.h"

#include <sio/api.h>
#include <sio/version.h>
#include <sio/io_device.h>
#include "ExampleHitCollection.h"

#include  <typeindex>




class ExampleHitSIOBlock: public podio::SIOBlock{
  
public:
  
  
  ExampleHitSIOBlock() :
    SIOBlock( "ExampleHit", sio::version::encode_version(0, 1) ){
    podio::SIOBlockFactory::instance().registerBlockForCollection( std::type_index(typeid(::ExampleHitCollection)), this) ;
  }
  
  ExampleHitSIOBlock(const std::string &nam ) :
    SIOBlock( nam+std::string("__ExampleHit"), sio::version::encode_version(0, 1) ){
  }
  
  // Read the particle data from the device
  virtual void read( sio::read_device &device,
         sio::version_type vers ) override ;
  
  // Write the particle data to the device
  virtual void write( sio::write_device &device ) override ;
  
  SIOBlock* const create(const std::string name) override { return new ExampleHitSIOBlock(name) ; }

};


static ExampleHitSIOBlock _dummyExampleHitSIOBlock ;



#endif
