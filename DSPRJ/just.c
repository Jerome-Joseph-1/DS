#include<stdio.h>
#include<stdlib.h>
#include<string.h>

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
            printf("\nADDED TO RIGHT OF %s\n", prev->word);
            prev->right = temp;
        }
        else{
            prev->left = temp;
            printf("\nADDED TO LEFT OF %s\n", prev->word);
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
            printf("\n Got %s", new_word->word);
            new_word->description[j] = '\0';

            create_bst(new_word);
        }
    }while(chp != EOF);
    fclose(fptr);
}

void inorder(WORD* node){
    if(!node) return;
    inorder(node->left);
    printf("%s ---> ", node->word);
    inorder(node->right);
}

int main(){
    read_file();
    inorder(root);
}