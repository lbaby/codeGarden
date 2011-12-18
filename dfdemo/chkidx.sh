#!/bin/sh
if [ $# -ne 3 ] ; then
	echo USAGE:
	echo $0 old_index_dir new_index_dir tmp_dir
	exit 0
fi

#program's limitation for parallel jobs
plimit=10
dfdemo=dfdemo
#program's base dir for dfdemo
progdir=`echo $0 | sed s':[^/]*$::'`

#program's example count
n=0
#make the same subdir
#and do the index check
for subdir in `ls $1`
do
	mkdir -p $3/$subdir
	for f in `ls $1/$subdir/`
	do
		#find if new index exist in the old one
		cat $2/$subdir/$f | \
		$progdir/$dfdemo $1/$subdir/$f \
		> $3/$subdir/$f &
		n=`ps -ef | grep "$progdir/$dfdemo"\
			 | grep -v grep | wc -l`
		while [ $n -gt $plimit ] 
		do
			n=`ps -ef | grep "$progdir/$dfdemo"\
			 | grep -v grep | wc -l`
			sleep 1
		done
		
	done
done



