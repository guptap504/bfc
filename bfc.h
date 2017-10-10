#include <iostream>
#include <stack>
#include <string>
#include <vector>

#define MAX 30000

using namespace std;

class bfc
{
  private:
	string prog;
	int arr[MAX];
	unsigned int arrPointer;
	unsigned int progPointer;
	int operation();
	int performLoop();
	void printError(int);

  public:
	bfc(string p)
	{
		prog = p;
		arrPointer = progPointer = 0;
	}
	int progRun();
};