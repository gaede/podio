
// SIO specifc includes
#include "sio/block.h"

// podio specific includes
#include "podio/CollectionBase.h"
#include "podio/EventStore.h"
#include "podio/SIOWriter.h"
#include "podio/SIOBlock.h"

namespace podio {

  SIOWriter::SIOWriter(const std::string& filename, EventStore* store) :
    m_filename(filename),
    m_store(store) {

    m_stream.open( filename , std::ios::binary ) ;

    if( not m_stream.is_open() ){
      SIO_THROW( sio::error_code::not_open, "Couldn't open output stream '" + filename + "'" ) ;
    }

  }

  SIOWriter::~SIOWriter(){
  }

  void SIOWriter::writeEvent(){

    m_buffer.clear() ;
    
    for (auto& coll : m_storedCollections){
      coll->prepareForWrite();
    }
    // write the record to the sio buffer
    auto rec_info = sio::api::write_record( "event_record", m_buffer, m_blocks, 0 ) ;

    /// and now write record to the file !
    sio::api::write_record( m_stream, m_buffer.span(), rec_info ) ;

  }

  void SIOWriter::finish(){
    // now we want to safe the metadata
    // m_metadatatree->Branch("CollectionIDs",m_store->getCollectionIDTable());
    // m_metadatatree->Fill();
    // m_file->Write();

    m_stream.close() ;
  }

  void SIOWriter::registerForWrite(const std::string& name){

    const podio::CollectionBase* colB(nullptr) ;
    m_store->get( name , colB );

    if( !colB ){
      throw std::runtime_error( std::string("no such collection to write: ")+name ) ;
    }
    auto blk = podio::SIOBlockFactory::instance().createBlock( colB, name ) ;

    if( !blk ){
      std::string typName = podio::demangleClassName( colB ) ;
      throw std::runtime_error( std::string("could not create SIOBlock for type: ")+typName ) ;
    }
    m_blocks.push_back(blk) ;
  }   

} // namespace
