#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "bitmap.h"
#include "stego.h"


void print_help(char *path){
    printf("*** Image Steganography by LSB substitution ***\n\n"
           "Usage:  \n"
           "%s [-e] <text file to encode> <source bitmap> <destination bitmap>\n"
           "%s [-d] <encoded bitmap> <decoded file>\n\n"
           "-e : Encode text in image\n"
           "-d : Decode text from image\n",
           path, path);
}


int main(int argc, char **argv) 
{
    if ( argc != 5 && argc != 4 ) 
    {
        print_help(argv[0]);
        exit(1);
    }

    int mode;

    if (!strcmp(argv[1], "-e"))
        mode = 1;
    else if (!strcmp(argv[1], "-d"))
        mode = 0;
    else 
    {
        print_help(argv[0]);
        exit(1);
    }
//Create folder to hold images

//************************************************************************************************
//Compressed video into decompressed video
//Store into a folder of images to have them seperated
//************************************************************************************************

//Break apart text file into individual parts adn prepare them for threads
    
//************************************************************************************************

    //Encode file using threads
    if(mode)
    {
        //Insert one photo and first piece of text into a thread and have them execute squentially
        encode(argv[2], argv[3], argv[4]);
    } 
    else
    {
        //Insert one photo and first piece of text into a thread and have them execute squentially
        decode(argv[2], argv[3]);
    }

    return EXIT_SUCCESS;
}

