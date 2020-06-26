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
static int AX = 0; // Initialize AX register

static int MAXSIZE = 12;       
static int stack[12];     
static int top = -1;            

int isempty() {

   if(top == -1)
      return 1;
   else
      return 0;
}
   
int isfull() {

   if(top == MAXSIZE)
      return 1;
   else
      return 0;
}

int peek() {
   return stack[top];
}

int pop() {
   int data;
	
   if(!isempty()) {
      data = stack[top];
      top = top - 1;   
      return data;
   } else {
      printf("Could not retrieve data, Stack is empty.\n");
   }
   return 0;
}

void push(int data) {
   if(!isfull()) {
      top = top + 1;   
      stack[top] = data;
   } else {
      printf("Could not insert data, Stack is full.\n");
   }
}

int main(int argc, char *argv[]){
// Defining variables here
FILE *filePointer;
char *line = NULL;
size_t len = 0;
ssize_t nread;
char *token = NULL;
ins **instructions = (ins **) malloc(256 * sizeof(ins*));
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
    /*printf("program counter: %d\n" , pc);*/
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
        printf("%d ", AC);
        pc+=1;
    }

    if(strcmp(ins, "DASC") == 0){
        printf("%c", AC);
        pc+=1;
    }

    if(strcmp(ins, "HALT") == 0){
        printf("execution stopped!\n");
        pc+=1;
    }

    if(strcmp(ins, "PUSH") == 0){
        push(value);
        pc+=1;
    }

    if(strcmp(ins, "POP") == 0){
        AC = pop();
        pc+=1;
    }

    if(strcmp(ins, "RETURN") == 0){
        pc = pop();
    }

    if(strcmp(ins, "LOADI") == 0){
        AC = memory[AX];
        pc+=1;
    }

    if(strcmp(ins, "STOREI") == 0){
        memory[AX] = AC;
        pc+=1;
    }
    
    if(strcmp(ins, "SWAP") == 0){
        int temp = AC;
        AC = AX;
        AX = temp;
        pc+=1;
    }
    return pc;
}

