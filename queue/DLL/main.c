#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>

typedef struct node {
    char name[30];
    char phone[15];
    struct node *next, *prev;
} NODE;

void showMenu();
NODE *createNode();
void assign(NODE **new, char person[], char number[]);
void enQueue(NODE *new, NODE **L);
void deQueue(NODE **L);
void showData(NODE *L);
void clearScr();
void delay(int seconds);

int nodeCount = 0, maxCap = 3;

int main(){

    NODE *head = NULL, *new_node;
    char choice, name[30], number[15];
    int position, choiceOfChange;
    clearScr();
    printf("Welcome to Machacon and Miole's Phonebook!\n\n");
    printf("Loading...\n\n");
    pause();
    clearScr();
    do{
        showMenu();
        printf("Choice : ");
        scanf(" %c", &choice);
        while(choice < 'a' || choice == 'c' || choice == 'd' || choice > 'e')
        {
            printf("You have entered an invalid choice. Please try again.\n");
            printf("Choice : ");
            scanf(" %c", &choice);
        }
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
                enQueue(new_node, &head);
                if(nodeCount > maxCap)
                    deQueue(&head);
            }
        }

        else if(choice == 'b')
        {
            clearScr();
            showData(head);
            printf("Press any key to continue...");
            getch();
        }
        
    if(choice != 'e')
    {
        pause();
        clearScr();
    }
    else
    {
        clearScr();
        printf("Thank you! See you next time!\n\n");
        pause();
        clearScr();
    }
    }while(choice != 'e');
    return 0;
}

void showMenu(){

    printf("Menu:\n");
    printf("[a]ppend\n");
    printf("[b]rowse\n");
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

void enQueue(NODE *new, NODE **L){

    NODE *current_node = malloc(sizeof(NODE));
    if(*L == NULL)
    {
        new->next = *L;
        new->prev = NULL;
        *L = new;
    }
    else 
    {
        for(current_node = *L; current_node->next != NULL; current_node = current_node->next){}
        new->next = current_node->next;
        current_node->next = new;
        new->prev = current_node;
    }
    printf("\n\nSUCCESS: New record enqueued!\n\n");
    nodeCount++; 
}

void deQueue(NODE **L){

    NODE *current_node = malloc(sizeof(NODE));
    if(current_node == NULL)
        printf("ERROR: Not enough memory on this device to carry out this operation!\n");
    else
    {
        current_node = *L;
        *L = current_node->next;
        free(current_node);
        printf("SUCCESS: Front record dequeued!\n\n");
    }
    nodeCount--;
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
        for(; L != NULL; L = L->next, i++)
            printf("%d. %-35s\t\t\t%s\n", i, L->name, L->phone);
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
    while (clock() < start_time + milli_seconds);
}

void pause(){
    #ifdef _WIN32
        delay(2);
    #elif __APPLE__
        delay(2000);
    #elif __unix__
        delay(2000);
    #endif
}