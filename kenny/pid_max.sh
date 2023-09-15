#!/bin/bash
pid_max=$(cat /proc/sys/kernel/pid_max)
echo "The Maximum PID Value is: $pid_max"
