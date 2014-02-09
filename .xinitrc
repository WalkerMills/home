#! /bin/sh

export LANG=en_US.UTF-8

urxvtd -q -o -f
xautolock -time 45 -locker "slock" &
exec awesome
