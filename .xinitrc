#! /bin/sh

export LANG=en_US.UTF-8

xrandr --setprovideroutputsource modesetting NVIDIA-0
xrandr --auto

urxvtd -q -o -f
xautolock -time 45 -locker "slock" &
exec awesome
