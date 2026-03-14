*This project has been created as part of the 42 curriculum by cycolonn.*

# 📞 Minitalk - Technical Documentation

## 1. Description
**Minitalk** is a small data exchange program designed to explore the mechanics of UNIX signals. The goal is to establish a communication protocol between a client and a server using only bitwise transmission. This project deepens the understanding of process synchronization and inter-process communication (IPC) in a restricted environment.

---

<br />

## 2. Technical Instructions & Features
The project consists of two executable programs, `client` and `server`, implementing the following requirements:

---

<br />

* **Signal-Based Communication**: Data is transmitted exclusively using `SIGUSR1` and `SIGUSR2` signals.
* **PID Identification**: Upon launch, the server displays its Process ID (PID) to allow the client to target it.
* **String Transmission**: The client converts a given string into binary and sends it bit by bit to the server.
* **Bonus - Acknowledgement**: The server sends a signal back to the client to acknowledge the receipt of every message, ensuring synchronized transmission.
* **Bonus - Unicode Support**: Full support for UTF-8 characters, allowing the transmission of complex symbols and emojis.

---

<br />

## 3. Resources & Technical Choices
The implementation of Minitalk follows specific logic to ensure speed and reliability despite the limitations of UNIX signals:

---

<br />

### 🧠 Bit-Shifting Protocol
* **Bitwise Operations**: Each character (8 bits) is processed using bitwise operators (`>>` and `&`). The client sends one signal for a '0' and another for a '1'.
* **Static Reconstruction**: The server uses a static variable to reconstruct characters bit by bit. Once 8 bits are received, the character is printed immediately to ensure high performance.
* **Zero-Delay Printing**: To meet the subject's speed requirements, the server avoids buffering strings and prints characters as soon as they are fully reconstructed.

---

<br />

### 📡 Signal Handling & Synchronization
* **sigaction Implementation**: We opted for `sigaction` over `signal` to access advanced features like `sa_sigaction`, which provides the PID of the signal sender (essential for the bonus acknowledgement).
* **Binary Acknowledgement**: For the bonus, the client pauses and waits for a confirmation signal from the server before sending the next bit. This prevents signal loss on Linux systems where signals are not queued.
* **Pause & Sleep**: The server uses `pause()` to wait for signals efficiently, minimizing CPU usage while inactive.

---

<br />

### 🏗️ Robustness and Error Handling
* **Error Management**: The programs handle invalid PIDs, incorrect numbers of arguments, and transmission failures without crashing.
* **Memory Integrity**: The project is written in C and follows the Norm. All heap-allocated memory is properly managed to ensure a total absence of memory leaks.

---

<br />

### 📜 Authorized Functions
This project uses a specific set of system calls for process and signal management: `write`, `ft_printf`, `signal`, `sigaction`, `kill`, `getpid`, `pause`, and `usleep`.

---

<br />

## 💻 How to Compile and Run
The project includes a Makefile with a `bonus` rule to enable acknowledgement and Unicode support:

---

<br />

```bash
# Clone the repository
git clone [https://github.com/cycolonn/minitalk.git](https://github.com/cycolonn/minitalk.git)

# Compile the mandatory and bonus parts
cd minitalk
make bonus

# 1. Start the server
./server

# 2. In another terminal, run the client (replace PID with the one displayed)
./client [SERVER_PID] "Hello World! 🚀"
