#include <sio/block.h>
#include <sio/version.h>
#include <sio/io_device.h>

#include "ExampleMCCollection.h"

namespace posio{
  class ICollectionProvider ;
}

class ExampleMCBlock: public sio::block{
  
public:
  
  ExampleMCBlock() :
    sio::block( "ExampleMC",
		sio::version::encode_version(0, 1) ){
  }
  
  // Read the particle data from the device
  virtual void read( sio::read_device &device,
	     sio::version_type vers ) override ;
  
  // Write the particle data to the device
  virtual void write( sio::write_device &device ) override ;
  

  void setCollection(ExampleMCCollection* col) { _col = col ; }
  void setCollectionProvider(podio::ICollectionProvider* iCP ){ _store = iCP ; } 
  
private:
  
  ExampleMCCollection*  _col{} ;
  podio::ICollectionProvider* _store{} ;
};
