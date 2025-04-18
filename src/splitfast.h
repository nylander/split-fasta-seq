#ifndef SPLITFAST_H
#define SPLITFAST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Constants
#define STR_MAX_SIZE 400 // Max length for fasta header
#define VERSION "1.0.0"  // Program version

// Function Prototypes
void print_wrapped_sequence(const char *sequence, size_t length, long int wraplength);
void extract_first_string(char *header);

#endif // SPLITFAST_H
