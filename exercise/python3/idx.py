#!/usr/bin/env python
# -*- coding:utf-8 -*-
import re
#separators :
space_sep = re.compile(r'\s+')
vertical_sep = re.compile(r'\|')
default_concat = '/'
#comment line
conf_comment = re.compile(r'^\s*#')

def index_file(lines, sep,concat, *keys ):
    index = dict()
    for  line in lines:
        #wipe comment line
        if conf_comment.match(line) is not None:
            continue
        fields = sep.split(line)
        #make a key for index
        if len(keys) > 1:
            key = list()
            for k in keys:
                key.append (fields[k])
            index [concat.join(key)] = fields
        else:
             index [fields[keys[0]] ] = fields
    return index


index_file(('1|2|3', 'a|b|c', ' # a comment line '), vertical_sep,  '/' , 0)
index_file(('1|2|3', 'a|b|c', ' # a comment line '), vertical_sep,  '/' , 0,2)
