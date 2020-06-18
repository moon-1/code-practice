/*문해원 201812312 2019/05/10 계산기 프로그램 main함수 */ 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "HW3_201812312.h"/*피연산자 스택 헤더파일*/
#include "HW3_201812312_2.h"/*연산자 스택 헤더파일*/

int Calculate(char exp[])/*입력받은 수식을 계산하는 함수*/
{
	Stack OperandStack;/* 피연산자 스택*/
	Stack2 OperatorStack;/* 연산자 스택*/
	int i,j,d,anw;
	float op0,op1,op2;
	while(exp[i]!=0)/*입력받은 배열의 길이 체크*/
	{
		i++;
	}
	int OperandCount,OperatorCount,minusNum;
	int expLen = i;
	char tok;
	int num[expLen];/*연산자의 우선순위를 비교할 배열*/
	
	num[0] = 0;/*연산자스택의 처음 우선순위값은 0으로 설정*/
	
	/*스택 초기화*/
	StackInit(&OperandStack);
	StackInit2(&OperatorStack);

	/*우선순위를 표현하기 위한 k값*/
	int k =2;
	/* k>1인 모든 자연수 k에 대하여 k+1<2k이 성립하므로
 * 	 '+'과'-'연산자는 k,  '*'과 '/'연산자는 k+1,
 * 	 '('가 시작할때마다 우선순위를 x2해주고, ')'가 나타나면/2 함으로써
 * 	 모든 연산자의 우선순위를 결정 */
	
	for(i=0; i<expLen ; i++)
	{
		tok = exp[i];
		if(isdigit(tok)) /*tok이 숫자이면*/
		{
			SPush(&OperandStack,tok - '0');/*피연산자 스택에 넣기*/
			if(minusNum == 1)/*음수 입력 처리*/
			{
				op0 = SPop(&OperandStack);
				SPush(&OperandStack,op0*-1);
				minusNum = 0;
			}
			OperandCount++;
		}
		else if(OperandCount<=OperatorCount && tok=='-')/*음수입력 처리*/
                {
                      
			minusNum = 1;
                }

		else
		{		
			if(tok=='(')/* '('가 있으면 우선순위를  2배해줌  */
				k = 2*k;
			else{
				switch(tok)
				{
					/* '*'과'/'일때의 우선순위*/
					case '*':
					case '/':
						num[++j] = k+1;
						break;
					/* '+'과'-'일때의 우선순위*/
					case '+':
					case '-':
						num[++j] = k;
						break;
					default : 
						break;
				}
				/* 연산자스택에 넣을때 Push하는 연산자의 우선순위가 더 크면*/ 
				if(num[j-1]<num[j]&&tok!=')')
				{
				SPush2(&OperatorStack,tok); /*연산자 스택에 그대로 Push*/
				OperatorCount++;
				anw = 1;
				}

				/*연산자스택에 넣을때 Push하는 연산자의 우선순위가 더 작으면*/
				else if(num[j-1]>=num[j]&&tok!=')')
				{
					op2 =SPop(&OperandStack);
					op1 =SPop(&OperandStack);
					switch(SPop2(&OperatorStack))
						{
							case '+':
							SPush(&OperandStack,op1+op2);/*계산한 값을 피연산자 스택에 Push*/
							break;
							case '-':
							SPush(&OperandStack,op1-op2);/*계산한 값을 피연산자 스택에 Push*/
							break;
							case '*':
							SPush(&OperandStack,op1*op2);/*계산한 값을 피연산자 스택에 Push*/
							break;
							case '/':
							SPush(&OperandStack,op1/op2);/*계산한 값을 피연산자 스택에 Push*/
							break;		
						}
						OperatorCount--;
						OperandCount--;
						anw = -1;
				}
			
					/*계산이 진행되었을 경우*/
				if(anw == -1){
				j = j-2;/* 연산자 우선순위 배열값 재조정*/ 
				i--;/*탐색할 수식 배열의 인덱스-1*/
				}
				if(tok==')')/*괄호내의 수식이 끝나면 우선순위값 원래대로  복귀*/
					k = k/2;
			}
		}

	}
	/*연산자스택을 전부 비울때까지 계산*/
	while(!SIsEmpty2(&OperatorStack))
	{
	float num1,num2;
	num2 = SPop(&OperandStack);
	num1 = SPop(&OperandStack);
		switch(SPop2(&OperatorStack))
		{
			case '+':
			SPush(&OperandStack,num1+num2);/*계산한 값을 피연산자 스택에 Push*/
			break;
			case '-':
			SPush(&OperandStack,num1-num2);/*계산한 값을 피연산자 스택에 Push*/
			break;
			case '*':
			SPush(&OperandStack,num1*num2);/*계산한 값을 피연산자 스택에 Push*/
			break;
			case '/':
			SPush(&OperandStack,num1/num2);/*계산한 값을 피연산자 스택에 Push*/
			break;		
		}
	}
	return SPop(&OperandStack);/*계산 결과 값 리턴*/
}

int main()
{
	char str[100]={0,};
	printf("\n계산할 수식을 입력하세요 : ");
	scanf("%s",&str);
	printf("\n\n%s  = %d \n\n",str,Calculate(str));
	
	return 0;
}
