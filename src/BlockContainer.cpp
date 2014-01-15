#include <mine/BlockContainer.hpp>
#include <mine/SoilBlock.hpp>
#include <mine/Exceptions.hpp>
#include <mine/Enforce.hpp>
#include <mine/Logger.hpp>

using namespace mine;

const static int Y_UPPER_LIMIT = 255;
const static int Y_LOWER_LIMIT = 0;

static Pos getChunkPos(int x, int y)
{
  return { x / CHUNK_SIZE, y / CHUNK_SIZE };
}

BlockContainer::BlockContainer()
  : m_zeroOffset(-1)
{
  expandFront(1);
}

void BlockContainer::createBlock(BlockType typeId, int x, int y)
{
  LOG_DEBUG("Creating block to pos=", Pos{x,y});
  if (Y_LOWER_LIMIT > y || y > Y_UPPER_LIMIT)
  {
    MINE_RAISE(MineException, "y-position is out of range! It must be " <<
                              Y_LOWER_LIMIT << " <= y <= " << Y_UPPER_LIMIT << "!");
  }
  auto & ref = getRef(x,y);
  if (ref != nullptr)
  {
    MINE_RAISE(MineException, "Position " << (Pos{x,y}) << " is already occupied!");
  }

  std::unique_ptr<Block> block;
  switch (typeId)
  {
    case BlockType::Air:
      break;
    case BlockType::Soil:
      block.reset(new SoilBlock(Pos{x,y}, *this));
      break;
  }
}

std::unique_ptr<Block> & BlockContainer::getRef(int x, int y)
{
  Pos chunkPos = getChunkPos(x, y);
  LOG_DEBUG("chunkpos: ", chunkPos);

  // if we dont have the required chunk
  if (!hasChunk(chunkPos))
    expandToHave(chunkPos); ///< expand our storage to have the required chunk
  // "Having a chunk" does not mean that we already have the blocks in memory.

  Chunk & chunk = getChunk(chunkPos);
  if (!chunk.isInMemory())
    chunk.load();

  return chunk.getRef(x % CHUNK_SIZE, y % CHUNK_SIZE);
}

bool BlockContainer::hasChunk(Pos chunk) const
{
  LOG_DEBUG("hasChunk? x=",chunk.x, " zero-offset=", m_zeroOffset);
  int size = m_chunks[0].size();

  LOG_DEBUG("Q: ", chunk.x, " >= ", -m_zeroOffset, " && ", chunk.x, " < ", size-m_zeroOffset);
  if (chunk.x >= -m_zeroOffset && chunk.x < size-m_zeroOffset)
    return true;
  return false;
}

void BlockContainer::expandToHave(Pos chunk)
{
  int size = m_chunks[0].size();

  LOG_DEBUG("Expanding chunk to have x=",chunk.x,", whereas we have ", -m_zeroOffset, ":", size-m_zeroOffset-1);
  ENFORCE(!hasChunk(chunk), "We have the chunk" << chunk);
  // we need x=(chunk.x - m_zeroOffset)
  if (chunk.x - m_zeroOffset < 0)
  {
    LOG_DEBUG("1st: ", chunk.x - m_zeroOffset, " < ", 0);
    expandFront(m_zeroOffset - chunk.x);
  }
  else // if (chunk.x -m_zeroOffset > size)
  {
    LOG_DEBUG("2nd: ", chunk.x - m_zeroOffset, " > ", size);
    expandBack((chunk.x - m_zeroOffset) - size);
  }
  ENFORCE(hasChunk(chunk), "Fatal error: expandToHave is buggy!");
}

Chunk& BlockContainer::getChunk(Pos chunk)
{
  ENFORCE(hasChunk(chunk), "We don't have chunk: " << chunk);
  return m_chunks[chunk.y][chunk.x - m_zeroOffset];
}


void BlockContainer::expandFront(int size)
{
  for (auto & deq : m_chunks)
  {
    for (int i = 0; i < size; ++i)
      deq.emplace_front();
  }
  ++m_zeroOffset;
}

void BlockContainer::expandBack(int size)
{
  for (auto & deq : m_chunks)
  {
    for (int i = 0; i < size; ++i)
      deq.emplace_back();
  }
}
