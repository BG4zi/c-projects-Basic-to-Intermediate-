#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

void usage(char *program) {
  printf("USAGE:\n");
  printf("%s operator n1 n2\n", program);
  printf("operators:\n");
  printf("\t+, -, *, /\n");
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
  double firstNumber = atoi(a);
  
  if (*argv == NULL) {
	 usage(program);
	 exit(1);
  }
  char *b =  *argv++;
  double secondNumber = atoi(b);

  switch (*expr) {
  case '+':
	 printf("Result: %f", firstNumber+secondNumber);
	 break;
  case '-':
	 printf("Result: %f", firstNumber-secondNumber);
	 break;
  case '*':
	 printf("Result: %f", firstNumber*secondNumber);
	 break;
  case '/':
	 printf("Result: %f", firstNumber/secondNumber);
	 break;
  }	 
	 
  return 0;
}
