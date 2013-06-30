for file in ` ls `
do
	cat $file | sed 's/std::ostream/std::std::ostream/g' > $file.$$
	if [ -s $file.$$ ]  ; then 
		mv  -f $file.$$ $file
	fi
done
