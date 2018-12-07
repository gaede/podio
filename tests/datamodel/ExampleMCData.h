#ifndef ExampleMCDATA_H
#define ExampleMCDATA_H

#include <type_traits>

/** @class ExampleMCData
 *  Example MC-particle
 *  @author: F.Gaede
 */

class ExampleMCData {
public:
  double energy; ///< energy
  int PDG;       ///< PDG code
  unsigned int parents_begin;
  unsigned int parents_end;
  unsigned int daughters_begin;
  unsigned int daughters_end;
};

static_assert(std::is_trivially_copyable<ExampleMCData>::value,
              "Please check your definition of ExampleMC in the yaml file.");

#endif
