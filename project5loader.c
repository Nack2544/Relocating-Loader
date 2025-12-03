#include "loader.h"

// parse object file
// Function prototypes
void parse_object_file(FILE *file, TextRecord *t_records, int *t_count, ModRecord *m_records, int *m_count, int *start_addr, int *prog_len, int *exec_addr);
void relocate_and_print(TextRecord *t_records, int t_count, ModRecord *m_records, int m_count, int relocation_addr, int exec_addr, const char *machine_type);

// Count the total arguments input and use argv to read each arguments
int main(int argc, char *argv[])
{

    // Ensure correct number of arguments, if arguments are not correct, print usage message
    // stderr is the standard error stream - it use to print error messages, warnings, and diagnostics.
    if (argc != 4)
    {
        fprintf(stderr, "Error: %s Requires 4 arguments with <object_file> <relocation_address> <machine_type(SIC/SICXE)>\n", argv[0]);

        return 1;
    }

    // variable for arguments input
    // strtol is used to convert hex string into integer

    char *object_file = argv[1];
    int relocation_address = (int)strtol(argv[2], NULL, 16);
    char *machine_type = argv[3];

    // ensure the machine type is either be 'SIC' or 'SICXE'
    if (strcmp(machine_type, "SIC") != 0 && strcmp(machine_type, "SICXE") != 0)
    {
        fprintf(stderr, "Invalid machine type. Must be 'SIC' or 'SICXE'. \n");
        return 1;
    }

    // check if the file existed
    FILE *file = fopen(object_file, "r");
    if (file == NULL)
    {
        printf("Error: %s opening a file", object_file);
        return 1;
    }

    // store T and M records which will be used it for parsed object file data
    TextRecord t_records[MAX_LINE_LENGTH];
    ModRecord m_records[MAX_RECORD];

    // initialize counters and values
    int t_count = 0, m_count = 0, start_addr = 0, prog_len = 0, exec_addr = 0;

    parse_object_file(file, t_records, &t_count, m_records, &m_count, &start_addr, &prog_len, &exec_addr);

    fclose(file);

    relocate_and_print(t_records, t_count, m_records, m_count, relocation_address, exec_addr, machine_type);

    return 0;
}

void parse_object_file(FILE *file, TextRecord *t_records, int *t_count, ModRecord *m_records, int *m_count, int *start_addr, int *prog_len, int *exec_addr) {
    char line[MAX_LINE_LENGTH];

    // removes newlines
    while (fgets(line, sizeof(line), file) != NULL)
    {

        size_t len = strlen(line);

        if (len > 0 && (line[len - 1] == '\n' || line[len - 1] == '\r'))
        {
            line[len - 1] = '\0';
            
        }

        if (line[0] == 'H') {

            char name[7] = {0};
            char start_str[7] = {0};
            char len_str[7] = {0};

            sscanf(line, "H%6s%6s%6s", name, start_str, len_str);

            *start_addr = (int)strtol(start_str, NULL, 16);
            *prog_len = (int)strtol(len_str, NULL, 16);
            *exec_addr = *start_addr;

        }

        // T startaddr length opcode
        else if (line[0] == 'T') {

            char addr_str[7] = {0};
            char length_str[3] = {0};
            char obj_code[MAX_LINE_LENGTH] = {0};

            sscanf(line, "T%6s%2s%s", addr_str, length_str, obj_code);

            t_records[*t_count].start_address = (int)strtol(addr_str, NULL, 16);
            t_records[*t_count].length = (int)strtol(length_str, NULL, 16);

            strcpy(t_records[*t_count].object_code, obj_code);

            (*t_count)++;
        }

        // M address length (+/- symbol)
        else if (line[0] == 'M') {

            char addr_str[7] = {0};
            char length_str[3] = {0};

            sscanf(line, "M%6s%2s", addr_str, length_str);

            m_records[*m_count].address = (int)strtol(addr_str, NULL, 16);
            m_records[*m_count].length = (int)strtol(length_str, NULL, 16);

            (*m_count)++;
        }

        // E execaddr
        else if (line[0] == 'E')
        {

            char exec_str[7] = {0};

            if (sscanf(line, "E%6s", exec_str) == 1)
            {
                *exec_addr = strtol(exec_str, NULL, 16);
            }
            
            return; // end of file
        }
    }
}

void relocate_and_print(TextRecord *t_records, int t_count, ModRecord *m_records, int m_count, int relocation_addr, int exec_addr, const char *machine_type)
{
    (void)machine_type;

    for(int i =0 ; i < m_count; i++) {
        int m_addrress= m_records[i].address;
        int m_length = m_records[i].length;

        TextRecord *tr = NULL;

        for(int t = 0; t < t_count; t++) {
            int start = t_records[t].start_address;
            int end = start + t_records[t].length;

            if(m_addrress >= start && m_addrress < end){
                tr = &t_records[t];
                break;
            }
        }

        if (!tr){
            fprintf(stderr,"Warning: M record at %06X (len=%02X) does not match any T record\n",m_addrress, m_length);
            continue;
        }

        int byte_offset = m_addrress- tr->start_address;
        int nibble_offset = byte_offset * 2;
        int obj_len = (int)strlen(tr->object_code);

        if(nibble_offset + m_length > obj_len){
            fprintf(stderr, "Warning: M record at %06X exceeds T data range \n", m_addrress);
            continue;
        }

        char field[16];
        if (m_length > (int)sizeof(field) - 1) {
            m_length = (int)sizeof(field) - 1;
        }
            strncpy(field, tr->object_code + nibble_offset, m_length);
            field[m_length] = '\0';

            long value = strtol(field, NULL, 16);
            value += relocation_addr;

            char fmt[16]; 
            char new_field[16];

            sprintf(fmt, "%%0%dlX", m_length);
            sprintf(new_field, fmt, value);

            memcpy(tr->object_code + nibble_offset, new_field, m_length);
        }

        for(int t = 0; t < t_count; t++) {
            int new_start = t_records[t].start_address + relocation_addr;
            printf("T %06X %02X %s\n", new_start, t_records[t].length, t_records[t].object_code);
        }

        int new_exec = exec_addr + relocation_addr;
        printf("E %06X\n", new_exec);
    
}
