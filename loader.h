#ifndef LOADER_H
#define LOADER_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#define MAX_RECORD 100
#define MAX_LINE_LENGTH 1024

// Structure to hold a Text record
typedef struct {
    int start_address;
    int length;
    char object_code[MAX_LINE_LENGTH];
} TextRecord;

// Structure to hold a Modification record
typedef struct {
    int address;
    int length;
}ModRecord;

#endif 