#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

void die(const char *message) {
  int errcode = errno;
  fprintf(stderr, "[%d] %s/n", errcode, message);
  abort();
}
