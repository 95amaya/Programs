#include <stdio.h>
#include <stdlib.h>
#include "Hello.h"

int main(int argc, char *argv[])
{
  int i = 1;
	//printf("Hello World\n");
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
