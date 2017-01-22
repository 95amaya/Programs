#include <iostream>
using namespace std;
#include "Hello.h"

int main(int argc, char *argv[])
{
  int i = 1;
	//std::cout << "Hello World!" << std::endl; // without namespace
	//cout << "Hello World!!!" << endl; // With namespace
	hello();
  if(argc > 1) {
    while(i < argc) {
      sayHi(argv[i]);
      sayBye(argv[i]);
      i++;
    }
  }

  return 0;
}

