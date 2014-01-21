#ifndef MINE_CHUNKSTORAGE_HPP_INC
#define MINE_CHUNKSTORAGE_HPP_INC

#include <deque>
#include <mine/goodies.hpp>
#include <mine/Pos.hpp>
#include <mine/Chunk.hpp>

namespace mine
{
  Pos blockToChunk(Pos block);
  Pos blockToChunkRelative(Pos block);

  class Block;
  class ChunkStorage : NonTransferable
  {
    public:
      ChunkStorage();

      /**
       * @param x,y are WORLD-BLOCK coordinates
       * It will load/generate the required chunk. It will block the current thread.
       */
      std::unique_ptr<Block> & getBlockRef(int x, int y);

      /**
       * @param x,y,p are WORLD-CHUNK coordinates.
       */
      bool hasChunk(int x, int y) const;
      bool hasChunk(Pos p) const;

    private:
      void expandToHave(Pos p);
      void expandBack(int diff);
      void expandFront(int diff);

      int m_offset;
      std::array<std::deque<Chunk>, 16> m_chunks;
  };
}

#endif
