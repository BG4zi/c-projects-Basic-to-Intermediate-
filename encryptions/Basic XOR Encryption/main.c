#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void usage(char* program) {
  printf("Usage:\n");
  printf("\t%s <key> <text_file>\n", program);
  printf("\t <key> is a character");
  printf("\t <text_file> is a string that refers to the path of the file");
  
}

long read_file(char* program, char* file_path,char** text) {
  FILE* file = fopen(file_path, "r"); 
  if (file == NULL) {
	 fprintf(stderr, "ERROR: Could not read the file\n");
	 usage(program);
	 exit(1);
  }

  fseek(file, 0, SEEK_END);
  long file_len = ftell(file);
  rewind(file);
  
  *text = (char*) malloc(file_len + 1);

  if (*text == NULL) {
	 fprintf(stderr, "ERROR: Could not allocate memory for plain text\n");
	 exit(1);
  }

  fread(*text, 1, file_len, file);

  fclose(file);

  return file_len;
}


int main(int argc, char *argv[])
{
  char* program = argv[0];
  if (argc < 3) {
	 fprintf(stderr, "ERROR: The program requires at least 2 subcommands\n");
	 usage(program);
	 exit(1);
  }

  char key = argv[1][0];
  char* text_path = argv[2];
  char* plain_text;

  printf("Key; %c,\nText Path: %s\n", key, text_path);

  long text_len = read_file(program, text_path, &plain_text);
  
  printf("TEXT: %s\nTEXT LEN: %d\n", plain_text, text_len);
  
  char* ciphered_text = (char*) malloc(text_len + 1);
  for (long i = 0; i < text_len; ++i) {
	 ciphered_text[i] = plain_text[i] ^ key;
  }

  printf("Ciphered_text: %s", ciphered_text);
  
  free(plain_text);
  free(ciphered_text);
  
  return 0;
}
