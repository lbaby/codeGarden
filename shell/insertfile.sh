#!/bin/sh
#Synchronize rate parameter to DB CC & RB
#Using : sqlplus 



#Call syntax:
#insert_tab_sql table column[@!field1!|value] column[@field2|value]...  
insert_tab_sql()  
{
	#argument
	tab=$1
	cnt=1
	key=''
	val=''
	shift 1
	[ -n "$FS" ] && awk="awk -F$FS" || awk='awk'
	if [ ! -f $$.$tab.awk ] ; then
		for arg in $*
		do 
			col=`echo $arg | sed 's/\(^[^@]*\)@.*$/\1/'`

			if [ $col = $arg ]  ; then
				[ "X"$key = 'X' ] && key=$arg || key=${key}","$arg
			
				[ "X"$val = 'X' ] && val='$'$cnt||val=$val",$"$cnt
				cnt=$(expr $cnt + 1)
			else
				[ "X"$key = 'X' ] && key=$col || key=${key}","$col
				pos=`echo $arg | sed 's/^[^@]*@\(.*\)$/\1/'`
				pos=`echo $pos | sed 's/!\([0-9]*\)!/$\1/'`
				[ "X"$val = 'X' ] && val=$pos||val=$val","$pos
			fi
		done
		awk_key=$val

		cat <<EOF | sed '/values(/s/\(\$[0-9]\{1,\}\)/\\47\"\1\"\\47/g' > $$.$tab.awk
		 {
				  print  "insert into $tab ( $key) 	 values($val); ";
				  if (NR%1000 == 0)  print "commit;";
		 }
		 END{
			print "commit;"
		 }
EOF
	fi

	eval $awk -f $$.$tab.awk 
	 rm -f $$.$tab.awk 

}



	 
