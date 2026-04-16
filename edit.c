#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "view.h"
#include "main.h"

/* Global buffer to store the selected ID3 tag name (e.g., TIT2, TPE1) */
char tagname[10];

/* Buffer to store new text entered by the user */
char newdata[100];   // allocate memory properly

/* Validate command-line arguments for edit mode */
int validateEditArgs(int argc, char *argv[])
{
    /* 1. Check for correct argument count */
    if (argc != 5)
    {
        fprintf(stderr,
                "Usage: ./a.out -e -t/-a/-A/-y/-m/-c new_text filename\n");
        return 1;
    }

    /* 2. Validate the edit option */
    if (strcmp(argv[2], "-t") != 0 &&
        strcmp(argv[2], "-a") != 0 &&
        strcmp(argv[2], "-A") != 0 &&
        strcmp(argv[2], "-y") != 0 &&
        strcmp(argv[2], "-m") != 0 &&
        strcmp(argv[2], "-c") != 0)
    {
        fprintf(stderr,
                "Error: Invalid edit option '%s'\n"
                "Allowed options: -t -a -A -y -m -c\n",
                argv[2]);
        return 1;
    }

    /* 3. Validate that input file has .mp3 extension */
    char *ext = strrchr(argv[4], '.');
    if (ext == NULL || strcmp(ext, ".mp3") != 0)
    {
        fprintf(stderr,
                "Error: Invalid file format. Only .mp3 files are allowed\n");
        return 1;
    }

    return 0;
}

/* Copy new tag data and return its length */
int sizeofnewdata(char *argv[])
{
    strcpy(newdata, argv[3]);          // copy new tag text
    int newsize = strlen(argv[3]);     // calculate length of new text
    return newsize;
}

/* Map command option to ID3v2 tag name */
void Tagname(char *argv[])
{
    if (strcmp(argv[2], "-t") == 0)
    {
        strcpy(tagname, "TIT2");   // Title
    }
    else if (strcmp(argv[2], "-a") == 0)
    {
        strcpy(tagname, "TPE1");   // Artist
    }
    else if (strcmp(argv[2], "-A") == 0)
    {
        strcpy(tagname, "TALB");   // Album
    }
    else if (strcmp(argv[2], "-y") == 0)
    {
        strcpy(tagname, "TYER");   // Year
    }
    else if (strcmp(argv[2], "-m") == 0)
    {
        strcpy(tagname, "TCON");   // Genre
    }
    else if (strcmp(argv[2], "-c") == 0)
    {
        strcpy(tagname, "COMM");   // Comment
    }
    else
    {
        tagname[0] = '\0';         // invalid option fallback
    }
}

/* Convert integer between big endian and little endian */
void endianswap(int *num, int size)
{
    char *ptr = (char *)num;
    char temp;

    /* Swap bytes from both ends */
    for (int i = 0; i < size / 2; i++)
    {
        temp = ptr[i];
        ptr[i] = ptr[size - 1 - i];
        ptr[size - 1 - i] = temp;
    }
}

/*Modify selected ID3v2 tag in MP3 file */
void editTag(int newsize, const char *tagname, const char *newdata, const char *filename)
{
    /* Open original MP3 file in read-binary mode */
    FILE *fptr = fopen("sample.mp3", "rb");
    if (!fptr)
    {
        perror("File open failed");
        return;
    }

    /* Create a temporary file to store updated data */
    FILE *temp = fopen("temp.mp3", "wb");
    if (!temp)
    {
        perror("Temp file creation failed");
        fclose(fptr);
        return;
    }

    /* Copy the 10-byte ID3 header */
    char buffer[10];
    fread(buffer, 1, 10, fptr);
    fwrite(buffer, 1, 10, temp);

    char tag[5] = {0};   // buffer to store frame ID
    int oldsize;         // size of existing tag data
    char flag[2];        // flag bytes
    char ch;             // single byte buffer

    /* Read frames until EOF */
    while (1)
    {
        if (fread(tag, 1, 4, fptr) != 4)
            break;

        /* Stop when padding (null bytes) is encountered */
        if (tag[0] == '\0')
            break;

        fread(&oldsize, 1, 4, fptr);     // read frame size
        fread(flag, 1, 2, fptr);         // read frame flags

        endianswap(&oldsize, sizeof(oldsize)); // convert size to little endian

        /* If tag matches the user-selected tag */
        if (strcmp(tag, tagname) == 0)
        {
            fwrite(tag, 1, 4, temp);     // write tag name

            int tempsize = newsize + 1;  // include encoding byte
            endianswap(&tempsize, sizeof(tempsize));
            fwrite(&tempsize, 1, 4, temp); // write new size

            fwrite(flag, 1, 2, temp);    // write flags

            fputc(0x00, temp);           // text encoding (ISO-8859-1)
            fwrite(newdata, 1, newsize, temp); // write updated data

            fseek(fptr, oldsize, SEEK_CUR); // skip old data
        }
        else
        {
            /* Copy unchanged frame */
            fwrite(tag, 1, 4, temp);

            int tempsize = oldsize;
            endianswap(&tempsize, sizeof(tempsize));
            fwrite(&tempsize, 1, 4, temp);

            fwrite(flag, 1, 2, temp);

            /* Copy existing data byte-by-byte */
            while (oldsize--)
            {
                fread(&ch, 1, 1, fptr);
                fwrite(&ch, 1, 1, temp);
            }
        }
    }

    /* remaining audio data */
    fwrite(tag, 1, 4, temp);
    while (fread(&ch, 1, 1, fptr) == 1)
        fwrite(&ch, 1, 1, temp);

    /* Close files */
    fclose(fptr);
    fclose(temp);

    /* Replace original MP3 with modified file */
    remove("sample.mp3");
    rename("temp.mp3", "sample.mp3");

    printf("Tag %s edited successfully\n", tagname);
}
