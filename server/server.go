package main

import (
	"errors"
	"flag"
	"fmt"
	"io"
	"log"
	"net"
)

func main() {
	port := flag.Int("port", 8081, "Port to listen on")
	flag.Parse()

	addr := net.TCPAddr{IP: net.IPv4(0, 0, 0, 0), Port: *port}
	listener, err := net.ListenTCP("tcp", &addr)
	if err != nil {
		panic(fmt.Sprintf("Error listening on port %d: %s", *port, err))
	}

	defer listener.Close()
	log.Printf("Listening on port %d", *port)

	for {
		conn, err := listener.Accept()
		if err != nil {
			log.Printf("Error accepting connection: %s", err)
			continue
		}

		go handleConnection(conn)
	}
}

func handleConnection(conn net.Conn) {
	defer conn.Close()
	buffer := make([]byte, 1024)

	for {
		n, err := conn.Read(buffer)
		if err != nil && !errors.Is(err, io.EOF) {
			log.Printf("Error reading from connection: %s", err)
		}

		if n == 0 {
			log.Printf("Connection closed")
			break
		}

		log.Printf("Received %d bytes: %s", n, string(buffer[:n]))
	}
}
