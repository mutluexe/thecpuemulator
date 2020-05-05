#include <stdio.h>
#include <string.h> 
#include <stdlib.h>

// Instructions struct
typedef struct {
    char *name;
    int value;
} ins;
// Protoyping functions here
int execute(char *ins, int value);

// Static variables
static int pc = 0; // Program Counter
static int memory[256]; // Memory
static int F = 0; // Initialize F flag
static int AC = 0; // Initialize accumulator

int main(int argc, char *argv[]){
// Defining variables here
FILE *filePointer;
char *line = NULL;
size_t len = 0;
ssize_t nread;
char *token = NULL;
ins **instructions = (ins **) malloc(1024 * sizeof(ins*));
int test = 0;
// Create node

    // Check if invalid number of args entered
    if(argc != 2){
    printf("Invalid number of args entered\n");
    printf("Usage: ./emulator program.txt\n");
    }

    // Open File 
    filePointer = fopen(argv[1], "r");
    
    // Test file if exist
    if (filePointer == NULL) {
    printf("Error! Could not open the file\n");   
    exit(EXIT_FAILURE);
    }
    
    int i = 0;
    // Read file line by line 
    while((nread = getline(&line, &len, filePointer)) != -1){
        // Value token must be initiliazed
        char *valuetoken = NULL; 
        // Skip first part of lines 
        token = strtok(line, " ");
        // Take instructions
        token = strtok(NULL, "\n ");
        char *duptoken = strdup(token);
        // Take values
        token = strtok(NULL, "\n ");
        // This part was a pain but i couldn't manage to find another way 
        if(token == NULL){
            valuetoken = "-1";
        } else {
            valuetoken = strdup(token);
        }

        // Initialize a temporary instruction struct 
        ins *temp = (ins *)malloc(sizeof(ins));
        temp->name = duptoken;
        temp->value = atoi(valuetoken);

        // Insert structs on a struct array
        instructions[i] = temp; 
        i++;
    }
    free(line);
    fclose(filePointer);

    // Execute instructions
    while(pc != i){
    execute(instructions[pc]->name, instructions[pc]->value);
    }
    return 0;
}

int execute(char *ins, int value){

    if(strcmp(ins, "START") == 0){
    printf("execution started!\n");
    pc += 1;
    }

    if(strcmp(ins, "LOAD") == 0){
    AC = value;
    pc+=1;
    }

    if(strcmp(ins, "LOADM") == 0){
    AC = memory[value];
    pc+=1;
    }

    if(strcmp(ins, "STORE") == 0){
    memory[value] = AC;
    pc+=1;
    }

    if(strcmp(ins, "CMPM") == 0){
        if(AC > memory[value]){ F = 1; }
        if(AC < memory[value]){ F = -1; }
        if(AC == memory[value]){ F = 0; }
    pc+=1;
    }

    if(strcmp(ins, "CJMP") == 0){
        if(F == 1){ pc = value; }
        else { pc+=1; }
    }

    if(strcmp(ins, "JMP") == 0){
    pc = value;
    }

    if(strcmp(ins, "ADD") == 0){
    AC += value;
    pc+=1;
    }

    if(strcmp(ins, "ADDM") == 0){
    AC += memory[value];
    pc+=1;
    }

    if(strcmp(ins, "SUBM") == 0){
    AC -= memory[value];
    pc+=1;
    }

    if(strcmp(ins, "SUB") == 0){
    AC -= value;
    pc+=1;
    }

    if(strcmp(ins, "MUL") == 0){
    AC *= value;
    pc+=1;
    }

    if(strcmp(ins, "MULM") == 0){
    AC *= memory[value];
    pc+=1;
    }

    if(strcmp(ins, "DISP") == 0){
    printf("%d\n", AC);
    pc+=1;
    }

    if(strcmp(ins, "HALT") == 0){
    printf("execution stopped!\n");
    pc+=1;
    }
    return pc;
}

