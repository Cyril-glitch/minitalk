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
* **String Transmission**: The client takes the server PID and a string as parameters to send the data.
* **Bonus - Acknowledgement**: The server acknowledges each received bit by sending a signal back to the client, ensuring perfect synchronization.
* **Bonus - Unicode Support**: Full support for UTF-8 and Unicode characters, allowing the transmission of complex symbols and emojis.

---

<br />

## 3. Resources & Technical Choices
The implementation of Minitalk follows specific logic to ensure speed and reliability despite the limitations of UNIX signals:

---

<br />

### 🧠 Global Data Management
* **Justified Global Variable**: As authorized by the subject, one global variable is used per program to handle signal contexts.
* **Centralized Structure**: Instead of using static variables, a global structure is used on the server side to store and reconstruct the character bits, ensuring data persistence between signal interruptions.
* **State Preservation**: This architecture allows the server to keep track of the current bit index and the byte being formed without losing information during asynchronous signal reception.

---

<br />

### 📡 Signal Handling & Synchronization
* **sigaction Implementation**: We opted for `sigaction` over `signal` to access the `sa_sigaction` flags, which are necessary to retrieve the sender's PID for the bonus acknowledgement.
* **Binary Acknowledgement**: To prevent signal loss (as Linux does not queue identical pending signals), the client waits for a confirmation signal from the server before sending the next bit.
* **Efficient Waiting**: The server utilizes `pause()` to remain in a low-power state until a signal is received, optimizing CPU usage.

---

<br />

### 🏗️ Robustness and Error Handling
* **Error Management**: The programs are designed to handle invalid PIDs and incorrect arguments thoroughly to prevent unexpected exits.
* **Memory Integrity**: The project is written in C and follows the Norm, ensuring that all allocated memory is properly managed and no leaks occur.

---

<br />

### 📜 Authorized Functions
This project is built using a restricted set of system calls: `write`, `ft_printf`, `signal`, `sigaction`, `kill`, `getpid`, `malloc`, `free`, `pause`, `sleep`, `usleep`, and `exit`.

---

<br />

## 💻 How to Compile and Run
The project includes a Makefile with all mandatory rules and a `bonus` rule:

---

<br />

```bash
# Clone the repository
git clone [https://github.com/cycolonn/minitalk.git](https://github.com/cycolonn/minitalk.git)

# Compile the project with bonuses
cd minitalk
make bonus

# 1. Start the server
./server

# 2. In another terminal, run the client (replace PID with the one displayed)
./client [SERVER_PID] "Hello World! 🚀"
