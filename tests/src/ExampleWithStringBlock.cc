#include "ExampleWithStringBlock.h"

#include <iostream>

#include <sio/block.h>
#include <sio/version.h>
#include <sio/io_device.h>



namespace {
  // for non POD data we have to copy the data srtucture's elements individually
  template <typename devT>
  void handleNonPODData( ExampleWithStringData* data, devT &device , size_t size) {

    for(unsigned i=0; i<size;++i){
      SIO_SDATA( device, data[i].theString ) ;
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

  ::handleNonPODData( &(*dataVec)[0] , device, size ) ;
  
  //---- read ref collections -----
  podio::CollRefCollection* refCols = _col->referenceCollections() ;
  for( auto* refC : *refCols ){
    device.data( size ) ;
    refC->resize(size) ;
    count =  size * sizeof(podio::ObjectID) ;
    char* dataPtr = reinterpret_cast<char*>( &((*refC)[0]));
    device.data( dataPtr , count ) ;
  }

  _col->prepareAfterRead() ;
  if(_store != nullptr ) 
    _col->setReferences( _store ) ;
}
  
// Write the particle data to the device
void ExampleWithStringBlock::write( sio::write_device &device ){
  
  _col->prepareForWrite() ;

  std::vector<ExampleWithStringData>* dataVec = static_cast<ExampleWithStringCollection*>(_col)->_getBuffer() ;

  unsigned size =   dataVec->size() ;
  device.data( size ) ;

  ::handleNonPODData( &(*dataVec)[0] , device, size ) ;


  //---- write ref collections -----
  podio::CollRefCollection* refCols = _col->referenceCollections() ;
  for( auto* refC : *refCols ){
    size = refC->size() ;
    device.data( size ) ;
    unsigned count =  size * sizeof(podio::ObjectID) ;
    char* dataPtr = reinterpret_cast<char*>(  & ( (*refC)[0] ) );
    device.data( dataPtr , count ) ;
  }


}
