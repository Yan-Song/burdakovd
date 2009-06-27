#!/usr/bin/python
# -*- coding: utf8 -*-

import sys

#print sys.setrecursionlimit(200000)

#exit(0)

f = file("e2.in")
nn = int(f.readline())
print "nn=%d" % nn

ss = [i for i in f.read().split("\n") if i]

assert(len(ss)==nn)

#print ss
global n
#n = 2
global s
#s = "()"



#def concatsolve(pos):
    ##print "concatsolve("+str(pos)+")"
    #l = 0
    #w = -1
    #h = 0
    #b = 0
    #while (pos<n) and (s[pos]=='('):
        #iw, ih, ib, il = singlesolve(pos)
        #l += il
        #pos += il
        #w += 1 + iw
        #h = max(h, ih)
        #b += ib
    #return (w, h, b, l)

#def singlesolve(pos):
    ##print "singlesolve("+str(pos)+")"
    #if s[pos]!='(':
        #raise "( expected"
    #pos += 1
    #if s[pos]==')': return (1, 1, 1, 2)
    #else:
        #iw, ih, ib, il = concatsolve(pos)
        #w = iw + 2
        #h = ih + 1
        #b = w * h - ib
        #l = il + 2
        #if s[pos+il]!=')':
            #raise ") expected"
        #return (w, h, b, l)

#(()((())()))

for si in ss:
    global n
    global s
    stack = []
    #stack.append((1, 1, 1, 2))
    
    n = len(si)
    s = si
    pos = 0

    #print "s=<%s>" % s
    
    while(pos<n):
        if s[pos] == "(":
            pos += 1
            stack.append(None) # "("
        else:
            assert(s[pos] == ")")
            pos += 1
            if stack[-1] is None:
                stack[-1] = (1, 1, 1, 2)
            else:
                
                assert(type(stack[-1]) is tuple)
                assert(stack[-2] is None)
                iw, ih, ib, il = stack[-1]
                w = iw + 2
                h = ih + 1
                b = w * h - ib
                l = il + 2
                stack.pop()
                stack[-1] = (w, h, b, l)
        #print stack
        # объединение
        if (len(stack)>1) and (type(stack[-1]) is tuple) and (type(stack[-2]) is tuple):
            w, h, b, l = stack[-1]
            pw, ph, pb, pl = stack[-2]
            w = pw + 1 + w
            h = max(ph, h)
            b = pb + b
            l = pl + l
            stack.pop()
            stack[-1] = (w, h, b, l)
        #print stack
        
    assert(len(stack)==1)
    ans = stack[-1]
    #ans = (ans[0] - 2, 99

    
    #print s
    #print ans
    print ans[2]
    assert(ans[3]==n)


