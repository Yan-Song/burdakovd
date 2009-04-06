#!/usr/bin/python

import sys
import re


otip = "".join(sys.stdin.readlines())
tip = otip[otip.find("'<table>")+1:otip.find("</table>'")]

assert(len(tip)>10)

tip = re.sub(r'(<.+?>)+','\n',tip,re.DOTALL);

tip = "\n".join(filter(lambda x:x, tip.split("\n")))

print tip

