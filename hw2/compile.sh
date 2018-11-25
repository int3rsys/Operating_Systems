#!/bin/bash

cd /usr/src/linux-2.4.18-14custom
make bzImage
cd arch/i386/boot
cp bzImage /boot/vmlinuz-2.4.18-14custom > tmp.log
str=`tail -5 tmp.log | grep '*Error*'`
echo "$str"
if [ -z $str ]; then
	echo "rebooting"
	reboot
fi	




