#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    char name[30];
    char phone[15];
    struct node *next;
} NODE;

void showMenu();
NODE *createNode();
void assign(NODE **new, char person[], char number[]);
void push(NODE *new, NODE **L);
void pop(NODE **L, int position);
void showData(NODE *L);
void clearScr();
void delay(int seconds);

int nodeCount = 0;

int main(){

    NODE *head = NULL, *new_node;
    char choice, name[30], number[15];
    int position, choiceOfChange;
    clearScr();
    printf("Welcome to Zach Riane Machacon's Phonebook!\n\n");
    printf("Loading...\n\n");
    delay(2);
    clearScr();
    do{
        showMenu();
        printf("Choice : ");
        scanf(" %c", &choice);
        if(choice == 'a')
        {
            clearScr();
            new_node = createNode();
            if(new_node == NULL)
                continue;
            else
            {
                printf("Name : ");
                scanf(" %[^\n]s", name);
                printf("Number: ");
                scanf(" %[^\n]s", number);
                assign(&new_node, name, number);
                push(new_node, &head);
            }
        }

        else if(choice == 'b')
        {
            clearScr();
            showData(head);
            delay(1);
        }

        else if(choice == 'c')
        {
            clearScr();
            if(head == NULL)
                printf("\n\nERROR: No records available.\n\n");
            else
            {
                showData(head);
                printf("Record to be changed: ");
                scanf("%d", &position);
                while(position > nodeCount || position < 1)
                {
                    printf("ERROR: No record in that position. Please try again.\n");
                    printf("Record to be changed: ");
                    scanf("%d", &position);
                } 
                printf("What would you like to change?\n");
                printf("1. Name\n");
                printf("2. Phone number\n");
                printf("3. Both name and number\n");
                printf("Enter your choice : ");
                scanf("%d", &choiceOfChange);
                while(choiceOfChange < 0 || choiceOfChange > 3)
                {
                    printf("You have entered an invalid choice. Please try again.\n");
                    printf("Enter your choice : ");
                    scanf("%d", &choiceOfChange);
                }
                if(choiceOfChange == 1)
                {
                    printf("New name : ");
                    scanf(" %[^\n]s", name);
                    changeRecord(&head, position, choiceOfChange, name, number);
                }
                else if(choiceOfChange == 2)
                {
                    printf("New number: ");
                    scanf(" %[^\n]s", number);
                    changeRecord(&head, position, choiceOfChange, name, number);
                }
                else if(choiceOfChange == 3)
                {
                    printf("New name : ");
                    scanf(" %[^\n]s", name);
                    printf("New number : ");
                    scanf(" %[^\n]s", number);
                    changeRecord(&head, position, choiceOfChange, name, number);
                }
            }
        }

        else if(choice == 'd')
        {
            clearScr();
            showData(head);
            if(nodeCount > 0)
            {
                printf("Record to be removed : ");
                scanf("%d", &position);
                while(position > nodeCount || position < 1)
                {
                    printf("You have entered an invalid record. Please try again.\n");
                    printf("Record to be removed : ");
                    scanf("%d", &position);
                }
                removeRecord(&head, position);
            }
        }
    if(choice != 'e')
    {
        delay(1);
        clearScr();
    }
    else
    {
        clearScr();
        printf("Thank you! See you next time!\n\n");
        delay(1);
        clearScr();
    }
    }while(choice != 'e');
    return 0;
}

void showMenu(){

    printf("Menu:\n");
    printf("[a]ppend\n");
    printf("[b]rowse\n");
    printf("[d]elete\n");
    printf("[e]xit\n");
}

NODE *createNode(){

    NODE *new = malloc(sizeof(NODE));
    if(new == NULL)
        printf("ERROR: Not enough memory on this device to create a new contact!\n");
    return new;
}

void assign(NODE **new, char person[], char number[]){

    strcpy((*new)->name, person);
    strcpy((*new)->phone, number);
}

void push(NODE *new, NODE **L){

    new->next = *L;
    *L = new;
    printf("\n\nSUCCESS: New record pushed to the top!\n\n");
    nodeCount++; 
}

void changeRecord(NODE **L, int position, int choice, char person[], char number[]){

    position--;
    int currentPos = 0;
    NODE *current_node = malloc(sizeof(NODE));
    if(current_node == NULL)
        printf("ERROR: Not enough memory on this device to carry out this operation!\n");
    else
    {
        current_node = *L;
        if(position > 0)
        {
            do{
                current_node = current_node->next;
                currentPos++;
            }while(currentPos < position);
        }
        if(current_node == NULL)
        {
            printf("\n\nERROR: No record located.\n");
            return;
        }
        if(choice == 1)
        {
            strcpy(current_node->name, person);
            printf("\n\nSUCCESS: Name change successful!\n\n");
        }    
        else if(choice == 2)
        {
            strcpy(current_node->phone, number);
            printf("\n\nSUCCESS: Number change successful!\n\n");
        } 
        else if(choice == 3)
        {
            strcpy(current_node->name, person);
            strcpy(current_node->phone, number);
            printf("\n\nSUCCESS: Record change successful!\n\n");
        }
    }
}

void removeRecord(NODE **L, int position){

    position--;
    int currentPos = 0;
    NODE *current_node = malloc(sizeof(NODE)), *prev_node;
    if(current_node == NULL)
        printf("ERROR: Not enough memory on this device to carry out this operation!\n");
    else
    {
        current_node = *L;
        if(position == 0)
        {
            *L = current_node->next;
            free(current_node);
            printf("\n\nSUCCESS: Delete successful!\n\n");
            nodeCount--;
        }
        if(position > 0)
        {
            do{
                prev_node = current_node;
                current_node = current_node->next;
                currentPos++;
            }while(currentPos < position);
            prev_node->next = current_node->next;
            free(current_node);
            printf("\n\nSUCCESS: Delete successful!\n\n");
            nodeCount--;
        }
        else if(current_node == NULL)
            printf("\n\nERROR: No record located.\n");
    }
}

void showData(NODE *L){

    int i = 1;
    if(L == NULL)
        printf("\n\nERROR: No records available.\n\n");
    else
    {
        printf("\n\nPhonebook\n\n");
        if(nodeCount == 1)
            printf("%d contact available\n\n", nodeCount);
        else
            printf("%d contacts available\n\n", nodeCount);
        while(L != NULL)
        {
            printf("%d. %-35s\t\t\t%s\n", i, L->name, L->phone);
            i++;
            L = L->next;
        }
        printf("\n");
    }
}

void clearScr(){
    printf("\e[1;1H\e[2J");
}

void delay(int seconds)
{
    int milli_seconds = 1000 * seconds;
    clock_t start_time = clock();
    while (clock() < start_time + milli_seconds)
        ;
}