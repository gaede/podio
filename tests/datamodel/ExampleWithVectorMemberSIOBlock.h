//AUTOMATICALLY GENERATED - DO NOT EDIT
#ifndef ExampleWithVectorMemberSIOBlock_H
#define ExampleWithVectorMemberSIOBlock_H

#include "podio/SIOBlock.h"

#include <sio/api.h>
#include <sio/version.h>
#include <sio/io_device.h>
#include "ExampleWithVectorMemberCollection.h"

#include  <typeindex>




class ExampleWithVectorMemberSIOBlock: public podio::SIOBlock{
  
public:
  
  
  ExampleWithVectorMemberSIOBlock() :
    SIOBlock( "ExampleWithVectorMember", sio::version::encode_version(0, 1) ){
    podio::SIOBlockFactory::instance().registerBlockForCollection( std::string("ExampleWithVectorMember"), this) ;
  }
  
  ExampleWithVectorMemberSIOBlock(const std::string &nam ) :
    //SIOBlock( nam+std::string("__ExampleWithVectorMember"), sio::version::encode_version(0, 1) ){
    SIOBlock(nam , sio::version::encode_version(0, 1) ){
  }
  
  // Read the particle data from the device
  virtual void read( sio::read_device &device,
         sio::version_type vers ) override ;
  
  // Write the particle data to the device
  virtual void write( sio::write_device &device ) override ;
  
  virtual  void createCollection() override {
    setCollection(  new ExampleWithVectorMemberCollection ) ;
  }

  SIOBlock* const create(const std::string name) override { return new ExampleWithVectorMemberSIOBlock(name) ; }

};


static ExampleWithVectorMemberSIOBlock _dummyExampleWithVectorMemberSIOBlock ;



#endif
