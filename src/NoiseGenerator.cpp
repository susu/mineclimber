#include <mine/NoiseGenerator.hpp>
#include <random>

using namespace mine;

// 1-D Noise generator based on Stefan Gustavson's Noise1234 class.

static float fade(float t)
{
  return t * t * t * (t * (t * 6 - 15) + 10);
}

// TODO cosine interpolate
static float interpolate(float t, float a, float b)
{
  return a + t * (b - a);
}

static float grad(int hash, float x)
{
  int h = hash & 15;
  float grad = 1.0 + (h & 7);
  if (h & 8) grad = -grad;
  return grad * x;
}

NoiseGenerator::NoiseGenerator(uint32_t seed)
{
  std::mt19937 rng(seed);
  std::uniform_int_distribution<> dist(0, 255);

  for (auto & i : m_permutationTable)
    i = dist(rng);
}

float NoiseGenerator::noise(float x) const
{
  int ix0 = x;
  float fx0 = x - ix0;
  float fx1 = fx0 - 1.0f;
  int ix1 = (ix0 + 1) & 0xff;
  ix0 = ix0 & 0xff;

  float s = fade(fx0);

  float n0 = grad(m_permutationTable[ix0], fx0);
  float n1 = grad(m_permutationTable[ix1], fx1);

  return 0.188f * interpolate(s, n0, n1);
}
