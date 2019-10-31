#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define MAX_BUFFER_SIZE 1000000

void readFile(int argc, char const *argv[]) {
    if(argc >= 2) {

    printf("The arguments supplied are:\n");

    for(int i = 1; i < argc; i++) {
        printf("%s\t \n", argv[i]);
    }

    FILE *file = fopen(argv[1], "rb");
    uint8_t buffer[MAX_BUFFER_SIZE];

    if(file == 0) {
        printf("file could not be open");
    } else {

        fseek(file, 0L, SEEK_END);
        int size = ftell(file);
        fseek(file, 0L, SEEK_SET);

        fread(buffer, sizeof(buffer), 1, file);

        for(int i = 0; i<size; i++) {

            if(i%4 == 0) {
                printf("\n%02x",buffer[i]);
                
            } else {
                printf("%02x",buffer[i]);
            }

        };
        
        // while ((x = fgetc( file ) ) != EOF ) {
        //   printf("%c", x );
        // };

        //9100 0d29 1400 0004 (binary)

        //91000D29 = 10010001000000000000110100101001

        //14000004 = 00010100000000000000000000000100

    };

    fclose(file);
        

    } else {
        printf("No Arguments\n");
    };

}