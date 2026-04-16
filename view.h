#ifndef VIEW_H
#define VIEW_H

/* Standard input-output library */
#include <stdio.h>

/* Standard library for general utilities */
#include <stdlib.h>

/* Store ID3v2 tag information of an MP3 file */
typedef struct {
    char *title;    // Pointer to song title
    char *artist;   // Pointer to artist name
    char *album;    // Pointer to album name
    char *year;     // Pointer to release year
    char *music;    // Pointer to music/genre information
    char *comment;  // Pointer to comment field
} TagData;


/* Validate command-line arguments for view mode */
int validateViewArgc(int argc, char *argv[]);

/* Read and display MP3 tag information */
int doView(TagData *taginfo);

/* Open MP3 file in read mode */
int openFile(char *filename);

#endif
