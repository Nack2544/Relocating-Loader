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
        char line[MAX_LINE_LENGTH];

        // removes newlines
        while (fgets(line, sizeof(line), file) != NULL) {
            size_t len = strlen(line);
            if (len > 0 && (line[len - 1] == '\n' || line[len - 1] == '\r')) {
                line[len - 1] = '\0';
                len--;
            }

            if (len == 0) continue;

            switch (line[0]) {
                    // H name startaddr proglen
                case 'H': {

                    char name[7] = {0};
                    char start_str[7] = {0};
                    char len_str[7] = {0};

                    // might need to change format string
                    sscanf(line, "H%6s%6s%6s", name, start_str, len_str);

                    *start_addr = (int)strtol(start_str, NULL, 16);
                    *prog_len = (int(strtol(len_str, NULL, 16);

                    *exec_addr = *start_addr;
                    break;
                }

                // T startaddr length opcode
                case 'T': {

                    char addr_str[7] = {0};
                    char length_str[7] = {0};
                    char obj_code[MAX_LINE_LENGTH] = {0};

                    sscanf(line, "T%6s%2s%s", name, start_str, len_str);
        
                    *t_records[*t_count].start_address = (int)strtol(start_str, NULL, 16);
                    *t_records[*t_count].length = (int(strtol(len_str, NULL, 16);
                    strcopy(t_records[*t_count].object_code, obj_code);

                    (*t_count)++;
                    break;
                }

                // M address length (+/- symbol)
                case 'M': {

                    char addr_str[7] = {0};
                    char length_str[3] = {0};

                    sscanf(line, "M&6s&2s", addr_str, length_str);
        
                    *m_records[*m_count].address = (int)strtol(start_str, NULL, 16);
                    *m_records[*m_count].length = (int(strtol(len_str, NULL, 16);

                    (*m_count)++;
                    break;
                }

                // E execaddr
                case 'E': {

                    char exec_str[7] = {0};
                    
                    sscanf(line, "E%6s", exec_str) == 1) {
                        *exec_records = (int)strtol(start_str, NULL, 16);
                    }
                    // done with file
                    return;
                }

            }
            // ignores anything else (comments, breaks)
            default:
                break;
        }
 }
 void relocate_and_print(TextRecord *t_records, int t_count, ModRecord *m_records, int m_count, int relocation_addr, int exec_addr, const char *machine_type){

 }
