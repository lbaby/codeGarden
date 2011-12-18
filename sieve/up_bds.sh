#!/bin/sh
#upload bds files , with file size verification
#version: 1.1 add file missing verification
. ~/.profile > /dev/null 2>&1
target_host='localhost'
ftp_usr='bmc'
ftp_passwd='ztesmart'
#host dir to store uploaded data
host_dir='./'

cur_day=`date +%Y%m%d`

local_dir='/ztesoft/bmc/in'
bak_dir='/ztesoft/bmc/bak'
log_dir='/ztesoft/bmc/log'
log_file=$log_dir/bds'.Upload.'$cur_day.log

up_files="C_I_17_*_A_0.XML"

put_files()
{
	ftp -i -v -n $target_host <<!EOF 
		user $ftp_usr $ftp_passwd
		cd $host_dir
		pwd
		lcd $local_dir
		mput $up_files
		bye
!EOF
}
ls_ftp()
{	
	ftp -i -v -n $target_host <<!EOF 
		user $ftp_usr $ftp_passwd
		cd $host_dir
		lcd $local_dir
		ls -l
		bye
!EOF
}

verify_put()
{
	{
		echo local
		cd $local_dir && ls -l $file | sed -n '/^-/p'  && cd -
		echo remote
		ls_ftp | sed -n '/^-/p' 
	}| awk 'BEGIN{ 
			context ="local";  
			verified="OK"; 
		}
		/^local$/  { context = "local"; }
		/^remote$/ { context = "remote"; }
		/^-/ 	  {
			if(context == "local"){
				fz[$9] = $5;
				fl[$9] = $5;
			}else if( context ==  "remote"){
				if ($9 in fz){
					if($5 != fz[$9]){
						verified="BAD remote file:"$9""$5 ;
						exit;
					}
					fl[$9]= "checked";
				}

			}
		}


	END{ 
		for(f in fz){
			if(fl[f] != "checked"){
				verified="BAD remote file:"f"size"fz[f];
			}
		}

		print verified	;
	}'

}

put_files >> $log_file

vo=$(verify_put)
[ "$vo" = "OK" ] &&cd $local_dir &&  mv  $up_files $bak_dir && cd - && echo put ok :$up_files ||echo $vo >> $log_file 2>&1

