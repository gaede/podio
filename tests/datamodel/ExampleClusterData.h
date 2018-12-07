#ifndef ExampleClusterDATA_H
#define ExampleClusterDATA_H

#include <type_traits>

/** @class ExampleClusterData
 *  Cluster
 *  @author: B. Hegner
 */

class ExampleClusterData {
public:
  double energy; ///< cluster energy
  unsigned int Hits_begin;
  unsigned int Hits_end;
  unsigned int Clusters_begin;
  unsigned int Clusters_end;
};

static_assert(
    std::is_trivially_copyable<ExampleClusterData>::value,
    "Please check your definition of ExampleCluster in the yaml file.");

#endif
