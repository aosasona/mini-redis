#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "server.h"
#include "utils.h"

void print_help() {
  printf(
      "Available arguments:\n\tserver - run the "
      "mini-redis server\n\trepl - run the client as a repl\n");
}

int main(int argc, char *argv[]) {
  if (argc <= 1 || strcmp(argv[1], "help") == 0 || strcmp(argv[1], "h") == 0) {
    print_help();
    return 0;
  }

  if (strcmp(argv[1], "server") == 0) {
    run_server(9800);
  } else {
    printf("Error: no valid argument specified\n");
    print_help();
  }

  return 0;
}
