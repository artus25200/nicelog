#include "nicelog.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Logger {
  char name[21];
  unsigned int log_level;
  unsigned int show_file_and_line;
};

static Logger nicelog_internal_logger = {
    .name = "NICELOG", .log_level = NL_ALL, .show_file_and_line = 0};

static unsigned int depth = 0;

static const char *log_level_str[] = {"NULL",
                                      "TRACE",
                                      "DEBUG",
                                      "INFO",
                                      (NL_BOLDYELLOW "WARN" NL_RESET),
                                      (NL_BOLDRED "ERROR" NL_RESET),
                                      (NL_BOLDRED "FATAL" NL_RESET),
                                      "NULL"};

static const char *stage_info[] = {(NL_BOLDGREEN "DONE" NL_RESET),
                                   (NL_BOLDYELLOW "SKIPPED" NL_RESET),
                                   (NL_BOLDRED "ABORTED" NL_RESET)};

static unsigned int just_finished_phase = 0;

Logger *NL_create_logger(char *name) {
  Logger *logger = malloc(sizeof(struct Logger));
  NL_set_logger_name(logger, name);
  return logger;
}

void NL_set_logger_name(Logger *logger, char *name) {
  int i = 0;
  int length = strlen(name);
  while (i < 20 && i < length && (logger->name[i] = name[i]) != '\0')
    ++i;
  logger->name[i] = '\0';
}

void NL_reset_logger_name(Logger *logger) { logger->name[0] = '\0'; }

void NL_set_log_level(Logger *logger, unsigned int log_level) {
  logger->log_level = log_level;
}

void NL_log_output(Logger *logger, unsigned int log_level, char *file,
                   unsigned int line, const char *fmt, ...) {
  if (log_level < 1 && log_level > NL_ENUM_LOG_LEVEL_COUNT - 1) {
    WARN(&nicelog_internal_logger, "NiceLog: Unknown log level: %d", log_level);
    return;
  }
  if (logger != NULL && log_level < logger->log_level)
    return; // ignore
  va_list args;
  va_start(args, fmt);

  for (int i = 0; i < depth; ++i)
    printf("│  ");

  if (logger != NULL && logger->name[0] != '\0')
    printf("[%s]", logger->name);
  printf("[%s] ", log_level_str[log_level]);
  if (logger == NULL || logger->show_file_and_line)
    printf("(%s:%d) ", file, line);
  if (log_level == NL_WARN)
    printf(NL_YELLOW);
  else if (log_level > NL_WARN)
    printf(NL_RED);

  vprintf(fmt, args);
  printf(NL_RESET);
  printf("\n");
  just_finished_phase = 0;
}

void NL_phase_begin(char *stage) {
  for (int i = 0; i < depth; ++i)
    printf("│  ");
  if (!just_finished_phase) {
    printf("\n");
    for (int i = 0; i < depth; ++i)
      printf("│  ");
  }
  printf("┌─[" NL_GREEN "%s" NL_RESET "]\n", stage);
  ++depth;
}

void NL_phase_done(unsigned int info) {
  const char *state;
  if (info > NL_ENUM_STAGE_INFO_COUNT) {
    WARN(&nicelog_internal_logger, "Unkown stage state");
    state = "DONE";
  } else {
    state = stage_info[info];
  }
  for (int i = 0; i < depth - 1; ++i)
    printf("│  ");
  printf("└" NL_GREEN "%s\n" NL_RESET, state);
  for (int i = 0; i < depth - 1; ++i)
    printf("│  ");
  printf("\n");
  --depth;
  just_finished_phase = 1;
}

void NL_set_file_and_line(Logger *logger, int enable) {
  logger->show_file_and_line = enable;
}

void NL_test(void) {
  Logger test_logger;
  NL_set_log_level(&test_logger, NL_ALL);
  BEGIN("Initializing app");
  INFO(&test_logger, "Hello World! 1+2 = %d", 1 + 2);
  WARN(&test_logger, "Unknown Error !");
  BEGIN("Trying something");
  ERROR(&test_logger, "Error, skipping");
  DONE(NL_SKIPPED);
  INFO(&test_logger, "OK.");
  DONE(NL_OK);
  BEGIN("initializing module 1");
  INFO(&test_logger, "initialized");
  DONE(NL_OK);
  BEGIN("initializing module 2");
  INFO(&test_logger, "HI");
  FATAL(&test_logger, "Unknown error, exiting...");
  DONE(NL_ABORTED);
}
