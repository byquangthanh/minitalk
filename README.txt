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

## Contributing

Your contributions are welcome! Whether you find a bug, have an enhancement suggestion, or want to contribute code, follow these steps:

- Fork the repository.
- Create a new branch for your changes.
- Commit your improvements.
- Push your branch and create a pull request.

## Support

If you encounter any problems or have questions, feel free to open an issue on the GitHub repository.
