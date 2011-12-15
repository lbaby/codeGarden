#!/usr/bin/env python
import sys
import re
key_value_separator = re.compile( r'\s*:\s*')
key_value_replace=re.compile( r'[^:]*:\s*')
field_separator = re.compile(r'\s*\|\s*')
field_replace=re.compile( r'[^|]*\|\s*')
trim_replace=re.compile(r'\s*')
opt_flag = 'O'
ofs = '|' #Field separator

def format_item(f, header , item_node, option_item_node=list()):
	'''
	format text
	input 
	header:node:val1|node2:val2|...
	output
	val1|val2|...
	the value  is in item_node key order
	'''
	#value 
	val_dict = dict()
	#output field line list
	out_line=list()
	#output node we have extract from line,for node missing  check.
	out_node = list()

	for line in f:
		try:
			#header:i1:v1|i2:v2
			line_header= key_value_separator.split(line)[0].upper()
			if line_header != header:
				continue

			#into -i1:v1|i2:v2
			no_header_line = key_value_replace.sub('', line,1)

			split_item = field_separator.split(no_header_line)
			for node in split_item:
				#pass empty node 
				if len(node) == 0:
					continue;
				#
				key_value = key_value_separator.split(node)
				if ( key_value[0].upper() in item_node ): 
					val_dict[key_value[0].upper()] =  key_value[1] 
					out_node.append(key_value[0].upper())
				else:
					continue;

			for node in item_node:#Is all item node is here ?
				if (node.upper() not in out_node) :
					#Add NULL string if the node is optional one
					if node.upper()  in option_item_node:
						out_line.append('')
					else:
						raise KeyError(node)
				else:
					if  node.upper() not in val_dict.keys() :#a node required missing 
						raise KeyError(node)
					out_line.append(val_dict[node] )

			print ofs.join(out_line)
			#Clear the  line
			out_line=list()
			out_node = list()
					
		except KeyError, e:
			print >>sys.stderr, line,

if __name__ == '__main__':
	if len(sys.argv) < 3:
		print >> sys.stderr, ' usage : %s header item [ item2 ...]' % sys.argv[0]
		sys.exit(0)
	
	require_node = list()
	option_node = list()
	for node in sys.argv[2:] :
		onode = node.split(':')
		if len(onode) > 1:
			#Store all the option node
			if onode[1].upper() == opt_flag:
				option_node.append(onode[0].upper())
		require_node.append(onode[0].upper())
	

	format_item(sys.stdin, sys.argv[1].upper(), require_node , option_node)

