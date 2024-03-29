import os
import re
import sys

string_constant = r'"(?:\\\\|\\"|[^"])*"'
numeric_constant = r'[0-9\.]+'

pattern = re.compile(string_constant + r'|' + numeric_constant, re.DOTALL)
comments = re.compile(r'\-\-[^"]*')

path = "."

def calculate(text):
	ans = len(set(map(str, pattern.findall(text))))
	return ("%d constants (%d%%)" % (ans, ans * 100 / (2 ** 18)), ans)

def calcstats(filename):
	text = file(path + "/" + filename, "r").read()
	text = comments.sub("", text)
	ans = calculate(text)
	return ("%s: %s" % (filename, ans[0]), ans[1])
	
def main():
	if len(sys.argv) > 1:
		stat = calcstats(sys.argv[1])
		print "constant_count = %s" % repr(stat)
	else:
		stats = [calcstats(filename) for filename in os.listdir(path) if filename.endswith(".lua")]
		stats.sort(key = lambda x: -x[1])
		for x in stats:
			print x[0]

if __name__ == "__main__":
	main()
