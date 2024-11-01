# Console Chat Application

A simple console-based chat application implemented in C that allows users to communicate over a network using Hamachi.

## Table of Contents

- [Features](#features)
- [Prerequisites](#prerequisites)
- [Installation](#installation)
- [Usage](#usage)
- [How to Connect Using Hamachi](#how-to-connect-using-hamachi)
- [Example](#example)
- [License](#license)

## Features

- Simple console interface for sending and receiving messages.
- Supports multiple clients connecting to a single server.
- Easy setup using Hamachi for local network connections.

## Prerequisites

Before you begin, ensure you have met the following requirements:

- A C compiler (GCC, Clang, etc.)
- Make (GNU make, MinGW make)
- Hamachi installed and set up on your machine.
- Basic knowledge of using the terminal/command line.

## Installation

1. **Clone the repository:**
   ```bash
   git clone https://github.com/without-eyes/ConsoleChat.git
   cd ConsoleChat
   ```

2. **Use executables:**
   ```bash
   ./server
   ./client
   ```

3. **OR Compile the code:**
   ```bash
   make client
   make server
   ```

## Usage

1. **Start the Server:**
   Open a terminal and run:
   ```bash
   ./server
   ```
   When prompted, enter the Hamachi IP address and port (e.g., 1111).

2. **Start the Client:**
   Open another terminal and run:
   ```bash
   ./client
   ```
   When prompted, enter the username, server's IP address and port (e.g., 1111).

3. **Send Messages:**
    - Type your message and press Enter to send it.
    - Messages from other users will appear in the console.

## How to Connect Using Hamachi

1. **Install Hamachi:**
   Download and install Hamachi from the official website: [Hamachi Download](https://vpn.net/)

2. **Create or Join a Network:**
    - Open Hamachi and create a new network or join an existing one by entering the network ID and password.

3. **Find Your Hamachi IP Address:**
    - Your Hamachi IP address will be displayed in the Hamachi window. Share this IP with other users to allow them to
      connect to your server.

4. **Configure Firewall:**
    - Ensure that your firewall allows incoming connections on the specified port (default: 1111).

## Example

```plaintext
Enter your username(or skip by pressing 'Enter'): without eyes    
Enter IP address: 25.XX.XX.XX  # Replace with the Hamachi IP
Enter port: 1111
Connected!
[without eyes] > hello
[anonymous] > hi, how are you?
```

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.
