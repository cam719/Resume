#Authors: Cameron O'Neal, Joe Minicucci
import random
import sys
import socket
import dns.message
import dns.query
import dns.name
import collections
from collections import defaultdict
from dns.query import UnexpectedSource, BadResponse

import time

class Resolver():

        def initializeCache(self):
                cache = {}
                cache['.'] = {'NS': ['e.root-servers.net', 'l.root-servers.net', 'g.root-servers.net', 'h.root-servers.net', 'c.root-servers.net', 'f.root-servers.net', 'k.root-servers.net', 'j.root-servers.net', 'a.root-servers.net', 'm.root-servers.net', 'b.root-servers.net', 'i.root-servers.net', 'd.root-servers.net']}
                cache['e.root-servers.net'] = {'A': ['192.203.230.10']}
                cache['l.root-servers.net'] = {'A': ['199.7.83.42']}
                cache['g.root-servers.net'] = {'A': ['192.112.36.4']}
                cache['h.root-servers.net'] = {'A': ['128.63.2.53']}
                cache['c.root-servers.net'] = {'A': ['192.33.4.12']}
                cache['f.root-servers.net'] = {'A': ['192.5.5.241']}
                cache['k.root-servers.net'] = {'A': ['193.0.14.129']}
                cache['j.root-servers.net'] = {'A': ['192.58.128.30']}
                cache['a.root-servers.net'] = {'A': ['198.41.0.4']}
                cache['m.root-servers.net'] = {'A': ['202.12.27.33']}
                cache['b.root-servers.net'] = {'A': ['192.228.79.201']}
                cache['i.root-servers.net'] = {'A': ['192.36.148.17']}
                cache['d.root-servers.net'] = {'A': ['199.7.91.13']}
                return cache

        def __init__(self):
                self.cache = self.initializeCache()
                self.answerCache = defaultdict(list)
                #self.cnameFlag = False

        def readFile(self, fileName):
                f = open(fileName, 'r')

                for line in f.readlines():
                        line = line.replace('\n', '')
                        line = line.split(" ")
                        command = line[0]
                        if command == 'resolve':
                                domain = line[1]
                                record = line[2]
                                self.resolve(domain, record)
                                #print 'COMMAND IS RESOLVE WITH DOMAIN ' + domain + " " + record
                        elif command == 'print':
                                self.printCache()
                        elif command == 'quit':
                                sys.exit(1)
                        else:
                                print 'ERROR: Unknown command'


        def putSomethingIntoCache(self, d1):
                self.cache.update(d1)
                return 
        def putSomethingIntoCache2(self, d1, key):
                self.answerCache[key].append(d1)
                return 	

        def resolve(self, domain, record, origdomain=None):
                #domain = 'gmail.com'
                name = dns.name.from_text(domain)
                print "***************************************************\n\n"
                print 'COMMAND:  resolve ' + domain + " " + record

                for i in range(len(name),0,-1):
                        s = name.split(i)
                        if self.cache.has_key(s[1].to_text()):
                                startKey = s[1].to_text()
                                break		

                origT = time.time()
                if not self.answerCache.has_key(domain):
                        self.answerCache[domain] = []

                elif self.answerCache.has_key(domain):
                        for i in range(len(self.answerCache[domain])):
                                if self.answerCache[domain][i].has_key(record):
                                        endT = time.time()
                                        print "*** QUERY " + domain + " for RRType " + record
                                        print "*** Answer found in Cache"
                                        print "*** FINAL RESPONSE found with latency " + str((endT - origT)) + "\n"
                                        print self.answerCache[domain][i][record]
                                        return 


                print "*** NS records fetched from cache: " + str(self.cache[startKey]['NS'])
                nameServer = self.cache[startKey]['NS'][0]
                ips = self.cache[nameServer]['A']
                print "*** Nameserver " +  nameServer + " has IP addresses " + str(ips)
                print "*** QUERY name server " +  '\'' + nameServer  + '\'' + " at " + ips[0] + " for " + '\'' + str(name) + '\'' + "  " +  '\''+ record +  '\''
                nameServerList = []
                #LOOP HERE
                depth = 1
                root = False
                while not root:
                        s = name.split(depth)



                        subdomain = s[1]
                      
                        response = None
                        if depth == 1 : 
                                nameserver = ips[0]#Keeping this intact for the first iteration
                                startT = time.time()
                                response = self.tryQueryingNameServer(nameserver,domain,record)
                                endT = time.time()
                                print "*** Response received with latency:  " + str((endT - startT))
                                print response
                        else:
                                print "*** Start next iteration with domain " +  '\'' + str(subdomain) +  '\'' + " nameservers " + str(self.cache[subdomain.to_text()]['NS'])
                                nameServer = self.cache[subdomain.to_text()]['NS']
                                print "*** Nameserver " + '\'' +  nameServer[0] + '\'' + " has IP addresses "  + str(self.cache[nameServer[0]]['A'])
                                for i in range(len(nameServer)):
                                        #temporary hotfix below: select a random server. refactor to recurse nameServerList length if response is empty
                                        #nameserver = nameServerList[random.randint(0,len(nameServerList)-1)]
                                        print "*** QUERY name server "+  '\'' + nameServer[i] +  '\'' + ' at ' + str(self.cache[nameServer[i]]['A'][0]) + " for " + '\'' + str(name) + '\'' + "   " + '\'' + record + '\''
                                        nameserver = self.cache[nameServer[i]]['A'][0]
                                        ST = time.time()
                                        response = self.tryQueryingNameServer(nameserver,domain,record)
                                        endT = time.time()
                                        print "*** Response received with latency:  " + str((endT-ST))
                                        if response is not None: 
                                                print response 
                                                break

                        if response is None:
                                print "All of the queries on the following servers have failed, with blank responses:"
                                for k in range(len(nameServerList)):
                                        print nameServerList[k]
                                return
                        if response.rcode() != 0:
                                key = domain
                                key1 = record
                                value = response.to_text()

                                d = {key1 : value}
                                self.putSomethingIntoCache2(d, key)
                                return	

                        if len(response.answer) != 0:
                                print "_____________________________________________________"
                                print "*** QUERY " + str(name) + " for RRType " + record
                                print "*** FINAL RESPONSE found with latency " + str((endT-origT)) + "\n\n"
                                print response
                                print "_____________________________________________________"
                                root = True	

                                d1 = {}	

                        if (response.authority and response.authority[0].rdtype == 6):
                                key = domain
                                key1 = record
                                value = response.to_text()      
                                d = {key1 : value}
                                self.putSomethingIntoCache2(d, key)
                                return response			    

                        if(len(response.answer) != 0):

                                if (response.authority and response.authority[0].rdtype == 6 and origdomain == None):

                                        key = domain
                                        key1 = record
                                        value = response.to_text()

                                        d = {key1 : value}
                                        self.putSomethingIntoCache2(d, key)
                                        return response

                                for i in range(len(response.answer)):
                                        s = response.answer[i].to_text()
                                        s = s.replace('\n', ' ').split(" ")	
                                        line = s[0:5]
                                        if response.answer[i].rdtype == 5:
                                                res = self.resolve(s[4],record, domain)
                                                if origdomain == None:
                                                        for r in (res.answer):
                                                                response.answer.append(r)							
                                                        d1 = { record : response.to_text()}
                                                        self.putSomethingIntoCache2(d1, name)				
                                                #self.resolveCNAME(domain, nameServerList, record , line[4], response)
                                                return response
                                        #if (self.cnameFlag):
                                                #key = 
                                        #	continue
                                        elif  origdomain == None:
                                                key = s[0].rstrip(".")
                                                key1 = s[3].rstrip(".")
                                                value = response.to_text()
                                                d1 = {key1 : value}
                                                self.putSomethingIntoCache2(d1, key)

                                        #print "FIRST ANSWER = " + str(s[0:5])

                                        #y = 10
                                        #z = 5
                                        #for j in range(len(response.answer)):
                                                #y = 10
                                                #z = 5
                                                #for k in range(len(response.answer[j])-1):
                                                        #print "ANSWER = " + str(s[z:y])
                                                        #v = s[y-1]
                                                        #d1[key][key1].append(v)				
                                                        #z += 5
                                                        #y += 5
                                        #self.answerCache.update(d1)
                                        break #answer section is filled so the iterations are complete
                        else:

                                #print response
                                j = 10
                                i = 5
                                s = response.authority[0].to_text()
                                s = s.replace('\n', ' ').split(" ")
                                if s[0].rstrip(".") == domain.strip("www."):
                                        key = s[0].rstrip(".")
                                else:
                                        key = s[0]
                                key = s[0]
                                key1 = s[3]
                                value = [s[4]]
                                #first nameserver response



                                #Get authority section
                                d1 = {}
                                d2 = {}
                                for k in range(len(response.authority)):
                                        lines = response.authority[k].to_text().split("\n")
                                        for line in lines:
                                                line = line.split(" ")
                                                key = line[0]
                                                key1 = line[3]	
                                                if key1 == "DS" or key1 == "RRSIG" or key1 == "NSEC3":
                                                        v = ' '.join(line[4:])
                                                        d1.setdefault(key, {})
                                                        d2.setdefault(key1, [])
                                                        d2[key1].append(v)
                                                        d1[key].update(d2)	
                                                        self.putSomethingIntoCache(d1)
                                                else:
                                                        v = line[4]
                                                        d1.setdefault(key, {})
                                                        d2.setdefault(key1, [])
                                                        d2[key1].append(v)
                                                        d1[key].update(d2)
                                                        i += 5
                                                        j += 5
                                                        self.putSomethingIntoCache(d1)

                                #initialize keys
                                d2 = {}
                                nameServerList = []

                                for k in range(len(response.additional)):
                                        line = response.additional[k].to_text()
                                        line = line.split(" ")
                                        nameServerList.append(line[4]) #raw nameserver list
                                        key = line[0]
                                        d2[key] = {}

                                for k in range(len(response.additional)):
                                        line = response.additional[k].to_text()
                                        line = line.split(" ")	
                                        key = line[0]
                                        key1 = line[3]
                                        d3 = {key1: []}
                                        d3[key1].append(line[4]) 
                                        d2[key].update(d3)

                                self.putSomethingIntoCache(d2)
                                depth+=1
                return response

        def tryQueryingNameServer(self,nameserver,domain,record):
                try:
                        query = dns.message.make_query(domain, record, want_dnssec=True)
                        response = dns.query.udp(query, nameserver, timeout=5)
                        if response: return response
                except (IndexError,socket.error,UnexpectedSource,BadResponse,dns.exception.Timeout) as caughtException:
                #index error is in case programmer forgets to check answer section on previous iteration. 
                #socket catch is because sometimes the nameservers will refuse connections
                        print caughtException
                return None

        def resolveCNAME(self, domain, nameServerList, record, cname, oldresponse):
                ret = self.tryQueryingNameServer(nameServerList[3], cname, record)
                if len(ret.additional) != 0:
                        nameServerList = []
                        for i in range(len(ret.additional)):
                                txt = ret.additional[i].to_text().split(" ")
                                nameServerList.append(txt[4])
                        ret = self.tryQueryingNameServer(nameServerList[3], cname, record)
                for i in range(len(oldresponse.answer)):
                        ret.answer.append(oldresponse.answer[i])
                key = domain
                key1 = record
                value = ret.to_text()
                d1 = {key1 : value}
                self.putSomethingIntoCache2(d1, key)		
                #self.answerCache[domain] = ret.to_text()

        def printCache(self):
                print 'Cache Answer Contents: \n'
                tmp = self.answerCache.items()
                for k, v in self.answerCache.iteritems():
                        print k,':'
                        for i in range(len(v)):
                                print v[i].keys()[0], ': ', v[i].values()[0]
                print 'Cache Contents: \n'
                tmp = collections.OrderedDict(sorted(self.cache.items()))
                #tmp = self.cache
                for k, v in tmp.iteritems():
                        print k, ':\n', 
                        for i in range(len(v)):
                                print v.keys()[i], ': ', v.values()[i]
                        print '\n'

if __name__ == "__main__":
        R = Resolver()
        R.readFile(sys.argv[1])
