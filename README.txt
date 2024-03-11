Notes:
- Signal in C is basically notification from an application telling us something has happened
- Ctrl c for example sends unix signal to terminate process
- To create a signal in C we use
	- kill() function
	- int kill(pid_t pid, int sig);
		- allows a process to send a specified signal to another process identified by its process ID (PID)
		- PID represents the proces ID of the target process
		- sig specifies the signal to be sent
