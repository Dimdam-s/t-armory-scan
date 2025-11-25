# t-armory-scan

This project is an implementation of a basic network reconnaissance tool written in C. It performs a synchronous TCP port scan to identify active services on a target machine. It is compatible with both **Windows** and **Linux**.

DXP – Recon

# Purpose and Mechanism

The tool is designed to probe the system port range (0 to 1024) using a simple sequence:
`socket` → `connect` → `close`

| Technical Function | Critical Role |
| :--- | :--- |
| **Timeout Handling** | The scanner uses `setsockopt` (`SO_RCVTIMEO` / `SO_SNDTIMEO`) to enforce a maximum timeout of 2 seconds. This is essential to avoid indefinite blocking on filtered (silent drop) or unresponsive ports. |
| **State Verification** | The port status is determined by the return value of `connect()` (0 = open, -1 = closed/error). |
| **Endianness** | Uses `htons()` to ensure proper conversion of port numbers from host byte order to network byte order. |

# Compilation

## Windows

### MinGW (GCC)
```bash
gcc recon.c -o recon.exe -lws2_32
```

### Visual Studio (MSVC)
```cmd
cl recon.c
```

## Linux
```bash
gcc recon.c -o recon
```

# Usage

Run the executable followed by the target IP address:

```bash
# Windows
./recon.exe 127.0.0.1

# Linux
./recon 127.0.0.1
```
