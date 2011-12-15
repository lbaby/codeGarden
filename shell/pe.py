#!/usr/bin/env python
import sys
import xlrd
import re

reload(sys)
sys.setdefaultencoding('utf-8')

field=('netcode', 'hcode', 'provcode')
field_re={
	field[0]: re.compile(r'net.?code', re.I),
	field[1]:re.compile(r'(h\d)+', re.I),
	field[2]:re.compile(r'prov.?code', re.I)
}

valid_field_re=re.compile(r'd+')


def expand_xls(file):
	book=xlrd.open_workbook(file)
	for n in range(book.nsheets):
		sh=book.sheet_by_index(n)
		nrows=sh.nrows
		ncols=sh.ncols

		if nrows == 0  or ncols == 0:
			print >>sys.stderr, 'pass empty sheet',sh.name
			continue


		field_pos={
			field[0]:-1,
			field[1]:-1,
			field[2]:-1
		}

		if nrows > 1: #look for proper colon 
			first_row=sh.row_values(0)
			for i in range(len(first_row)):
				for fc in range(len(field)):
					if field_re[field[fc]].match(first_row[i]):
						field_pos[field[fc]]=i
						continue
			for f in field:
				if field_pos[f] == -1:
					raise RuntimeError('Can NOT locate field:'+f)

		else:
			 
			raise RuntimeError('Not a valid H code file')


				
		for r in range(nrows):
			for f in field:
				print sh.cell_value(r, field_pos[f]),
			print
if __name__== '__main__' and len(sys.argv) > 1:			
	expand_xls(sys.argv[1])

