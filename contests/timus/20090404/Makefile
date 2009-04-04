all: ${PROBLEM}

${PROBLEM}: ${PROBLEM}.cpp
	g++ -g ${PROBLEM}.cpp -o ${PROBLEM}

check: ${PROBLEM}
	@checker ./${PROBLEM} ${PROBLEM}-*.in

${PROBLEM}.cpp: tpl.cpp
	@test -e ${PROBLEM}.cpp || (cp tpl.cpp ${PROBLEM}.cpp && echo "Copying template to ${PROBLEM}.cpp")

clean:
	rm -f *.o *~
	for i in *.cpp; do rm -f `basename $$i .cpp`; done

run: ${PROBLEM}
	./${PROBLEM}

