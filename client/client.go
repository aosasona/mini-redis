package main

import (
	"flag"
	"fmt"
	"net"
)

func main() {
	port := flag.String("port", "8081", "Port to listen on")
	flag.Parse()

	conn, err := net.Dial("tcp", fmt.Sprintf("0.0.0.0:%s", *port))
	if err != nil {
		panic(fmt.Sprintf("Error connecting to server: %s", err))
	}
	defer conn.Close()

	err = write(conn, []byte("Hello, server!"))
	if err != nil {
		panic(fmt.Sprintf("Error writing to server: %s", err))
	}

	resp := read(conn)
	fmt.Printf("Received: %s\n", string(resp))
}

func write(conn net.Conn, data []byte) error {
	_, err := conn.Write(data)
	if err != nil {
		return err
	}

	return nil
}

func read(conn net.Conn) []byte {
	buffer := make([]byte, 1024)

	n, err := conn.Read(buffer)
	if err != nil {
		panic(fmt.Sprintf("Error reading from server: %s", err))
	}

	if n == 0 {
		fmt.Println("Connection closed")
		return nil
	}

	return buffer[:n]
}
