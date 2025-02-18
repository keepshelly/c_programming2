#!/bin/bash
echo "Информация о процессоре:"
cat /proc/cpuinfo | grep "model name" | uniq
cat /proc/cpuinfo | grep "cpu MHz" | uniq
./test134.c