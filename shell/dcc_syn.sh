numseg='python xml2txt.py  NUMSEGRULEREQ.RECORDLIST.NUMSEGRULE   '
numseg_fmt='python fmt.py  NUMSEGRULEREQ.RECORDLIST.NUMSEGRULE  NUMSEGRULEREQ.RECORDLIST.NUMSEGRULE.OPERATESN  NUMSEGRULEREQ.RECORDLIST.NUMSEGRULE.OPERATETYPE  NUMSEGRULEREQ.RECORDLIST.NUMSEGRULE.RULEID  NUMSEGRULEREQ.RECORDLIST.NUMSEGRULE.NUMSEGSTART  NUMSEGRULEREQ.RECORDLIST.NUMSEGRULE.NUMSEGSTOP  NUMSEGRULEREQ.RECORDLIST.NUMSEGRULE.HOMEOCSID  NUMSEGRULEREQ.RECORDLIST.NUMSEGRULE.COMMENTS:O '

ocs='python xml2txt.py  OCSNODESYNCREQ.RECORDLIST.OCSNODEINFO '
ocs_fmt='python fmt.py  OCSNODESYNCREQ.RECORDLIST.OCSNODEINFO  OCSNODESYNCREQ.RECORDLIST.OCSNODEINFO.OPERATESN  
        OCSNODESYNCREQ.RECORDLIST.OCSNODEINFO.OPERATETYPE   OCSNODESYNCREQ.RECORDLIST.OCSNODEINFO.NODEID  
 OCSNODESYNCREQ.RECORDLIST.OCSNODEINFO.HOSTNAME   OCSNODESYNCREQ.RECORDLIST.OCSNODEINFO.REALMNAME   OCSNODESYNCREQ.RECORDLIST.OCSNODEINFO.PROVINCEID  
 OCSNODESYNCREQ.RECORDLIST.OCSNODEINFO.IPADDRESS   OCSNODESYNCREQ.RECORDLIST.OCSNODEINFO.PORT   OCSNODESYNCREQ.RECORDLIST.OCSNODEINFO.COMMENTS:O  '

ggsn='python xml2txt.py  GGSNNODESYNCREQ.RECORDLIST.GGSNINFO  ' 
ggsn_fmt='python fmt.py   GGSNNODESYNCREQ.RECORDLIST.GGSNINFO  GGSNNODESYNCREQ.RECORDLIST.GGSNINFO.OPERATESN  GGSNNODESYNCREQ.RECORDLIST.GGSNINFO.OPERATETYPE  GGSNNODESYNCREQ.RECORDLIST.GGSNINFO.NODEID  GGSNNODESYNCREQ.RECORDLIST.GGSNINFO.HOSTNAME  GGSNNODESYNCREQ.RECORDLIST.GGSNINFO.REALMNAME  GGSNNODESYNCREQ.RECORDLIST.GGSNINFO.PROVINCEID  GGSNNODESYNCREQ.RECORDLIST.GGSNINFO.IPADDRESS  GGSNNODESYNCREQ.RECORDLIST.GGSNINFO.PORT  GGSNNODESYNCREQ.RECORDLIST.GGSNINFO.SHRWOF  GGSNNODESYNCREQ.RECORDLIST.GGSNINFO.COMMENTS:O '

indir='send'
bakdir='bak'
outdir='res'
trans=$bakdir/dcc.transaction

err_file()
{
	cat "$1" | sed '/<Errors>/,/<\/Errors>/d' > "$1".$$
	mv "$1".$$ $1
}
[ -f $trans ] && sh $trans
file=$(find $indir -type f  -name "*.req" | awk '
	{
	a=$0
	gsub(/^[^\/]*/, "",a)
       	gsub(/[^\/]*$/, "",a)
	gsub(/\//,"",a) 
	type[$0] = a
	alltype[$0] =1 
	}

	END{
		priority[1] = "ggsn"
		priority[2] = "ocs"
		priority[3] = "numseg"

		for (i= 1; i<4;i++ ){
			for (file in type){
				if(type[file] == priority[i]){
					print  file
				}
			}
		}
	}')



for f in $file
do
	echo $f
	name=$f
	type=`echo $f| sed 's/[^/]*\/\([^/]*\)\/.*$/\1/'`

	fno=`echo $name| sed 's/^[^.]*\([0-9]\{4\}\)\.req$/\1/'`
	fret=`echo $name | sed 's/req/res/'`
	cmd="cat $name |   $""$type""  |  $""$type""_fmt ""|python dcc_syn_db.py $type"
	eval $cmd | sed "s/:filesn:/$fno/" > $fret 2>$fret.err
	[ -s  $fet.err ]  && err_file $fret
	#transaction
	{
	echo mv $name $bakdir/$type
	echo mv $fret $outdir/$type
	echo rm $trans
	} > $trans.$$
	mv $trans.$$ $trans
	#sh $trans

	
done



