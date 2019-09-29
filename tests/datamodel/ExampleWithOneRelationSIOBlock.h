//AUTOMATICALLY GENERATED - DO NOT EDIT
#ifndef ExampleWithOneRelationSIOBlock_H
#define ExampleWithOneRelationSIOBlock_H

#include "podio/SIOBlock.h"

#include <sio/api.h>
#include <sio/version.h>
#include <sio/io_device.h>
#include "ExampleWithOneRelationCollection.h"

#include  <typeindex>




class ExampleWithOneRelationSIOBlock: public podio::SIOBlock{
  
public:
  
  
  ExampleWithOneRelationSIOBlock() :
    SIOBlock( "ExampleWithOneRelation", sio::version::encode_version(0, 1) ){
    podio::SIOBlockFactory::instance().registerBlockForCollection( std::type_index(typeid(::ExampleWithOneRelationCollection)), this) ;
  }
  
  ExampleWithOneRelationSIOBlock(const std::string &nam ) :
    SIOBlock( nam+std::string("__ExampleWithOneRelation"), sio::version::encode_version(0, 1) ){
  }
  
  // Read the particle data from the device
  virtual void read( sio::read_device &device,
         sio::version_type vers ) override ;
  
  // Write the particle data to the device
  virtual void write( sio::write_device &device ) override ;
  
  SIOBlock* const create(const std::string name) override { return new ExampleWithOneRelationSIOBlock(name) ; }

};


static ExampleWithOneRelationSIOBlock _dummyExampleWithOneRelationSIOBlock ;



#endif
