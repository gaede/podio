#ifndef EventInfoBlock_H
#define EventInfoBlock_H

#include "podio/SIOBlock.h"

#include <sio/api.h>
#include <sio/version.h>
#include <sio/io_device.h>
#include "EventInfoCollection.h"

#include  <typeindex>



class EventInfoBlock: public podio::SIOBlock{
  
public:
  
  
  EventInfoBlock() :
    SIOBlock( "EventInfo", sio::version::encode_version(0, 1) ){
///    podio::SIOBlockFactory::instance().registerBlockForCollection( std::type_index(typeid(EventInfoCollection)), this) ;
  }
  
  EventInfoBlock(const std::string &nam ) :
    SIOBlock( nam+std::string("__EventInfoXXX"), sio::version::encode_version(0, 1) ){
  }
  
  // Read the particle data from the device
  virtual void read( sio::read_device &device,
		     sio::version_type vers ) override ;
  
  // Write the particle data to the device
  virtual void write( sio::write_device &device ) override ;
  
  SIOBlock* const create(const std::string name) override { return new EventInfoBlock(name) ; }

};


static EventInfoBlock _dummyEventInfoBlock ;

#endif
