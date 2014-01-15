#ifndef MINE_CHUNK_HPP_INC
#define MINE_CHUNK_HPP_INC

#include <memory>
#include <vector>
#include <mine/Block.hpp>
#include <mine/goodies.hpp>

namespace mine
{
  constexpr int CHUNK_SIZE = 16;
  class Chunk : NonTransferable
  {
    public:
      Chunk();

      bool isInMemory() const;
      void load();

      std::unique_ptr<Block> & getRef(int i, int j)
      { return m_blocks[ j * CHUNK_SIZE + i ]; }
    private:
      /**
       *  (i,j) coord. is chunk-dependent.
       */
      Block& get(int i, int j)
      { return *getRef(i,j); }

      const Block& get(int i, int j) const;

      std::vector< std::unique_ptr<Block> > m_blocks;
  };
}

#endif
