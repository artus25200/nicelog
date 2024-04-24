#ifndef NICELOG_H_
#define NICELOG_H_

#define TRACE(fmt, ...)                                                        \
  NL_log_output(NL_TRACE, __FILE__, __LINE__, fmt, ##__VA_ARGS__)
#define DEBUG(fmt, ...)                                                        \
  NL_log_output(NL_DEBUG, __FILE__, __LINE__, fmt, ##__VA_ARGS__)
#define INFO(fmt, ...)                                                         \
  NL_log_output(NL_INFO, __FILE__, __LINE__, fmt, ##__VA_ARGS__)
#define WARN(fmt, ...)                                                         \
  NL_log_output(NL_WARN, __FILE__, __LINE__, fmt, ##__VA_ARGS__)
#define ERROR(fmt, ...)                                                        \
  NL_log_output(NL_ERROR, __FILE__, __LINE__, fmt, ##__VA_ARGS__)
#define FATAL(fmt, ...)                                                        \
  NL_log_output(NL_FATAL, __FILE__, __LINE__, fmt, ##__VA_ARGS__)

#define BEGIN(text) NL_phase_begin(text)
#define DONE(info) NL_phase_done(info)

#define NL_RESET "\033[0m"
#define NL_BLACK "\033[30m"              /* Black */
#define NL_RED "\033[31m"                /* Red */
#define NL_GREEN "\033[32m"              /* Green */
#define NL_YELLOW "\033[33m"             /* Yellow */
#define NL_BLUE "\033[34m"               /* Blue */
#define NL_MAGENTA "\033[35m"            /* Magenta */
#define NL_CYAN "\033[36m"               /* Cyan */
#define NL_WHITE "\033[37m"              /* White */
#define NL_BOLDBLACK "\033[1m\033[30m"   /* Bold Black */
#define NL_BOLDRED "\033[1m\033[31m"     /* Bold Red */
#define NL_BOLDGREEN "\033[1m\033[32m"   /* Bold Green */
#define NL_BOLDYELLOW "\033[1m\033[33m"  /* Bold Yellow */
#define NL_BOLDBLUE "\033[1m\033[34m"    /* Bold Blue */
#define NL_BOLDMAGENTA "\033[1m\033[35m" /* Bold Magenta */
#define NL_BOLDCYAN "\033[1m\033[36m"    /* Bold Cyan */
#define NL_BOLDWHITE "\033[1m\033[37m"   /* Bold White */

enum LogLevel {
  NL_ALL = 0,
  NL_TRACE,
  NL_DEBUG,
  NL_INFO,
  NL_WARN,
  NL_ERROR,
  NL_FATAL,
  NL_NONE,
  NL_ENUM_LOG_LEVEL_COUNT
};

enum StageInfo { NL_OK, NL_SKIPPED, NL_ABORTED, NL_ENUM_STAGE_INFO_COUNT };

void NL_set_app_name(char *name);

void NL_set_log_level(unsigned int logLevel);
void NL_log_output(unsigned int logLevel, char *file, unsigned int line,
                   const char *fmt, ...);

void NL_phase_begin(char *stage);
void NL_phase_done(unsigned int info);

/*    ┌─[Initializing app]
 *    │  [WARN] Hello World! 1+2 = 3
 *    │  [ERROR] Unknown Error !
 *    │
 *    │  ┌─[Trying something]
 *    │  │  [INFO] OK.
 *    │  └DONE
 *    │
 *    │  [FATAL] Unknown fatal error ! Exiting...
 *    └ABORTED
 */
#endif // NICELOG_H_
