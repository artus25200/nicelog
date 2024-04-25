# nicelog

A simple and easy to use logging library.

## Example
```c
void NL_test(void) {
  NL_set_log_level(NL_ALL);
  BEGIN("Initializing app");
  INFO("Hello World! 1+2 = %d", 1 + 2);
  WARN("Unknown Error !");
  BEGIN("Trying something");
  ERROR("Error, skipping");
  DONE(NL_SKIPPED);
  INFO("OK.");
  DONE(NL_OK);
  BEGIN("initializing module 1");
  INFO("initialized");
  DONE(NL_OK);
  BEGIN("initializing module 2");
  INFO("HI");
  FATAL("Unknown error, exiting...");
  DONE(NL_ABORTED);
}
```
![image](https://github.com/artus25200/nicelog/assets/68189043/ed9b0e1c-2fad-4205-950c-cc356b9ad9cd)

## Documentation

Read nicelog.h. Every function is documented.

