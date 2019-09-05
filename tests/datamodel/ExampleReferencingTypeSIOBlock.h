// AUTOMATICALLY GENERATED - DO NOT EDIT
#ifndef ExampleReferencingTypeSIOBlock_H
#define ExampleReferencingTypeSIOBlock_H

#include "podio/SIOBlock.h"

#include "ExampleReferencingTypeCollection.h"
#include <sio/api.h>
#include <sio/io_device.h>
#include <sio/version.h>

#include <typeindex>

class ExampleReferencingTypeSIOBlock : public podio::SIOBlock {

public:
  ExampleReferencingTypeSIOBlock()
      : SIOBlock("ExampleReferencingType", sio::version::encode_version(0, 1)) {
    podio::SIOBlockFactory::instance().registerBlockForCollection(
        std::type_index(typeid(::ExampleReferencingTypeCollection)), this);
  }

  ExampleReferencingTypeSIOBlock(const std::string &nam)
      : SIOBlock(nam + std::string("__ExampleReferencingType"),
                 sio::version::encode_version(0, 1)) {}

  // Read the particle data from the device
  virtual void read(sio::read_device &device, sio::version_type vers) override;

  // Write the particle data to the device
  virtual void write(sio::write_device &device) override;

  SIOBlock *const create(const std::string name) override {
    return new ExampleReferencingTypeSIOBlock(name);
  }
};

static ExampleReferencingTypeSIOBlock _dummyExampleReferencingTypeSIOBlock;

#endif
