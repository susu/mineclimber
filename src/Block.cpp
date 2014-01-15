#include <mine/Block.hpp>
#include <mine/Enforce.hpp>

using namespace mine;

Block::Block(Pos pos, BlockContainer & container)
  : m_container(container)
  , m_pos(pos)
{}

void Block::relocate(Pos )
{
  ENFORCE(false, "Relocation is unsupported!");
}
