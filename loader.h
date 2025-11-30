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

void parse_object_file(FILE *file,
                       TextRecord *t_records, int *t_count,
                       ModRecord *m_records, int *m_count,
                       int *start_addr, int *prog_len, int *exec_addr);

void relocate_and_print(TextRecord *t_records, int t_count,
                        ModRecord *m_records, int m_count,
                        int relocation_addr, int exec_addr,
                        const char *machine_type);

#endif 
