// AUTOMATICALLY GENERATED - DO NOT EDIT
#ifndef ExampleHitSIOBlock_H
#define ExampleHitSIOBlock_H

#include "podio/SIOBlock.h"

#include "ExampleHitCollection.h"
#include <sio/api.h>
#include <sio/io_device.h>
#include <sio/version.h>

#include <typeindex>

class ExampleHitSIOBlock : public podio::SIOBlock {

public:
  ExampleHitSIOBlock()
      : SIOBlock("ExampleHit", sio::version::encode_version(0, 1)) {
    podio::SIOBlockFactory::instance().registerBlockForCollection(
        std::string("ExampleHit"), this);
  }

  ExampleHitSIOBlock(const std::string &nam)
      : // SIOBlock( nam+std::string("__ExampleHit"),
        // sio::version::encode_version(0, 1) ){
        SIOBlock(nam, sio::version::encode_version(0, 1)) {}

  // Read the particle data from the device
  virtual void read(sio::read_device &device, sio::version_type vers) override;

  // Write the particle data to the device
  virtual void write(sio::write_device &device) override;

  virtual void createCollection() override {
    setCollection(new ExampleHitCollection);
  }

  SIOBlock *const create(const std::string name) override {
    return new ExampleHitSIOBlock(name);
  }
};

static ExampleHitSIOBlock _dummyExampleHitSIOBlock;

#endif
