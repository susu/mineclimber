#include <mine/SoilBlock.hpp>
#include <mine/BlockContainer.hpp>
#include <mine/Logger.hpp>

using namespace mine;

void SoilBlock::tick(int difftime)
{
  LOG_DEBUG("SoilBlock, difftime=", difftime);
}

void SoilBlock::print(std::ostream & out) const
{
  out << "SoilBlock";
}
