#!/bin/bash

fs=ext2

if [ x$1 == xvfat ]; then
   fs=vfat

elif [ x$1 == xext2 ]; then
   fs=ext2

elif [ x$1 == xreiserfs ]; then
   fs=reiserfs
   journal_size=2048

elif [ x$1 == xreiser4 ]; then
   fs=reiser4
   journal_size=2048

elif [ x$1 == xext3 ]; then
   fs=ext3
elif [ x$1 == xext4 ]; then
   fs=ext4
elif [ x$1 == x ]; then
   echo Us: $0 '<filesystem-type>'
   echo "                        tests the disk with the filesystem type provided"
   exit 1
else
   echo "filesystem" $1 "not supported in this test"
   exit 1
fi

if [ x`id -u` != x0 ]; then
   echo "your UID is `id -u`(`id -u --name`)..."
   echo "please use ***sudo*** or execute $0 as ***root***"
   exit 1
fi

# if we are ***root*** we can add /sbin:/usr/sbin to the PATH
PATH=/sbin:/usr/sbin:$PATH

echo "** using $fs filesystem *******"

if [[ `lsmod | grep myblkdrv` ]]; then
   echo "** Module myblkdrv is correctly loaded *******"
else
   echo "** Loading module myblkdrv *******"
   insmod myblkdrv.ko
fi



if [ -d /mnt/point ]; then

   success=0;

   echo "** creating $fs filesystem *******" && sleep 1 &&
   if [ x$fs == xreiser4 ]; then
       mkfs -t $fs -f -s $journal_size /dev/xrd1
   elif [ x$fs == xreiserfs ]; then
       mkfs -t $fs -s $journal_size /dev/xrd1
   else 
       mkfs -t $fs /dev/xrd1 
   fi &&
   sleep 1 && echo "** checking $fs filesystem *******" && sleep 1 &&
   fsck -t $fs /dev/xrd1 &&
   sleep 1 && echo "** mounting device *******" && sleep 1 &&
   mount /dev/xrd1 /mnt/point &&
   sleep 1 && echo "** copying files *******" && sleep 1 &&
   tar cf - . | (cd /mnt/point; tar  xf -; exit 0) &&
   sleep 1 && echo "** verifying files *******" && sleep 1 &&
   for i in `ls`; do echo "  ** comparing $i *******"; cmp $i /mnt/point/$i; done &&
   sleep 1 && echo "** unmounting device *******" && sleep 1 &&
   umount /mnt/point && success=1
   if [ x$success == x1 ]; then
      echo "Test   SUCCESSFUL!!"
   else
      echo "Test UNSUCCESSFUL!!!!"!
   fi
else
   echo "Please create an empty directory /mnt/point"
fi

