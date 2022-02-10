#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdio_ext.h>
#include<unistd.h>
#include<ctype.h>

char chp;

struct word_node{
    char word[100];
    char description[1000];
    struct word_node *left;
    struct word_node *right;
};

typedef struct word_node WORD;

WORD* root = NULL;

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
            free(temp);
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

void search(){
    WORD* cur = root;

    char wrd[100];
    printf("NOTE:NO SPACES ALLOWED\nEnter Word : ");
    __fpurge(stdin);
    fgets(wrd, 100, stdin);
    wrd[strlen(wrd)-1] = '\0';
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
                new_word->description[j++];
                chp = fgetc(fptr);
            }
            new_word->description[j] = '\0';

            create_bst(new_word);
        }
    }while(chp != EOF);
}

void attach_to_file(){

}

int main()
{
    int choice, tme = 2, p = 0;
    read_file();
    while(1){
        printf("\n\n1.Add New Word\n2.Search\n3.Update Word Description\n4.Exit\nEnter Choice : ");
        if(scanf("%d", &choice) == 1){
            switch(choice){
            case 1: add();break;
            case 2: search();break;
            // case 3: delete();break;
            // case 3: update();break;
            case 4: //attach_to_file();
                    sleep(0.5); 
                    system("clear");
                    printf("Updating Dictionary .\n");
                    sleep(1); 
                    system("clear"); 
                    printf("Updating Dictionary ..\n");
                    sleep(1); 
                    system("clear"); 
                    printf("Updating Dictionary ...\n");
                    sleep(1); 
                    system("clear"); 
                    printf("Updating Dictionary ....\n");
                    
                    printf("UPDATED!");
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
