#!/bin/echo This file should be sourced with . or source commond.

xunlei_userid()
{
    #fetch userid from cookie
    awk '$6 ~ /userid/ {print $7 }' $1
}

filelist()
{
   #extract tasklist on offline task page
   sed -n '/=\s*"dl_url[0-9]\{1,\}/s/^.\{1,\}value[[:space:]]*=[[:space:]]*"\([^"]\{1,\}\)".*$/\1/p' 
}

url_header()
{
    #print http header
    sed -n '1,/^$/p'
}

url_redirect()
{
    #get http redirect location
    grep -i location| sed  's/^[^:]\{1,\}:[[:space:]]\(http.*\)$/\1/'
}

[ $# -lt 1 ] && echo you must place cookie file name on argument >&2 && exit 1


downable_url()
{
    #get downloadable file  URL in cloud 
    fwurl=$(eval $curlwh   "'$1'"  2>/dev/null | url_header | url_redirect)
    if [  -z "$fwurl " ] ; then
        fwurl=$url
    fi
    echo $fwurl
}


userid=$(xunlei_userid $1)
home_task_page="http://dynamic.cloud.vip.xunlei.com/user_task?userid=$userid&st=0"
curl="curl   -b  $1 "
#curl with http header
curlwh="curl -i   -b $1 "


new_page_number()
{
    #output a redirect page number if required page is redirected.
    required_page=$home_task_page"&p=$1"
    npn=$(eval $curlwh   "'$required_page'"  2>/dev/null | url_header | url_redirect |sed 's/^.*&p=\([1-9][0-9]*\).*$/\1/')
    echo $npn
}


all_task_page()
{
    i=1
    np=""
    while [ -z "$np" ] 
    do
        echo $i
        i=$(( i + 1))
        #if out of the task page range , there will be a redirect
        #and np will be a number, then this loop end
        np=$(new_page_number $i)
    done
}



    
