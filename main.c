#include <stdio.h>


struct node {
  char key[100];
  int value;
};

int main(int argc, char const *argv[])
{

  char a[100] = "Hi from teletype";

  printf("%s", a);


  if(argc >= 2) {
    printf("The arguments supplied are:\n");
      for(int i = 1; i < argc; i++)
      {
        printf("%s\t \n", argv[i]);
      }
  }

  FILE *file = fopen(argv[1], "r");

  if(file == 0) {
    printf("file could not be open");
  } else {

    int x;

    while ((x = fgetc( file ) ) != EOF ) {
      printf( "%c", x );
    }
  };


  fclose(file);
  return 0;
};
