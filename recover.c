#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef uint8_t  BYTE;  // initiaties a "Byte"



int main(int argc, char *argv[])
{
    // Check for invalid usage
    if (argc != 2)
    {
        printf("Please enter only 1 fucking image!\n");
        return 1;
    }



    // Open input file
    FILE *inptr = fopen(argv[1], "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", argv[1]);
        return 4;
    }

    // allocate a 512-byte block of memory
    BYTE buffer[512];

    // declaring stuff for the loops
    int number = 0;
    char filename[8] = { 0 };
    FILE *img = NULL;
    bool flag = false;

    // reads the data in 512-byte chunks

    while (number < 50)
    {
        while (fread(buffer, sizeof(BYTE), 512, inptr) == 512)                                           // reads file - while the end of file has not been reached
        {
            if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && ((buffer[3] & 0xf0) == 0xe0))  // if start of new jpeg
            {
                if (number == 0) // if first jpg
                {
                    sprintf(filename, "000.jpg");
                    img = fopen(filename, "w");

                    fwrite(buffer, sizeof(BYTE), 512, img);
                    fclose(img);
                    number++;
                    flag = true;
                }


                else // if it's other jpegs
                {


                    sprintf(filename, "%03i.jpg", number);
                    img = fopen(filename, "w");
                    fwrite(buffer, sizeof(BYTE), 512, img);
                    fclose(img);  // need to close because we need to open the file for appending
                    number++;

                }
            }
            else if (flag == true)
            // if it's not the start of the new jpegs   // we append to prevent ourselves from overwriting the jpeg
            {
                img = fopen(filename, "a");
                fwrite(buffer, sizeof(BYTE), 512, img);
                fclose(img);

            }
        int bytes_read = ftell(inptr);


        }

        free(buffer);

        return 0;

    }

    fclose(img);
    fclose(inptr);
    
}
