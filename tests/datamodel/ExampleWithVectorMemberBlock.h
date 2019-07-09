#include <sio/block.h>
#include <sio/version.h>
#include <sio/io_device.h>

#include "ExampleWithVectorMemberCollection.h"

namespace posio{
  class ICollectionProvider ;
}

class ExampleWithVectorMemberBlock: public sio::block{
  
public:
  
  ExampleWithVectorMemberBlock() :
    sio::block( "ExampleWithVectorMember",
		sio::version::encode_version(0, 1) ){
  }
  
  // Read the particle data from the device
  virtual void read( sio::read_device &device,
	     sio::version_type vers ) override ;
  
  // Write the particle data to the device
  virtual void write( sio::write_device &device ) override ;
  

  void setCollection(ExampleWithVectorMemberCollection* col) { _col = col ; }
  void setCollectionProvider(podio::ICollectionProvider* iCP ){ _store = iCP ; } 
  
private:
  
  ExampleWithVectorMemberCollection*  _col{} ;
  podio::ICollectionProvider* _store{} ;
};
