#include <sio/block.h>
#include <sio/version.h>
#include <sio/io_device.h>

#include "EventInfoCollection.h"


class EventInfoBlock: public sio::block{
  
public:
  
  EventInfoBlock() :
    sio::block( "EventInfo",
		sio::version::encode_version(0, 1) ){
  }
  
  // Read the particle data from the device
  virtual void read( sio::read_device &device,
	     sio::version_type vers ) override ;
  
  // Write the particle data to the device
  virtual void write( sio::write_device &device ) override ;
  

  void setCollection(EventInfoCollection* col) { _col = col ; }

private:
  
  EventInfoCollection*  _col{} ;
  
};
