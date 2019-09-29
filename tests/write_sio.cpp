// -- sio headers
#include <sio/definitions.h>
#include <sio/exception.h>
#include <sio/api.h>

// podio specific includes
#include "podio/EventStore.h"

#include "EventInfoBlock.h"
#include "ExampleMCBlock.h"
#include "ExampleWithVectorMemberBlock.h"

/**
 *  This example illustrate how to write a simple data structure.
 *  The sio block writing function is available in sioexamples/blocks.h 
 */
int main( int argc, char **argv ) {
  
  // place the whole code in a try-catch block.
  // sio provides an exception class (sio::exception)
  try {
    // the .sio extension is not important here.
    // it just helps in identiying the file name clearly in these examples
    const std::string fname = (argc > 1) ? argv[1] : "particle.sio" ;
    
    // Open a stream for writing.
    // sio::ofstream is a simple typedef of a standard std file stream.
    // Nevertheless, we are dealing with binary data, you need to open 
    // it with the appropriate mode  
    sio::ofstream stream ;
    stream.open( fname , std::ios::binary ) ;
    if( not stream.is_open() ) {
      // These macros catch the line, current file name and function
      // in which the exception is thrown, and throw an exception
      // with code and message
      SIO_THROW( sio::error_code::not_open, "Couldn't open output stream '" + fname + "'" ) ;
    }

    
    auto store = podio::EventStore();
//    auto writer = podio::ASCIIWriter("example.txt", &store);
    
    /// SIO write data in records, formed of a list of blocks.
    /// This example illustrates how to create a simple block
    /// containing a simple data structure, a particle.
    /// We first create our particle block and add it to the list
    sio::block_list blocks {} ;

 
    auto& info = store.create<EventInfoCollection>("info");
    const podio::CollectionBase* evtColB = nullptr ;
    store.get("info" , evtColB );
    auto evtBlk = BlockFactory::instance().createBlock( evtColB, "info") ;
    blocks.push_back(evtBlk) ;

    auto& mcpCol = store.create<ExampleMCCollection>("mcparticle");
    const podio::CollectionBase* mcpColB = nullptr ;
    store.get("mcparticle" , mcpColB );
    auto mcpBlk = BlockFactory::instance().createBlock( mcpColB, "mcparticle") ; 
    blocks.push_back(mcpBlk) ;
   

    auto& vecCol = store.create<ExampleWithVectorMemberCollection>("vectormember");
    const podio::CollectionBase* vecColB = nullptr ;
    store.get( "vectormember",vecColB );
    auto vecBlk = BlockFactory::instance().createBlock( vecColB, "vectormember") ; 
    blocks.push_back(vecBlk) ;


    for(int i=0 ; i < 4 ; ++i){  // loop over events

      //--------- add some data ---------------
      
      info.create( i ) ;

      for(int j=0;j<42;++j){

	auto mcp =  ExampleMC(  1.+i*j , j+i  ) ;
	mcpCol.push_back( mcp ) ;
	
	if( j>0 )
	  mcp.adddaughters( mcpCol[ j-1 ] ) ;
      }

      auto vec = ExampleWithVectorMember();
      vec.addcount(i);
      vec.addcount(i+10);
      vecCol.push_back(vec);
      auto vec1 = ExampleWithVectorMember();
      vec1.addcount(i+1);
      vec1.addcount(i+11);
      vec1.addcount(i+12);
      vecCol.push_back(vec1);


      /// The record is first written in a buffer before being written 
      /// in a file. Let's create a buffer that will hold our record data.
      /// The buffer constructor requires a initial buffer size. Let's 
      /// give something reasonable there ...
      sio::buffer buf( sio::mbyte ) ;
      
      /// We can write our record there. The first argument is the record name.
      /// You can write multiple times a record with the same name if you wish.
      /// The returned strcture contains information on the record you've just 
      /// written in the buffer 
      auto rec_info = sio::api::write_record( "event_record", buf, blocks, 0 ) ;
      
      /// The record is ready to be written in the file !
      sio::api::write_record( stream, buf.span(), rec_info ) ;
      
      info.clear() ;
      mcpCol.clear() ;
      vecCol.clear() ;
    }


  /// A bit of cleanup and we are done !
    stream.close() ;
  }
  catch( sio::exception &e ) {
    std::cout << "Caught sio exception :\n" << e.what() << std::endl ;
  }
  
  return 0 ;
}
