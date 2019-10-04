// AUTOMATICALLY GENERATED - DO NOT EDIT
#ifndef ExampleForCyclicDependency2SIOBlock_H
#define ExampleForCyclicDependency2SIOBlock_H

#include "podio/SIOBlock.h"

#include "ExampleForCyclicDependency2Collection.h"
#include <sio/api.h>
#include <sio/io_device.h>
#include <sio/version.h>

#include <typeindex>

class ExampleForCyclicDependency2SIOBlock : public podio::SIOBlock {

public:
  ExampleForCyclicDependency2SIOBlock()
      : SIOBlock("ExampleForCyclicDependency2",
                 sio::version::encode_version(0, 1)) {
    podio::SIOBlockFactory::instance().registerBlockForCollection(
        std::string("ExampleForCyclicDependency2"), this);
  }

  ExampleForCyclicDependency2SIOBlock(const std::string &nam)
      : // SIOBlock( nam+std::string("__ExampleForCyclicDependency2"),
        // sio::version::encode_version(0, 1) ){
        SIOBlock(nam, sio::version::encode_version(0, 1)) {}

  // Read the particle data from the device
  virtual void read(sio::read_device &device, sio::version_type vers) override;

  // Write the particle data to the device
  virtual void write(sio::write_device &device) override;

  virtual void createCollection() override {
    setCollection(new ExampleForCyclicDependency2Collection);
  }

  SIOBlock *const create(const std::string name) override {
    return new ExampleForCyclicDependency2SIOBlock(name);
  }
};

static ExampleForCyclicDependency2SIOBlock
    _dummyExampleForCyclicDependency2SIOBlock;

#endif
