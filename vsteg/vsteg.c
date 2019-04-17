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

void *decode_thr_func(void *arg)
{
	printf("\n\nENTERED DECODE\n\n");
        thread_data_t *data = (thread_data_t *)arg;

        char text [25], image [25];

        sprintf(image, "img%06d.bmp", (data -> tid) + 1);

	sprintf(text, "subtext%02d.txt", (data -> tid));
	
	printf("image = %s, subtext = %s, Thread ID = %d\n", image, text, data -> tid);
	printf("\nBefore Decode\n");
	encode("subtext03","img000004.bmp","img000004.bmp");
	printf("AFTER encode\n");
        decode("img000004.bmp", "text.txt");
	printf("\nAfter Decode\n");
	
        pthread_exit(NULL);
}

void *encode_thr_func(void *arg)
{
	thread_data_t *data = (thread_data_t *)arg;

	char text [25], image [25], fimage [25];
	
	sprintf(text, "subtext%02d", (data -> tid));

	sprintf(image, "img%06d.bmp", (data -> tid) + 1);
	
	sprintf(fimage, "img%06d.bmp", (data -> tid) + 1);
	
	encode(text, image, fimage);

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
    
    char inputText[100], inputVideo[100], outputVideo[100];

    printf("argv[1] = %p, %s\nargv[2] = %p, %s\nargv[3] = %p, %s\nargv[4] = %p, %s\n", argv[1], argv[1],argv[2], argv[2], argv[3], argv[3], argv[4], argv[4]);
    //ENCODING
    if(mode)
    {
	printf("ENTERING ENCODE\n");
	sprintf(inputText, "split -l 1000 --numeric-suffixes ../%s subtext", argv[2]);

	system(inputText);

	printf("\ninputText = %s\n", inputText);
	
	FILE *fp;

	fp = popen("find subtext* -type f | wc -l", "r");

	fscanf(fp, "%d", &NUM_THREADS);
    	
	printf("NUM of THREADS = %d", NUM_THREADS);

	sprintf(inputVideo, "ffmpeg -i ../%s -vf fps=30 img%%06d.bmp -hide_banner", argv[3]);

	system(inputVideo);
    	
    	pthread_t thr [NUM_THREADS];
	
    	thread_data_t thr_data [NUM_THREADS];    	
	
	for(i = 0; i < NUM_THREADS; ++i)
	{
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
	
	sprintf(outputVideo, "ffmpeg -r 30 -f image2 -s 640x360 -i img%%06d.bmp -vcodec libx264 -crf 25  -pix_fmt yuv420p ../%s", argv[4]);

	system(outputVideo);
    }
    else //DECODING
    {
	printf("\n\nBREAKING APPART VIDEO\n\n");

	sprintf(inputVideo, "ffmpeg -i ../%s -vf fps=30 img%%06d.bmp -hide_banner", argv[2]);

        system(inputVideo);

	printf("\n\nGETING NUMBER OF THREADS\n\n");
	FILE *fp;

        fp = popen("find img* -type f | wc -l", "r");

        fscanf(fp, "%d", &NUM_THREADS);

	NUM_THREADS = 1;

	printf("\n\nNUM_THREADS = %d", NUM_THREADS);

	printf("\n\nSTARTING UP THREADS\n\n");
        pthread_t thr [NUM_THREADS];

        thread_data_t thr_data [NUM_THREADS];

	printf("\n\nLAUNCHING THREADS\n\n");
        for(i = 0; i < NUM_THREADS; ++i)
        {
                thr_data[i].tid = i;
                if((rc = pthread_create(&thr[i], NULL, decode_thr_func, &thr_data[i])))
                {
                        fprintf(stderr, "error: pthread_create, rc: %d\n", rc);
                        return EXIT_FAILURE;
                }
        }

        // block until all threads complete 
        for (i = 0; i < NUM_THREADS; ++i)
        {
                pthread_join(thr[i], NULL);
        }
	printf("\n\nJOINED ALL THREADS\n\n");
     









	//decode("eimg00001.bmp","decoded_text.txt");
	//ffmpeg -r 30 -f image2 -s 640x359 -i img%04d.bmp -vcodec libx264 -crf 25  -pix_fmt yuv420p decoded_video.mp4
    }

    //ffmpeg -r 30 -f image2 -s 640x359 -i img%04d.bmp -vcodec libx264 -crf 25  -pix_fmt yuv420p test.mp4

    //Can be implemented in version 2 to make it more efficient
    //ffmpeg -i “concat:test.mp4|video2.avi” output_video.avi

//    system("rm img*");
//    system("rm subtext*");

    
    return EXIT_SUCCESS;
}
