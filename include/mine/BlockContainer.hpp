#ifndef MINE_BLOCKCONTAINER_HPP_INC
#define MINE_BLOCKCONTAINER_HPP_INC

#include <deque>
#include <mine/goodies.hpp>
#include <mine/Chunk.hpp>
#include <mine/BlockType.hpp>
#include <mine/ChunkStorage.hpp>

namespace mine
{
  /**
   *  See doc/BlockContainer.markdown
   */
  class BlockContainer : public NonTransferable
  {
    public:
      BlockContainer();
      void createBlock(BlockType typeId, int x, int y);

      Block* getBlock(int x, int y)
      { return m_chunks.getBlockRef(x, y).get(); }

    private:
      ChunkStorage m_chunks;
  };
}

#endif
