#! /usr/bin/env python
#mf.py  record=line number key=key old='old string' new='new string'
import sys
import re
#One record in xml
re_record=re.compile(r'<(mobile[a-zA-Z]+Call)|supplServiceEvent|serviceCentreUsage|gprsCall|contentTransaction|(locationService)>')
#BCD data in xml <key>vv vv vv xF</key>
re_bcd_content = re.compile(r'^([0-9]{2}\s+)+([0-9][0-9Ff])?\s*$')
re_xml=re.compile(r'^[^>]*>([^<]+)<[^<]*$')

def pad_bcd(s, pad='F'):
    ns=''
    cc = 0
    for c in s: 
        if( (cc%2 == 0) and  cc != 0 ) :
            ns = ns + ' '
        cc += 1
        ns = ns + c
    #see if  need to pad 
    if (len(s) % 2):
        ns += pad
    return ns

  

def modline(line, old,  new):
    m = re_xml.match(line)
    isbcd = re_bcd_content.match(m.groups()[0])
    split = line.split(m.groups()[0])
    xml_str = ''
    if old ==   m.groups()[0]:
        xml_str = (isbcd and pad_bcd(new) or new)
    elif isbcd :
        if m.groups()[0] != pad_bcd(old) :  #oops,target not match to value given
            return line #do nothing
        xml_str = pad_bcd(new)
    else:
            return line
    return split[0]+xml_str+split[1]


def parse_arg(arg):
    arg_re=re.compile(r'^([^=]+)=(.+)$')
    argv=dict()
    for a in arg:
        m = arg_re.match(a)
        if m is not  None: # number
            argv[m.group(1)] = m.group(2)
    return argv
        
argv = parse_arg(sys.argv)
if 'record_regex' in argv:
    re_record=re.compile(argv['record_regex'])
re_key = re.compile('^\s*<'+argv['key']+'>[^><]*</'+argv['key']+'>\s*$')
rc = 0
for line in sys.stdin:
    if  re_record.search(line):
        rc += 1
        print line,
    elif re_key.match(line):
        if   ('record' not in argv) or (rc == int(argv['record']) ) :
            print modline(line, argv['old'],  argv['new']),
        else:
            print line,
    else :
        print line,
