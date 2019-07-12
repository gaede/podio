#include "ExampleWithVectorMemberBlock.h"

#include <iostream>

#include <sio/block.h>
#include <sio/version.h>
#include <sio/io_device.h>

#define VECMEMTYPE0 int


void ExampleWithVectorMemberBlock::read( sio::read_device &device,
			   sio::version_type vers ) {


  auto* dataVec = static_cast<ExampleWithVectorMemberCollection*>(_col)->_getBuffer() ;

  unsigned size(0) ;

  device.data( size ) ;
  dataVec->resize( size) ;
  unsigned count =  size * sizeof(ExampleWithVectorMemberData) ;
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
  //---- read vector members
  podio::VectorMembersInfo * vecMemInfo = _col->vectorMembers() ;
  std::vector<VECMEMTYPE0>* vec0 =  *reinterpret_cast< std::vector<VECMEMTYPE0>** >( vecMemInfo->at(0).second ) ;
  device.data( size ) ;
  vec0->resize(size) ;
  count = size * sizeof(VECMEMTYPE0) ;
  dataPtr = reinterpret_cast<char*>(&((*vec0)[0]));
  device.data( dataPtr , count ) ;

  _col->prepareAfterRead() ;
  if(_store != nullptr ) 
    _col->setReferences( _store ) ;
}
  
// Write the particle data to the device
void ExampleWithVectorMemberBlock::write( sio::write_device &device ){
  
  _col->prepareForWrite() ;

  std::vector<ExampleWithVectorMemberData>* dataVec = static_cast<ExampleWithVectorMemberCollection*>(_col)->_getBuffer() ;

  unsigned size =   dataVec->size() ;
  device.data( size ) ;
  unsigned count =  size * sizeof(ExampleWithVectorMemberData) ;
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
  //---- write vector members
  podio::VectorMembersInfo * vecMemInfo = _col->vectorMembers() ;
  std::vector<VECMEMTYPE0>* vec0 =  *reinterpret_cast< std::vector<VECMEMTYPE0>** >( vecMemInfo->at(0).second ) ;
  size = vec0->size() ;
  device.data( size ) ;
  count = size * sizeof(VECMEMTYPE0) ;
  dataPtr = reinterpret_cast<char*>(&((*vec0)[0]));
  device.data( dataPtr , count ) ;


}
