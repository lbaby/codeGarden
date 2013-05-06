#!/usr/bin/env python
# -*- coding: UTF-8 -*-
import smtplib
import re
import time
import sys
from email.mime.text import MIMEText
import os
re_vpn = re.compile(r'172\.17\.17\.[0-9]{1,3}')

ipcmd = 'ipconfig'

mailto_list=[ 'lbabyy@yahoo.com.cn' ]

mail_host="smtp.126.com"
mail_user="hlc_ip_alter"
mail_pass="alterip"
mail_postfix="126.com"

def send_mail(to_list,sub,content):
    me=mail_user+"<"+mail_user+"@"+mail_postfix+">"
    msg = MIMEText(content)
    msg['Subject'] = sub
    msg['From'] = me
    msg['To'] = ";".join(to_list)
    s = smtplib.SMTP()   
    s.connect(mail_host)
    s.login(mail_user,mail_pass)
    s.sendmail(me, to_list, msg.as_string())
    s.close()

def vpnip():
    m = None
    for line in os.popen(ipcmd):
        m = re_vpn.search(line)
        if m is not None:
            break
    return m

def genmsg():
    msg = None
    oldip = None
    newip = None
    first_time = 'yes'
    while True:
        newip = vpnip()
        if newip is not None:
            newip = newip.group() 
            if newip != oldip : #hold a new lease
                msg=["New IP for HLC VPN client is :%s"%newip,
                 '''
                    Please change  your destination IP to %s .
                    Mail sent by %s 
                    %s
                  ''' %(newip,sys.argv[0],time.ctime()) ]
	else :  #disconnected
            if newip != oldip or first_time == 'yes'  : #msg not send yet
                msg = ["HLC VPN client has been disconnected",
                '''
                  Please restart the client.
                  Mail sent by %s 
                  %s
                 ''' %(sys.argv[0],time.ctime()) ]
                first_time = 'no'
        oldip = newip
        if msg is not None :
            yield msg 
        msg = None
        time.sleep(5)
            

    
if __name__ == '__main__':
    for  msg in genmsg():
        try :
            print >>sys.stderr, msg[0]
            send_mail(mailto_list, msg[0], msg[1])
        except:
            pass
