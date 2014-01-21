#include <igloo/igloo_alt.h>
#include <mine/ChunkStorage.hpp>

using namespace igloo;

namespace
{
  Describe(blockToChunkFunction)
  {
    It(can_convert_block_coordinates_to_chunk_coordinates)
    {
      using namespace mine;
      AssertThat(blockToChunk(Pos( 0, 0)), Equals(Pos(0, 0)));
      AssertThat(blockToChunk(Pos( 1, 0)), Equals(Pos(0, 0)));
      AssertThat(blockToChunk(Pos( 8, 0)), Equals(Pos(0, 0)));
      AssertThat(blockToChunk(Pos(15, 0)), Equals(Pos(0, 0)));
      AssertThat(blockToChunk(Pos(16, 0)), Equals(Pos(1, 0)));
      AssertThat(blockToChunk(Pos(16, 16)), Equals(Pos(1, 1)));
      AssertThat(blockToChunk(Pos(65, 17)), Equals(Pos(4, 1)));

      AssertThat(blockToChunk(Pos( 0, -1)), Equals(Pos(0, -1)));
      AssertThat(blockToChunk(Pos(-1, -1)), Equals(Pos(-1, -1)));
      AssertThat(blockToChunk(Pos(-1, 19)), Equals(Pos(-1, 1)));
      AssertThat(blockToChunk(Pos(-15, -7)), Equals(Pos(-1, -1)));
      AssertThat(blockToChunk(Pos(-20, -17)), Equals(Pos(-2, -2)));
    }
  };

  Describe(blockToChunkRelativeFun)
  {
    It(can_convert_block_coordinates_to_chunk_relative_coordinates)
    {
      using namespace mine;
      AssertThat(blockToChunkRelative(Pos(  0,  0)), Equals(Pos(0,   0)));
      AssertThat(blockToChunkRelative(Pos(  0,  1)), Equals(Pos(0,   1)));
      AssertThat(blockToChunkRelative(Pos(  0, -1)), Equals(Pos(0,  15)));
      AssertThat(blockToChunkRelative(Pos( -1, -1)), Equals(Pos(15, 15)));
      AssertThat(blockToChunkRelative(Pos(-15,-15)), Equals(Pos(1,   1)));
      AssertThat(blockToChunkRelative(Pos( -2, -1)), Equals(Pos(14, 15)));
      AssertThat(blockToChunkRelative(Pos(-16,  0)), Equals(Pos(0,   0)));
    }
  };

  Describe(AChunkStorage)
  {
    It(can_be_instantiated)
    {
      mine::ChunkStorage storage;
    }

    It(should_load_the_chunk_under_the_requested_block)
    {
      // Arrange
      mine::ChunkStorage storage;

      // Act
      storage.getBlockRef(0, 0);
      storage.getBlockRef(0, -1);
      storage.getBlockRef(20, -20);

      // Assert
      AssertThat(storage.hasChunk(0, 0), Equals(true));
      AssertThat(storage.hasChunk(0, -1), Equals(true));
      AssertThat(storage.hasChunk(1, -1), Equals(true));
    }
  };
}
