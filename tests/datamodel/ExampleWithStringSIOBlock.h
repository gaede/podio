//AUTOMATICALLY GENERATED - DO NOT EDIT
#ifndef ExampleWithStringSIOBlock_H
#define ExampleWithStringSIOBlock_H

#include "podio/SIOBlock.h"

#include <sio/api.h>
#include <sio/version.h>
#include <sio/io_device.h>
#include "ExampleWithStringCollection.h"

#include  <typeindex>




class ExampleWithStringSIOBlock: public podio::SIOBlock{
  
public:
  
  
  ExampleWithStringSIOBlock() :
    SIOBlock( "ExampleWithString", sio::version::encode_version(0, 1) ){
    podio::SIOBlockFactory::instance().registerBlockForCollection( std::string("ExampleWithString"), this) ;
  }
  
  ExampleWithStringSIOBlock(const std::string &nam ) :
    SIOBlock( nam+std::string("__ExampleWithString"), sio::version::encode_version(0, 1) ){
  }
  
  // Read the particle data from the device
  virtual void read( sio::read_device &device,
         sio::version_type vers ) override ;
  
  // Write the particle data to the device
  virtual void write( sio::write_device &device ) override ;
  
  SIOBlock* const create(const std::string name) override { return new ExampleWithStringSIOBlock(name) ; }

};


static ExampleWithStringSIOBlock _dummyExampleWithStringSIOBlock ;



#endif
