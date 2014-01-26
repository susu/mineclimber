#ifndef MINE_NOISEGENERATOR_HPP_INC
#define MINE_NOISEGENERATOR_HPP_INC

#include <array>
#include <cstdint>

namespace mine
{
  /**
   * 1-D Noise generator based on Stefan Gustavson's Noise1234 class.
   */
  class NoiseGenerator
  {
    public:
      /// seed: for the random generator
      NoiseGenerator(uint32_t seed);

      float noise(float x) const;

    private:
      std::array<int, 256> m_permutationTable;
  };
}

#endif
