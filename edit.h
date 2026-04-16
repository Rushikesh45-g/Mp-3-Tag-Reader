#ifndef EDIT_H
#define EDIT_H

/* Standard input-output library */
#include <stdio.h>

/* Standard library for memory management and utilities */
#include <stdlib.h>

/* Used to store ID3 tag identifiers like TIT2, TPE1, etc. */
extern char tagname[10];

/* Validate command-line arguments for MP3 edit mode */
int validateEditArgs(int argc, char *argv[]);

/* Copy new tag data and return its size */
int sizeofnewdata(char *argv[]);

/* Map edit option to corresponding ID3v2 tag name */
void Tagname(char *argv[]);

/* Edit the selected ID3 tag in the MP3 file */
void editTag(int newsize, const char *tagname, const char *newdata, const char *filename);

#endif
