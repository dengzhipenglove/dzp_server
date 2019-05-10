#!/usr/bin/env python
# coding=utf8
#
import sys
import socket
import time
import json
import hashlib

# server info and dispatcher port

host = "127.0.0.1"
port = 11111 

g_version = 1.0
g_gid = 0

def send(cmd, dat, uid):
	sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	hostport = (host, port)
	data = 'Version:%s\r\nLength:%d\r\nCommand:%s\r\nUid:%d\r\nGid:%d\r\n\r\n%s'%(g_version
			, len(dat)
			, cmd
			, uid
			, g_gid
			, dat)
	#data = data.encode('utf8', 'ignore')
	print(data)
	sock.connect(hostport)
	sock.send(data)

	recvdata = sock.recv(10240)
	print (recvdata)

def sendCmd(cmd, data):
	if not isinstance(data, dict):
		return
	send(cmd, json.dumps(data, ensure_ascii=False), data.get('uid', 1))

def  getBillTime():
	data={}
	data['op'] = 7
	data['startTime'] = 1528997453
	data['endTime'] = 1529997453
	sendCmd('xbltvlbpaybill', data)


if __name__ == "__main__":
	getBillTime()

