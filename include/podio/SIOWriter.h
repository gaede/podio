#ifndef SIOWRITER_H
#define SIOWRITER_H

#include "podio/CollectionBase.h"
#include "podio/EventStore.h"

#include <string>
#include <vector>
#include <iostream>

// SIO specific includes
#include <sio/definitions.h>
#include <sio/exception.h>
#include <sio/api.h>


// forward declarations


namespace podio {
  class Registry;

  class SIOWriter {

  public:
    SIOWriter(const std::string& filename, EventStore* store);
    ~SIOWriter();

    void registerForWrite(const std::string& name);
    void writeEvent();
    void finish();

  private:
    // members
    std::string m_filename{};
    EventStore* m_store=nullptr;

    sio::ofstream m_stream{} ;
    sio::block_list  m_blocks {} ;
    sio::buffer m_buffer{ sio::mbyte } ;
 
    std::vector<CollectionBase*> m_storedCollections{};
  };

} //namespace
#endif
