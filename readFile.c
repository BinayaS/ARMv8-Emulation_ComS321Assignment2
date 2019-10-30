#include <stdio.h>

void readFile(int argc, char const *argv[]) {
    if(argc >= 2) {

    printf("The arguments supplied are:\n");

        for(int i = 1; i < argc; i++) {
            printf("%s\t \n", argv[i]);
        }

        FILE *file = fopen(argv[1], "r");

        if(file == 0) {
            printf("file could not be open");
        } else {

            //TODO: read the file and feed it the right files into the decoder
            int x;

            while ((x = fgetc( file ) ) != EOF ) {
              printf("%c", x );
            }
        };

        fclose(file);

    } else {
        printf("No Arguments\n");
    };

}