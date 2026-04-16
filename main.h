#ifndef TYPES_H
#define TYPES_H

/* ---------------------------------------------------------
   User-defined type aliases
   --------------------------------------------------------- */

/* Unsigned integer type alias for better readability */
typedef unsigned int uint;

/* Represent different program operation modes */
typedef enum
{
    e_view,   // View MP3 tag information
    e_edit,   // Edit MP3 tag information
    e_help,   // Display help/usage instructions
    e_error   // Invalid or unsupported operation
} OperationType;

#endif
