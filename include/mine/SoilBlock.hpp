#ifndef MINE_SOILBLOCK_HPP_INC
#define MINE_SOILBLOCK_HPP_INC

#include <mine/Block.hpp>

namespace mine
{
  class SoilBlock : public BlockBase<SoilBlock>
  {
    public:
      using BlockBase::BlockBase;

      void tick(int difftime) override;

      void print(std::ostream & out) const override;

    private:
  };
}

#endif
