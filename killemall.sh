ps -e | grep $1 | grep -v grep | awk '{print "kill", $1}' | sh
