#ifndef MINE_LOGGER_HPP_INC
#define MINE_LOGGER_HPP_INC

#include <iostream>
#include <fstream>
#include <utility>

#ifdef MINE_DEBUG

#define LOG_DEBUG LOG_MSG(mine::DEBUG)
#define LOG_FINE  LOG_MSG(mine::FINE)

#else

#define LOG_DEBUG(...)
#define LOG_FINE(...)

#endif

#define LOG_MSG(loglevel) \
  mine::Logger::instance().getGuardedStream( \
      mine::LogDetails{\
        (loglevel), __FILE__, __LINE__, __PRETTY_FUNCTION__} )


// errors,warnings,infos always logged
#define LOG_ERROR LOG_MSG(mine::ERROR)
#define LOG_WARNING LOG_MSG(mine::WARNING)
#define LOG_INFO  LOG_MSG(mine::INFO)

#define LOG_EXCEPTION( ex ) \
   LOG_ERROR("Exception ", (ex).getMessage())

namespace mine
{
  class Logger;
  enum LogLevel
  {
    // The following severity levels always compiled into build.
    ERROR,
    WARNING,
    INFO,

    // The following severity levels are not compiled into release build.
    DEBUG,
    FINE
  };
  struct LogDetails
  {
    LogLevel loglevel;
    const char* file;
    int line;
    const char* pretty;
  };

  class StreamGuard
  {
    public:
      StreamGuard(Logger & logger, LogDetails details);
      ~StreamGuard();

      template<typename...Args>
        void operator()(Args&&...args)
        {
          m_logger(m_details, std::forward<Args>(args)...);
        }
    private:
      Logger & m_logger;
      LogDetails m_details;
  };
  class Logger
  {
    public:
      ~Logger();
      static Logger& instance()
      {
        static Logger logger("logger");
        return logger;
      }

      StreamGuard getGuardedStream(LogDetails details)
      {
        return StreamGuard(*this, details);
      }

      template<typename...Args>
        void operator()(LogDetails details, Args&&...args)
        {
          startLog(details.loglevel, details.file, details.line, details.pretty);
          print(std::forward<Args>(args)...);
        }

      void endLog();
    private:
      Logger( const std::string & loggerName );
      Logger(Logger&);

      void startLog( LogLevel loglevel, const char * file, int line,
          const char * pretty);
      std::ostream& getOutputStream()
      { return *m_outputStream; }

      template<typename First,typename...Args>
      void print(First&& first, Args&&...args)
      {
        getOutputStream() << first;
        print(std::forward<Args>(args)...);
      }

      void print()
      {}

      std::ostream * m_outputStream;
  };
}

#endif
