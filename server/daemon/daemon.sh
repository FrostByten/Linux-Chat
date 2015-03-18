#!/bin/bash
#
# Daemon Name: thowis_scallentire_chat_d
#
# chkconfig: - 58 74
# description: Controls Thowis Scallentire Chat

# Programmer: Lewis Scott

# Include for 'daemon', 'killproc' and 'status'
. /etc/init.d/functions

# Include for '#NETWORKING'
. /etc/sysconfig/myconfig

prog=thowis_scallentire_chat
lockfile=/var/lock/subsys/$prog

start()
{
	# Check for networking capabilities
	[ "$NETWORKING" = "no" ] && exit 1
	[ -x /usr/sbin/$prog ] || exit 5
	
	echo -n $"Starting $prog: "
	
	# Start program as daeomn
	daemon -pidfile /var/run/${proc}.pid $prog
	RETVAL=$?
	echo
	
	# Touch the lockfile
	[ $RETVAL -eq 0 ] && touch $lockfile
	return $RETVAL
}

stop()
{
	echo -n $"Shutting down $prog: "
	
	# Kill the daemon
	killproc $prog
	RETVAL=$?
	echo
	
	# Remove the lockfile
	[ $RETVAL -eq 0 ] && rm -f $lockfile
	return $RETVAL
}

case "$1" in
	start)
		start
		;;
	stop)
		stop
		;;
	status)
		status $prog
		;;
	restart)
		stop
		start
		;;
	*)
		echo $"Usage; $0 {start|stop|status|restart}"
		exit 2
esac
