#include<Stdio.h>
#include<string.h>
#include<stdlib.h>
struct Book{
    
    int id;
    char title[100];
    char author[100];
    int issued;
    struct Book *next;
    struct Book *prev;

}
typedef struct Book book;
book getnode()
{
    book *new_book = (book *)malloc(sizeof(book));
    if(new_book == NULL)
    {
        printf("Memory allocation failed\n");
        exit(1);
    }
}
book insert_book(book First){
    book temp;
    temp = getnode();
    printf("Enter book id: ");
    scanf("%d", &temp->id);
    printf("Enter book title: ");
    scanf(" %[^\n]s", temp->title);
    printf("Enter book author: ");
    scanf(" %[^\n]s", temp->author);
    printf("Enter book issued status (0 for not issued, 1 for issued): ");
    scanf("%d", &temp->issued);
    temp -> next = First;
    temp -> prev =  NULL;
    First ->prev = temp;
    First = temp;
    return First;


}


book display_books(book First){
    book temp = First;
    if(temp == NULL)
    {
        printf("No books available\n");
        return;
    }
    printf("Book ID\tTitle\tAuthor\tIssued Status\n");
    while(temp != NULL)
    {
        printf("%d\t%s\t%s\t%d\n", temp->id, temp->title, temp->author, temp->issued);
        temp = temp->next;
    }
}

book remove_book(book First, int id){
    book temp = First;
    while(temp != NULL)
    {
        if(temp->id == id)
        {
            if(temp->prev != NULL)
            {
                temp->prev->next = temp->next;
            }
            else
            {
                First = temp->next;
            }
            if(temp->next != NULL)
            {
                temp->next->prev = temp->prev;
            }
            free(temp);
            printf("Book with ID %d removed successfully\n", id);
            return First;
        }
        temp = temp->next;
    }
    printf("Book with ID %d not found\n", id);
    return First;
}
book Sort_books(book First){
    if(First == NULL || First->next == NULL)
    {
        return First;
    }
    book temp1, temp2;
    for(temp1 = First; temp1->next != NULL; temp1 = temp1->next)
    {
        for(temp2 = temp1->next; temp2 != NULL; temp2 = temp2->next)
        {
            if(strcmp(temp1->title, temp2->title) > 0)
            {
                // Swap the book details
                int id_temp = temp1->id;
                char title_temp[100];
                strcpy(title_temp, temp1->title);
                char author_temp[100];
                strcpy(author_temp, temp1->author);
                int issued_temp = temp1->issued;

                temp1->id = temp2->id;
                strcpy(temp1->title, temp2->title);
                strcpy(temp1->author, temp2->author);
                temp1->issued = temp2->issued;

                temp2->id = id_temp;
                strcpy(temp2->title, title_temp);
                strcpy(temp2->author, author_temp);
                temp2->issued = issued_temp;
            }
        }
    }
    return First;
}
int main(){
    book First = NULL;
    int choice, id;
    while(1)
    {
        Printf("======Library Management System======\n");
        printf("1. Insert Book\n");
        printf("2. Display Books\n");
        printf("3. Remove Book\n");
        printf("4. Sort Books\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch(choice)
        {
            case 1:
                First = insert_book(First);
                break;
            case 2:
                display_books(First);
                break;
            case 3:
                printf("Enter book id to remove: ");
                scanf("%d", &id);
                First = remove_book(First, id);
                break;
            case 4:
                First = Sort_books(First);
                break;
            case 5:
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }
    return 0;
}