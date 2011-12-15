#!/usr/bin/env python
import sys
import re
import cx_Oracle as oradb
import time 

db_str='cc1/ai812345@dcc'

re_field_separator = re.compile(r'\s*\|\s*')
re_bind_var = re.compile(r':\w+\W*?')
re_word_strip=re.compile(r'\W+')
node_prefix='n' #For node count, n1 means node 1

insert_action='1'
delete_action='2'
modify_action='3' 
action_command={
		'1': ('insert_sql',),
		'2': ('delete_sql',),
		'3': ('insert_sql','delete_sql')
		}



support_file_list=('GGSN','OCS','NUMSEG')
#For cx_Oracle insertion

delete_sql={
		'GGSN':
		(
		'''
		delete from dcc_client_node d where d.dcc_client_id =(select dcc_client_id from  dcc_client_node where std_code=:n3)
		'''
		, #DO NOT delete this comma , if comma missing ,this line are take as a string instead of list
		)
		#
		,
		'OCS':
		(
		'''
		delete from   dcc_routing_seg where  ocs_server_id = (select  ocs_server_id  from ocs_server where std_code = :n3)
		''',
		'''
		delete from   ocs_number_seg  where  ocs_server_id = (select  ocs_server_id  from ocs_server where std_code = :n3)
		''',
		'''
		delete from  ocs_server where  ocs_server_id = (select  ocs_server_id  from ocs_server where std_code = :n3)
		'''
		,
		)
		#
		,
		'NUMSEQ':
		(
		'''
		delete from  dcc_routing_seg where routing_seg_id = to_number(:n3)

		'''
		,
		'''
		delete from ocs_number_seg  where seg_id = to_number(:n3)
		'''
		)
	}

insert_sql={
		'GGSN':
		(
		'''
		insert into dcc_client_node values((select nvl(max(dcc_client_id),1) from dcc_client_node),:n4,:n5,to_number(:n6),:n7,to_number(:n9),:n8,:n10, NULL,:n3)
		'''
		,
		)
	
		,
		'OCS':
		(
		'''
		insert  into ocs_server values((select nvl(max(ocs_server_id),1) from ocs_server),:n4, :n5,to_number(:n6), :n7,:n8,:n9,NULL,:n3)
		'''
		,#DO NOT delete this comma , if comma missing ,this line are taken as a string instead of truple
		)
		,
		'NUMSEG':
		(
		'''
		insert into  ocs_number_seg values(:n3,(select  ocs_server_id  from ocs_server where std_code = :n6),1,:n4,:n5,:n7)
		'''
		,
		'''
		insert into  dcc_routing_seg values(:n3,:n3,(select  ocs_server_id  from ocs_server where std_code = :n6),
		substr(:n4,1,  greatest(  length(trim(  TRAILING  '0' from  :n4)),  length( trim(TRAILING  '9' from  :n5))) )
		)
		'''
		)
	}



def exec_sql(cursor,sql, oneline):
	'''
	execute a sql with lines

	'''

	#cx_Oracle require exact number of key in dictionary
	#So I must extract the bind variable from sql so that combine the dictionary

	#bind_var_list (':va1',':va2')
	#var_key_list('va1','va2')
	bind_var_list=re_bind_var.findall(sql)
	var_key_list=list()
	for s in bind_var_list:
		var_key = re_word_strip.sub('',s)
		if var_key not in var_key_list:
			var_key_list.append(var_key)

	field=re_field_separator.split(oneline.rstrip())
	#Field are filled into dict v1|v2|v3 ==> {'n1':'v1', 'n2':'v2'
	#insert one line
	val_dict=dict()
	for key in var_key_list:
		val_dict[key] = field[int(key.replace(node_prefix,'')) -1]
	cursor.execute(sql, val_dict )


def insert_dcc_file(cursor, file, file_type):
	'''
	insert or delete or modify a dcc synchorize file
	action is operatetype, 1:add ,2 :delete, 3:modify(qual to delete and insert)
	'''
	if file_type.upper() not in support_file_list:
		raise KeyError('File type not support:'+file_type)

	result_code=dict()
	for line in file:
		action=re_field_separator.split(line)[1]
		result_code[re_field_separator.split(line)[0] ] = '0'
		if action == insert_action:
			try:
				for sql in insert_sql[file_type.upper()] :
					exec_sql(cursor, sql, line)
			except Exception,e:
				result_code[re_field_separator.split(line)[0] ] = '1002'
		elif action == delete_action:
			try:
				for sql in insert_sql[file_type.upper()] :
					exec_sql(cursor, sql, line)
			except Exception,e:
				result_code[re_field_separator.split(line)[0] ] = '1001'
		elif action == modify_action:
			try:
				for sql in insert_sql[file_type.upper()] :
					exec_sql(cursor, sql, line)
				for sql in delete_sql[file_type.upper()] :
					exec_sql(cursor, sql, line)
			except Exception,e:
				result_code[re_field_separator.split(line)[0] ] = '1001'
		else:
			raise KeyError('OPERATETYPE unrecognized')

			

		
	return result_code

def gen_ret(file, result):
	#result[key] = result_code
	'''
	generate return file
	'''
	header='''<?xml version="1.0" encoding="UTF-8"?>
	<SyncResult>
	<FileSN>:filesn:</FileSN>
	<Version>00000</Version>
	<CreateTime>%s</CreateTime>
	<Provider>000005107011-0000</Provider>
	<RecordNum>%d</RecordNum>
	<CorrectNum>%d</CorrectNum>
	<Reserve></Reserve>'''

	tail='''
	</SyncResult>'''

	body='''
			<Error>
				<OperateSN>%s</OperateSN>
				<ResultCode>%s</ResultCode>
			</Error>'''

	err_tag_start='''
		<Errors>'''
	err_tag_end='''
		</Errors>'''

	tm = time.localtime()
	timestr=str(tm.tm_year) + '%02d'%tm.tm_mon + '%02d'%tm.tm_mday + '%02d'%tm.tm_hour +  '%02d'%tm.tm_min +  '%02d'%tm.tm_sec  
	ok_cnt=0
	for k in result.keys():
		if result[k] == '0':
			ok_cnt = ok_cnt + 1
	header=header%(timestr, len(result.keys()) , ok_cnt)

	print >>file, header,
	if ok_cnt == len(result.keys()):
		print >>file,  tail,
	else:
		print >>file, err_tag_start,
		
		for k in result.keys():
			print >>file, body%(k, result[k]),
		print >>file, err_tag_end,
		print >>file, tail,

	
	#end of xml

if __name__ == '__main__':
	if len(sys.argv) < 2:
		print >>sys.stderr, '  usage : %s file_type ' % sys.argv[0]
	conn=oradb.connect(db_str)
	mycursor=conn.cursor()
	ok_err_node=list()
	try:
		result_code=insert_dcc_file(mycursor, sys.stdin, sys.argv[1])
	except Exception,e:
		print>>sys.stderr,   e
		mycursor.close()
		conn.close()
		sys.exit(1)
	gen_ret(sys.stdout,result_code)

	mycursor.close()
	conn.commit()
	conn.close()
