#include <stdio.h>
#include <stdlib.h>
#include "stack.c"
#include <conio.h>
#define swap(x,y)(t=x; x=y;y=t;)
int main()
{
    int x=0,j=0;
    system("color 20");
    s=(struct stack*)malloc(sizeof(struct stack));
    s->next=NULL;
    calc=(struct stackk*)malloc(sizeof(struct stackk));
    calc->next=NULL;
    headr=(struct read*)malloc(sizeof(struct read));
    valid=(struct read*)malloc(sizeof(struct read));
    invalid=(struct read*)malloc(sizeof(struct read));
    headr->next=NULL;
    valid->next=NULL;
    invalid->next=NULL;
    int pif=0,pvf=0,rf=0,pc=0;
    char op;
    do
    {
        menu();

        scanf("%c",&op);

        if(op=='1')
        {
            system("cls");
            if(rf==0){
            ReadFromFile();
            x++;
            rf=1;
            }
            else {
                printf("you have already done this option\n");
                printf("press any key to continue....\n");
                getch();

                }

        }
        else if (op=='2')
        {
            if(x<=0)
            {
                printf("you haven't read from file yet\n");
                printf("press any key to continue....\n");
                getch();
            }
            else
            {
                system("cls");
                if(pc==0){
                isvalid();
                printf("press any key to continue....\n");
                getch();
                pc++;
                j++;
                }
                else{
                   printf("you have already done this option\n");
                printf("press any key to continue....\n");
                getch();

                }
                }
            }

        else if (op=='3')
        {
            if(j<=0)
            {
                printf("you haven't check which valid and which not yet\n");
                printf("press any key to continue....\n");
                getch();
            }
            else
            {
                system("cls");
                if(pif==0){
                printinvalid();
                printf("press any key to continue....\n");
                getch();
                pif++;
                }
                else{
                printf("you have already done this option\n");
                printf("press any key to continue....\n");
                getch();

                }

                }
            }

        else if (op=='4')
        {

            if(j<=0)
            {
                printf("you haven't check which valid and which not yet\n");
                printf("press any key to continue....\n");
                getch();
            }
            else
            {
                system("cls");
                if(pvf==0){
                findpostfix();
                printf("press any key to continue....\n");
                getch();
                pvf++;
                }
                else {
                    printf("you have already done this option\n");
                printf("press any key to continue....\n");
                getch();

                }
                }
            }
            else if (op=='5'){
                break;
            }

    }
    while(op!='5');
    system("cls");
    printf("thanks for using this program\n");

    return 0;


}
