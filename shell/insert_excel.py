#!/usr/bin/env python
# -*- coding: utf-8 -*- 
#author : lbaby   lsylny@gmail.com
''' Insert an excel file into oracle db
    usage:
    insert_excel.py db=usr/passwd@db excel=all_data.xlsx 
	sql="insert into aa values(:n1, :n2, to_number(:n3), NULL)"
    Dependent package : xlrd, cx_Oracle
'''

import re
import os
import sys
import xlrd
import datetime
import cx_Oracle

clas parse_insert:
	def __init__(self, sql):
		pass

	def get_table():
		return self.table

	def get_fields():
		return self.fields



#Parse the sql , inspect target table structure , do necessary format conversion
def sql_executor(cursor, sql):
	#For closure imitation
	#Encapsule a sql statement in a class
	class bind_sql_to_executor:
		def __init__(self, cursor, sql)
			'''
			execute a sql with lines
			insert into client_node 
			values((select nvl(max(client_id),1) from client_node),:n4,:n5,
			to_number(:n6),:n7,to_number(:n9),:n8,:n10, NULL,:n3)
			'''
			self.re_bind_var = re.compile(r':\w+\W*?')
			self.re_word_strip=re.compile(r'\W+')
			self.node_prefix='n' #For node count, n1 means node 1
			self.sql = sql
			#cx_Oracle require exact number of key in dictionary
			#So I must extract the bindind variable from sql 
			#bind_var_list (':va1',':va2')
			#var_key_list('va1','va2')
			bind_var_list=self.re_bind_var.findall(sql)
			self.var_key_list=list()
			for s in bind_var_list:
				var_key = self.re_word_strip.sub('',s)
				if var_key not in self.var_key_list:
					self.var_key_list.append(var_key)
			self.tar
			#parse
		def exec_using(self, data)
			#Fill a dict for variable bind data => {'n1':'v1', 'n2':'v2'...}
			val_dict=dict()
			for key in self.var_key_list:
				val_dict[key] = field[int(key.replace(self.node_prefix,'')) -1]
			cursor.execute(self.sql, val_dict)	
	#Return analysed sql executor 
	return bind_sql_to_executor(cursor, sql).exec_using

def read_excel(excel):
	book = xlrd.open_workbook(excel)
	for n in range(book.nsheets):
		sh = book.sheet_by_index(n)
		for r in range(sh.nrows):
			yield sh.row_values(r)

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
    		insert_excel.py db=usr/passwd@db excel=all_data.xlsx  \
		sql="insert into aa values(:n1, :n2, to_number(:n3), NULL)"
    		''')
	argv = parse_arg(sys.argv[1:])
	db = cx_Oracle.connect(argv['DB'])
	cursor = db.cursor()
	sql_exec =  sql_executor(argv['SQL'])
	for row in read_excel(argv['EXCEL']):
		try:
			sql_exec(cursor, row)
		except Exception, e:
			print >>sys.stderr, row 
			print >>sys.stderr, e
	cursor.close()
	db.commit()
