#include "ExampleWithStringSIOBlock.h"

#include <iostream>

#include <sio/block.h>
#include <sio/version.h>
#include <sio/io_device.h>


 
namespace podio{
  template <typename devT >
  void handlePODDataSIO( devT &device, ::ExampleWithStringData* data, size_t size) {
    for(unsigned i=0; i<size;++i){
      device.data( data[i].theString);

    }
  }
}




void ExampleWithStringSIOBlock::read( sio::read_device &device,
         sio::version_type vers ) {


  auto* dataVec = static_cast<::ExampleWithStringCollection*>(_col)->_getBuffer() ;

  unsigned size(0) ;

  device.data( size ) ;
  dataVec->resize( size) ;

  podio::handlePODDataSIO( device ,  &(*dataVec)[0], size ) ;
  
 //---- read ref collections -----
  podio::CollRefCollection* refCols = _col->referenceCollections() ;
  for( auto* refC : *refCols ){
    device.data( size ) ;
    refC->resize(size) ;
    podio::handlePODDataSIO( device ,  &((*refC)[0]), size ) ;
  }

  //---- read vector members
  podio::VectorMembersInfo * vecMemInfo = _col->vectorMembers() ;

  
  
}
  
// Write the particle data to the device
void ExampleWithStringSIOBlock::write( sio::write_device &device ){
  
  _col->prepareForWrite() ;

  auto * dataVec = static_cast<::ExampleWithStringCollection*>(_col)->_getBuffer() ;

  unsigned size = dataVec->size() ;
  device.data( size ) ;

  podio::handlePODDataSIO( device ,  &(*dataVec)[0], size ) ;
 
  //---- write ref collections -----
  podio::CollRefCollection* refCols = _col->referenceCollections() ;
  for( auto* refC : *refCols ){
    size = refC->size() ;
    device.data( size ) ;
    podio::handlePODDataSIO( device ,  &((*refC)[0]), size ) ;
  }

  //---- write vector members
  podio::VectorMembersInfo * vecMemInfo = _col->vectorMembers() ;

 

}


