#!/bin/bash

#
# free-port.sh - returns an unused TCP port. 
#
PORT_START=4500
PORT_MAX=65000
port=${PORT_START}

while [ TRUE ] 
do
  portsinuse=`ss -tln | cut -c 36- | cut -d ' ' -f 1 | grep -E '[0-9]+' | sort -n | uniq | tr "\n" " "`

  echo "${portsinuse}" | grep -wq "${port}"
  if [ "$?" == "0" ]; then
    if [ $port -eq ${PORT_MAX} ]
    then
      exit -1
    fi
    port=`expr ${port} + 1`
  else
    echo $port
    exit 0
  fi
done
