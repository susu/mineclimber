#include <mine/BlockContainer.hpp>
#include <mine/SoilBlock.hpp>
#include <mine/Exceptions.hpp>
#include <mine/Enforce.hpp>
#include <mine/Logger.hpp>

using namespace mine;

const static int Y_UPPER_LIMIT = 255;
const static int Y_LOWER_LIMIT = 0;

BlockContainer::BlockContainer()
{
}

void BlockContainer::createBlock(BlockType typeId, int x, int y)
{
  LOG_DEBUG("=-------------> Creating block to pos=", Pos{x,y});
  if (Y_LOWER_LIMIT > y || y > Y_UPPER_LIMIT)
  {
    MINE_RAISE(MineException, "y-position is out of range! It must be " <<
                              Y_LOWER_LIMIT << " <= y <= " << Y_UPPER_LIMIT << "!");
  }
  auto & ref = m_chunks.getBlockRef(x,y);
  if (ref != nullptr)
  {
    MINE_RAISE(MineException, "Position " << (Pos{x,y}) << " is already occupied!");
  }

  switch (typeId)
  {
    case BlockType::Air:
      break;
    case BlockType::Soil:
      ref.reset(new SoilBlock(Pos{x,y}, *this));
      break;
  }
}

