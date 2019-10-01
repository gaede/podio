//AUTOMATICALLY GENERATED - DO NOT EDIT
#ifndef ExampleClusterSIOBlock_H
#define ExampleClusterSIOBlock_H

#include "podio/SIOBlock.h"

#include <sio/api.h>
#include <sio/version.h>
#include <sio/io_device.h>
#include "ExampleClusterCollection.h"

#include  <typeindex>




class ExampleClusterSIOBlock: public podio::SIOBlock{
  
public:
  
  
  ExampleClusterSIOBlock() :
    SIOBlock( "ExampleCluster", sio::version::encode_version(0, 1) ){
    podio::SIOBlockFactory::instance().registerBlockForCollection( std::string("ExampleCluster"), this) ;
  }
  
  ExampleClusterSIOBlock(const std::string &nam ) :
    SIOBlock( nam+std::string("__ExampleCluster"), sio::version::encode_version(0, 1) ){
  }
  
  // Read the particle data from the device
  virtual void read( sio::read_device &device,
         sio::version_type vers ) override ;
  
  // Write the particle data to the device
  virtual void write( sio::write_device &device ) override ;
  
  SIOBlock* const create(const std::string name) override { return new ExampleClusterSIOBlock(name) ; }

};


static ExampleClusterSIOBlock _dummyExampleClusterSIOBlock ;



#endif
