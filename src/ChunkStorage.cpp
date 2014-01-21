#include <mine/ChunkStorage.hpp>
#include <mine/Block.hpp>
#include <mine/Logger.hpp>
#include <mine/Enforce.hpp>

using namespace mine;

const static int Y_OFFSET = 8;

Pos mine::blockToChunk(Pos block)
{
  if (block.x < 0)
    block.x = block.x / 16 - 1;
  else
    block.x /= 16;

  if (block.y < 0)
    block.y = block.y / 16 - 1;
  else
    block.y /= 16;

  return block;
}

Pos mine::blockToChunkRelative(Pos block)
{
  if (block.x < 0)
    block.x = (block.x + 1) % 16 + 15;
  else
    block.x = block.x % 16;

  if (block.y < 0)
    block.y = (block.y + 1) % 16 + 15;
  else
    block.y = block.y % 16;

  return block;
}

ChunkStorage::ChunkStorage()
  : m_offset(-1)
{}

std::unique_ptr<Block> & ChunkStorage::getBlockRef(int x, int y)
{
  Pos p = blockToChunk(Pos(x,y));
  if (!hasChunk(p))
    expandToHave(p);

  auto & chunk = m_chunks[p.y + Y_OFFSET][p.x + m_offset];
  if (!chunk.isInMemory())
    chunk.load();

  return chunk.getRef(blockToChunkRelative(Pos(x,y)));
}

void ChunkStorage::expandToHave(Pos p)
{
  if (0 > (p.x + m_offset))
  {
    // expand beginning with -(x + m_offset)
    expandFront( -(p.x + m_offset) );
  }
  int size = int(m_chunks[p.y + Y_OFFSET].size());
  if ((p.x + m_offset) >= size)
  {
    // expand end with (x + m_offset) - size + 1
    expandBack( (p.x + m_offset) - size + 1 );
  }
}

void ChunkStorage::expandBack(int diff)
{
  ENFORCE(diff < 1024, "Too big expand-request!");
  for(auto & row : m_chunks)
  {
    row.resize(row.size() + diff);
  }
}

void ChunkStorage::expandFront(int diff)
{
  ENFORCE(diff < 1024, "Too big expand-request!");
  for(auto & row : m_chunks)
  {
    for(int i = 0; i < diff; ++i)
      row.emplace_front();
  }
  m_offset += diff;
}

bool ChunkStorage::hasChunk(Pos p) const
{
  return hasChunk(p.x, p.y);
}

bool ChunkStorage::hasChunk(int x, int y) const
{
  return 0 <= (x + m_offset) && (x + m_offset) < int(m_chunks[y + Y_OFFSET].size());
}
