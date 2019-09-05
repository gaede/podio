// AUTOMATICALLY GENERATED - DO NOT EDIT
#ifndef ExampleWithARelationSIOBlock_H
#define ExampleWithARelationSIOBlock_H

#include "podio/SIOBlock.h"

#include "ExampleWithARelationCollection.h"
#include <sio/api.h>
#include <sio/io_device.h>
#include <sio/version.h>

#include <typeindex>

namespace ex {

class ExampleWithARelationSIOBlock : public podio::SIOBlock {

public:
  ExampleWithARelationSIOBlock()
      : SIOBlock("ExampleWithARelation", sio::version::encode_version(0, 1)) {
    podio::SIOBlockFactory::instance().registerBlockForCollection(
        std::type_index(typeid(ex::ExampleWithARelationCollection)), this);
  }

  ExampleWithARelationSIOBlock(const std::string &nam)
      : SIOBlock(nam + std::string("__ExampleWithARelation"),
                 sio::version::encode_version(0, 1)) {}

  // Read the particle data from the device
  virtual void read(sio::read_device &device, sio::version_type vers) override;

  // Write the particle data to the device
  virtual void write(sio::write_device &device) override;

  SIOBlock *const create(const std::string name) override {
    return new ExampleWithARelationSIOBlock(name);
  }
};

static ExampleWithARelationSIOBlock _dummyExampleWithARelationSIOBlock;

} // namespace ex

#endif
