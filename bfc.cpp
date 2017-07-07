#include "bfc.h"

using namespace std;

int bfc::operation() {
	switch(prog[progPointer]) {
		case '+': arr[arrPointer]++; return 0;
		case '-': arr[arrPointer]--; return 0;
		case '>': if(arrPointer == MAX-1) return 1;
				  arrPointer++; return 0;
		case '<': if(arrPointer == 0) return 1;
				  arrPointer--; return 0;
		case '.': cout << (char)arr[arrPointer]; return 0;
		case ',': cout << "Enter input: ";
				  cin  >> arr[arrPointer]; return 0;
		case '[':
		case ']': return 2;
		default: return 0;
	}
}

int bfc::performLoop() {
	if(arr[arrPointer] == 0) {
		loop.push(prog[progPointer]);
		while(!loop.empty() && progPointer < prog.length()) {
			progPointer++;
			if(prog[progPointer] == '[') loop.push(prog[progPointer]);
			else if(prog[progPointer] == ']') loop.pop();
		}
		progPointer++;
		if(!loop.empty()) {

			return 2;
		}
	}

	else {
		int loopStart = progPointer, ret;
		progPointer++;
		while(progPointer < prog.length()) {
			if(prog[progPointer] == '[') {
				ret = performLoop();
				if(ret == 2) return 2;
			} 
			if(operation() == 1) return 1;
			if(prog[progPointer] == ']') {
				if(arr[arrPointer] != 0)
					progPointer = loopStart-1;
				else {
					progPointer++;
					break;
				}
			}
			progPointer++;
		}
	}	
	return 0;
}

void bfc::printError(int code) {
	int row = 0, col = 0;
	for(char c: prog) {
		if(c == '\n') {
			row++;
			col = 0;
		}
		else
			col++;
	}
	if(code == 1) {
		cout << row << ":" << col << ": Program going out of bounds" << endl;
	}
	else {
		cout << row << ":" << col << ": Unmatched " << prog[progPointer] << endl;
	}
}

int bfc::progRun() {
	int ret;
	while(progPointer < prog.length()) {
		if(prog[progPointer] == '[') {
			ret = performLoop();
			if(ret != 0) {
				printError(ret);
				break;
			}
		}
		ret = operation();
		if(ret != 0) {
			printError(ret);
			break;
		}
		progPointer++;
	}
	if(progPointer != prog.length())
		return 1;
	return 0;
}