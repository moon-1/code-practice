/* 문해원 201812312 2019/05/10 피연산자 스택의 헤더파일*/
#ifndef __LB_STACK_H__
#define __LB_STACK_H__

#define TRUE	1
#define FALSE	0

typedef float Data;/*float형 데이터-> 피연산자를 입력받음*/

typedef struct _node/*연결 리스트의 노드를 표현한 구조체*/
{
	Data data;
	struct _node * next;
} Node;

typedef struct _listStack/*연결 리스트 기반 스택을 표현한 구조체*/
{
	Node * head;
} ListStack;


typedef ListStack Stack;

void StackInit(Stack * pstack);/*스택 초기화*/
int SIsEmpty(Stack * pstack);/*스택이 비었는지 확인*/

void SPush(Stack * pstack, Data data);/* 스택의 Push연산*/
Data SPop(Stack * pstack);/*스택의 Pop연산*/
#endif
