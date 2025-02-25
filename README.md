# UNIX & TCP Socket Communication

This project consists of four C programs that demonstrate inter-process communication using both UNIX domain sockets and TCP sockets. The programs implement a simple client-server model where a client can send messages to a server, and the server responds accordingly.

---

## **1. UNIX Domain Sockets**

### **Files:**
- `unix_client.c`  (UNIX socket client)
- `unix_server.c`  (UNIX socket server)

### **Description:**
The UNIX domain socket programs allow local inter-process communication (IPC) within the same system using a socket file (`/tmp/unix_socket`).

### **How It Works:**
- The **server** creates a UNIX domain socket and waits for a client connection.
- The **client** connects to the server using the same socket file path.
- Messages are exchanged between the client and the server.
- The session terminates when the client sends "exit".

### **Compilation & Execution:**
#### **Step 1: Compile the Programs**
```sh
gcc unix_server.c -o unix_server
gcc unix_client.c -o unix_client
```

#### **Step 2: Run the Server**
```sh
./unix_server
```

#### **Step 3: Run the Client**
```sh
./unix_client
```

#### **Step 4: Communication**
Type messages in the client terminal and see responses from the server.

---

## **2. TCP Sockets**

### **Files:**
- `tcp_client.c`  (TCP client)
- `tcp_server.c`  (TCP server)

### **Description:**
The TCP socket programs allow network-based communication between a client and a server using an IP address (`127.0.0.1`) and a port (`3256`).

### **How It Works:**
- The **server** binds to `127.0.0.1:3256`, listens for connections, and waits for a client.
- The **client** connects to the server over the network using the same IP and port.
- Messages are exchanged between the client and the server.
- The session terminates when the client sends "exit".

### **Compilation & Execution:**
#### **Step 1: Compile the Programs**
```sh
gcc tcp_server.c -o tcp_server
gcc tcp_client.c -o tcp_client
```

#### **Step 2: Run the Server**
```sh
./tcp_server
```

#### **Step 3: Run the Client**
```sh
./tcp_client
```

#### **Step 4: Communication**
Type messages in the client terminal and see responses from the server.

---

## **3. Key Differences between UNIX and TCP Sockets**
| Feature | UNIX Domain Socket | TCP Socket |
|---------|-------------------|------------|
| Communication Scope | Local (Same System) | Network (Local or Remote) |
| Addressing | File Path (`/tmp/unix_socket`) | IP Address (`127.0.0.1`) & Port (`3256`) |
| Speed | Faster (no network overhead) | Slightly slower (network stack involved) |
| Use Case | IPC within a single machine | Communication over a network |

---

## **4. Notes & Considerations**
- The **UNIX socket** implementation requires `unlink(SOCKET_FILE)` before binding to remove an existing socket file.
- The **TCP socket** uses `INADDR_ANY` to allow any local IP address to connect.
- The `exit` command is used to terminate communication.
- Ensure that the **server** is running before starting the **client**.
- Both implementations use a **blocking read/write model**, meaning each message is processed one at a time.

---

## **5. Future Enhancements**
- Implement **multi-client support** for the server.
- Use **non-blocking I/O** for asynchronous communication.
- Add **encryption (TLS/SSL)** for secure network communication.
- Improve the message format using **protocols like JSON**.

---

**Author:** Munindra(23071A3238), Joshita(23071A3256), Swayam Jammula(23071A3256), Nagasresht(23071A3259) 
**Date:** 25-02-2025  


