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
/*
	Function to perform loops in the program. If a '[' is encountered, it checks whether the value of the 
	current array cell is 0 of not. Perform the loop only when current array cell has a non zero value
*/

int bfc::performLoop() {
	if(arr[arrPointer] == 0) {    // don't have to run the loop, just find the closing ] of the loop
		int loop = 1;             // if there are nested loops, still don't run them
		while(loop && progPointer < prog.length()) {  // loop till all the '[' and ']' are matched  
			progPointer++;
			if(prog[progPointer] == '[') loop++;   
			else if(prog[progPointer] == ']') loop--;
		}
		progPointer++;
		if(loop) {
			return 2;    // if no matching ']' found, return error
		}
	}

	else {      // if value at current cell not zero, run the loop
		int loopStart = progPointer, ret;     // store the starting of the loop
		progPointer++;
		while(progPointer < prog.length()) {
			if(prog[progPointer] == '[') {    // nested loop
				ret = performLoop();          // perform the inner loop
				if(ret == 2) {                // if no matching ']', print error
					progPointer = loopStart-1;
					return 2;
				}        
			} 
			if(operation() == 1) return 1;    // if the operation cannot be performed, return error code
			if(prog[progPointer] == ']') {  
				if(arr[arrPointer] != 0)      // current array cell not zero, loop not ended
					progPointer = loopStart;  // go to start of the loop 
				else {
					progPointer++;            // end the loop
					break;
				}
			}
			progPointer++;  // increment the program pointer till the end of the loop is not reached
		}
	}	
	return 0;   // loop performed successfully
}

/*
	Program to print the error 
*/
void bfc::printError(int code) {
	int row = 1, col = 0;   // find the row and col number of the error
	for(unsigned int i = 0; i < progPointer && i < prog.size(); ++i) {
		if(prog[i] == '\n') {
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
		cout << row << ":" << col << ": Unmatched '[' " << endl;
	}
}

/*
  Function called to run the entire code. It returns 0 on successful run and 1 otherwise
*/

int bfc::progRun() {
	int ret;
	while(progPointer < prog.length()) { // Program Pointer runs through the input
		if(prog[progPointer] == '[') {   // Beginning of a loop
			ret = performLoop();         // ret stores whether loop was successful
			if(ret != 0) {               // if loop was not successful, print corresponding error
				printError(ret);
				break;
			}
		}
		ret = operation();               // perform operation
		if(ret != 0) {
			printError(ret);             // print error if operation not successful
			break;
		}
		progPointer++;                   // increment program pointer otherwise
	}

	if(progPointer != prog.length())     // just return 1 if program had encountered errors
		return 1;
	return 0;
}