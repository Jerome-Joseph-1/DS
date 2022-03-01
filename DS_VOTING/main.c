/*DS Project*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdio_ext.h>
#include<unistd.h>
#include<ctype.h>

int count = 0;

struct BST{
    char details[5][100];
        // details[0] == Name
        // details[1] == Aadhar No.
        // details[2] == Voter ID
        // details[3] == DOB
        // details[4] == Vote (1 or 0)
    struct BST *left;
    struct BST *right;
};

struct CANDIDATE{
  char name[100];
  char votes[10];
  struct CANDIDATE *next;
};

typedef struct BST* NODE;
typedef struct CANDIDATE* cand; // candidate list is a singly linked list 

NODE root = NULL; // root of BST 
cand candidates = NULL, END = NULL;

cand make_candidate(){
    cand x = (cand)malloc(sizeof(struct CANDIDATE));
    x->next = NULL;
    return x;
}

NODE make_voter(){
    NODE x = (NODE)malloc(sizeof(struct BST));
    x->right = x->left = NULL;
    return x;
}

void user_panel(); // takes info of voters && evaluvates if exists && if vote possible
void create_candidate_list();
void create_voters_list();

NODE attach_bst(NODE voter, NODE root);

void admin_panel(); // can add/delete candidates -- adding/deleting done in BST then written to file
void display_standings(); // goes through candidates singly linked list and displays in descending order 
void write_to_file(){}; // write everything to file ... 

int main(){

  create_candidate_list();
  create_voters_list();

  int choice;
  while(1){
      printf("\n-------------SOME-MENU-----------\n");
      printf("\n1. Cast Vote\n2. Admin \n3. Current Standings\n4. EXIT\n\nENTER YOUR CHOICE : ");
      __fpurge(stdin);
      scanf("%d", &choice);
      switch(choice){
          case 1: user_panel();
                  break;
          case 2: admin_panel();
                  break;
          case 3: display_standings();
                  break;
          case 4: return 0;
          default: printf("\nINVALID CHOICE\n");

      }
  }
  return 0;
}
cand search_SLL(char name[]){
    cand cur = candidates;
    while(cur){
        if(strcmp(name, cur->name) == 0) return cur;
        cur = cur->next;
    }
}

NODE search_bst(NODE voter, NODE root){
    if(!root){ 
        printf("\nYou Arent Registered\n");
        return NULL;
    }
    if(strcmp(root->details[0], voter->details[0]) > 0) search_bst(voter, root->left);
    else if(strcmp(root->details[0], voter->details[0]) < 0) search_bst(voter, root->right);
    else{
        if(!strcmp(root->details[1], voter->details[1]) && !strcmp(root->details[2], voter->details[2]) && !strcmp(root->details[3], voter->details[3])){
            return root;
        }
        else{
            printf("\nINVALID CREDENTIALS\n");
            return NULL;
        }
    }
}

NODE login(){
    NODE person = make_voter();
    printf("\n--------------LOGIN--------------\n");
    printf("\nEnter Your Details\n\n| NOTE : USE UNDERSCORES '_' instead of spaces |\n\n");
    printf("\nYour Name : ");
    scanf("%s", person->details[0]);
    printf("\nYour Aadhaar Number : ");
    scanf("%s", person->details[1]);
    printf("\nYour Voter ID Number : ");
    scanf("%s", person->details[2]);
    printf("\nYour DOB (DD-MM-YYYY) : ");
    scanf("%s", person->details[3]);
    person = search_bst(person, root);
    return person;
}

void user_panel(){
    int choice, v, i;
    char list[count+1][100];
    while(1){
        NODE curr_person = login();
        if(!curr_person){
            char ch;
            printf("\nLOGIN FAILED\n");
            printf("Try Again ? (y/n) : ");
            __fpurge(stdin);
            scanf("%c", &ch);
            if(ch == 'y' || ch == 'Y') continue;
            else return;
        }
        printf("\n----------------VOTERS-PANEL------------------\n");
        printf("1. Cast Your Vote\n2. Back\nENTER YOUR CHOICE : ");
        __fpurge(stdin);
        scanf("%d", &choice);
        if(choice == 1){
            if(curr_person->details[4][0] == '1'){
                printf("\n!!! You Have Already Voted !!!\n");
                return;
            }
            int i = 1;
            printf("NUMBER\t\tNAME\n");
            cand cur = candidates;
            while(cur){
                printf("%d\t\t%s\n", i, cur->name);
                strcpy(list[i++], cur->name);
                cur = cur->next;
            }
            printf("\nCAUTION :: ENTERING A WRONG ENTRY WOULD TERMINATE THE SESSION\n::: Enter Number of the candidate you want to vote :::\n----> ");
            scanf("%d", &v);
            if(v > count){
                printf("::: INVALID CHOICE :::\n::: Session terminated :::\n");
                return;
            }
            else{
                cand person = search_SLL(list[v]);
                int number = 0;
                for(i = 0; person->votes[i] != '\0'; i++){
                    number = number*10 + person->votes[i] - '0';
                }

                strcpy(curr_person->details[4], "1");
                sprintf(person->votes, "%d", number + 1);
                printf("::: Thank You For Voting :::");
                write_to_file();
                return;
            }
        }
    }
}

void create_candidate_list(){
    char chp;
    
    FILE *fptr = fopen("candidates.txt", "r");
    if(!fptr) return;
    do{
        chp = fgetc(fptr);
        if(chp == '&'){
            count++;
            cand person = make_candidate();
            chp = fgetc(fptr);
            int i = 0, j = 0;
            do{
                person->name[i++] = chp;
                chp = fgetc(fptr);
            }while(chp != ':');

            person->name[i] = '\0';
            
            chp = fgetc(fptr);

            do{
                person->votes[j++] = chp;
                chp = fgetc(fptr);
            }while(chp != '%');

            if(!candidates){
                candidates = END = person;
            }
            else{
                END->next = person;
                END = person;
            }
        }
    }while(chp != EOF);
    fclose(fptr);
}

void create_voters_list(){
  char chp;

  FILE *fptr = fopen("voters.txt", "r");
  if(!fptr) return;
  do{
      chp = fgetc(fptr);
      if(chp == '&'){
          NODE voter = make_voter();
          int i = 0, j = 0;
          while(1){
              chp = fgetc(fptr);
                if(chp == '%'){
                    voter->details[i][j] = '\0';
                    break;
                }
                if(chp == ':'){
                    chp = fgetc(fptr);
                    voter->details[i][j] = '\0';
                    i++;
                    j = 0;
                }
                voter->details[i][j++] = chp;
          }
          root = attach_bst(voter, root);
      }
  }while(chp != EOF);
}

NODE attach_bst(NODE voter, NODE root){
    if(!root){
        root = voter;
    }
    else if(strcmp(root->details[0], voter->details[0]) > 0) root->left = attach_bst(voter, root->left);
    else root->right = attach_bst(voter, root->right);
    return root;
}

void admin_panel(){

}

int string_to_number(char text[]){
    int i, res = 0;
    for(i = 0; text[i] != '\0'; i++){
        res = res*10 + text[i] - '0';
    }
    return res;
}

void display_standings(){
    char names[count][100];
    int votes[count];
    int i = 0, j = 0;
    for(cand head = candidates; head ; head = head->next){
        strcpy(names[i], head->name);
        votes[i++] = string_to_number(head->votes);
    }
    printf("\nNAME\t|\tVOTES\n--------------------------------------------\n");
    for(i = 0; i < count; i++){
        int max = votes[i], index = i;        
        for(j = 0; j < count; j++){
            if(votes[j] >= max){
                max = votes[j];
                index = j;
            }
        }
        printf("%s\t|\t%d\n", names[index], votes[index]);
        votes[index] = -1;
    }
}
