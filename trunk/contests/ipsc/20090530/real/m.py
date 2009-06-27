#!/usr/bin/python
# -*- coding: utf8 -*-

import sys
import re

#print sys.setrecursionlimit(200000)

#exit(0)

f = file("m2.in")
nn = int(f.readline())
print "nn=%d" % nn

for ii in range(nn):
    trash = f.readline()
    desc = f.readline().strip()

    # translating
    desc = re.sub(r"ONE OF THE CHARACTERS \^((\w|;)+)", r"[\^\1]", desc) #?
    desc = re.sub(r"ONE OF THE CHARACTERS \[\:digit\:\]", r"\d", desc) #?
    desc = re.sub(r"ONE OF THE CHARACTERS \[\:alnum\:\]", r"\w", desc) #?
    desc = re.sub(r"ONE OF THE CHARACTERS ((\w|;)+)", r"[\1]", desc)
    
    desc = re.sub(r"ONE OF THE LETTERS (\w+)", r"[\1]", desc)
    desc = re.sub(r"OR", r"|", desc)
    desc = re.sub(r"THE STRING (\w+)", r"\1", desc)
    desc = re.sub(r"THE LETTER ([a-zA-Z])", r"\1", desc)
    desc = re.sub(r"ANY CHARACTER EXCEPT (\w+)", r"[^\1]", desc)
    desc = re.sub(r"FOLLOWED BY", r"  ", desc)
    desc = re.sub(r"AT LEAST (\d+) TIMES", r"{\1,}", desc)
    desc = re.sub(r"FROM (\d+) TO (\d+) TIMES", r"{\1,\2}", desc)
    desc = re.sub(r"AT MOST (\d+) TIMES", r"{,\1}", desc)
    desc = re.sub(r"AT MOST (\d+) TIMES", r"{,\1}", desc)
    desc = re.sub(r"(\d+) TIMES", r"{\1,\1}", desc)
    desc = desc.replace(" ", "")
    
    #print "desc = '%s'" % des
    desc = re.sub(r"\(\[(\w+)\]\)", r"[\1]", desc)
    desc = re.sub(r"\(\[\^(\w+)\]\)", r"[^\1]", desc)
    desc = re.sub(r"\((\w+)\)", r"\1", desc)
    desc = re.sub(r"\((\w+)\)", r"\1", desc)
    desc = re.sub(r"\((\w+)\)\|\((\w+)\)", r"\1|\2", desc)
    desc = re.sub(r"\((\w+)\)\|\((\w+)\)", r"\1|\2", desc)
    desc = re.sub(r"\((\w+)\)\|\((\w+)\)", r"\1|\2", desc)
    #print "desc = '%s'" % desc
    
    
    desc = "^"+desc+"$"
    
    #print "desc[%d] = '%s'" % (ii, desc)
    #print desc.count("(")
    c = re.compile(desc)
    sys.stderr.write("case #%d <%s>\n" % (ii, desc))
    n = int(f.readline())
    for i in range(n):
        query = f.readline().strip()
        sys.stderr.write(" query #%d = <%s>\n" % (i, query))
        if(c.match(query)):
            print "YES"
        else:
            print "NO"
        #print "query #%d is %s" % (i, query)
