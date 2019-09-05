#ifndef ExampleWithVectorMemberBlock_H
#define ExampleWithVectorMemberBlock_H

#include "podio/SIOBlock.h"

#include <sio/api.h>
#include <sio/version.h>
#include <sio/io_device.h>
#include "ExampleWithVectorMemberCollection.h"

#include  <typeindex>



class ExampleWithVectorMemberBlock: public podio::SIOBlock{
  
public:
  
  
  ExampleWithVectorMemberBlock() :
    SIOBlock( "ExampleWithVectorMember", sio::version::encode_version(0, 1) ){
//    podio::SIOBlockFactory::instance().registerBlockForCollection( std::type_index(typeid(ExampleWithVectorMemberCollection)), this) ;
  }
  
  ExampleWithVectorMemberBlock(const std::string &nam ) :
    SIOBlock( nam+std::string("__ExampleWithVectorMemberXX"), sio::version::encode_version(0, 1) ){
  }
  
  // Read the particle data from the device
  virtual void read( sio::read_device &device,
		     sio::version_type vers ) override ;
  
  // Write the particle data to the device
  virtual void write( sio::write_device &device ) override ;
  
  SIOBlock* const create(const std::string name) override { return new ExampleWithVectorMemberBlock(name) ; }

};


static ExampleWithVectorMemberBlock _dummyExampleWithVectorMemberBlock ;

#endif
