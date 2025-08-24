quadratic: quadratic_main.o quadratic_input.o quadratic_print.o \
		quadratic_solve.o quadratic_tests.o quadratic_utils.o
	g++ -o quadratic quadratic_main.o quadratic_input.o \
		quadratic_solve.o quadratic_print.o quadratic_tests.o quadratic_utils.o

quadratic_main.o: quadratic_main.cpp
	g++ -c quadratic_main.cpp
quadratic_input.o: quadratic_input.cpp
	g++ -c quadratic_input.cpp
quadratic_print.o: quadratic_print.cpp
	g++ -c quadratic_print.cpp
quadratic_solve.o: quadratic_input.cpp
	g++ -c quadratic_solve.cpp
quadratic_tests.o: quadratic_tests.cpp
	g++ -c quadratic_tests.cpp
quadratic_utils.o: quadratic_utils.cpp
	g++ -c quadratic_utils.cpp
clean:
	rm quadratic quadratic_main.o quadratic_input.o quadratic_print.o \
		quadratic_solve.o quadratic_tests.o quadratic_utils.o
