/* 문해원 201812312 2019/05/10 피연산자 스택의 c파일*/
#include <stdio.h>
#include <stdlib.h>
#include "HW3_201812312.h"

/*피연산자 스택의 초기화*/
void StackInit(Stack * pstack)
{
	pstack->head = NULL;
}

/*스택이 비었으면 TRUE값 리턴*/
int SIsEmpty(Stack * pstack)
{
	if(pstack->head == NULL)
		return TRUE;
	else
		return FALSE;
}

/*스택에 int형 데이터를 저장*/
void SPush(Stack * pstack, Data data)
{
	Node * newNode = (Node*)malloc(sizeof(Node));

	newNode->data = data;
	newNode->next = pstack->head;

	pstack->head = newNode;
}

/*마지막에 저장된 요소 삭제*/
Data SPop(Stack * pstack)
{
	Data rdata;
	Node * rnode;
	
	if(SIsEmpty(pstack)){
		printf("Stack Memory Error!");
		exit(-1);
	}

	rdata = pstack->head->data;
	rnode = pstack->head;

	pstack->head = pstack->head->next;
	free(rnode);

	return rdata;
}

