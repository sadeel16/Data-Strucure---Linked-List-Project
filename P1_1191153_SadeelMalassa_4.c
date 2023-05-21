#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define Max 250
#include <stdlib.h>
#include <math.h>

//Sadeel Malassa_1191153_4
struct node
{
    char Data[Max];
    float power;
    float coff;
    int count;
    struct node* Next;
    struct node* prev;
};

//all functions
void addition(struct node* L,struct node* Add);
void DeleteList(struct node* L);
struct node* FindAdd(float pow, struct node* L);
void subtraction(struct node* L,struct node* sub);
void multi(struct node* L,struct node* mul);
void printFinal(struct node* F);
void INsertX(float x,struct node* Final);
void save(struct node* F);

struct node* MakeEmpty(struct node* L)
{
    if(L != NULL)
        DeleteList( L );
    L = (struct node*)malloc(sizeof(struct node));

    if(L == NULL)
        printf("Out of memory!\n");

    L->Next = NULL;
    return L;
}

int IsEmpty(struct node* L)
{
    return L->Next == NULL;
}
int IsLast(struct node* P, struct node* L)
{
    return P->Next == NULL;
}

struct node* Find(int count, struct node* L)
{
    struct node* P;
    P = L->Next;

    while(P != NULL && P->count != count)
        P =P->Next;

    return P;
}


void InsertEquation(char equation[Max],struct node* L)
{

    struct node* temp, *P=L;

    temp = (struct node*)malloc(sizeof(struct node));
    strcpy(temp->Data,equation);

    while(P->Next != NULL)
        P=P->Next;

    P->Next = temp;

    temp->Next = NULL;
}

void InsertLast(float X,float y,int count, struct node* L)
{
    struct node* temp, *P=L;

    temp = (struct node*)malloc(sizeof(struct node));
    temp->coff = X;
    temp->power = y;
    temp->count=count;

    while(P->Next != NULL)
        P=P->Next;

    P->Next = temp;
    temp->prev = P->prev;


    temp->Next = NULL;

}

void PrintList(struct node* L)
{
    struct node* P = L;
    if( IsEmpty(L))
        printf("Empty list\n");
    else
        do
        {
            P=P->Next;
            printf("L1 coff: %f\t,L1 power: %f\t, count: %d\t\n", P->coff, P->power,P->count);
        }
        while( !IsLast(P, L) );
    printf("\n");
}
void PrintEquation(struct node* L)
{
    struct node* P = L;
    if( IsEmpty(L))
        printf("Empty list\n");
    else
        do
        {
            P=P->Next;
            printf("\t\t\t %s", P->Data);
        }
        while( !IsLast(P, L) );
    printf("\n");
}

void DeleteList(struct node* L)
{
    struct node *P, *temp;
    P = L->Next;
    L->Next = NULL;

    while(P != NULL)
    {
        temp = P->Next;
        free(P);
        P=temp;
    }
}

int size( struct node* L)
{
    struct node* p = L->Next;
    int count = 0;
    while(p != NULL )
    {
        count += 1;
        p = p->Next;
    }
    return count;
}


//remove all spaces from a string
void removeSpace(char equation[Max])
{
    int  i,s=0;
    for(i=0; equation[i]; i++)
    {
        equation[i]=equation[i+s];


        if(equation[i]==' '|| equation[i]=='\t')
        {
            s++;
            i--;
        }

    }
}


int main()
{
    //create linked lists

    struct node* L1;
    L1 = MakeEmpty(NULL);

    struct node* L2;
    L2 = MakeEmpty(NULL);

    struct node* Add;
    Add = MakeEmpty(NULL);

    struct node* sub;
    sub = MakeEmpty(NULL);

    struct node* mul;
    mul = MakeEmpty(NULL);

    FILE *in;
    in = fopen("equations.txt","r");
    char equation[Max];
    char* str = equation;
    float y,pow;
    float power;
    float coff;
    int position;
    int count=0;

    //while loop read the full line as a string ,
    //then scan each char in the string if its power or coff to convert it into float and then save it to its place
    while(!feof(in))
    {
        fgets(str,Max,in);
        removeSpace(equation);
        InsertEquation(equation,L2);
        for(int i=0; i<=strlen(equation); i++)
        {

            if(equation[i]>='0'&&equation[i]<='9')
            {
                position = i;
                coff=(int)(equation[i])-48;
                for(int n=i; n<strlen(str); n++)
                {
                    if(equation[i+1]>'0'&&equation[i+1]<='9')
                    {
                        y=(int)(equation[i+1])-48;
                        y=y/10;
                        coff=y+coff;
                        coff=coff*10;
                        n++;
                        i++;

                    }
                    else if(equation[i+1]=='0')
                    {
                        coff=coff*10;
                        n++;
                        i++;
                    }
                    else
                    {
                        break;
                    }
                }

                if(equation[position-1]=='-')
                {
                    coff=coff*-1;
                }
                else
                {

                }
                while(coff!=0)
                {
                    if(equation[i+1]!='x')
                    {
                        power=0;
                        break;
                    }
                    else
                    {
                        break;
                    }
                }

            }
            else if(equation[i]=='+'&&i>0)
            {
                count++;
                InsertLast(coff,power,count,L1);
                continue;
            }
            else if(equation[i]=='-'&&i>0)
            {
                count++;
                InsertLast(coff,power,count,L1);
                continue;
            }
            else if(i==strlen(equation))
            {
                count++;
                InsertLast(coff,power,count,L1);
                continue;
            }
            else if(equation[i]=='x'||equation[i]=='X')
            {
                if(equation[i-1]=='+')
                {
                    coff=1;
                    printf("coff = %f\n",coff);
                }
                else if(equation[i-1]=='-')
                {
                    coff=-1;
                    printf("coff = %f\n",coff);
                }
                for(int p=i; p<strlen(equation); p++)
                {
                    if(equation[i+1]=='+'||equation[i+1]=='-')
                    {
                        power=1;
                        break;
                    }

                    else if(equation[i+1]=='^')
                    {
                        i++;
                        power=(int)(equation[i+1])-48;
                        i++;
                        for(int pp=i; pp<strlen(equation); pp++)
                        {

                            if(equation[i+1]>'0'&&equation[i+1]<='9')
                            {
                                i++;
                                pow=(int)(equation[i])-48;
                                pow=pow/10;
                                power=pow+power;
                                power=power*10;

                            }
                            else if(equation[i+1]=='0')
                            {
                                i++;
                                power=power*10;
                            }
                            else
                            {
                                break;
                            }
                        }
                        break;
                    }
                    else
                    {
                        power = 1;
                        break;
                    }
                }
            }
        }
    }
//create a menu to the user and take orders
    printf("\t\t\t\t\t\t------ WELCOME ! ------\n");
    printf("\n");
    printf("\t\t EQUATIONS :\n");
    printf("\n");
    PrintEquation(L2);
    printf("\n");
    printf("\t\t Choose the output operation by entering it number\n");
    printf("\n");
    int choice;
    int x;
    float Xvalue;

    while(1)
    {

        printf("\t\t\t 1. Addition\n");
        printf("\t\t\t 2. Subtraction\n");
        printf("\t\t\t 3. Multiplication\n");
        printf("\t\t\t 4. Save\n");
        printf("\n");
        printf("\t\t\t\t");
        scanf("%d",&choice);


        switch(choice)
        {

        case 1:
        {
            MakeEmpty(Add);
            addition(L1,Add);
            printf("\t\t\t Calculate X ?");
            printf("\t Yes: Enter 1\tNo: Enter 0\n");
            printf("\t\t\t\t");
            scanf("%d", &x);
            if(x==1)
            {
                printf("\t\t\t X = ");
                scanf("%f",&Xvalue);
                INsertX(Xvalue,Add);
            }
            break;
        }

        case 2:
        {
            MakeEmpty(sub);
            subtraction(L1,sub);
            printf("\t\t\t Calculate X ?");
            printf("\t Yes: Enter 1\tNo: Enter 0\n");
            printf("\t\t\t\t");
            scanf("%d", &x);
            if(x==1)
            {
                printf("\t\t\t X = ");
                scanf("%f",&Xvalue);
                INsertX(Xvalue,sub);
            }
            break;
        }

        case 3:
        {
            MakeEmpty(mul);
            multi(L1,mul);
            printf("\t\t\t Calculate X ?");
            printf("\t Yes: Enter 1\tNo: Enter 0\n");
            printf("\t\t\t\t");
            scanf("%d", &x);
            if(x==1)
            {
                printf("\t\t\t X = ");
                scanf("%f",&Xvalue);
                INsertX(Xvalue,mul);
            }
            break;
        }
        case 4:
        {
            save(Add);
            save(mul);
            save(sub);
            printf("\n");
        }

        }
    }

    DeleteList(L1);
    DeleteList(L2);
    fclose(in);


    return 0;
}
//find the sum of all the equations
//by creating linked list for the result if its empty insert the first node in the L1 linked list to sub linked list
//if its not empty compare the power, if power exists, compare if equal add,
//if power does not exist create a node with that power then continue
void addition(struct node* L,struct node* Add)
{
    struct node* p;
    int flag;
    int q=0;

    for(int i =1; i<=size(L); i++)
    {
        p=Find(i,L);
        flag=0;
        if(!IsEmpty(Add))
        {
            for(int a=1; a<=size(Add); a++)
            {
                struct node* check = FindAdd(p->power,Add);
                if(check!=NULL)
                {
                    check-> coff = check->coff + p->coff;
                    flag=1;

                }

            }
            if(!flag)
            {
                q++;
                InsertLast(p->coff,p->power,q,Add);
            }
        }
        else
        {
            q++;
            InsertLast(p->coff,p->power,q,Add);
        }
    }
    printFinal(Add);
    printf("\n");
}
//find the subtraction of all equations
//by creating linked list for the result if its empty insert the first node in the L1 linked list to sub linked list
//if its not empty compare the power, if power exists, compare if equal subtract,
//if power does not exist create a node with that power then continue
void subtraction(struct node* L,struct node* sub)
{
    struct node* p;
    int q=0;
    int flag;

    for(int i =1; i<=size(L); i++)
    {
        p=Find(i,L);
        flag=0;
        if(!IsEmpty(sub))
        {
            for(int a=1; a<=size(sub); a++)
            {
                struct node* check = FindAdd(p->power,sub);
                if(check!=NULL)
                {
                    check-> coff = check->coff - p->coff;
                    flag=1;

                }

            }
            if(!flag)
            {
                q++;
                InsertLast(p->coff,p->power,q,sub);
            }
        }
        else
        {
            q++;
            InsertLast(p->coff,p->power,q,sub);
        }
    }
    printFinal(sub);
    printf("\n");
}
//find the multiplication of all equations
void multi(struct node* L,struct node* mul)
{
    struct node* p;
    p = Find(1,L);
    float finalP=p->power;
    float finalC=p->coff;

    for(int i=2; i<=size(L); i++)
    {
        p = Find(i,L);
        finalP = finalP + p->power;
        finalC = finalC * p->coff;
    }
    InsertLast(finalC,finalP,1,mul);
    printf("\t\t\t %fX^%f",finalC,finalP);
    printf("\n");
}

//find specific node by its power
struct node* FindAdd(float pow, struct node* L)
{
    struct node* P;
    P = L->Next;

    while(P != NULL && P->power != pow)
        P =P->Next;

    return P;
}
//print the final result after an operation (if the coff > 0 print the positive sign (+) if coff<0 print the same value
void printFinal(struct node* F)
{

    struct node* p;
    printf("\t\t");
    for(int i=1; i<=size(F); i++)
    {
        p=Find(i,F);
        if(p->power==0)
        {
            if((p->coff)>0)
            {
                printf("+ %f ",p->coff);
            }
            else
            {
                printf("%f",p->coff);
            }
        }
        else
        {
            if(p->coff>0)
            {
                printf(" + %f X ^ %f ",p->coff,p->power);
            }
            else
            {
                printf(" %f X ^ %f ",p->coff,p->power);
            }
        }


    }

}
//save the results to file
void save(struct node* F)
{

    FILE* out;
    out = fopen("results.txt","a");
    fprintf(out,"\n");
    struct node* p;
    for(int i=1; i<=size(F); i++)
    {
        p=Find(i,F);
        if(p->power==0)
        {
            if((p->coff)>0)
            {
                fprintf(out,"+ %f ",p->coff);
            }
            else
            {
                fprintf(out,"%f",p->coff);
            }
        }
        else
        {
            if(p->coff>0)
            {
                fprintf(out," + %f X ^ %f ",p->coff,p->power);
            }
            else
            {
                fprintf(out," %f X ^ %f ",p->coff,p->power);
            }
        }


    }
    fclose(out);

}
//calculate the result if the user gave you value for x by taking the power then multiply it by the coff
void INsertX(float x,struct node* Final)
{

    struct node* p;
    float resultF;


    for(int i=1; i<=size(Final); i++)
    {
        p = Find(i,Final);
        resultF += (p->coff)*(pow(x,p->power)) ;


    }
    printf("\t\t\tFinal Value = %f\n",resultF);

}





