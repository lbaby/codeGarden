#!/bin/sh
#upload shell for net manager interface translation
. ~/.profile > /dev/null 2>&1

svc_type='gwosend'	
target_host='133.160.22.19'
ftp_usr='hnjs'
ftp_passwd='Child0601!'
#host dir to store uploaded data
host_dir='/opt/mcb/pcs/data/source/nps'

cur_day=`date +%Y%m%d`
cur_hour=`date +%H`
cur_min=`date +%M`
prev_hour=`expr $cur_hour - 1`

#local dir where the file we want to upload be,
#and where the log file should be placed
#modify it with your need 
local_base='/fs2/netnow/gwosend'
local_dir=$local_base'/out/'
bak_dir=$local_base'sendbak'
log_dir=$local_base'sendlog'
log_file=$log_dir/$svc_type'.Upload.'$cur_day.log


#we put the data for previous hour , and current hour's data
#shoud be created on next hour ,so ,do NOT edit the following line ,
#unless the rule of data  creating changed 
up_files="B*.371"
ftp -i -v -n $target_host <<!EOF >>$log_file
	user $ftp_usr $ftp_passwd
	cd $host_dir
	pwd
	lcd $local_dir
	mput $up_files
	bye
!EOF


mv $local_dir/$up_files  $bak_dir

t=`date`
echo $t : ftp upload done >> $log_file

