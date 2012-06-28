#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "simple_list.h"
#include "linear_sequence.h"

void gotoxy(int x, int y)
{
  printf("\033[%d;%df", y, x);
  fflush(stdout);
}

int main(void)
{
    node *p;
    p = LSQ_HandleInvalid;
    int num;

    srand ( time(NULL) );
    int i;
    for(i=0;i<10;i++)
    {
        num = rand() % 10 +1;
        append(&p, num);
    }

    display(p);


//    char choice;
//    do
//    {
//        system("clear");
//        printf("PROGRAM TO IMPLEMENT SINGLY LINKED LIST ");
//        printf("\n=====================================");
//        printf("\n\n1.Create \\ Appending The List");
//        printf("\n2.Insert Node At Begining");
//        printf("\n3.Insert Node In Middle");
//        printf("\n4.Deleting a  Node");
//        printf("\n5.Counting The No Of Nodes");
//        printf("\n6.Displaying the list");
//        printf("\n7.Exit");
//oper:
//        gotoxy(1,15);
//        printf("                                          ");
//        gotoxy(1,11);
//        printf("\n\nEnter ur Choice : ");
//        choice=getchar();
//        switch(choice)
//        {
//            case '1':
//        {
//                char asd;
//                do
//                {
//                    printf("Enter any number : ");
//                    scanf("%d",&num);
//                    append(&p,num);
//                    printf("Enter more (y/n) :");
//                    fflush(stdin);
//                    asd=getchar();
//                }
//                while(asd !='n');
//        }
//            break;
//            case '2':
//                 printf("Enter The Data : ");
//                 scanf("%d",&num);
//                 in_begin(&p,num);
//            break;
//            case '3':
//                 printf("\nEnter The Position :");
//                 scanf("%d",&loc);
//                 printf("\nEnter The Data : ");
//                 scanf("%d",&num);
//                 in_middle(&p,loc,num);
//            break;
//            case '4':
//                 printf("\nEnter The Data u Want To Delete : ");
//                 scanf("%d",&num);
//                 del(&p,num);
//            break;
//            case '5':
//                 printf("\nThe No Of Nodes Are %d",count(p));
//                 getchar();
//            break;
//            case '6':
//                 display(p);
//                 getchar();
//            break;
//            case '7':
//                 printf("\n\nQuiting.......");
//                 getchar();
//                 return 0;
//            break;
//            default:
//                 gotoxy(1,15);printf("Invalid choice.Please Enter Correct Choice");
//                 getchar();
//                 goto oper;
//            }
//    }
//    while(choice !=7);
    return 0;
}

