#!/bin/sh

. xl_tookit.sh $1

for p in $(all_task_page)
do
    task_page=$home_task_page"&p=$p"
    eval $curl "'$task_page'" 2>/dev/null |  filelist
done| while read one_task
do
    downable_url $one_task
done
    


