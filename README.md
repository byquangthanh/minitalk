# Minitalk

Minitalk is a simple communication program in C that demonstrates signal handling and inter-process communication. This project is part of the 42 School curriculum, designed to teach students the basics of networking and process management in Unix-like systems.

## Overview

The objective of Minitalk is to code a small data exchange program using UNIX signals. This project consists of a server and a client. The server must be launched first, and after being launched, it must display its PID. The client will take two parameters:
1. The server PID.
2. The string that should be sent.

## Key Features

- **Signal Handling:** Implements communication using UNIX signals.
- **Server-Client Architecture:** Includes a server program that listens for messages and a client program that sends messages to the server.
- **Custom Communication Protocol:** Utilizes a simple protocol to manage the communication between client and server.

## Getting Started

### Installation

Clone the Minitalk repository:

```bash
git clone https://github.com/yourusername/minitalk.git
```

Compile the server and client:

```bash
cd minitalk
make
```

### Usage

Run the server:

```bash
./server
```

In a separate terminal, send a message from the client:

```bash
./client [server PID] "Your message here"
```

## How does the project work?
1. After writing ./server, PID will be printed
2. We will then use ./client [PID] MSG to send the message to the server process
3. Client process will send signals to the server process by sending SIGUSR1 (bit 0) and SIGUSR2 (bit 1)
4. It will firstly check whether the MSG exists, if it exists it will iterate through each char of the MSG
5. To send a bit from each char we're using bitwise operations to compare each bit of the character with MSG[i] 1<<j
6. If the outcome of the bit operation is 0 we will use Kill(server_pid, SIGUSR2), if its 1 kill(server_pid, SIGUSR1), this will send the signal to our server process
7. G_ack_received will then be 0 and the client.c process will pause itself
8. After a bit is sent server.c will send a SIGUSR2 signal to our client.c process in order to let the client.c process know that the bit was received, and client.c can work on another bit
9. After server.c receives 8 bits it will write out a char one by one. 

## Contributing

Your contributions are welcome! Whether you find a bug, have an enhancement suggestion, or want to contribute code, follow these steps:

- Fork the repository.
- Create a new branch for your changes.
- Commit your improvements.
- Push your branch and create a pull request.

## Support

If you encounter any problems or have questions, feel free to open an issue on the GitHub repository.
