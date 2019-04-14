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
    system("split -l 1000 --numeric-suffixes ../text_to_encode.txt subtext");

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

    int numOfFrames = 7;

    

    //split -l 1000 --numeric-suffixes text_to_encode.txt subtext
    //
    //find subtext* -type f | wc -l

    //Can be implemented in version 2 to make it more efficient
    //ffmpeg -i video.m4v -t 00:00:10 -c copy workingVideo.mp4 -ss 00:00:10 -codec copy leftOver.mp4

    //ffmpeg -i workingVideo.m4v -vf fps=30 img%04d.bmp -hide_banner

    //Encode file using threads
    if(mode)
    {
        //Insert one photo and first piece of text into a thread and have them execute squentially
        encode(argv[2], argv[3], argv[4]);
	//ffmpeg -r 30 -f image2 -s 640x359 -i img%04d.bmp -vcodec libx264 -crf 25  -pix_fmt yuv420p encoded_video.mp4
    } 
    else
    {
	//Can be implemented in version 2 to have it check every 10 to see if it is EOF and break
        //Insert one photo and first piece of text into a thread and have them execute squentially 
        decode(argv[2], argv[3]);
	//ffmpeg -r 30 -f image2 -s 640x359 -i img%04d.bmp -vcodec libx264 -crf 25  -pix_fmt yuv420p decoded_video.mp4
    }

    //ffmpeg -r 30 -f image2 -s 640x359 -i img%04d.bmp -vcodec libx264 -crf 25  -pix_fmt yuv420p test.mp4

    //Can be implemented in version 2 to make it more efficient
    //ffmpeg -i “concat:test.mp4|video2.avi” output_video.avi
    
    return EXIT_SUCCESS;
}

