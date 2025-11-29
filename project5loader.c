#include "loader.h"

// Count the total arguments input and use argv to read each arguments
int main(int argc, char *argv[]) {
    
    // Ensure correct number of arguments, if arguments are not correct, print usage message
    // stderr is the standard error stream - it use to print error messages, warnings, and diagnostics.
    if(argc != 4){
        fprintf(stderr, "Error: %s Requires 4 arguments with <object_file> <relocation_address> <machine_type(SIC/SICXE)>\n", argv[0]);
        
        return 1;
    }


    // variable for arguments input 
    // strtol is used to convert hex string into integer 

    char *object_file = argv[1];
    int relocation_address = (int)strtol(argv[2], NULL, 16);
    char *machine_type = argv[3];


    // ensure the machine type is either be 'SIC' or 'SICXE'
    if(strcmp(machine_type, 'SIC') != 0 && strcmp(machine_type, "SICXE") != 0){
        fprintf(stderr, "Invalid machine type. Must be 'SIC' or 'SICXE'. \n");
        return 1;
    }


    // check if the file existed 
    FILE *file = fopen(object_file, "r");
    if(file == NULL){
        printf("Error: %s opening a file", object_file);
        return 1;
    }


    // store T and M records which will be used it for parsed object file data
    TextRecord t_records[MAX_LINE_LENGTH];
    ModRecord m_records[MAX_RECORD];

    // initialize counters and values
    int t_count = 0, m_count = 0, start_addr = 0, prog_len = 0, exec_addr = 0;

    // parse object file
    // Function prototypes
    void parse_object_file(FILE *file, TextRecord *t_records, int *t_count, ModRecord *m_records, int *m_count, int *start_addr, int *prog_len, int *exec_addr);
    void relocate_and_print(TextRecord *t_records, int t_count, ModRecord *m_records, int m_count, int relocation_addr, int exec_addr, const char *machine_type);

    fclose(file);
    return 0;
}



 void parse_object_file(FILE *file, TextRecord *t_records, int *t_count, ModRecord *m_records, int *m_count, int *start_addr, int *prog_len, int *exec_addr){
    
 }
 void relocate_and_print(TextRecord *t_records, int t_count, ModRecord *m_records, int m_count, int relocation_addr, int exec_addr, const char *machine_type){

 }
