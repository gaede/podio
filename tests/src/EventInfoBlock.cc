#include "EventInfoBlock.h"
#include <iostream>

#include <sio/block.h>
#include <sio/version.h>
#include <sio/io_device.h>


void EventInfoBlock::read( sio::read_device &device,
			   sio::version_type vers ) {


  std::vector<EventInfoData>* dataVec = _col->_getBuffer() ;

  unsigned size(0) ;

  device.data( size ) ;

  dataVec->resize( size) ;

   unsigned count =  size * sizeof(EventInfoData) ;
   char* dataPtr = (char*)  &(*dataVec)[0] ;
   device.data( dataPtr , count ) ;

   _col->prepareAfterRead() ;
}
  
// Write the particle data to the device
void EventInfoBlock::write( sio::write_device &device ){
  
  _col->prepareForWrite() ;

  std::vector<EventInfoData>* dataVec = _col->_getBuffer() ;

  unsigned size =   dataVec->size() ;

  device.data( size ) ;

  unsigned count =  size * sizeof(EventInfoData) ;

  char* dataPtr = reinterpret_cast<char*>(  & ( (*dataVec)[0] ) );

  device.data( dataPtr , count ) ;

}
