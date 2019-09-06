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
  }


  void SIOReader::closeFile(){
    m_stream.close() ;
  }



  void SIOReader::readEvent(){
  
    // clear old collections
    //m_inputs.clear() ;

    sio::api::read_record_info( m_stream, m_rec_info, m_info_buffer ) ;
    sio::api::read_record_data( m_stream, m_rec_info, m_rec_buffer ) ;
    sio::api::read_blocks( m_rec_buffer.span( 0, m_rec_info._data_length ), m_blocks ) ;

    for( auto bl : m_blocks ){ // creates the object layer
      static_cast<SIOBlock*>(bl.get())->prepareAfterRead();
    }
    for( auto bl : m_blocks ){  // resolves the references
      static_cast<SIOBlock*>(bl.get())->setReferences();
    }


    // m_inputs.emplace_back(std::make_pair(collection,name));

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
