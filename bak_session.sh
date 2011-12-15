#!/bin/sh
day_of_backup=50
max_modify_sec=600  #will backup the file if the time from last modify  larger than  $max_modify_sec 


rpc='ssh zxin10@132.35.98.7'
scp='scp zxin10@132.35.98.7:'

dstdir='/interface/datbak/'
md5dgst='openssl dgst -md5'
dgstdb='/interface/datbak/.session.md5.db'

srcdir='impsys/log/'

gz='gzip -f '
ungz='gzip -cd '

#rpc=cat
rpc_mdiff_time()
{
cat <<EOS | eval  $rpc  2>/dev/null
	 python   -c " 
#Do NOT edit the following indent
import time
import os 
import sys
print str(int(time.time() - os.stat(sys.argv[1]).st_mtime )) + ':' + sys.argv[1] 
" "$1"   2>/dev/null 
EOS
	
}

need_to_backup()
{
	[ $(rpc_mdiff_time $1 | awk -F: '{print $1}' )""   -ge $max_modify_sec ] && echo yes || echo no
}

mk_dgst()
{
	eval $md5dgst "$1" | sed 's/^.*=[[:space:]]*\([0-9a-zA-Z]\{1,\}\)$/\1/'   2>/dev/null
}

need_to_save()
{
	#if a file digest does not exist in db , I need to save it .
	dgst=$(mk_dgst $1)
	[ -f $dgstdb ]  &&  qry=$(     cat "$dgstdb"   |  grep $dgst )  || qry=''
	#echo  $1: db :$qry 1>&2	
	[  ! -z "$qry"  ] && echo no || echo yes 
}

add_db_entry()
{
	{
		[ -f "$dgstdb" ] && cat "$dgstdb" 2>/dev/null
		dgst=$(mk_dgst $1)
		echo $dgst
		[ -z "$dgst" ] || echo $dgst:$1
	}  > $dgstdb.$$
	mv -f $dgstdb.$$ $dgstdb 
}


rebuild_db_entry()
{
	>$dgstdb
	while [ $# -gt 0 ] 
	do
		#echo $1
		add_db_entry $1
		shift 
	done
}

del_db_entry()
{
	
	{
		[ -f "$dgstdb" ] && cat "$dgstdb" | sed  /"$1"/d 2>/dev/null
	} > $dgstdb.$$
	mv -f $dgstdb.$$ $dgstdb 
}

backup_a_file()
{
	# file  dir
	if [  $(need_to_backup $1)  == 'yes' ]  ; then
		midfile=$2/$(date +%Y%m%d%M%S)$(basename $1)
		myscp="$scp$1  $midfile"
		eval $myscp > /dev/null
		echo $myscp	
		#midfile will be delete by gzip

		if [ $(need_to_save $midfile)  == 'yes' ] ; then
			add_db_entry  $midfile   #&& eval $rpc rm "$1"
			eval $gz $midfile  2>/dev/null
			dst=$midfile
			[ $(echo $midfile | sed 's/^.*\(..\)$/\1/'  ) != 'gz' ]  && dst=$dst.gz
			eval $ungz  $dst >/dev/null 2>&1 
			[ $? -eq 0 ] && rm -f $midfile  && eval $rpc rm "$1"  || rm $dst 
			
		else
			#echo dummy
			eval $rpc rm "$1"
		fi

			
	fi	
	
}

del_a_out_of_date()
{
	del_db_entry $(mk_dgst $1)
	rm -f $1
}


for f in $(eval $rpc ls "$srcdir/session_380.log*"   )
do
	backup_a_file  $f $dstdir
done

for f in $(eval $rpc ls "$srcdir/service380.log*" )
do
	backup_a_file  $f $dstdir
done


for f in $(eval $rpc ls "$srcdir/imptrace.old" )
do
	backup_a_file  $f $dstdir
done

#del the file out of date
for f  in $(find $dstdir -name "*.gz" -ctime +$day_of_backup)
do
	del_a_out_of_date $f
done

