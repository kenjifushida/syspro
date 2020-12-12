#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// structure definition //

typedef struct member{
    char name[20];
    char group[30];
    int number;
    int numact;
    struct member* next;
} MEMBER;

// Prototypes //

MEMBER* NewMember(char* name, char* group, int num);
void PrintMember(MEMBER* start);
MEMBER* AddMember(MEMBER* start, MEMBER* node_to_insert);
static int comparison(MEMBER* node_1, MEMBER* node_2);
void ArrangeNumbers(MEMBER* start);
void DeleteMember(MEMBER** start, int id);
MEMBER* find_node(MEMBER* start, int id);

// Main Function //
int main(int argc, char** argv){
    static int serialNum = 0;
    MEMBER* start = NULL;
    MEMBER* new_node;
    MEMBER* temp;
    char com;
    while(1) {
        printf("enter command.  (s = show, a = add, r = remove, quit = q) ---");
        scanf(" %c", &com);
        if (com == 'a') {
            char name[20];
            char group[20];
            printf("Enter a name: ");
            scanf(" %[^\n]%*c", name);
            printf("Enter group: ");
            scanf(" %[^\n]%*c", group);
            new_node = NewMember(name, group, serialNum++);
            start = AddMember(start, new_node);
            ArrangeNumbers(start);
        } else if (com =='s') {
            PrintMember(start);
        } else if (com =='r') {
            int id;
            printf("Enter the id you want to delete: ");
            scanf(" %d", &id);
            temp = find_node(start, id);
            if (temp == NULL)
            {
                printf("No active member. Please input a valid ID.\n");
            } else
            {
                DeleteMember(&start, id);
                ArrangeNumbers(start);
            }
        } else if (com =='q') {
            break;
        } else {
            printf("no such command %c, please re-enter\n", com);
        }
    }
    free(start);
    free(new_node);
    free(temp);
    return(0);
}

// Make a new List //

MEMBER* NewMember(char* name, char* group, int num){
    MEMBER* this;
    this = (MEMBER*)malloc(sizeof(MEMBER));
    strcpy(this->name, name);
    strcpy(this->group, group);
    this->number = num;
    this->next = NULL;
    return(this);
}

// Print the list in order //

void PrintMember(MEMBER* start){
    if(start == NULL) {
        printf("There are no members yet.\n");
    } else {
        MEMBER* p;
        for(p=start; p != NULL; p=p->next){
            printf(" %s, %s,  order: %d\n", p->name, p->group, p->numact);
        }
    }
}

// Append a new Member //

MEMBER* AddMember(MEMBER* start, MEMBER* node_to_insert){
    if (start == NULL || comparison(node_to_insert, start) < 0) {
        node_to_insert->next = start;
        return node_to_insert;
    } else {
        MEMBER* current = start;
        while(current->next != NULL && comparison(node_to_insert, current->next) >= 0) {
            current = current->next;
        }
        node_to_insert->next = current->next;
        current->next = node_to_insert;
        return start;
    }
}

static int comparison(MEMBER* node_1, MEMBER* node_2) {
    return strcmp(node_1->name, node_2->name);
}

void ArrangeNumbers(MEMBER* start) {
    MEMBER* current;
    int i = 0;
    for (current = start; current != NULL; current=current->next)
    {
        current->numact = i;
        i+=1;
    }
    return;
}

// Check if node exists //

MEMBER* find_node(MEMBER* start, int id) {
    MEMBER* current = start;
    while (current != NULL)
    {
        if(current->numact == id) return current;
        current = current->next;
    
    }
    return NULL;
}

// Delete a node //

void DeleteMember(MEMBER** start, int id) {
    MEMBER* current = *start;
    MEMBER* next_node;
    MEMBER* delete_node;
    if (id == 0)
    {
        next_node = (*start)->next;
        free(*start);
        *start = next_node;
        return;
    }

    while(current != NULL) {
        if(current->next->numact ==  id) {
            break;
        }
        current = current->next;
    }
    delete_node = current->next;
    current->next = delete_node->next;
    free(delete_node);
    return;
}