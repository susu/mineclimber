#ifndef MINE_BLOCKCONTAINER_HPP_INC
#define MINE_BLOCKCONTAINER_HPP_INC

#include <deque>
#include <mine/goodies.hpp>
#include <mine/Chunk.hpp>
#include <mine/BlockType.hpp>

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

    private:
      std::unique_ptr<Block>& getRef(int x, int y);
      bool hasChunk(Pos chunk) const;
      void expandToHave(Pos chunk);
      Chunk& getChunk(Pos chunk);

      void expandFront(int size);
      void expandBack(int size);

      int m_zeroOffset; ///< has to be incremented if an element is push_front'ed
                        ///< or decremented if an element pop_front'ed
      std::array<std::deque<Chunk>, 16> m_chunks;
  };
}

#endif
