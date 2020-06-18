/* 문해원 201812312 2019/05/10 연산자 스택의 헤더파일*/
#ifndef __LB_STACK_H2__
#define __LB_STACK_H2__

#define TRUE    1
#define FALSE   0

typedef char Data2;/* char형 데이터의 입력-> 연산자를 입력받음 */

typedef struct _node2 /*연결 리스트의 노드를 표현한 구조체*/
{
        Data2 data2;
        struct _node2 * next2;
} Node2;

typedef struct _listStack2/*연결 리스트 기반 스택을 포현한 구조체*/
{
        Node2 * head2;
} ListStack2;


typedef ListStack2 Stack2;

void StackInit2(Stack2 * pstack2);/*스택 초기화*/
char SIsEmpty2(Stack2 * pstack2);/*스택이 비었는지 확인*/

void SPush2(Stack2 * pstack2, Data2 data2);/* 스택의 Push 연산*/
Data2 SPop2(Stack2 * pstack2); /* 스택의 Pop 연산*/
#endif

