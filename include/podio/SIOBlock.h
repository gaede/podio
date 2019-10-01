#ifndef SIOBlock_H
#define SIOBlock_H

#include <sio/block.h>

#include <podio/CollectionBase.h>

#include <map>
#include <string>


namespace podio {

  template <typename devT, typename PODData>
  void handlePODDataSIO( devT &device , PODData* data, size_t size) {

    unsigned count =  size * sizeof(PODData) ;
    char* dataPtr = reinterpret_cast<char*> (data) ;
    device.data( dataPtr , count ) ;
  }



/// Base class for sio::block handlers used with PODIO
  class SIOBlock: public sio::block{
  
  public:
  
  
    SIOBlock( const std::string &nam, sio::version_type vers) :
      sio::block( nam, vers ){
    }
  
    void setCollection(podio::CollectionBase* col) { _col = col ; }
    void setCollectionProvider(podio::ICollectionProvider* iCP ){ _store = iCP ; }

    void prepareAfterRead(){ _col->prepareAfterRead(); }

    void setReferences(){
      if(_store != nullptr)
	_col->setReferences(_store);
    }

    virtual SIOBlock* const create(const std::string name)=0 ;
  
  protected:
  
    podio::CollectionBase*  _col{} ;
    podio::ICollectionProvider* _store{} ;

  };


  typedef std::map<std::string,SIOBlock*> BlockMap ;

/// factory for creating sio::blocks for a given type of EDM-collection
  class SIOBlockFactory{
  private:
    SIOBlockFactory(){};
    BlockMap  _map ;
  public:
    void registerBlockForCollection(std::string type, SIOBlock* b){_map[type] = b ; }

    std::shared_ptr<SIOBlock> createBlock( const podio::CollectionBase* col, std::string name){
      std::string typeStr =  col->getValueTypeName() ;

      auto it=_map.find(typeStr) ;
    
      if( it!= _map.end() ){
	SIOBlock* blk= it->second->create( name ) ;
	blk->setCollection( const_cast< podio::CollectionBase* > ( col ) ) ;
	return  std::shared_ptr<SIOBlock>( blk ) ;
      }else{
	return nullptr;
      }
    }

    static SIOBlockFactory& instance() {
      static SIOBlockFactory me ;
      return me ;
    }
  } ;

/// helper method for class name demangling 
  inline std::string demangleClassName(std::string rawName){
    std::string className( rawName );
    size_t  pos = className.find_first_not_of("0123456789");
    className.erase(0,pos);
    // demangling the namespace: due to namespace additional characters were introduced:
    // e.g. N3fcc18TrackHit
    // remove any number+char before the namespace:
    pos = className.find_first_of("0123456789");
    if (pos != std::string::npos) {
      size_t pos1 = className.find_first_not_of("0123456789", pos);
      className.erase(0, pos1);
    }
    // replace any numbers between namespace and class with "::"
    pos = className.find_first_of("0123456789");
    if (pos != std::string::npos) {
      size_t pos1 = className.find_first_not_of("0123456789", pos);
      className.replace(pos, pos1-pos, "::");
    }
    return className ;
  }

  template <class T>
  std::string demangleClassName(const T* t){
    return ( typeid(*(t)).name() );
  }

} // end namespace
#endif
