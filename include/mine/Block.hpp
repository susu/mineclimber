#ifndef MINE_BLOCK_HPP_INC
#define MINE_BLOCK_HPP_INC

#include <mine/Pos.hpp>
#include <mine/BlockVisitor.hpp>

namespace mine
{
  class BlockContainer;
  class Block
  {
    public:
      virtual ~Block() = default;

      /**
       * @param difftime is in millisec.
       */
      virtual void tick(int difftime) = 0;

      virtual void accept(BlockVisitor & visitor) const = 0;

      const Pos & getPos() const
      { return m_pos; }

      Block(Pos pos, BlockContainer & container); // FIXME make it protected

    protected:

      void relocate(Pos newPos);

    // private:
      BlockContainer & m_container;

    private:
      Pos m_pos;
  };

  template<typename T>
  class BlockBase : public Block
  {
    public:
      using Block::Block;

      void accept(BlockVisitor & visitor) const override
      { visitor.visit(dynamic_cast<const T&>(*this)); }
  };
}

#endif
