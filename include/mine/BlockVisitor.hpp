#ifndef MINE_BLOCKVISITOR_HPP_INC
#define MINE_BLOCKVISITOR_HPP_INC

namespace mine
{
  class Block;
  class SoilBlock;
  class BlockVisitor
  {
    public:
      virtual void visit(const SoilBlock &) = 0;
  };
}

#endif
