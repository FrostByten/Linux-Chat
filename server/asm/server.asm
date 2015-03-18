#! ----------------------------------------- !#
#! | Chat server						   | !#
#! | -- Receives text from clients  	   | !#
#! | -- and distributes it to all   	   | !#
#! | -- other clients					   | !#
#! | 							   	       | !#
#! | Design by: Lewis Scott				   | !#
#! | Programming by: Lewis Scott		   | !#
#! |									   | !#
#! | Date: March 10th, 2015				   | !#
#! ----------------------------------------- !#

# Symbols
.equiv port_num, 8088			# the port number to listen on
.equiv buff_size, 4096			# the size of the receive buffer

# Defines
.equiv SOL_SOCKET, 1
.equiv SO_REUSEADDR, 2
.equiv SYS_SETSOCKOPT, 14
.equiv AF_INET, 2
.equiv PF_INET, 2
.equiv SOCK_STREAM 1
.equiv SYS_BIND, 2
.equiv SYS_LISTEN, 4
.equiv SYS_ACCEPT, 5
.equiv STDOUT, 1
.equiv SIGHUP, 1
.equiv PR_SED_PDEATHDIG 1

# Sys-call numbers
.equiv EXIT_CALL, 1
.equiv FORK_CALL, 2
.equiv READ_CALL, 3
.equiv WRITE_CALL, 4
.equiv CLOSE_CALL, 6
.equiv SOCKET_CALL, 102
.equiv SYS_PRCTL_CALL, 172

.bss
	client_socket: .int 0		# holds file descriptor for client socket
.text

# Main macro
.macro server
		.globl _start
		.weak _start			# re-declare weak for debug
	_start:
		.globl main
	main:
		setup
		loop
.endm

# Setup the socket and listen on it
.macro setup
	print_message $loading_msg,$loading_len

	open_socket
	set_reuse
	bind
	listen
	
	print_message $ready_msg,$ready_len
.endm

# The main loop
.macro loop
	begin_loop:
		accept
		print_message $client_msg,$client_len
		fork
.endm

# Open a socket
.macro open_socket
	push_regs
	
	newvar socket_args, .long 2, 1, 0 # PF_INET, SOCK_STREAM
	
	movl $socket_args,%ecx
	movl $1,%ebx 			# SYS_SOCKET
	movl $102,%eax 			# socketcall
	int $0x80				# syscall
	
	check_err
	movl %eax, socket_reg
	
	pop_regs
.endm

# Set the TCP/IP stack to be able to re-use the address we bind the socket to
.macro set_reuse
	push_regs
	
	newvar true, .int 1
	#SOL_SOCKET, SO_REUSEADDR, true, length of socket
	newvar sockopt_args, .long 0, 1, 2, true, 4 # reuse option
	
	movl socket_reg,(sockopt_args) # Append the socket address to the argument list
	
	movl $sockopt_args,%ecx
	movl $14,%ebx				# SYS_SETSOCKOPT
	movl $102,%eax				# socketcall
	int $0x80					# syscall
	
	check_err
	
	pop_regs
.endm

# Bind the socket to the port
.macro bind
	.data
		address:
				 .short 2 							  # AF_INET
				 .byte port_num >> 8, port_num & 0xff # convert byte order
				 .int 0								  # any address
	.text
		push_regs
	
		newvar sockbind_args, .long 0, address, 16 # 16 = sizeof(sockaddr_in)
		
		movl socket_reg,(sockbind_args) # Append the socket address to the argument list
		
		movl $sockbind_args,%ecx
		movl $2,%ebx					 # SYS_BIND
		movl $102,%eax					 # socketcall
		int $0x80						 # systemcall
		
		check_err
	
		pop_regs
.endm

# Listen on the socket
.macro listen
	push_regs
	
	newvar socklisten_args, .long 0, 5 # Max backlog
	
	movl socket_reg,(socklisten_args) # Append the socket address to the argument list
	
	movl $socklisten_args,%ecx
	movl $4,%ebx				# SYS_LISTEN
	movl $102,%eax				# socketcall
	int $0x80					# systemcall
	
	check_err
	
	pop_regs
.endm

# Accept a connection
.macro accept
	.bss
		sockaddr: .fill 16, 1, 0 # 16 = sizeof(sockaddr_in)
		sockaddr_len: .int 0
	.text
		push_regs
		
		newvar accept_args, .long 0, sockaddr, sockaddr_len
		
		movl socket_reg,(accept_args) # Append the socket address to the argument list
		
		movl $accept_args,%ecx
		movl $5,%ebx			# SYS_ACCEPT
		movl $102,%eax			# socketcall
		int $0x80				# systemcall
		
		mov %eax,(client_socket)# Get the returned connection
		
		check_err
		
		pop_regs
.endm

# Fork the process
.macro fork
	movl $2,%eax 	 # fork
	int $0x80		 # systemcall
	
	cmp $0,%eax		
	jg parent		# return value > 0
	jz child		# return value = 0
	check_err		# error, as return value < 0
.endm

# Check the return of a system call for error
.macro check_err
	push_regs
	
	cmp $0,%eax
	jl error_occured				# return value was less than 0? (i.e. -1)
	
	pop_regs
.endm

# Print a message to stdout
.macro print_message message, length
	push_regs # Save the register values
	
	movl \length,%edx
	movl \message,%ecx
	movl $1,%ebx		# stdout
	movl $4,%eax		# write
	int $0x80			# syscall
	
	pop_regs # Restore the register values
.endm

# Exit the program
.macro exit return
	movl $file,%ebx
	movl $6,%eax		# close
	int $0x80			# syscall

	movl \return,%ebx
	movl $1,%eax		# exit
	int $0x80			# syscall
.endm

# Save the registers on the stack
.macro push_regs
	push %edx
	push %ecx
	push %ebx
	push %eax
.endm

# Recover the registers from the stack
.macro pop_regs
	pop %eax
	pop %ebx
	pop %ecx
	pop %edx
.endm

# Create a new allocated variable
.macro newvar var, contents:vararg
	.data
	\var: \contents
	.previous
.endm

# Run the main macro
.text
	server

error_occured:
	print_message $error_msg,$error_len
	exit $1

parent:
	movl (client_socket),%ebx	# parent should close the client socket, as it won't be using it
	movl $6,%eax				# close
	int $0x80					# systemcall
	jmp begin_loop
	
child:
	jmp child_loop
	exit $0
	
child_loop:
	.bss
		buff_pos: .int 0
		buffer: .fill buff_size, 1, 0 # Create a buffer and zero it
	.text
		jmp req_par_kill
	
req_par_kill:
	# tell the kernel to kill the child when the parent dies
	movl $1,%ecx		# SIGHUP
	movl $1,%ebx		# PR_SET_PDEATHSIG
	movl $172,%eax		# SYS_PRCTL
	int $0x80			# systemcall
	
	jmp prepare

prepare:
	# prepare the registers for first time through the loop
	movl (client_socket),socket_reg
	movl $0,(buff_pos)
	
	jmp data_read
		
data_read:
	movl (buff_pos),%ecx
	movl $buff_size-1,%edx
	subl %ecx,%edx					# buffer space left
	addl $buffer,%ecx				# current address
	
	movl socket_reg,%ebx
	movl $3,%eax					# read
	int $0x80						# systemcall
	
	check_err
	cmp $0,%eax
	je handle_data
	
	addl (buff_pos),%eax			# add to the buffer position
	movl %eax,(buff_pos)
	
	jmp data_read

.data
	loading_msg:
		.ascii "Loading server...\n"
		loading_len = . - loading_msg
	error_msg:
		.ascii "An error occured... Exiting!\n"
		error_len = . - error_msg
	ready_msg:
		.ascii "Server ready, listening...\n"
		ready_len = . - ready_msg
	usage_msg:
		.ascii "Usage: ./server {file path}\n"
		usage_len = . - usage_msg
