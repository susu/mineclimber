#ifndef MINE_GOODIES_HPP_INC
#define MINE_GOODIES_HPP_INC

#include <type_traits>

template<typename T>
auto to_underlying_cast(T value) -> typename std::underlying_type<T>::type
{
  return static_cast<typename std::underlying_type<T>::type>(value);
}

template<typename T>
T from_underlying_cast(typename std::underlying_type<T>::type value)
{
  return static_cast<T>(value);
}

/**
 * non-copyable BUT moveable
 */
struct NonCopyable
{
  NonCopyable() = default;
  ~NonCopyable() = default;

  NonCopyable(const NonCopyable&) = delete;
  NonCopyable& operator=(const NonCopyable&) = delete;

  NonCopyable(NonCopyable&&) = default;
  NonCopyable& operator=(NonCopyable&&) = default;
};

/**
 *  non-copyable AND non-moveable either
 */
struct NonTransferable
{
  NonTransferable() = default;
  ~NonTransferable() = default;

  NonTransferable(const NonTransferable&) = delete;
  NonTransferable& operator=(const NonTransferable&) = delete;

  NonTransferable(NonTransferable&&) = delete;
  NonTransferable& operator=(NonTransferable&&) = delete;
};

#endif
