#!/usr/bin/python

import sys
import re

ans = []

for line in sys.stdin.readlines():
    ans += re.findall("http\:\/\/ru\.wowhead\.com\/\?item\=(\d{2,10})", line)

ans = map(int, ans)

ans = list(set(ans))

ans.sort()

print " ".join(map(str,ans))
