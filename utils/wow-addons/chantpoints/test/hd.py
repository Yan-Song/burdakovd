#!/usr/bin/python
# -*- coding: utf-8 -*-


import sys
import re

phrases = []

files = sys.argv[1:]

for f in files:
    lines = file(f).readlines()[1:] # without item name
    lines = map(lambda x: unicode(x, "utf-8"), lines)
    for l in lines:
        ph = l.split("\n")
        ph = filter(lambda x:x, ph)
        phrases += ph
    #print "\n".join(dphrases)
    #print "----------"

print "got phrases"

###########################################################################

#class word:
    #def __init__(_w):
        #self.w = _w
    #def __unicode__():
        #return "word("+self.w+")"

#class sym:
    #def __init__(_w):
        #self.w = _w
    #def __unicode__():
        #return "symbol("+self.w+")"

#class number: # integer
    #def __init__(_x):
        #self.x = _x
    #def __unicode__():
        #return "number("+str(self.x)+")"

###########################################################################

BASE=0; NUMBER=1; WORD=2

def isdigit(c):
    return c in "0123456789"

def isletter(c):
    return c.lower() in u"abcdefghijklmnopqrstuvwxyzабвгдеёжзийклмнопрстуфхцчшщъыьэюя"

def isspace(c):
    return c==" "

class lexem1:
    def next(self):
        if self.stream:
            self.c = self.stream[0]
            self.stream = self.stream[1:]
        else:
            self.c = None
    def __init__(self, s):
        self.result = []
        self.stream = s+" "
        self.next()
        state = BASE
        while self.c:
            if state==BASE:
                if isspace(self.c): self.next()
                elif isdigit(self.c):
                    d=0
                    state=NUMBER
                elif isletter(self.c):
                    w=""
                    state=WORD
                else:
                    self.result.append(self.c)
                    self.next()
            elif state==NUMBER:
                if isdigit(self.c):
                    d = d*10+ord(self.c)-ord('0')
                    self.next()
                else:
                    state=BASE
                    self.result.append(d)
            elif state==WORD:
                if isletter(self.c):
                    w += self.c
                    self.next()
                else:
                    state=BASE
                    self.result.append(w)

lex1 = map(lambda x: lexem1(x).result, phrases)

print "lex1 done"

#print "\n--------\n".join(map(lambda x: "|".join(map(unicode, x)), lex1))


class lexem2:
    def next(self):
        if self.stream:
            self.c = self.stream[0]
            self.stream = self.stream[1:]
        else:
            self.c = None
    def __init__(self, s):
        self.result = []
        self.stream = s+" "
        self.next()
        state = BASE
        while self.c:
            pass
        



