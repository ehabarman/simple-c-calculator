struct read
{
    char line[50];
    struct read*next;
};
struct stack
{
    char op;
    struct stack * next;
};
struct stackk
{
    double op;
    struct stackk*next;
};

void findpostfix(void);
void calcpostfix(struct read* temp,FILE*output);
void push(char elem);
void isvalid(void);
void ReadFromFile(void);
void addtolistread(char line[]);
void addvalid(struct read* temp);
void addinvalid(struct read* temp);
void printinvalid(void);
double convertdouble(char num[]);
double popp(void);
void pushh(double elem);
char pop(void) ;
int checkright(char b);
int checkleft(char b);
int checkadd(char b);
int checkminus(char b);
int checkmult(char b);
int checkdiv(char b);
int checknum(char b);
int pr(char elem);
int finderror(char a,char b,int *count,int i);



struct stackk*calc;
struct stack* s;
struct read* headr;
struct read* valid;
struct read* invalid;

void menu(void)
{

    system("cls");//cleaning screen before new menu
    printf("please choose operation you want to be excuted from menu below:\n\n");
    printf("________________________________________\n");
    printf("|1|read from a file                     |\n");
    printf("________________________________________\n");
    printf("|2|checking which valid and which is not|\n");
    printf("________________________________________\n");
    printf("|3|print invalid                        |\n");
    printf("________________________________________\n");
    printf("|4|print valid                          |\n");
    printf("________________________________________\n");
    printf("|5|exist                                |\n");
    printf("________________________________________\n");
    printf("\nHint : only using operation numbers above will make program work\n");

}

void ReadFromFile (void)
{
    FILE*inp;
    char line[50];
    int s;
    char name[15];
    system("cls");
    printf("please enter file name\n");
    scanf("%s",name);
    inp = fopen( name ,"r" ) ;
    if(inp==NULL)
    {
        printf("an error happened while opening file\n");
        printf("please press any key to try again\n");
        getch();
        ReadFromFile();
    }
    else
    {
        s=fgets(line,50,inp);
        if( s == EOF )
        {
            printf("file is empty\n");
            printf("press any key to continue....");
            getch();
        }
        else
        {
            strtok(line,"\n");//to get rid of empty line after first name
            while(s!=NULL)
            {
                addtolistread(line);
                s=fgets(line,50,inp);
                strtok(line,"\n");
            }
            fclose(inp);

            printf("press any key to continue....");
            getch();

        }
    }
}

void addtolistread(char line[])
{
    struct read* temp=(struct read*)malloc(sizeof(struct read));
    if(headr->next==NULL)//if list is empty
    {
        temp->next=headr;
        headr->next=temp;
        strcpy(temp->line,line);
    }
    else // if list has already nodes // do it as a circle
    {
        temp->next=headr->next;
        headr->next=temp;
        strcpy(temp->line,line);
    }
}

void addvalid(struct read* temp)
{
    struct read*keep=(struct read*)malloc(sizeof(struct read));
    strcpy(keep->line,temp->line);
    if(valid->next==NULL)
    {
        keep->next=valid;
        valid->next=keep;
    }
    else
    {
        keep->next=valid->next;
        valid->next=keep;
    }

}

void addinvalid(struct read* temp)// add invalid equation to invalid head circle add
{
    struct read*keep=(struct read*)malloc(sizeof(struct read));
    strcpy(keep->line,temp->line);
    if(invalid->next==NULL)
    {
        keep->next=invalid;
        invalid->next=keep;
    }
    else
    {
        keep->next=invalid->next;
        invalid->next=keep;
    }
}
double convertdouble(char num[])//convert string into a double
{
    int  i, len;
    double result=0;
    double constant1 =10,constant2=1;
    len = strlen(num);
    for(i=0; i<len; i++)
    {
        if(num[i]!='.')
            result = result * constant1 +constant2*((double)num[i] - 48 );//ascii 0 = 30H
        else
        {
            constant1=1;
            constant2=0.1;
        }
    }

    return result;

}
int finderror(char a,char b,int *count,int i)//function to find error with flags
{
    if (i==0) //first char in equation
    {
        if (a=='*'||a=='/'||a==')')//starting error
            return 0;
        else if (a=='(') //starting with ( case
        {
            *count++;
            return 1;
        }
        else
        {
            return 1;
        }

    }
    switch(a)
    {
    case '(':
        *count++;
        return checkright(b);
        break;
    case ')':
        *count--;
        return checkleft(b);
        break;
    case '+':
        return checkadd(b);
        break;
    case '-':
        return checkminus(b);
        break;
    case '*':
        return checkmult(b);
        break;
    case '/':
        return checkdiv(b);
    default:
        return checknum(b);

    }
}
int checkright(char b)
{
    if (b=='('||b=='+'||b=='-'||b=='/'||b=='*')
        return 1;
    return 0;
}
int checkleft(char b)
{
    if(b=='('||b=='+'||b=='-'||b=='/'||b=='*')
        return 0;
    return 1;
}
int checkadd(char b)
{
    if(b=='+')
        return 0;
    return 1;
}
int checkminus(char b)
{
    if(b=='-')
        return 0;
    return 1;
}
int checkmult(char b)
{
    if(b=='*'||b=='/'||b=='-'||b=='+'||b=='(')
        return 0;
    return 1;

}
int checkdiv(char b)
{
    if(b=='*'||b=='/'||b=='-'||b=='+'||b=='(')
        return 0;
    return 1;
}
int checknum(char b)
{
    if(b==')')
        return 0;
    return 1;
}
void isvalid(void)//function to check if equations valid or not then separate them into two lists
{
    int i,len,*count=0,flag,n,done;
    struct read* temp=(struct read*)malloc(sizeof(struct read));
    temp=headr;//to keep very first head
    headr=headr->next;

    while(headr!=temp)
    {
        done=0;
        count=0;
        n=0;
        len=strlen(headr->line);
        for(i=0; i<len; i++)
        {
            flag= finderror(headr->line[i],headr->line[i-1],&count,i);
            if (flag==0)
            {
                addinvalid(headr);
                done =1;// flag for valid
                n=1;//to not use same equation twice in invalid case
                break;
            }
            else if (flag==1)
            {

                continue;
            }

        }
        i=len;
        if((headr->line[i]=='*'||headr->line[i]=='/'||headr->line[i]=='+'||headr->line[i]=='-'||headr->line[i]=='('||count!=0)&&n==0)
        {

            addinvalid(headr);
            done =1;
        }
        if(done==0)
        {
            addvalid(headr);
        }

        headr=headr->next;
    }
}
void printinvalid(void)
{   FILE*output=fopen("invalid.txt","w+");
    struct read*temp;
    temp=invalid->next;
    while(temp!=invalid)
    {
        fprintf(output,"invalid equation is :%s\n",temp->line);
        temp=temp->next;
    }
    fclose(output);
}


void findpostfix(void)
{
    struct read* temp;
    FILE*output=fopen("valid.txt","w+");
    char pofx[50], ch, elem;
    int i = 0, k = 0;
    s->op='@';
    temp=valid->next;
    while (temp!=valid)
    {
        i = 0;
        k = 0;

        while ((ch = temp->line[i]) != '\0')
        {
            i++;


            if (ch == '(')//putting ( in stack
            {
                push(ch);

            }

            else if (isalnum(ch)||ch=='.') //check if value number or letter to return non-zero else return 0
            {
                while((isalnum(ch)||ch=='.')&&ch!='\0')
                {

                    pofx[k++] = ch;
                    ch=temp->line[i];
                    i++;
                }
                i--;
                pofx[k++]=' ';

                continue;

            }
            else if (ch == ')')//for )
            {
                while (s->next->op != '(')
                    pofx[k++] = pop();
                elem = pop(); // to Remove {(}


            }
            else     // Operator case
            {
                if(i==1&&ch=='+')//+a op b
                    continue;
                if(i>=3&&(temp->line[i-2]=='-'||temp->line[i-2]=='/'||temp->line[i-2]=='*')&&ch=='+')//a op +b {
                    continue;
                 if(i==1&&ch=='-'){ //-a
                       pofx[k++]=ch;
                    continue;}
                 if(i>=2&&ch=='-'&&(temp->line[i-2]=='/'||temp->line[i-2]=='('||temp->line[i-2]=='*'||temp->line[i-2]=='+')&&(isalnum(temp->line[i]))){ //op -a
                    pofx[k++]=ch;
                    continue;
                 }


                while (s->next!=NULL)

                    if(pr(s->next->op) >= pr(ch))//pull everything that have higher priority
                    {
                            pofx[k++] = pop();
                    }

                    else//if we get to op that have less priority then push ch
                        break;
                push(ch);

            }
        }
        while (s->next != NULL) // Pop from stack till it empty completely
            pofx[k++] = pop();
        pofx[k] = '\0'; /* make it valid string for copy */
        fprintf(output,"original equation: %s\n",temp->line);
        strcpy(temp->line,pofx);
        calcpostfix(temp,output);
        temp=temp->next;

    }
    fclose(output);


}

void push(char elem)   // Function for PUSH operation
{
    struct stack* temp=(struct stack*)malloc(sizeof(struct stack));
    temp->op=elem;
    temp->next=s->next;
    s->next=temp;

}
char pop(void)   //Function for POP operation
{
    char c;
    struct stack*temp;
    temp=s->next;
    s->next=temp->next;
    c=temp->op;
    free(temp);
    return c;
}
int pr(char elem)   /* Function for precedence */
{
    switch (elem)
    {
    case '@':
        return 0;
    case '(':
        return 1;
    case '+':
    case '-':
        return 2;
    case '*':
    case '/':
        return 3;
    }
}
void calcpostfix(struct read * temp,FILE*output)
{
    char ch;
    double op1,op2;
    int i=0;
    int j;
    int n;
    int minus;
    double result;
    char num[10];

        while( (ch=temp->line[i]) != '\0')
        {
        op1=0;
        op2=0;
        j=0;
        minus=0;
        i++;
            if((i-1)==0&&ch=='+')
            {
                continue;
            }
            if((i-1)==0&&ch=='-'){
              minus=1;
            ch=temp->line[i++];
               }
            if(ch=='-'&&temp->line[i-2]==' '&&isdigit(temp->line[i])){
                minus=1;
                ch=temp->line[i++];
            }
            if(isdigit(ch)||ch=='.')
            {

                n=0;

                while((isdigit(ch)||ch=='.')&&ch!=' ')
                {
                    num[j++]=ch;
                    ch=ch=temp->line[i++];
                }
                num[j]='\0';
                if(minus==0)
                result=convertdouble(num);
                else
                    result=-1.0*convertdouble(num);

                pushh(result); /* Push the value */
                continue;
            }

            else
            {

                op2=popp();
                op1=popp();


                if (op2==0&&ch=='/')
                {
                    fprintf(output,"Postfix Expression: %s\n",temp->line);
                    fprintf(output,"Result after Evaluation:divided by zero\n");
                    fprintf(output,"________________________\n");
                    n=1;
                    break;
                }
                else
                    switch(ch)
                    {

                    case '+':
                        pushh(op1+op2);

                        break;
                    case '-':
                        pushh(op1-op2);

                        break;
                    case '*':
                        pushh(op1*op2);

                        break;
                    case '/':
                        pushh(op1/op2);

                        break;
                    }
            }
        }
        if(n==0)//if its not divided by zero
        {
            op2=calc->next->op;
            fprintf(output,"Postfix Expression: %s\n",temp->line);
            fprintf(output,"Result after Evaluation: %0.2f\n",op2);
            fprintf(output,"_______________________________________\n");

    }
}


void pushh(double elem)   // Function for PUSH operation
{
    struct stackk* temp=(struct stackk*)malloc(sizeof(struct stackk));
    temp->op=elem;
    temp->next=calc->next;
    calc->next=temp;

}

double popp(void)   //Function for POP operation
{
    double c;
    struct stackk*temp;
    temp=calc->next;
    calc->next=temp->next;
    c=temp->op;
    free(temp);
    return c;
}
