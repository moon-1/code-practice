/* 문해원 201812312 2019/05/10 연산자 스택의 c파일*/
#include <stdio.h>
#include <stdlib.h>
#include "HW3_201812312_2.h"

/*연산자 스택의 초기화*/
void StackInit2(Stack2 * pstack2)
{
        pstack2->head2 = NULL;
}

/*스택이 빈 경우 TRUE값 리턴*/
char SIsEmpty2(Stack2 * pstack2)
{
        if(pstack2->head2 == NULL)
                return TRUE;
        else
                return FALSE;
}

/*스택에 char형 데이터를 저장*/
void SPush2(Stack2 * pstack2, Data2 data2)
{
        Node2 * newNode = (Node2*)malloc(sizeof(Node2));

        newNode->data2 = data2;
        newNode->next2 = pstack2->head2;

        pstack2->head2 = newNode;
}

/*마지막에 저장된 요소를 삭제*/
Data2 SPop2(Stack2 * pstack2)
{
        Data2 rdata;
        Node2 * rnode;

        if(SIsEmpty2(pstack2)){
                printf("Stack Memory Error!");
                exit(-1);
        }

        rdata = pstack2->head2->data2;
        rnode = pstack2->head2;

        pstack2->head2 = pstack2->head2->next2;
        free(rnode);

        return rdata;
}


