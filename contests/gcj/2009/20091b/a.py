import re, sys

fi = file("e:\\in.txt", "r")
fo = file("e:\\out.txt", "w")


def getdata():
	n = int(fi.readline())
	text = "".join((fi.readline() for i in xrange(n)))

	text = text.replace(')', '),')

	drep = re.compile(r'([0-9.]+)', re.DOTALL)

	wrep = re.compile(r'([a-z]+)', re.DOTALL)

	text = re.sub(drep, r'\1,', text)
	text = re.sub(wrep, r'"\1",', text)

	#print text
	
	data = eval(text)

	#print data
	return data[0]


def solve(data, features):
	p = data[0]
	if(len(data)==1):
		return p
	feature = data[1]
	if(feature in features):
		return p * solve(data[2], features)
	else:
		return p * solve(data[3], features)

def getanimal():
	s = [i.strip() for i in fi.readline().split(" ")]
	return (s[0], s[2:])

tc = int(fi.readline())
for cas in xrange(tc):
	data = getdata()
	print data
	fa = int(fi.readline())
	animals = [getanimal() for i in xrange(fa)]
	fo.write("Case #%s:\n" % (cas+1))
	for a in animals:
		#print solve(data, a[1])
		fo.write("%.9f\n" % solve(data, a[1]))
