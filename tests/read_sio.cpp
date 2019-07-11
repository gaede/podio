// STL
#include <vector>
#include <iostream>
#include <exception>
#include <cassert>

// podio specific includes
#include "podio/EventStore.h"
#include "podio/SIOReader.h"

// test data model
#include "EventInfoCollection.h"
#include "ExampleHitCollection.h"
#include "ExampleClusterCollection.h"
#include "ExampleMCCollection.h"
#include "ExampleReferencingTypeCollection.h"
#include "ExampleWithOneRelationCollection.h"
#include "ExampleWithVectorMemberCollection.h"
#include "ExampleWithComponentCollection.h"
#include "ExampleWithARelationCollection.h"
#include "ExampleWithStringCollection.h"
#include "ExampleWithNamespace.h"
#include "ExampleWithArrayCollection.h"

int glob = 0;

void processEvent(podio::EventStore& store, bool verboser, unsigned eventNum) {

  auto& failing = store.get<ExampleClusterCollection>("notthere");
  if(failing.isValid() == true) {
    throw std::runtime_error("Collection 'notthere' should not be valid");
  };

//not yet  auto& strings = store.get<ExampleWithStringCollection>("strings");
//not yet  if(strings.isValid()){
//not yet    auto string = strings[0];
//not yet    if (string.theString() != "SomeString") {
//not yet      throw std::runtime_error("Couldn't read string properly");
//not yet    }
//not yet  } else {
//not yet    throw std::runtime_error("Collection 'strings' should be present.");
//not yet  }
//not yet
//not yet  auto& clusters = store.get<ExampleClusterCollection>("clusters");
//not yet  if(clusters.isValid()){
//not yet    auto cluster = clusters[0];
//not yet    for (auto i = cluster.Hits_begin(), end = cluster.Hits_end(); i!=end; ++i){
//not yet      std::cout << "  Referenced hit has an energy of " << i->energy() << std::endl;
//not yet      glob++;
//not yet    }
//not yet  } else {
//not yet    throw std::runtime_error("Collection 'clusters' should be present");
//not yet  }


  auto& mcps =  store.get<ExampleMCCollection>("mcparticles");
  if( mcps.isValid() ){
    // check that we can retrieve the correct parent daughter relation
    // set in write.cpp :

    // particle 0 has particles 2,3,4 and 5 as daughters:
    auto p = mcps[0] ;

    //-------- print relations for debugging:
    for( auto p : mcps ){
      std::cout << " particle " << p.getObjectID().index << " has daughters: " ;
      for(auto it = p.daughters_begin(), end = p.daughters_end() ; it!=end ; ++it ){
        std::cout << " " << it->getObjectID().index ;
      }
      std::cout << "  and parents: " ;
      for(auto it = p.parents_begin(), end = p.parents_end() ; it!=end ; ++it ){
        std::cout << " " << it->getObjectID().index ;
      }
      std::cout << std::endl ;
    }

    auto d0 = p.daughters(0) ;
    auto d1 = p.daughters(1) ;
    auto d2 = p.daughters(2) ;
    auto d3 = p.daughters(3) ;

    if( ! ( d0 == mcps[2] ) )  throw std::runtime_error(" error: 1. daughter of particle 0 is not particle 2 ");
    if( ! ( d1 == mcps[3] ) )  throw std::runtime_error(" error: 2. daughter of particle 0 is not particle 3 ");
    if( ! ( d2 == mcps[4] ) )  throw std::runtime_error(" error: 3. daughter of particle 0 is not particle 4 ");
    if( ! ( d3 == mcps[5] ) )  throw std::runtime_error(" error: 4. daughter of particle 0 is not particle 5 ");


    // particle 3 has particles 6,7,8 and 9 as daughters:
    p = mcps[3] ;

    d0 = p.daughters(0) ;
    d1 = p.daughters(1) ;
    d2 = p.daughters(2) ;
    d3 = p.daughters(3) ;

    if( ! ( d0 == mcps[6] ) )  throw std::runtime_error(" error: 1. daughter of particle 3 is not particle 6 ");
    if( ! ( d1 == mcps[7] ) )  throw std::runtime_error(" error: 2. daughter of particle 3 is not particle 7 ");
    if( ! ( d2 == mcps[8] ) )  throw std::runtime_error(" error: 3. daughter of particle 3 is not particle 8 ");
    if( ! ( d3 == mcps[9] ) )  throw std::runtime_error(" error: 4. daughter of particle 3 is not particle 9 ");

  } else {
    throw std::runtime_error("Collection 'mcparticles' should be present");
  }


//not yet  //std::cout << "Fetching collection 'refs'" << std::endl;
//not yet  auto& refs = store.get<ExampleReferencingTypeCollection>("refs");
//not yet  if(refs.isValid()){
//not yet    auto ref = refs[0];
//not yet    for (auto j = ref.Clusters_begin(), end = ref.Clusters_end(); j!=end; ++j){
//not yet      for (auto i = j->Hits_begin(), end = j->Hits_end(); i!=end; ++i){
//not yet        //std::cout << "  Referenced object has an energy of " << i->energy() << std::endl;
//not yet        glob++;
//not yet      }
//not yet    }
//not yet  } else {
//not yet    throw std::runtime_error("Collection 'refs' should be present");
//not yet  }
//not yet  //std::cout << "Fetching collection 'OneRelation'" << std::endl;
//not yet  auto& rels = store.get<ExampleWithOneRelationCollection>("OneRelation");
//not yet  if(rels.isValid()) {
//not yet    //std::cout << "Referenced object has an energy of " << (*rels)[0].cluster().energy() << std::endl;
//not yet    glob++;
//not yet  } else {
//not yet    throw std::runtime_error("Collection 'OneRelation' should be present");
//not yet  }

//  std::cout << "Fetching collection 'WithVectorMember'" << std::endl;
  auto& vecs = store.get<ExampleWithVectorMemberCollection>("WithVectorMember");
  if(vecs.isValid()) {
    std::cout << vecs.size() << std::endl;
    for( auto item : vecs )
      for (auto c = item.count_begin(), end = item.count_end(); c!=end; ++c){
	std::cout << "  Counter value " << (*c) << std::endl;
	glob++;
    }
  } else {
    throw std::runtime_error("Collection 'WithVectorMember' should be present");
  }

//not yet  auto& comps = store.get<ExampleWithComponentCollection>("Component");
//not yet  if (comps.isValid()) {
//not yet    auto comp = comps[0];
//not yet    int a = comp.component().data.x + comp.component().data.z;
//not yet  }
//not yet
//not yet  auto& arrays = store.get<ExampleWithArrayCollection>("arrays");
//not yet  if (arrays.isValid() && arrays.size() != 0) {
//not yet    auto array = arrays[0];
//not yet    if (array.myArray(1) != eventNum) {
//not yet      throw std::runtime_error("Array not properly set.");
//not yet    }
//not yet    if (array.arrayStruct().data.p.at(2) != 2*eventNum) {
//not yet      throw std::runtime_error("Array not properly set.");
//not yet    }
//not yet    if (array.structArray(0).x != eventNum) {
//not yet      throw std::runtime_error("Array of struct not properly set.");
//not yet    }
//not yet  } else {
//not yet    throw std::runtime_error("Collection 'arrays' should be present");
//not yet  }
//not yet
//not yet  auto& nmspaces = store.get<ex::ExampleWithARelationCollection>("WithNamespaceRelation");
//not yet  auto& copies = store.get<ex::ExampleWithARelationCollection>("WithNamespaceRelationCopy");
//not yet  auto& cpytest = store.create<ex::ExampleWithARelationCollection>("TestConstCopy");
//not yet  if (nmspaces.isValid() && copies.isValid()) {
//not yet    for (int j = 0; j < nmspaces.size(); j++) {
//not yet      auto nmsp = nmspaces[j];
//not yet      auto cpy = copies[j];
//not yet      cpytest.push_back(nmsp.clone());
//not yet      if (nmsp.ref().isAvailable()) {
//not yet        if (nmsp.ref().data().x != cpy.ref().data().x || nmsp.ref().data().y != cpy.ref().data().y) {
//not yet          throw std::runtime_error("Copied item has differing data in OneToOne referenced item.");
//not yet        }
//not yet        // check direct accessors of POD sub members
//not yet        if (nmsp.ref().x() != cpy.ref().x()) {
//not yet          throw std::runtime_error("Getting wrong values when using direct accessors for sub members.");
//not yet        }
//not yet        if (nmsp.number() != cpy.number()) {
//not yet          throw std::runtime_error("Copied item has differing member.");
//not yet        }
//not yet        if (!(nmsp.ref().getObjectID() == cpy.ref().getObjectID())) {
//not yet          throw std::runtime_error("Copied item has wrong OneToOne references.");
//not yet        }
//not yet      }
//not yet      auto cpy_it = cpy.refs_begin();
//not yet      for (auto it = nmsp.refs_begin(); it != nmsp.refs_end(); ++it, ++cpy_it) {
//not yet        if (it->data().x != cpy_it->data().x || it->data().y != cpy_it->data().y) {
//not yet          throw std::runtime_error("Copied item has differing data in OneToMany referenced item.");
//not yet        }
//not yet        if (!(it->getObjectID() == cpy_it->getObjectID())) {
//not yet          throw std::runtime_error("Copied item has wrong OneToMany references.");
//not yet        }
//not yet      }
//not yet    }
//not yet  } else {
//not yet    throw std::runtime_error("Collection 'WithNamespaceRelation' and 'WithNamespaceRelationCopy' should be present");
//not yet  }
}

int main(){
//  auto reader = podio::SIOReader();
  podio::SIOReader reader; // SIOReader has no copy c'tor ...
  auto store = podio::EventStore();
  reader.openFile("example.sio");
// do not call this as this expects the meta data table to be read on opening the file
//  store.setReader(&reader);


  // define which collections to read from the file
  // for now this has to be exact same order as used for writing !
  //  -- will be fixed when meta data is also written to sio file ....
  reader.registerCollection<EventInfoCollection>("info",&store);
  reader.registerCollection<ExampleMCCollection>("mcparticles",&store);
  reader.registerCollection<ExampleWithVectorMemberCollection>("WithVectorMember",&store);

  
  unsigned nEvents = 1410065408 ;
  for(unsigned i=0; i<nEvents; ++i) {

    if(i%1000==0)
      std::cout<<"reading event "<<i<<std::endl;

    reader.readEvent() ;

    processEvent(store, true, i);

    // only clear collections for re-use
    store.clearCollections();
    // store.clear(); // this would delete the collections as well ...

  }
  reader.closeFile();
  return 0;
}
