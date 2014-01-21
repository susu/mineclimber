#include "igloo/igloo.h"

using namespace igloo;

class LoggerTestListener : public NullTestListener
{
  public:
    LoggerTestListener()
      : m_out(std::cout)
    {}
    virtual void SpecRunStarting( const ContextBase&, const std::string& name )
    {
      m_out << "  * It " << name << std::endl;
    }
    virtual void ContextRunStarting(const ContextBase& context)
    {
      m_out << "\n# Describe " << context.Name() << std::endl;
    }
    virtual void SpecSucceeded(const ContextBase&, const std::string&)
    {
#if (defined(WIN32) || defined(_WIN32) || defined(__WIN32__))
      m_out << "    [SUCCESS!]" << std::endl;
#else
      m_out << "    \033[1;32m" << "[SUCCESS!]" << "\033[0m" << std::endl;
#endif
    }
  private:
    std::ostream & m_out;
};

template<class T>
bool hasArg( const T& argv, const std::string & needle )
{
  for( auto arg : argv )
  {
    if ( arg == needle ) return true;
  }
  return false;
}

int main(int argc, const char* argv[])
{
  DefaultTestResultsOutput output;
  TestRunner runner(output);

  std::vector<std::string> args(argv, argv+argc);
  LoggerTestListener listener;
  if ( hasArg(args, "--verbose") )
  {
    runner.AddListener(&listener);
  }

  return runner.Run();
}
