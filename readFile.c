#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define MAX_ARRAY_SIZE 1000000

//Unused
//http://www.firmcodes.com/write-c-program-convert-little-endian-big-endian-integer/
unsigned int LitToBigEndian(unsigned int x)
{
	return (((x>>24) & 0x000000ff) | ((x>>8) & 0x0000ff00) | ((x<<8) & 0x00ff0000) | ((x<<24) & 0xff000000));
}

int readFile(int argc, char const *argv[], int instructionArray[]) {
    int c;
    int counter = 0;
    FILE *file = fopen(argv[1], "rb");
    
    if(argc >= 2) {

    printf("The arguments supplied are:\n");

    for(int i = 1; i < argc; i++) {
        printf("%s\t \n", argv[i]);
    }
    
    if(file == 0) {
        
        printf("file could not be open");
        
    } else {
    
        //while not at the end of file
        while(!feof(file)) {
          fread(&c, sizeof(c), 1, file);
          c = be32toh(c);
          instructionArray[counter] = c;
          counter++;
          printf("%02x\n", c);
        }
        
        printf("--\n");

    };

    fclose(file);
        

    } else {
        printf("No Arguments\n");
    };
    
    return counter;

}