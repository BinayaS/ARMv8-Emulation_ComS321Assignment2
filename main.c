#include <stdio.h>

struct node {
  char key[100];
  int value;
};

int main(int argc, char const *argv[])
{

  struct node n[60];

  n.key = "";

  char a[100] = "Hi from teletype";

  printf("%s", a);

  return 0;
}
