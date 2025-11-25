# t-armory-scan

This project is an implementation of a basic network reconnaissance tool written in C System. It performs a synchronous TCP port scan to identify active services on a target machine.

DXP – Recon

# Purpose and Mechanism

The tool is designed to probe the system port range (0 to 1024) using a simple sequence:
socket → connect → close

Technical Function	Critical Role
Timeout Handling	The scanner uses setsockopt (SO_RCVTIMEO / SO_SNDTIMEO) to enforce a maximum timeout of 2 seconds. This is essential to avoid indefinite blocking on filtered (silent drop) or unresponsive ports, a common issue with synchronous TCP connections.
State Verification	The port status is determined by the return value of connect() (0 = open, -1 = closed/error).
Endianness	Uses htons() to ensure proper conversion of port numbers from host byte order to network byte order.
