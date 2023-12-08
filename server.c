#include "server.h"

#include <arpa/inet.h>
#include <errno.h>
#include <netinet/ip.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include "utils.h"

static void handle_request(int connfd) {
  char rbuf[64] = {};

  // read into the 'buffer'
  ssize_t n = read(connfd, rbuf, sizeof(rbuf) - 1);
  if (n < 0) {
    fprintf(stderr, "%s", "failed to read()");
    return;
  }

  printf("client says -> %s\n", rbuf);

  char wbuf[] = "world";
  write(connfd, wbuf, strlen(wbuf));
}

void listen_forever(int fd) {
  while (1) {
    struct sockaddr_in client_addr = {};
    socklen_t socklen = sizeof(client_addr);
    int connfd = accept(fd, (struct sockaddr *)&client_addr, &socklen);
    // if there is an error reading, continue
    if (connfd < 0) {
      continue;
    }

    handle_request(connfd);
    close(connfd);
  }
}

int run_server(int port) {
  int fd = socket(AF_INET, SOCK_STREAM, 0);
  if (fd < 0) {
    die("call to socket() failed!");
  }

  int opt = 1;
  setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

  struct sockaddr_in addr = {};
  addr.sin_family = AF_INET;
  addr.sin_port = ntohs(port);
  addr.sin_addr.s_addr = ntohl(0);
  int rv = bind(fd, (const struct sockaddr *)&addr, sizeof(addr));
  if (rv) {
    die("call to bind() failed");
  }

  rv = listen(fd, SOMAXCONN);
  if (rv) {
    die("call to listen() failed");
  }

  fprintf(stderr, "[info] listening on http://0.0.0.0:%d", port);

  listen_forever(fd);

  return 0;
}
