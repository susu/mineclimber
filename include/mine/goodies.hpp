#ifndef MINE_GOODIES_HPP_INC
#define MINE_GOODIES_HPP_INC

#include <type_traits>
#include <string>
#include <set>
#include <sstream>
#include <memory>

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

template<typename T>
std::string flagsetToString(const std::set<T> & flagset)
{
  static_assert(std::is_enum<T>::value == true, "T must be enum!");
  std::ostringstream os;
  os << "{";
  for (auto flag : flagset)
  {
    os << flag << ", ";
  }
  os << "}";
  return std::move(os.str());
}

template<typename T>
auto flagsetToValue(const std::set<T> & flagset) -> typename std::underlying_type<T>::type
{
  typename std::underlying_type<T>::type ret = 0;
  for (auto flag : flagset)
    ret |= to_underlying_cast(flag);
  return ret;
}

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

inline std::string ToUpper(std::string str)
{
  for (char & c : str)
  {
    c = toupper(c);
  }
  return str;
}

class MakeString
{
  public:
    MakeString()
    {}

    template<typename T>
    MakeString& operator<<(const T& value)
    {
      m_out << value;
      return *this;
    }

    operator std::string() const
    {
      return m_out.str();
    }
  private:
    std::ostringstream m_out;

};

namespace std
{
  template<typename T, typename... Args>
  std::unique_ptr<T> make_unique(Args&&... args)
  {
    static_assert(std::is_array<T>::value == false,
                  "This version of make_unique cannot be applied to arrays");
    return std::unique_ptr<T>(new T(std::forward<Args&&>(args)...));
  }
}

#endif
