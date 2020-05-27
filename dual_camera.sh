#!/bin/sh

#/etc/init.d/matrix-gui-2.0 stop

#export TSLIB_TSDEVICE=/dev/input/touchscreen0
#export QWS_MOUSE_PROTO=Tslib:/dev/input/touchscreen0

#dual_camera -qws

#/etc/init.d/matrix-gui-2.0 start

/etc/init.d/weston stop
sleep 1

echo 0 > /sys/class/graphics/fbcon/cursor_blink

./dual_camera -platform linuxfb

echo 1 > /sys/class/graphics/fbcon/cursor_blink

/etc/init.d/weston start
sleep 1
