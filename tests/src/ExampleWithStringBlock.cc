#include "ExampleWithStringBlock.h"

#include <iostream>

#include <sio/block.h>
#include <sio/version.h>
#include <sio/io_device.h>



namespace {
  // for non POD data we have to copy the data structure's elements individually
  template <typename devT>
  void handleNonPODData( ExampleWithStringData* data, devT &device , size_t size) {

    for(unsigned i=0; i<size;++i){
      device.data( data[i].theString ) ;
    }
  }
}

namespace podio{
  template <typename devT >
  void handlePODDataSIO( devT &device , ExampleWithStringData* data, size_t size) {
    for(unsigned i=0; i<size;++i){
      device.data( data[i].theString ) ;
    }
  }
}


void ExampleWithStringBlock::read( sio::read_device &device,
			   sio::version_type vers ) {


  auto* dataVec = static_cast<ExampleWithStringCollection*>(_col)->_getBuffer() ;

  unsigned size(0) ;
  unsigned count(0) ;

  device.data( size ) ;
  dataVec->resize( size) ;

  //::handleNonPODData( &(*dataVec)[0] , device, size ) ;
  podio::handlePODDataSIO( device ,  &(*dataVec)[0], size ) ;
 
  //---- read ref collections -----
  podio::CollRefCollection* refCols = _col->referenceCollections() ;
  for( auto* refC : *refCols ){
    device.data( size ) ;
    refC->resize(size) ;
    podio::handlePODDataSIO( device ,  &((*refC)[0]), size ) ;
  }

  _col->prepareAfterRead() ;
  if(_store != nullptr ) 
    _col->setReferences( _store ) ;
}
  
// Write the particle data to the device
void ExampleWithStringBlock::write( sio::write_device &device ){
  
  _col->prepareForWrite() ;

  auto * dataVec = static_cast<ExampleWithStringCollection*>(_col)->_getBuffer() ;

  unsigned size =   dataVec->size() ;
  device.data( size ) ;

//  ::handleNonPODData( &(*dataVec)[0] , device, size ) ;
  podio::handlePODDataSIO( device ,  &(*dataVec)[0], size ) ;

  //---- write ref collections -----
  podio::CollRefCollection* refCols = _col->referenceCollections() ;
  for( auto* refC : *refCols ){
    size = refC->size() ;
    device.data( size ) ;
    podio::handlePODDataSIO( device ,  &((*refC)[0]), size ) ;
  }


}
