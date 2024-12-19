#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

void usage(char *program) {
  printf("USAGE:\n");
  printf("%s operator n1 n2\n", program);
  printf("operators:\n");
  printf("\t+, -, x, /\n");
}


int main(int argc, char *argv[]) {

  char *program = *argv++;

  if (*argv == NULL) {
	 usage(program);
	 exit(1);
  }
  char *expr = *argv++;

  if (*argv == NULL) {
	 usage(program);
	 exit(1);
  }
  char *a =  *argv++;
  double firstNumber = atof(a);
  
  if (*argv == NULL) {
	 usage(program);
	 exit(1);
  }
  char *b =  *argv++;
  double secondNumber = atof(b);

  switch (*expr) {
  case '+':
	 printf("Result: %f\n", firstNumber+secondNumber);
	 break;
  case '-':
	 printf("Result: %f\n", firstNumber-secondNumber);
	 break;
  case 'x':
	 printf("Result: %f\n", ((double)firstNumber)*((double)secondNumber));
	 break;
  case '/':
	 printf("Result: %f\n", firstNumber/secondNumber);
	 break;
  default:
	 printf("Unknown Operator!\n");
	 exit(1);
	 break;
  }	 
	 
  return 0;
}
