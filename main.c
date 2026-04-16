/*
Name : Rushikesh Ghuge
Date : 06/02/2026

Title : MP3 Tag Reader and Editor (ID3v2)

Description :
MP3 files store metadata such as song title, artist name, album name,
year, music type, and comments using ID3 tags. In this project, an
MP3 Tag Reader and Editor is developed to read and modify ID3v2 tags
present in MP3 files. The application parses the MP3 file structure,
extracts ID3v2 frames, and updates them safely without corrupting
the original audio data.

View Mode :
Reads and displays MP3 metadata such as Title, Artist, Album, Year,
Music type, and Comments from the MP3 file.

Edit Mode :
Allows the user to modify specific MP3 tag fields using command-line
options while preserving the original audio content.

Features :
 - Reads ID3v2 MP3 tag information
 - Edits MP3 metadata without audio data loss
 - Supports command-line options for tag editing
 - Uses structured programming and file handling

Help / Usage Information :
To get help, run the program using:
    ./a.out --help

Available Options :
 -v  -> View MP3 file contents (ID3 tag information)

 -e  -> Edit MP3 file contents
        -t -> Edit song title
        -a -> Edit artist name
        -A -> Edit album name
        -y -> Edit year
        -m -> Edit music/content type
        -c -> Edit comment

Sample Input :
    ./mp3_tag -v sample.mp3
    ./mp3_tag -e -t "New Song Title" sample.mp3
    ./mp3_tag -e -a "New Artist" sample.mp3

Sample Output :
----------------------------------------------------------
         MP3 TAG READER AND EDITOR FOR ID3v2
----------------------------------------------------------

-----------------SELECTED VIEW DETAILS--------------------
TITLE   : Sunny Sunny - Yo Yo Honey Singh - [SongsPk.CC]
ARTIST  : Yo Yo Honey Singh - [SongsPk.CC]
ALBUM   : Yaariyan
YEAR    : 2003
MUSIC   : Bollywood Music - [SongsPk.CC]
COMMENT : engDownloaded From SongsPk.CC
----------------------------------------------------------

---------------DETAILS DISPLAYED SUCCESSFULLY-------------
----------------------------------------------------------

Conclusion :
This project demonstrates practical understanding of file handling,
binary data processing, and structured programming in C.
By implementing an MP3 Tag Reader and Editor, the project provides
hands-on experience with real-world multimedia file formats,
memory management, and low-level data manipulation techniques.
*/

#include<stdio.h>
#include<string.h>
#include"view.h"
#include"main.h"
#include"edit.h"

/* Determine the operation type based on arguments */
OperationType checkOperation(char *argv[])
{
   // Compare argument with view flag
    if(strcmp(argv[1],"-v") == 0) 
        return e_view;

    // Compare argument with edit flag
    else if(strcmp(argv[1],"-e") == 0) 
        return e_edit;

    // Compare argument with help flag
    else if(strcmp(argv[1],"--help") == 0) 
        return e_help;

    // Invalid operation
    else
        return e_error;
}


int main(int argc, char *argv[])
{
    TagData taginfo;   // structure to store tag information

    /* Check for minimum required arguments */
    if(argc < 2)
    {
        fprintf(stderr, "To view please pass like: ./a.out -v filename\n");
        fprintf(stderr, "To edit please pass like: ./a.out -e -t/-a/-A/-m/-y/-c changing_text filename\n");
        fprintf(stderr, "To get help please pass like: ./a.out --help\n");
        return 1;
    }

    /* ---------------- VIEW OPERATION ---------------- */
    if (checkOperation(argv) == e_view)
    {
        /* Check for filename */
        if(argc < 3)
        {
            fprintf(stderr, "To view please pass filename!\n");
            return 1;
        }

        /* Validate view arguments */
        if (validateViewArgc(argc, argv))
            return 1;

        /* Open the MP3 file */
        if (openFile(argv[2]))
            return 1;

        /* Display tag information */
        if(doView(&taginfo))
        {
            printf("---------------DETAILS DISPLAYED SUCCESSFULLY-------------\n");
        }
    }

    /* ---------------- EDIT OPERATION ---------------- */
    else if(checkOperation(argv) == e_edit)
    {
        /* Validate edit arguments */
        if (validateEditArgs(argc, argv))
            return 1;

        /* Decide tag name based on option */
        Tagname(argv);

        /* Get size of new tag text */
        int newsize = strlen(argv[3]);

        /* Edit the selected tag */
        editTag(newsize, tagname, argv[3], argv[4]);
    }

    /* ---------------- HELP OPERATION ---------------- */
    else if(checkOperation(argv) == e_help)
    {
        printf("1. -v -> to view mp3 file contents\n");
        printf("2. -e -> to edit mp3 file contents\n");
        printf("\t 2.1. -t -> to edit song title\n");
        printf("\t 2.2. -a -> to edit artist name\n");
        printf("\t 2.3. -A -> to edit album name\n");
        printf("\t 2.4. -y -> to edit year\n");
        printf("\t 2.5. -m -> to edit content\n");
        printf("\t 2.6. -c -> to edit comment\n");
    }

    /* ---------------- ERROR HANDLING ---------------- */
    else if(checkOperation(argv) == e_error)
    {
        printf("Please Pass Valid Input!\n");
    }
}
