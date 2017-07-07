CPPFLAGS = -O2 -Wall -Werror

bfc: bfc.cpp bfc.h main.cpp 
	g++ $(CPPFLAGS) bfc.h bfc.cpp main.cpp -o bfc