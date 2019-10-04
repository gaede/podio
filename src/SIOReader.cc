#include <sio/compression/zlib.h>

// podio specific includes
#include "podio/SIOReader.h"

#include "podio/CollectionIDTable.h"
#include "podio/CollectionBase.h"

namespace podio {


  CollectionBase* SIOReader::readCollection(const std::string& name) {
    
    //  here we return only collections allready read form the file in readEvent()
    
    auto p = std::find_if(begin(m_inputs), end(m_inputs),
			  [name](SIOReader::Input t){ return t.second == name;});
    
    return ( p != end(m_inputs) ?  p->first : nullptr ) ;
  }
  

  void SIOReader::openFile(const std::string& filename){
    m_stream.open( filename , std::ios::binary ) ;

    m_metaDataBlock = new SIOMetaDataBlock( "meta_data" , sio::version::encode_version(0, 1) ) ;
 }


  void SIOReader::closeFile(){
    m_stream.close() ;
  }

  void SIOReader::readMetaData(){

    m_info_buffer.clear() ;
    m_rec_buffer.clear() ;
    sio::record_info rec_info ;

    sio::api::read_record_info( m_stream, rec_info, m_info_buffer ) ;
    sio::api::read_record_data( m_stream, rec_info, m_rec_buffer ) ;

    sio::block_list blocks {} ;
    blocks.push_back( std::shared_ptr<sio::block>( m_metaDataBlock ) ) ;

    sio::api::read_blocks( m_rec_buffer.span( 0, rec_info._data_length ), blocks ) ;

    
    std::cout << " read meta data: \n" ;
    for(auto& mb :  m_metaDataBlock->m_vec ){
      std::string name = mb.name ;
      std::string typeName = mb.typeName ;
      int id = mb.colID; 

      std::cout << "\t " << id << ", " << name  << ", " << typeName << "\n" ; 


      

    }

    
  }

  void SIOReader::readEvent(){
  
    if( ! m_metaData ){
      readMetaData() ;
      m_metaData = true ;
    }

    sio::record_info rec_info ;
    sio::api::read_record_info( m_stream, rec_info, m_info_buffer ) ;
    sio::api::read_record_data( m_stream, rec_info, m_rec_buffer ) ;

    m_unc_buffer.resize( rec_info._uncompressed_length ) ;
    sio::zlib_compression compressor ;
    compressor.uncompress( m_rec_buffer.span(), m_unc_buffer ) ;

    sio::api::read_blocks( m_unc_buffer.span(), m_blocks ) ;

    for( auto bl : m_blocks ){ // creates the object layer
      static_cast<SIOBlock*>(bl.get())->prepareAfterRead();
    }
    for( auto bl : m_blocks ){  // resolves the references
      static_cast<SIOBlock*>(bl.get())->setReferences();
    }
  }

  bool SIOReader::isValid() const {
    return m_stream.good()  ;
  }

  SIOReader::~SIOReader() {
    // delete all collections
    // at the moment it is done in the EventStore;
    // TODO: who deletes the buffers?
  }

// void SIOReader::endOfEvent() {
//   ++m_eventNumber;
//   m_inputs.clear();
// }


} //namespace
