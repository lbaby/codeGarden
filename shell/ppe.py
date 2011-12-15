#!/usr/bin/env python
from threading import Thread
import subprocess
from Queue import Queue
from Queue import Empty
import re
import sys
from time import sleep

queue_wait_time=.059
timeout_ping=999999
		
src_ip=''
re_ping_time=re.compile(r'=\s*\d+(\.\d+)?/(\d+(\.\d+)?)/\d+(\.\d+)?')


#wraps system ping command
def pinger(i, ipque,outque):
	"""Pings a ip in a subprocess environment"""
	ip = ipque.get()
	if len(src_ip) == 0:
		execve_ping = ['ping' ,  '-c' , '1' ,'%s' % ip]
	else:
		execve_ping = ['ping' ,'-S','%s' % src_ip ,  '-c' , '1' ,'%s' % ip]

	p = subprocess.Popen(execve_ping,
		stdout=subprocess.PIPE,
		stderr=subprocess.PIPE
		)
	#note:must process the output pipe before to wait the process ,
	# or there will be a dead lock:
	# ping -> waiting pipe line to empty
	# parent -> waiting for child to terminate
	for line in p.communicate()[0].splitlines():
		m = re_ping_time.search(line)
		if m is not None:
			time=m.group(2)
	ret=p.wait()

	if ret != 0:
		time = str(timeout_ping)
	if  (m is None)  and  (ret == 0) :#ping OK ,but invalid output is captured
		raise RuntimeError('ping does not work properly'+str(exceve_ping))	

	outque.put({ip:time})
	outque.task_done()
	ipque.task_done()

def ping_list(iplist):
	'''
	ping a ip list and return a dict with  corresponding value of delay time in  milliseconds
	sub ping process will run win concurrent mode
	'''
	ipque = Queue()
	outque = Queue()
	all_workers=[]
	#Spawn thread pool
	for i in range(len(iplist)):
		worker = Thread(target=pinger, args=(i,ipque,outque ))
		worker.setDaemon(True)
		worker.start()
		all_workers.append(worker)
	#Place work in que
	for ip in iplist:
		ipque.put(ip)
	#Wait until worker threads are done to exit	
	ret=[]
	while True:	
		try:
			d=outque.get(block=False)
		except Empty,e:
			if len(ret) < len(iplist):#some ping instance still waiting for echo 
				sleep(queue_wait_time)
				continue
			else:	
				break;
		ret.append(d)
	outque.join()
	ipque.join()
	return ret

argv = []
for a in sys.argv[1:]:
	r = re.match(r'srcip=([0-9]+\.[0-9]+\.[0-9]+\.[0-9]+)$',a) #parse argument to see if source IP  specified
	if r is None:
		argv.append(a)
	else:
		src_ip=r.group(1)
	
print ping_list(argv)
#python p.py srcip=192.168.3.88 192.168.3.1 g.cn
#python p.py 192.168.3.1 g.cn

	

