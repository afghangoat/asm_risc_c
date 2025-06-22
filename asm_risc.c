//UNFINISHED basic RISC asm interpreter
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>


#define NO_LIMIT 10000
#define REGISTER_AMM 16
#define MAX_TOKEN_LEN 7

typedef struct ASM_command{
    int command;
    int param1;
    int param2;
    bool implicite;
    struct ASM_command* next;
} ASM_command;

typedef struct ASM_list{
    ASM_command* next;
} ASM_list;

ASM_list* global_asm_commands=NULL;
ASM_command* next_command=NULL;
int registers[REGISTER_AMM]={0};
int global_test=0;

void ASM_init_sequence(){
    global_asm_commands = (ASM_list*) malloc(sizeof(ASM_list));
    if (global_asm_commands == NULL) {
        printf("Error allocating memory for global_asm_commands!\n");
        exit(1);
    }
    global_asm_commands->next = NULL;
    next_command = global_asm_commands->next;
}

void show_registers(){
    printf("Registers states:\n|");
    for(int i=0;i<REGISTER_AMM;i++){
        printf("%d|",registers[i]);
    }
    printf("\n");
}

ASM_command* traverse_to_end(ASM_list* list,int limit){
    if(list->next==NULL){
        return NULL;
    }
    int iter=0;
    ASM_command* cur=list->next;
    while(cur->next!=NULL){
        if(iter==limit){
            return cur;
        }
        cur=cur->next;
    }
    return cur; //End is reached;
}

//create_asm_command(global_asm_commands, aa_cmd, atoi(param1), atoi(param2), isimp);
void create_asm_command(ASM_list* list,int c, int p1, int p2,bool imp){
    ASM_command* aa= (ASM_command*) malloc(sizeof(ASM_command));
    if(aa==NULL){
        printf("Error allocating memory to new asm command!");
        return;
    }
    aa->command=c;
    aa->param1=p1;
    aa->param2=p2;
    aa->implicite=imp; //Is false then pointer, if true then value
    aa->next=NULL;
    ASM_command* prev_end=traverse_to_end(list,NO_LIMIT);
    if(prev_end==NULL){
        list->next=aa;
    } else {
        prev_end->next=aa;
    }
}

void interpret_asm_command(ASM_command* aa){
    bool no_mem_inc=false;
    
    switch(aa->command){
        case 0: //ADD
            if(aa->implicite==true){
                registers[aa->param1]+=aa->param2;
            } else {
                registers[aa->param1]+=registers[aa->param2];
            }
            break;
        case 1: //SUB
            if(aa->implicite==true){
                registers[aa->param1]-=1;
            } else {
                registers[aa->param1]-=1;
            }
            break;
        case 2: //MOV
            if(aa->implicite==true){
                registers[aa->param1]=aa->param2;
            } else {
                registers[aa->param1]=registers[aa->param2];
            }
            break;
        case 3: //INC
            if(aa->implicite==true){
                registers[aa->param1]+=1;
            } else {
                registers[aa->param1]+=1;
            }
            break;
        case 4: //JMP
            if(aa->implicite==true){
                next_command=traverse_to_end(global_asm_commands,aa->param1);
             //   global_test=aa->param1;
            } else {
                next_command=traverse_to_end(global_asm_commands,registers[aa->param1]);
             //   global_test=registers[aa->param1];
            }
            no_mem_inc=true;
            break;
        case 5: //TST
            if(aa->implicite==true){
                global_test=aa->param1;
            } else {
                global_test=registers[aa->param1];
            }
            no_mem_inc=true;
            break;
        case 6: //JNZ
            if(global_test==0){
                break;
            }
            if(aa->implicite==true){
                next_command=traverse_to_end(global_asm_commands,registers[aa->param1]);
             //   global_test=aa->param1;
            } else {
                next_command=traverse_to_end(global_asm_commands,registers[aa->param1]);
             //   global_test=registers[aa->param1];
            }
            no_mem_inc=true;
            break;
        case 7: //JZ
            if(global_test!=0){
                break;
            }
            if(aa->implicite==true){
                next_command=traverse_to_end(global_asm_commands,registers[aa->param1]);
             //   global_test=aa->param1;
            } else {
                next_command=traverse_to_end(global_asm_commands,registers[aa->param1]);
             //   global_test=registers[aa->param1];
            }
            no_mem_inc=true;
            break;
        case 8: //CMP
            if(aa->implicite==true){
                global_test=0;
                if (aa->param1==aa->param2){
                    global_test=1;
                }
            } else {
                global_test=0;
                if (registers[aa->param1]==aa->param2){
                    global_test=1;
                }
            }
            break;
        case 9: //XOR
            if(aa->implicite==true){
                registers[aa->param1]==registers[aa->param1]^aa->param2;
            } else {
                registers[aa->param1]==registers[aa->param1]^registers[aa->param2];
            }
            break;
        case 10: //OR
            if(aa->implicite==true){
                registers[aa->param1]==registers[aa->param1]|aa->param2;
            } else {
                registers[aa->param1]==registers[aa->param1]|registers[aa->param2];
            }
            break;
        case 11: //AND
            if(aa->implicite==true){
                registers[aa->param1]==registers[aa->param1]&aa->param2;
            } else {
                registers[aa->param1]==registers[aa->param1]&registers[aa->param2];
            }
            break;
        case 12: //SHL
            if(aa->implicite==true){
                registers[aa->param1]==registers[aa->param1]<<aa->param2;
            } else {
                registers[aa->param1]==registers[aa->param1]<<registers[aa->param2];
            }
            break;
        case 13: //SHR
            if(aa->implicite==true){
                registers[aa->param1]==registers[aa->param1]>>aa->param2;
            } else {
                registers[aa->param1]==registers[aa->param1]>>registers[aa->param2];
            }
            break;
        case 14: //NOT
            if(aa->implicite==true){
                registers[aa->param1]==registers[aa->param1]+!aa->param2;
            } else {
                registers[aa->param1]==registers[aa->param1]+!registers[aa->param2];
            }
            break;
        case 15: //HLT
            no_mem_inc=true;
            next_command=NULL;
            break;
        default:
            break;
    }
    
    if(no_mem_inc==false){
        if(next_command!=NULL){
            next_command=next_command->next;
        }
    }
}

void ASM_execute_sequence(ASM_list* list){
    if(list->next==NULL){
        return;
    }

    next_command=list->next;
    while(next_command!=NULL){
        interpret_asm_command(next_command);
    }
}

void parse_line_ASM(char* line) {
    // Convert entire line to lowercase
    char t_line[strlen(line) + 1];
    for (int i = 0; line[i] != '\0'; i++) {
        t_line[i] = tolower(line[i]);
    }
    t_line[strlen(line)] = '\0';
    

    char cmd[4];
    strncpy(cmd, t_line, 3);
    cmd[3] = '\0';
    char aa_cmd = -1;

    if (strcmp(cmd, "add") == 0) {
        aa_cmd = 0;
    } else if (strcmp(cmd, "sub") == 0) {
        aa_cmd = 1;
    } else if (strcmp(cmd, "mov") == 0) {
        aa_cmd = 2;
    } else if (strcmp(cmd, "inc") == 0) {
        aa_cmd = 3;
    } else if (strcmp(cmd, "jmp") == 0) {
        aa_cmd = 4;
    } else if (strcmp(cmd, "tst") == 0) {
        aa_cmd = 5;
    } else if (strcmp(cmd, "jnz") == 0) {
        aa_cmd = 6;
    } else if (strcmp(cmd, "jz") == 0) {
        aa_cmd = 7;
    } else if (strcmp(cmd, "cmp") == 0) {
        aa_cmd = 8;
    } else if (strcmp(cmd, "xor") == 0) {
        aa_cmd = 9;
    } else if (strcmp(cmd, "or") == 0) {
        aa_cmd = 10;
    } else if (strcmp(cmd, "and") == 0) {
        aa_cmd = 11;
    } else if (strcmp(cmd, "shl") == 0) {
        aa_cmd = 12;
    } else if (strcmp(cmd, "shr") == 0) {
        aa_cmd = 13;
    } else if (strcmp(cmd, "not") == 0) {
        aa_cmd = 14;
    } else if (strcmp(cmd, "hlt") == 0) {
        aa_cmd = 15;
    }
    
    if(aa_cmd==-1){
        return;
    }
    
    //params
    char* param1 = (char*)malloc(sizeof(char)*MAX_TOKEN_LEN);
    char* param2 = (char*)malloc(sizeof(char)*MAX_TOKEN_LEN);
    char* rem[50];
    bool isimp = false;

    int num_params = sscanf(t_line, "%49s %9[^,],%9s", rem, param1, param2);
    if (param2 && param2[0] == '#') {
        isimp = true;
        param2++;  // Remove the '#' symbol
    }
    
    create_asm_command(global_asm_commands, aa_cmd, atoi(param1), atoi(param2), isimp);

    free(param1);
    if(isimp==true){
        free(param2-1);
    } else {
        free(param2);
    }
    
}
int main(void) {
    //"Add r0, #2"
    /*
    # is a constant number, while others are pointers to registers
    
    */
    ASM_init_sequence();
    parse_line_ASM("mov 0,#2");
    ASM_execute_sequence(global_asm_commands);
    show_registers();
    return 0;
}
