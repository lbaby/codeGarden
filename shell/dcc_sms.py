#!/usr/bin/env python



import sys
import cx_Oracle
import subprocess
import sys
#SMSmodem.py -c /dev/tty1 -p +8681565252781 ok

sms_modem_py='SMSmodem.py'
sms_time_out='4/24'
sms_log_level = '3'
sms_encoding='GBK'

sms_sql='''
	SELECT  b.EVENT_INST_ID ,to_char(a.create_date,'yyyy-mm-dd hh24:mi:ss'),
	d.NE_NODE_NAME,
	      b.detail_info    
	 FROM NM_DATA.NM_ALARM_CDR A, NM_DATA.NM_ALARM_EVENT B, NM.NM_NE_LIB d 
	 WHERE  B.EVENT_INST_ID = A.ALARM_INST_ID
		and b.alarm_level < %s
		and d.NE_NODE_ID = b.ne_node_id
		and a.create_date > sysdate - %s
		and not exists  
		(select  *  from NM_DATA.NM_ALARM_SEND c where c.EVENT_INST_ID = b.EVENT_INST_ID
			and c.FROM_STAFF = '%s'
			and c.send_state != 'E')
	'''

insert_sms_send_sql='''
	insert into nm_data.nm_alarm_send 
	values(send_inst_id_seq.nextval, %s, 'S', '%s' ,sysdate, '%s')
'''

def check_out_sms(cursor, one_msisdn):
	''' return 
		'''
	exe_sql = sms_sql%(sms_log_level,sms_time_out ,one_msisdn)
	#print exe_sql
	return cursor.execute(exe_sql)

ntos=lambda x: int(x)and 'E'or'S'

def mark_sms_send(cursor,one_msisdn, msg):
	#print 'mark'
	for m in msg: 
		insql=insert_sms_send_sql%(m[0],one_msisdn,ntos(m[len(m)-1]))
		cursor.execute(insql)



def one_msisdn_sms_send(dev, one_msisdn, msg):
	retmsg=list()
	for m in msg:
		retcode=0
		cmd=['python', sms_modem_py, '-c' , '%s'%dev, '-p' , '%s'%one_msisdn, ('%s'%(m[1]+m[2]+m[3])).encode(sms_encoding)]
		try:
			subprocess.check_call(cmd)
		except :
			retcode=1	
		retmsg.append((m[0],retcode))
			
	return retmsg	
	

def send_sms (dev ,cursor, msisdns):
	for m in msisdns:
		#print m
		msgs=check_out_sms(cursor,m)
		msgs=one_msisdn_sms_send(dev,m,msgs)
		mark_sms_send(cursor,m, msgs)
	 	
arg_default={ 
	'db'.upper():'nm_data/smart@nmdb',
	'dev'.upper():'/dev/tty1',
	'num'.upper():'+8618637156500,+8615996318932'
}

def parse_arg(arg):
		
	import re
	arg_re=re.compile(r'^([^=]+)=(.+)$')
	argv=dict()
	for a in arg:
		m = arg_re.match(a)
		if m is None: # number
			#check if is cell phone number
			if re.match('^((\+?)|(00))?[0-9]{11,13}$', a) is None:
				raise KeyError(a + 'is not a valid phone number')
			if 'num' not in argv.keys():
				argv['num'.upper()] = a
			else:
				argv['num'.upper()] = argv['num'.upper()] +','+a
		else:
			argv[m.group(1).upper()] = m.group(2)
	argk=argv.keys()
	for k in arg_default.keys():
		if k not in argk:
			argv[k] = arg_default[k]
			
	return argv
			
			 

if __name__ == '__main__':
	if(len(sys.argv) < 2):
		print 'usage :'
		print sys.argv[0] ,' dev=/dev/tty1  num=+8613212345678,13912345678 db=nm/passwd@db'
		print 'will continue using :'
		s='	'+sys.argv[0]
		for  a in arg_default.keys():
			s = s +' ' +a + '=' + arg_default[a]
		print s	 	
	argv=parse_arg(sys.argv[1:])
	db=cx_Oracle.connect(argv['DB'])
	cursor=db.cursor()
	send_sms(argv['DEV'], cursor, argv['NUM'].split(','))
	cursor.close()
	db.commit()

