
#include <stdio.H>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

/*
    Structure node ???
    . Doubly linked list 
    . Each node is divided into nine parts or data members to represent-
        1. Ladder
        2. Snake 
        3. Block Number.
        4. Player 1
        5. Player 2
        6. Player 3
        7. Player 4
        8. To store address of next node
        9. To store address of previous node
*/

struct node
{
    char Ladder[3];
    char Snake[3];
    int data;
    char Player1;
    char Player2;
    char Player3;
    char Player4;
    struct node *next;
    struct node *prev;
};

/*
    . The head structure pointer is used to represent the starting point of board
    . The last structure pointer is used to represent the ending point of board
*/

struct node *head = NULL;
struct node *last = NULL;

/*
    . p1 structure pointer is used to represent the movement of Player 1.
    . p2 structure pointer is used to represent the movement of Player 2.
    . p3 structure pointer is used to represent the movement of Player 3.
    . p4 structure pointer is used to represent the movement of Player 4.
*/

struct node *p1 = NULL;
struct node *p2 = NULL;
struct node *p3 = NULL;
struct node *p4 = NULL;

/*
    . data represents the block number
    . ladder represents the ladder data in string format
    . snake represents the snake data in string format
*/

void insertNode( int data, char *ladder, char *snake)
{
    // inputting string to be placed
    // Allocating value to new node 

    struct node *n = (struct node *)malloc(sizeof(struct node));
    n->data = data;
    n->Player1 = ' ';
    n->Player2 = ' ';
    n->Player3 = ' ';
    n->Player4 = ' ';
    strcpy(n->Ladder, ladder);
    strcpy(n->Snake, snake);

    /*
        . This condition will work if no node is there on board
    */

    if (head == NULL)
    {
        n->prev = NULL;
        n->next = NULL;
        head = n;
        last = n;
    }

    /*
        . This condition will work if there is a node on board
    */

    else
    {
        last->next = n;
        n->prev = last;
        n->next = NULL;
        last = n;
    }
}

/*
    . L represents the ladder start 
    . l represents the ladder end 
    . L[] stores the ladders' starting block number
    . l[] stores the corresponding ending block number of ladders
*/

int L[10] = {2, 8, 17, 29, 32, 39, 62, 70, 75};   
int l[10] = {23, 12, 93, 54, 51, 80, 78, 89, 96}; 

/*
    . S represents the Snake Head 
    . s represents the Sanke Tail 
    . S[] stores the Snakes head's block number
    . s[] stores the corresponding tail's block number of Snakes
*/

int S[8] = {31, 41, 59, 68, 83, 92, 99}; 
int s[8] = {14, 20, 37, 50, 80, 76, 4};  

// Creating Board

void createBoard()
{
    /*
        . i represents the board number
        . j represents ladder start counter
        . k represents ladder end counter
        . j1 represents Snake's head counter
        . k1 represents Snake's tail counter
        . idx represents the index value from l[] array if ladder is at i 
        . idx1 represents the index value from s[] array if ladder is at i
    */  
   
    int i = 1, j = 0, k = 0, m, j1 = 0, m1 = 0, k1 = 0, idx = -1, idx1 = -1;

    /*
        . ld represents the ladder data 
        . sd represents the snake data 
    */

    char ld[3]; 
    char sd[3];
    
    // Related data to enter in each block is evaluated

    while (i <= 100)
    {
        idx = -1;

        /*
            . m is counter for traversing the l[] array
            . This loop is used to check whether ladder end lies at block number i 
        */

        for (m = 0; m < 10; m++)
        {
            if (l[m] == i)
            {
                idx = m;
                break;
            }
        }

        /*
            . This conditional statement is used to check whether ladder's start lies at block number i
            . If yes the data is assigned to ld 
        */

        if (L[j] == i)
        {
            ld[0] = 'L';
            ld[1] = (char)(j + 49); // int to char conversion
            ld[2] = '\0';
            j++;
        }

        /*
            . This conditional statement works if ladder end lies in block number i
            . To assign data in ld
        */

        else if (idx != -1)
        {
            ld[0] = 'l';
            ld[1] = (char)(idx + 49);
            ld[2] = '\0';
            k++;
        }

        /*
            . This block works when neither ladder start and end lies in block i
        */

        else
        {

            ld[0] = ' ';
            ld[1] = ' ';
            ld[2] = '\0';
        }

        idx1 = -1;

        /*
            . m1 is counter for traversing the s[] array
            . This loop is used to check whether snake tail lies at block number i 
        */

        for (m1 = 0; m1 < 8; m1++)
        {
            if (s[m1] == i)
            {
                idx1 = m1;
                break;
            }
        }

        /*
            . This conditional statement is used to check whether Snake's head lies at block number i
            . If yes the data is assigned to sd 
        */

        if (S[j1] == i)
        {
            sd[0] = 'S';
            sd[1] = (char)(j1 + 49);
            sd[2] = '\0';
            j1++;
        }

        /*
            . This conditional statement works if Snake tail's lies in block number i
            . To assign data in sd
        */

        else if (idx1 != -1)
        {
            sd[0] = 's';
            sd[1] = (char)(idx1 + 49);
            sd[2] = '\0';
            k1++;
        }

        /*
            . This block works when neither Snake head nor tail lies in block i
        */

        else
        {

            sd[0] = ' ';
            sd[1] = ' ';
            sd[2] = '\0';
        }

        /*
            . As we calculated all the desired values these are now passed to insertNode function.
        */
        insertNode( i, ld, sd);
        i++;
    }
}

void displayBoard()
{
    int i, k = 0;
    /*
        . The three pointers are used to print three inner rows within each block 
    */
    struct node *ptr = last;
    struct node *ptr1 = last;
    struct node *ptr2 = last;
    getch();

    /*
        . This loop is used to display the horizontal border
        . 7 * 10 + 10 + 1 = 81 Because each node in block has nine data members 
          and we are displaying only first seven members which can be represented as
            
            *   l[0]    L[1]    *       P1      P3     *
            *     *      *     data     *       *      *
            *    P2      P3     *      S[0]    S[1]    *

    */

    for (i = 0; i <= 80; i++)
    {
        printf(".");
    }

    /*
        . This do loop is used to print the board as combination of 10 rows

        100 99 98 ...............91
        81  82 83 ...............90
        .
        .
        20  19 18 ...............11
        1   2  3  ...............10
    */

    do
    {
        /*
            . This statement checks whether we have to print forward while moving from L to R
            . i.e row no. is odd the pointers will move 10 steps back so as to do forward printing
        */
        if (k % 2 != 0)
        {
            for (i = 0; i < 10; i++)
            {
                ptr = ptr->prev;
                ptr1 = ptr1->prev;
                ptr2 = ptr2->prev;
            }
        }
        printf("\n.");

        /* 
            . The loop is used to print the first line which is 
                *   l[0]    L[1]    *       P1      P3     *    .
        */
        for (i = 0; i < 10; i++)
        {
            printf(" %s ",ptr->Ladder); 
            /*
                . \033[1;35m%c\033[0m is used to provide color to text
            */
            printf("\033[1;35m%c\033[0m",ptr->Player1);
            printf("\033[1;36m%c \033[0m",ptr->Player3);
            printf(".");

            /*
                . if k is even i.e we have to move backward else forward
            */

            if (k % 2 == 0)
                ptr = ptr->prev;
            else
                ptr = ptr->next;
        }

        /*
            . While moving forward or backward we are always one step ahead
            . Hence to get back to desired location we use this condition 
        */

        if (k % 2 != 0)
            ptr = ptr->prev;
        else
            ptr = ptr->next;
        printf("\n.");

        /*
            This loop is used print the second line that is the data part
        */
        for (i = 0; i < 10; i++)
        {
            printf("\033[0;33m");
            if (ptr1->data == 100)
            {
                printf("  %d  ", ptr1->data);
            }
            else if (ptr1->data >= 10)
            {
                printf("   %d  ", ptr1->data);
            }
            else
            {
                printf("   %d   ", ptr1->data);
            }
            printf("\033[0m");

            /*
                . This is same as previous one
            */
            if (k % 2 == 0)
                ptr1 = ptr1->prev;
            else
                ptr1 = ptr1->next;
            printf(".");
        }
        printf("\n.");

        /*
            . This is same as previous one
        */

        if (k % 2 != 0)
            ptr1 = ptr1->prev;
        else
            ptr1 = ptr1->next;

        /*
            . This is used to print the third row ie
                *    P2      P3     *      S[0]    S[1]    *    .
        */
        for (i = 0; i < 10; i++)
        {
            printf("\033[1;32m %c\033[0m",ptr2->Player2);
            printf("\033[1;34m%c\033[0m",ptr2->Player4);
            printf(" %s .", ptr2->Snake);

            /*
                . Same as before
            */
            if (k % 2 == 0)
                ptr2 = ptr2->prev;
            else
                ptr2 = ptr2->next;
        }
        printf("\n");

        /*
            . Same as before
        */

        if (k % 2 != 0)
            ptr2 = ptr2->prev;
        else
            ptr2 = ptr2->next;

        /*
            . This is used to print bottom border line
        */
        for (i = 0; i <= 80; i++)
        {
            printf(".");
        }

        /*
            . We know that we to move forward ie from 1 to 10 
            . we have to first travel backward from 10 to 1
            . once we are done with printing we also have to get back to desired postion
            . therefore using below condition if k is odd we get back to desired location
        */
        if (k % 2 != 0)
        {
            for (i = 0; i < 10; i++)
            {

                ptr = ptr->prev;
                ptr1 = ptr1->prev;
                ptr2 = ptr2->prev;
            }
        }
        k++;
    } while (k < 10);
}

/*
    . Flag values represent whether the players are ready to play or not
*/
int flag1 = 0;
int flag2 = 0;
int flag3 = 0;
int flag4 = 0;

/*
    . The dice function is used to generate a random number 
    . The function srand() is used to initialize the generated pseudo random number by rand() function. 
    . It does not return anything.
    . The function rand() is used to generate the pseudo random number. 
    . It returns an integer value and its range is from 0 to rand_max i.e 32767.
*/

int dice()
{
    int number;
    srand(time(NULL));
    number = 1 + rand() % 6;
    return number;
}

void pl1(){
    int op;
    op = dice();
    printf("\n * : ");
    getch();
    printf("    %d\n", op);

    /*
        . If flag is 0 and dice number is 6 then player enters the gaming field
    */
    if (flag1 == 0 && op == 6)
    {
        p1 = head;
        p1->Player1 = '*';
        displayBoard();
        flag1 = 1;
    }
    else if (flag1 == 1)
    {
       int count = 0;
        struct node *temp = p1;
        for (int i = 0; i < op; i++)
        {
            temp = temp->next;
            if (temp != NULL)
            {
                count++;
            }
            else
                break;
        }
        if (count == op)
        {
            p1->Player1 = ' ';
            for (int i = 0; i < op; i++)
            {
                p1 = p1->next;
            }
            p1->Player1 = '*';
            displayBoard();
            printf("\n");
            if(p1->Snake[0]=='S')
            {
                printf("\n!!!OOPS!!!\n");
                //index to calculate snake number 
                int id = (int)(p1->Snake[1] - 49);
                //to locate snake at using parallel array
                int p_value = s[id];
                p1->Player1 = ' ';
                while(p1->data != p_value)
                {
                    p1= p1->prev;
                }
                p1->Player1 ='*';
                displayBoard();
                printf("\n");
            }
            else if(p1->Ladder[0]=='L')
            {
                printf("\n!!!YAY!!!\n");
                //index to calculate snake number 
                int id = (int)(p1->Ladder[1] - 49);
                //to locate snake at using parallel array
                int p_value = l[id];
                p1->Player1 = ' ';
                while(p1->data != p_value)
                {
                    p1= p1->next;
                }
                p1->Player1 ='*';
                displayBoard();
                printf("\n");
            }
        }  
        else
        return;
    }
}

void pl2()
{
    int op;
    op = dice();
    printf("\n # : ");
    getch();
    printf("    %d\n", op);

    if (flag2 == 0 && op == 6)
    {
        p2 = head;
        p2->Player2 = '#';
        displayBoard();
        flag2 = 1;
    }
    else if (flag2 == 1)
    {
        int count = 0;
        struct node *temp = p2;
        for (int i = 0; i < op; i++)
        {
            temp = temp->next;
            if (temp != NULL)
            {
                count++;
            }
            else
                break;
        }
        if(count==op)
        {
            p2->Player2 = ' ';
            for (int i = 0; i < op; i++)
            {
                p2 = p2->next;
            }
            p2->Player2 = '#';
            displayBoard();

            printf("\n");
            if(p2->Snake[0]=='S')
            {
                printf("\n!!!OOPS!!!\n");
                //index to calculate snake number 
                int id = (int)(p2->Snake[1] - 49);
                //to locate snake at using parallel array
                int p_value = s[id];
                p2->Player2 = ' ';
                while(p2->data != p_value)
                {
                    p2= p2->prev;
                }
                p2->Player2 ='#';
                displayBoard();
                printf("\n");
            }
            else if(p2->Ladder[0]=='L')
            {
                printf("\n!!!YAY!!!\n");
                //index to calculate snake number 
                int id = (int)(p2->Ladder[1] - 49);
                //to locate snake at using parallel array
                int p_value = l[id];
                p2->Player2 = ' ';
                while(p2->data != p_value)
                {
                    p2= p2->next;
                }
                p2->Player2 ='#';
                displayBoard();
                printf("\n");
            }
        }
        else
        return;
    }
}

void pl3()
{
    int op;
    op = dice();
    printf("\n ^ : ");
    getch();
    printf("    %d\n", op);

    if (flag3 == 0 && op == 6)
    {
        p3 = head;
        p3->Player3 = '^';
        displayBoard();
        flag3 = 1;
    }
    else if (flag3 == 1)
    {
        int count = 0;
        struct node *temp = p3;
        for (int i = 0; i < op; i++)
        {
            temp = temp->next;
            if (temp != NULL)
            {
                count++;
            }
            else
                break;
        }
        if (count == op)
        {
            p3->Player3 = ' ';
            for (int i = 0; i < op; i++)
            {
                p3 = p3->next;
            }
            p3->Player3 = '^';
            displayBoard();

            printf("\n");
            if(p3->Snake[0]=='S')
            {
                printf("\n!!!OOPS!!!\n");
                //index to calculate snake number 
                int id = (int)(p3->Snake[1] - 49);
                //to locate snake at using parallel array
                int p_value = s[id];
                p3->Player3 = ' ';
                while(p3->data != p_value)
                {
                    p3= p3->prev;
                }
                p3->Player3 ='^';
                displayBoard();
                printf("\n");
            }
            else if(p3->Ladder[0]=='L')
            {
                printf("\n!!!YAY!!!\n");
                //index to calculate snake number 
                int id = (int)(p3->Ladder[1] - 49);
                //to locate snake at using parallel array
                int p_value = l[id];
                p3->Player3 = ' ';
                while(p3->data != p_value)
                {
                    p3= p3->next;
                }
                p3->Player3 ='^';
                displayBoard();
                printf("\n");
            }
        }
        else
        return;
    }
}

void pl4()
{ int op;
    op = dice();
    printf("\n @ : ");
    getch();
    printf("    %d\n", op);

    if (flag4 == 0 && op == 6)
    {
        p4 = head;
        p4->Player4 = '@';
        displayBoard();
        flag4 = 1;
    }
    else if (flag4 == 1)
    {
        int count = 0;
        struct node *temp = p4;

        for (int i = 0; i < op; i++)
        {
            temp = temp->next;
            if (temp != NULL)
            {
                count++;
            }
            else
                break;
        }
        if(count==op)
        {
            p4->Player4 = ' ';
            for (int i = 0; i < op; i++)
            {
                p4 = p4->next;
            }
            p4->Player4 = '@';
            displayBoard();

            printf("\n");
            if(p4->Snake[0]=='S')
            {
                printf("\n!!!OOPS!!!\n");
                //index to calculate snake number 
                int id = (int)(p4->Snake[1] - 49);
                //to locate snake at using parallel array
                int p_value = s[id];
                p4->Player4 = ' ';
                while(p4->data != p_value)
                {
                    p4= p4->prev;
                }
                p4->Player4 ='@';
                displayBoard();
                printf("\n");
            }
            else if(p4->Ladder[0]=='L')
            {
                printf("\n!!!YAY!!!\n");
                //index to calculate snake number 
                int id = (int)(p4->Ladder[1] - 49);
                //to locate snake at using parallel array
                int p_value = l[id];
                p4->Player4 = ' ';
                while(p4->data != p_value)
                {
                    p4= p4->next;
                }
                p4->Player4 ='@';
                displayBoard();
                printf("\n");
            }
        }
        else
        return;
    }
}

void turn(int n)
{

    int op;

    switch (n)
    {
    case 2:
        printf("\nPlayer1 : ");
        pl1();
        printf("\nPlayer2 : ");
        pl2();
        break;
    case 3:
        printf("\nPlayer1 : ");         
        pl1();
        printf("\nPlayer2 : ");        
        pl2();
        printf("\nPlayer3 : ");
        pl3();
        break;
    case 4:
        printf("\nPlayer1 : ");        
        pl1();
        printf("\nPlayer2 : ");
        pl2();
        printf("\nPlayer3 : ");
        pl3();
        printf("\nPlayer4 : ");
        pl4();
        break;
    }
}

int main()
{
    /*
        . Initializing Players
    */
    char Player1 = '*';
    char Player2 = '#';
    char Player3 = '^';
    char Player4 = '@';
    int n;
    
    printf("\n\e[1mLet's Play Snake & Ladders :\e[m\n\n");
    createBoard();
    
    /*
        . The loop is used to check whether the user has entered 2,3 or 4 players
    */
    do
    {
        printf("\n\e[1mSelect the Number of Players : \e[m");
        scanf("%d", &n);
        if (n != 2 && n != 3 && n != 4)
        {
            printf("\n\033[1;31mNumber of Players should be between 2 and 4!!\033[0m\n");
        }
        else
            break;
    } while (1);

    displayBoard();
    
    switch (n)
    {
    case 2:
        printf("\n\nPlayer 1 : \033[1;35m%c\033[m\n", Player1);
        printf("Player 2 : \033[1;32m%c\033[m\n", Player2);
        printf("\nPress Enter to Start ....\n");
        getch();
        /*
            . This condition checks whether any player reaches the end or not
        */
        while(p1!=last && p2!=last)
        turn(n);
        break;
    case 3:
        printf("\n\nPlayer 1 : \033[1;35m%c\033[m\n", Player1);
        printf("Player 2 : \033[1;32m%c\033[m\n", Player2);
        printf("Player 3 : \033[1;36m%c\033[m\n", Player3);
        printf("\nPress Enter to Start ....\n");
        getch();
        /*
            . This condition checks whether any player reaches the end or not
        */
        while(p1!=last && p2!=last && p3!=last)
        turn(n);
        break;
    case 4:
        printf("\n\nPlayer 1 : \033[1;35m%c\033[m\n", Player1);
        printf("Player 2 : \033[1;32m%c\033[m\n", Player2);
        printf("Player 3 : \033[1;36m%c\033[m\n", Player3);
        printf("Player 4 : \033[1;34m%c\033[m\n", Player4);
        printf("\nPress Enter to Start ....\n");
        getch();
        /*
            . This condition checks whether any player reaches the end or not
        */
        while(p1!=last && p2!=last && p3!=last && p4!=last)
        {
            turn(n);
        }
        break;
    }

    if(p1==last)
    printf("\n\n\033[1;35m!!! Congratulations Player 1 !!!\033[m\n\n");
    else if(p2==last)
    printf("\n\n\033[1;35m!!! Congratulations Player 2 !!!\033[m\n\n");
    else if(p3==last)
    printf("\n\n\033[1;35m!!! Congratulations Player 3 !!!\033[m\n\n");
    else if(p4==last)
    printf("\n\n\033[1;35m!!! Congratulations Player 4 !!!\033[m\n\n");
    return 0;
}

