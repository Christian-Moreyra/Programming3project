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
//https://www.geeksforgeeks.org/tmpfile-function-c/
//https://www.tutorialspoint.com/c_standard_library/c_function_tmpfile.htm
//https://stackoverflow.com/questions/18892076/how-to-create-a-temporary-text-file-in-c

//************************************************************************************************
//Compressed video into decompressed video
    //https://www.bugcodemaster.com/article/extract-images-frame-frame-video-file-using-ffmpeg
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
    
    //Join back together the images into a video
    //https://www.bugcodemaster.com/article/how-extract-and-join-video-files-using-ffmpeg
    //Join back together the text files into one large text file

    //Join threads together
    
    return EXIT_SUCCESS;
}

