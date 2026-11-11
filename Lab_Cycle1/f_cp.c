#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX 20

typedef struct {
    int value, known;
} Symbol;

Symbol table[26];
char stmt[MAX][30];

int eval(int a, int b, char op)
{
    switch(op)  
    {
        case '+': return a+b;
        case '-': return a-b;
        case '*': return a*b;
        case '/': return a/b;
    }
    return 0;
}

int main()
{
    int n, val;
    char lhs, op1, op2, op;

    printf("Enter number of statements: ");
    scanf("%d",&n);

    printf("Enter statements:\n");
    for(int i=0;i<n;i++)
        scanf("%s",stmt[i]);

    printf("\nORIGINAL CODE\n");
    printf("----------------------\n");
    for(int i=0;i<n;i++)
        printf("%s\n",stmt[i]);

    printf("\nCONSTANT PROPAGATION\n");
    printf("----------------------\n");

    for(int i=0;i<n;i++)
    {
        if(sscanf(stmt[i],"%c=%d",&lhs,&val)==2)
        {
            table[lhs-'a'].known=1;
            table[lhs-'a'].value=val;
            printf("%c=%d\n",lhs,val);
        }
        else if(sscanf(stmt[i],"%c=%c%c%c",&lhs,&op1,&op,&op2)==4)
        {
            int leftKnown=0,rightKnown=0;
            int left,right;

            printf("%c=",lhs);

            if(islower(op1) && table[op1-'a'].known)
            {
                left=table[op1-'a'].value;
                leftKnown=1;
                printf("%d",left);
            }
            else
                printf("%c",op1);

            printf("%c",op);

            if(islower(op2) && table[op2-'a'].known)
            {
                right=table[op2-'a'].value;
                rightKnown=1;
                printf("%d",right);
            }
            else
                printf("%c",op2);

            printf("\n");

            if(leftKnown && rightKnown)
            {
                table[lhs-'a'].known=1;
                table[lhs-'a'].value=eval(left,right,op);
            }
            else
                table[lhs-'a'].known=0;
        }
    }

    printf("\nCONSTANT FOLDING\n");
    printf("----------------------\n");

    for(int i=0;i<n;i++)
    {
        if(sscanf(stmt[i],"%c=%d",&lhs,&val)==2)
        {
            printf("%c=%d\n",lhs,val);
        }
        else if(table[lhs-'a'].known)
        {
            printf("%c=%d\n",lhs,table[lhs-'a'].value);
        }
        else
        {
            printf("%s\n",stmt[i]);
        }
    }

    return 0;
}