#include "bfc.h"
#include <fstream>
using namespace std;

int main(int argc, char const *argv[]) {	
	if(argc == 1) {
		cout << "Enter a file name: " << endl;
		return 1;
	}
	ifstream fi(argv[1]);
	string str,line;
	while(getline(fi,line)){
		str+=line;
	}
	fi.close();
	bfc myprog(str);
	myprog.progRun();
	cout << endl;
	return 0;
}