#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdio_ext.h>
#include<unistd.h>
#include<ctype.h>

#define MAX 100000

char chp;
void capitalize();
void add();

struct word_node{
    char word[100];
    char description[1000];
    struct word_node *left;
    struct word_node *right;
};

typedef struct word_node WORD;

WORD* root = NULL;

WORD* stack[MAX];
int top = -1;

void push(WORD* temp){
    if(top == MAX-1) return;
    stack[++top] = temp;
}

WORD* pop(){
    if(top == -1) return NULL;
    return stack[top--];
}

int stack_empty(){
    return (top == -1)?1:0;
}

WORD* make_word(){
    WORD* node = (WORD*)malloc(sizeof(WORD));
    node->left = node->right = NULL;
    return node;
}

int empty(char s[]){
    for(int i = 0; s[i] != '\0'; i++)
        if(s[i] != ' ') return 0;
    return 1;
}

int spaces(char s[]){
    for(int i = 0; s[i] != '\0'; i++)
        if(s[i] == ' ') return 1;
    return 0;
}


void search(char* wrd){
    WORD* cur = root;
    
    capitalize(wrd);

    while(cur && strcmp(cur->word, wrd)){
        if(strcmp(cur->word, wrd) > 0) cur = cur->left;
        else cur = cur->right;
    }

    if(cur){
        printf("\n:::: WORD FOUND ::::\n");
        printf("Meaning : \n%s", cur->description);
    }
    else{
        char choice;
        printf("\n:::: Word Not Found ::::\n");
        printf("Would You Like To Add This Word ? (y/n) : ");
        scanf(" %c", &choice);
        if((choice == 'y') ||(choice == 'Y')) add();
        else return;
    }
}


void add_bst(WORD* temp){
    if(!root){
        root = temp;
            printf("Word Meaning : \n");
            __fpurge(stdin);
            fgets(temp->description, 1000, stdin);
            printf("\nWord Added Succesfully\n");
        }
    else{
        WORD* cur = root, *prev;
        while(cur && strcmp(temp->word, cur->word)){
            if(strcmp(temp->word, cur->word) > 0){
                prev = cur;
                cur = cur->right;
            }
            else{
                prev = cur;
                cur = cur->left;
            }
        }
        if(cur){
            printf("\n!!! Word Already Exists !!!\n");
            search(temp->word);
        }
        else{
            if(strcmp(temp->word, prev->word) > 0){
                // printf("\nADDED TO RIGHT OF %s\n", prev->word);
                prev->right = temp;
            }
            else{
                prev->left = temp;
                // printf("\nADDED TO LEFT OF %s\n", prev->word);
            }
            printf("Word Meaning : \n");
            __fpurge(stdin);
            fgets(temp->description, 1000, stdin);
            printf("\nWord Added Succesfully\n");
        }
    }
}

void capitalize(char* _word){
    for(int j = 0; _word[j] != '\0'; j++){
        _word[j] = toupper(_word[j]);
    }
}

void add(){
    WORD* new_word = make_word();
    
    printf("NOTE : NO SPACES ALLOWED\nEnter The New Word : ");
    __fpurge(stdin);
    fgets(new_word->word, 100, stdin);
    new_word->word[strlen(new_word->word)-1] = '\0';

    if((strlen(new_word->word) == 0) || empty(new_word->word)){
        printf("Word Too Short\n");
        free(new_word);
        return;
    }
    
    if(spaces(new_word->word)){
        printf("Spaces arent Allowed\n");
        free(new_word);
        return;
    }
    capitalize(new_word->word);
    add_bst(new_word); // traverse(); --> check if word already exists if not attach at end
}


void create_bst(WORD* temp){
    if(!root){
        root = temp;
    }
    else{
        WORD* cur = root, *prev;
        while(cur && strcmp(temp->word, cur->word)){
            if(strcmp(temp->word, cur->word) > 0){
                prev = cur;
                cur = cur->right;
            }
            else{
                prev = cur;
                cur = cur->left;
            }
        }
        if(strcmp(temp->word, prev->word) > 0){
            // printf("\nADDED TO RIGHT OF %s\n", prev->word);
            prev->right = temp;
        }
        else{
            prev->left = temp;
            // printf("\nADDED TO LEFT OF %s\n", prev->word);
        }
    }
}


void read_file(){
//chp
    FILE *fptr = fopen("dictionary.txt", "r");
    if(!fptr) return;
    do{
        chp = fgetc(fptr);
        if(chp == '&'){
            chp = fgetc(fptr);
            WORD* new_word = make_word();

            // char txt[100], desc[1000];
            int i=0, j=0;
            while(chp != ':'){
                new_word->word[i++] = chp; 
                chp = fgetc(fptr);
            }
            new_word->word[i] = '\0';
            chp = fgetc(fptr);
            while(chp != '%'){
                new_word->description[j++] = chp;
                chp = fgetc(fptr);
            }
            new_word->description[j] = '\0';
            // printf("%s = %s\n", new_word->word, new_word->description);
            create_bst(new_word);
        }
    }while(chp != EOF);
    fclose(fptr);
}

void attach_to_file(){
    FILE *fptr = fopen("dictionary.txt", "w");

    push(root);
    while(!stack_empty()){
        WORD* temp = pop();
        fputc('&', fptr);
        fputs(temp->word, fptr);
        fputc(':', fptr);
        fputs(temp->description, fptr);
        fputc('%', fptr);
        if(temp->right) push(temp->right);
        if(temp->left) push(temp->left);
    }
    fclose(fptr);
}

void update(char* wrd){
    WORD* cur = root;
    
    capitalize(wrd);

    while(cur && strcmp(cur->word, wrd)){
        if(strcmp(cur->word, wrd) > 0) cur = cur->left;
        else cur = cur->right;
    }

    if(cur){
        printf("Enter Updated Details : \n");
        printf("Enter Description : ");
        __fpurge(stdin);
        fgets(cur->description, 1000, stdin);
        cur->description[strlen(cur->description)-1] = '\0';

        printf("\nUpdated\n");
    }

    else{
        printf("\nWORD NOT FOUND\n");
    }
}


int main()
{
    int choice, tme = 500000, p = 0;
    read_file();
    while(1){
        char wrd[100];
        printf("\n\n1.Add New Word\n2.Search\n3.Update Word Description\n4.Save and Exit\nEnter Choice : ");
        if(scanf("%d", &choice) == 1){
            switch(choice){
            case 1: add();break;
            case 2:
            printf("NOTE:NO SPACES ALLOWED\nEnter Word : ");
            __fpurge(stdin);
            fgets(wrd, 100, stdin);
            wrd[strlen(wrd)-1] = '\0';
            search(wrd);
            break;
            case 3: 
            printf("NOTE:NO SPACES ALLOWED\nEnter Word : ");
            __fpurge(stdin);
            fgets(wrd, 100, stdin);
            wrd[strlen(wrd)-1] = '\0';
            update(wrd);
            break;
            case 4: attach_to_file();
                    sleep(0.5); 
                    system("clear");
                    printf("Updating Dictionary .\n");
                    usleep(tme); 
                    system("clear"); 
                    printf("Updating Dictionary ..\n");
                    usleep(tme); 
                    system("clear"); 
                    printf("Updating Dictionary ...\n");
                    usleep(tme); 
                    system("clear"); 
                    printf("Updating Dictionary ....\n");
                    
                    printf("UPDATED!\n");
                    return 0;
            default: printf("Enter choices from 1 - 5 ONLY !");
            }
        }
        else{
            printf("\nEnter Numbers Only!\n");
            __fpurge(stdin);
        }
    }
    return 0;
}
