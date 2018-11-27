#!/bin/bash

cd /usr/src/linux-2.4.18-14custom
make bzImage 2>&1 | tee /root/tmp.log
cd arch/i386/boot
cp bzImage /boot/vmlinuz-2.4.18-14custom
str=`tail -5 /root/tmp.log | grep 'Error'`
echo "$str"
if [ -z $str ]; then
	echo "rebooting"
	reboot
fi
