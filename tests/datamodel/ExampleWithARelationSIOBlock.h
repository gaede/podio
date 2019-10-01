//AUTOMATICALLY GENERATED - DO NOT EDIT
#ifndef ExampleWithARelationSIOBlock_H
#define ExampleWithARelationSIOBlock_H

#include "podio/SIOBlock.h"

#include <sio/api.h>
#include <sio/version.h>
#include <sio/io_device.h>
#include "ExampleWithARelationCollection.h"

#include  <typeindex>


namespace ex42 {

class ExampleWithARelationSIOBlock: public podio::SIOBlock{
  
public:
  
  
  ExampleWithARelationSIOBlock() :
    SIOBlock( "ExampleWithARelation", sio::version::encode_version(0, 1) ){
    podio::SIOBlockFactory::instance().registerBlockForCollection( std::string("ex42::ExampleWithARelation"), this) ;
  }
  
  ExampleWithARelationSIOBlock(const std::string &nam ) :
    SIOBlock( nam+std::string("__ExampleWithARelation"), sio::version::encode_version(0, 1) ){
  }
  
  // Read the particle data from the device
  virtual void read( sio::read_device &device,
         sio::version_type vers ) override ;
  
  // Write the particle data to the device
  virtual void write( sio::write_device &device ) override ;
  
  SIOBlock* const create(const std::string name) override { return new ExampleWithARelationSIOBlock(name) ; }

};


static ExampleWithARelationSIOBlock _dummyExampleWithARelationSIOBlock ;

} // namespace ex42

#endif
