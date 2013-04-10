#!/usr/bin/env python
# -*- coding: utf-8 -*- 
''' Insert an excel file into oracle db
    usage:
    insert_excel.py db=usr/passwd@db excel=all_data.xlsx sql="insert into aa values(:n1, :n2, to_number(:n3), NULL)"
    Dependent package : xlrd, cx_Oracle
'''
import re
import os
import sys
import xlrd
import cx_Oracle

os.environ['NLS_LANG'] = 'SIMPLIFIED CHINESE_CHINA.UTF8'

re_bind_var = re.compile(r':\w+\W*?')
re_word_strip=re.compile(r'\W+')
node_prefix='n' #For node count, n1 means node 1

def read_excel(excel):
	book = xlrd.open_workbook(excel)
	for n in range(book.nsheets):
		sh = book.sheet_by_index(n)
		rows = sh.nrows
		cols = sh.ncols
		for r in range(sh.nrows):
			yield sh.row_values(r)

def exec_sql(cursor,sql, oneline):
	'''
	execute a sql with lines
	insert into client_node 
	values((select nvl(max(client_id),1) from client_node),:n4,:n5,
	to_number(:n6),:n7,to_number(:n9),:n8,:n10, NULL,:n3)

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
	field=oneline
	#Field are filled into dict v1|v2|v3 ==> {'n1':'v1', 'n2':'v2'
	#insert one line
	val_dict=dict()
	for key in var_key_list:
		val_dict[key] = field[int(key.replace(node_prefix,'')) -1]
	cursor.execute(sql, val_dict )

def parse_arg(arg):
	'''
	argv['key1=v1', 'key2=v2']
	'''
	arg_re=re.compile(r'^([^=]+)=(.+)$')
	argv=dict()
	for a in arg:
		m = arg_re.match(a)
		argv[m.group(1).upper()] = m.group(2)
	return argv

if __name__ == '__main__':
	if len(sys.argv) != 4:
		raise RuntimeError('''
		usage:
    		insert_excel.py db=usr/passwd@db excel=all_data.xlsx sql="insert into aa values(:n1, :n2, to_number(:n3), NULL)"
    		''')
	argv = parse_arg(sys.argv[1:])
	db = cx_Oracle.connect(argv['DB'])
	cursor = db.cursor()
	row=None
	for row in read_excel(argv['EXCEL']):
		try:
			exec_sql(cursor, argv['SQL'], row)
		except Exception, e:
			print >>sys.stderr, row 
			print >>sys.sterr, e
	cursor.close()
	db.commit()
