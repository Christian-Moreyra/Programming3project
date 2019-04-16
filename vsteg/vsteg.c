#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "bitmap.h"
#include "stego.h"
#include <pthread.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

void print_help(char *path){
    printf("*** Image Steganography by LSB substitution ***\n\n"
           "Usage:  \n"
           "%s [-e] <text file to encode> <source bitmap> <destination bitmap>\n"
           "%s [-d] <encoded bitmap> <decoded file>\n\n"
           "-e : Encode text in image\n"
           "-d : Decode text from image\n",
           path, path);
}

typedef struct _thread_data_t
{
	int tid;
	double stuff;
}thread_data_t;

void *encode_thr_func(void *arg)
{
	printf("\n\n\n\n\n\n helllllooooooo \n\n\n\n\n\n");

	thread_data_t *data = (thread_data_t *)arg;

	char text [15];
	
	sprintf(text, "subtext%02d", (data -> tid));
	
	printf("%s", text);

	char image [15];

	sprintf(image, "img%06d.bmp", (data -> tid) + 1);

	char fimage [15];
	
	sprintf(fimage, "img%06d.bmp", (data -> tid) + 1);
	
	encode(text, image, fimage);

	printf("hello from thr_func, thread id: %d\n", data->tid);

	pthread_exit(NULL);
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
    
    //Number of frames needed to have code run
    int NUM_THREADS = 0, i, rc;
    
    //ENCODING
    if(mode)
    {
    	system("split -l 1000 --numeric-suffixes ../text_to_encode.txt subtext");
    	//system("split -l 1000 --numeric-suffixes argv[] subtext");
    	
	FILE *fp;

	fp = popen("find subtext* -type f | wc -l", "r");

	fscanf(fp, "%d", &NUM_THREADS);

    	//Can be implemented in version 2 to make it more efficient
    	//ffmpeg -i video.m4v -t 00:00:10 -c copy workingVideo.mp4 -ss 00:00:10 -codec copy leftOver.mp4
    	
    	system("ffmpeg -i ../part1.m4v -vf fps=30 img%06d.bmp -hide_banner");
    	
	printf("\n\n\n %d \n\n\n", NUM_THREADS);

    	pthread_t thr [NUM_THREADS];
	
    	thread_data_t thr_data [NUM_THREADS];    	
	
	printf("\n\n\n Before FOR LOOP %d\n\n\n\n\n", NUM_THREADS);
	
	for(i = 0; i < NUM_THREADS; ++i)
	{
		printf("\n\n\n\n In FOR LOOP \n\n\n\n");
		thr_data[i].tid = i;
		if((rc = pthread_create(&thr[i], NULL, encode_thr_func, &thr_data[i])))
		{
			fprintf(stderr, "error: pthread_create, rc: %d\n", rc);
			return EXIT_FAILURE;
		}
	}
	
	/* block until all threads complete */
	for (i = 0; i < NUM_THREADS; ++i) 
	{
		pthread_join(thr[i], NULL);
	}
	
        //encode("subtext00", "img00001.bmp", "eimg00001.bmp");
	system("ffmpeg -r 30 -f image2 -s 640x359 -i img%06d.bmp -vcodec libx264 -crf 25  -pix_fmt yuv420p encoded_video.m4v");
    }
    else //DECODING
    {
	//Can be implemented in version 2 to have it check every 10 to see if it is EOF and break
        //Insert one photo and first piece of text into a thread and have them execute squentially 
        decode("eimg00001.bmp","decoded_text.txt");
	//ffmpeg -r 30 -f image2 -s 640x359 -i img%04d.bmp -vcodec libx264 -crf 25  -pix_fmt yuv420p decoded_video.mp4
    }

    //ffmpeg -r 30 -f image2 -s 640x359 -i img%04d.bmp -vcodec libx264 -crf 25  -pix_fmt yuv420p test.mp4

    //Can be implemented in version 2 to make it more efficient
    //ffmpeg -i “concat:test.mp4|video2.avi” output_video.avi

    system("rm img*");
    system("rm subtext*");

    
    return EXIT_SUCCESS;
}

