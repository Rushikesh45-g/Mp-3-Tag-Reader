#include "view.h"
#include "main.h"
#include<string.h>

/* Global file pointer for source MP3 file */
FILE* srcFile = NULL;

/* Validate input filename for view operation */
int validateViewArgc(int argc, char *argv[])
{
    /* Find the dot character in filename */
    char *dot = strchr(argv[2], '.');

    /* Check for valid .mp3 extension */
    if (!dot || strcmp(dot, ".mp3") != 0)
    {
        fprintf(stderr, "File extension is not correct\n");
        return 1;
    }
    return 0;
}

/*  Open MP3 file in read-binary mode */
int openFile(char *filename)
{
    /* Open source MP3 file */
    srcFile = fopen("sample.mp3", "rb");
    if (!srcFile)
    {
        perror("fopen");
        return 1;
    }
    return 0;
}

/* Convert integer between big endian and little endian */
void swap(int *num, int size)
{
    char *ptr = (char *)num;
    char temp;

    /* Swap bytes to change endianness */
    for (int i = 0; i < size / 2; i++)
    {
        temp = ptr[i];
        ptr[i] = ptr[size - 1 - i];
        ptr[size - 1 - i] = temp;
    }
}

/* Read and display ID3v2 tag information */
int doView(TagData *taginfo)
{
    char buffer[5];        // buffer to store frame ID
    int size;              // frame size
    char tag_data[1000];   // buffer to store tag text

    /* Skip the 10-byte ID3 header */
    fseek(srcFile, 10, SEEK_SET);   

    /* Display header information */
    printf("----------------------------------------------------------\n");
    printf("\t MP3 TAG READER AND EDITOR FOR ID3v2\t\n");
    printf("----------------------------------------------------------\n\n");
    printf("-----------------SELECTED VIEW DETAILS--------------------\n");

    /* Read first 6 ID3 frames */
    for (int i = 0; i < 6; i++)
    {
        /* Read frame ID */
        fread(buffer, 1, 4, srcFile);
        buffer[4] = '\0';

        /* Read frame size and convert endianness */
        fread(&size, 1, 4, srcFile);
        swap(&size, sizeof(size));

        /* Skip text encoding byte and flags */
        fseek(srcFile, 3, SEEK_CUR);   

        /* Prevent buffer overflow */
        if (size - 1 >= sizeof(tag_data))
        {
            fseek(srcFile, size - 1, SEEK_CUR);
            continue;
        }

        /* Read tag data */
        fread(tag_data, 1, size - 1, srcFile);
        tag_data[size - 1] = '\0';

        /* Identify tag and print corresponding value */
        if(strcmp(buffer,"TIT2") == 0)
        {
            printf("TITLE   : %s\n",tag_data);
            taginfo -> title = tag_data;
        }
        else if(strcmp(buffer,"TPE1") == 0)
        {
            printf("ARTIST  : %s\n",tag_data);
            taginfo -> artist = tag_data;
        }
        else if(strcmp(buffer,"TALB") == 0)
        {
            printf("ALBUM   : %s\n",tag_data);
            taginfo -> album = tag_data;
        }
        else if(strcmp(buffer,"TYER") == 0)
        {
            printf("YEAR    : %s\n",tag_data);
            taginfo -> year = tag_data;
        }
        else if(strcmp(buffer,"TCON") == 0)
        {
            printf("MUSIC   : %s\n",tag_data);
            taginfo -> music = tag_data;
        }
        else if(strcmp(buffer,"COMM") == 0)
        {
            taginfo -> comment = tag_data;
            printf("COMMENT : ");
            int newsize = size;
            for(int i=0;i<size;i++)
            {
                printf("%c",taginfo->comment[i]);
            }
            printf("\n");
        }

        /* Clear buffers for next iteration */
        memset(buffer,0,5);
        memset(tag_data,0,1000);
    }

    printf("----------------------------------------------------------\n\n");

    /* Close the source file */
    fclose(srcFile);

    return 1;
}
