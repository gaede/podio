#include "ExampleWithVectorMemberSIOBlock.h"

#include <iostream>

#include <sio/block.h>
#include <sio/io_device.h>
#include <sio/version.h>

void ExampleWithVectorMemberSIOBlock::read(sio::read_device &device,
                                           sio::version_type vers) {

  auto *dataVec =
      static_cast<::ExampleWithVectorMemberCollection *>(_col)->_getBuffer();

  unsigned size(0);

  device.data(size);
  dataVec->resize(size);

  podio::handlePODDataSIO(device, &(*dataVec)[0], size);

  //---- read ref collections -----
  podio::CollRefCollection *refCols = _col->referenceCollections();
  for (auto *refC : *refCols) {
    device.data(size);
    refC->resize(size);
    podio::handlePODDataSIO(device, &((*refC)[0]), size);
  }

  //---- read vector members
  podio::VectorMembersInfo *vecMemInfo = _col->vectorMembers();

  std::vector<int> *vec0 =
      *reinterpret_cast<std::vector<int> **>(vecMemInfo->at(0).second);
  device.data(size);
  vec0->resize(size);
  podio::handlePODDataSIO(device, &((*vec0)[0]), size);

  // --------------
  _col->prepareAfterRead();
  if (_store != nullptr)
    _col->setReferences(_store);
}

// Write the particle data to the device
void ExampleWithVectorMemberSIOBlock::write(sio::write_device &device) {

  _col->prepareForWrite();

  auto *dataVec =
      static_cast<::ExampleWithVectorMemberCollection *>(_col)->_getBuffer();

  unsigned size = dataVec->size();
  device.data(size);

  podio::handlePODDataSIO(device, &(*dataVec)[0], size);

  //---- write ref collections -----
  podio::CollRefCollection *refCols = _col->referenceCollections();
  for (auto *refC : *refCols) {
    size = refC->size();
    device.data(size);
    podio::handlePODDataSIO(device, &((*refC)[0]), size);
  }

  //---- write vector members
  podio::VectorMembersInfo *vecMemInfo = _col->vectorMembers();

  std::vector<int> *vec0 =
      *reinterpret_cast<std::vector<int> **>(vecMemInfo->at(0).second);
  size = vec0->size();
  device.data(size);
  podio::handlePODDataSIO(device, &((*vec0)[0]), size);
}
