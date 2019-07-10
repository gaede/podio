#include "ExampleMCBlock.h"

#include <iostream>

#include <sio/block.h>
#include <sio/version.h>
#include <sio/io_device.h>


void ExampleMCBlock::read( sio::read_device &device,
			   sio::version_type vers ) {


  std::vector<ExampleMCData>* dataVec = static_cast<ExampleMCCollection*>(_col)->_getBuffer() ;

  unsigned size(0) ;

  device.data( size ) ;
  dataVec->resize( size) ;
  unsigned count =  size * sizeof(ExampleMCData) ;
  char* dataPtr = (char*)  &(*dataVec)[0] ;
  device.data( dataPtr , count ) ;
  
  //---- read ref collections -----
  podio::CollRefCollection* refCols = _col->referenceCollections() ;
  for( auto* refC : *refCols ){
    device.data( size ) ;
    refC->resize(size) ;
    count =  size * sizeof(podio::ObjectID) ;
    dataPtr = reinterpret_cast<char*>( &((*refC)[0]));
    device.data( dataPtr , count ) ;
  }

  _col->prepareAfterRead() ;
  if(_store != nullptr ) 
    _col->setReferences( _store ) ;
}
  
// Write the particle data to the device
void ExampleMCBlock::write( sio::write_device &device ){
  
  _col->prepareForWrite() ;

  std::vector<ExampleMCData>* dataVec = static_cast<ExampleMCCollection*>(_col)->_getBuffer() ;

  unsigned size =   dataVec->size() ;
  device.data( size ) ;
  unsigned count =  size * sizeof(ExampleMCData) ;
  char* dataPtr = reinterpret_cast<char*>(  & ( (*dataVec)[0] ) );
  device.data( dataPtr , count ) ;

  //---- write ref collections -----
  podio::CollRefCollection* refCols = _col->referenceCollections() ;
  for( auto* refC : *refCols ){
    size = refC->size() ;
    device.data( size ) ;
    count =  size * sizeof(podio::ObjectID) ;
    dataPtr = reinterpret_cast<char*>(  & ( (*refC)[0] ) );
    device.data( dataPtr , count ) ;
  }


}