/*메인함수 201812312  문해원 2019.04.03*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "HW1_201812312.h"
#define FLOWER 1

int main(void)
{	

        int i,day,data;
	List list;/*배열리스트의 생성 및 초기화*/
        ListInit(&list);
        scanf("%d",&day);
	int arr[day];
	LFirst(&list,&data);
	printf("\n기분을 입력하세요 :" );/*데이터 저장*/
	for(i=0;i<day;i++){
	scanf("%d",&data);
        LInsert(&list,data);
	arr[i]=data;
	}
	int p,flonum,count,a,b,MIndex,n,a1;
        int sadDay[day],sadDay2[day],Max[day],flo[day],flo2[day];

	for(i=0;i<day;i++)/*배열값 전부 0으로 초기화*/
	{
                flo[i]=0;
                sadDay[i]=0;
                Max[i]=0;
        }

        /*꽃을 주는 최댓값 계산 알고리즘
 	 (1) 기분의 양수와 음수를 구분하여 양수는 1로 초기화, 음수는 -1로 초기화하여
	     우울기간의 인덱스와 우울기간 지속일수를 배열sadDay에 저장
 	 (2) sadDay[우울기간 시작인덱스값 저장]=우울기간 지속일수; 를 저장한 배열
 	  을 이용하여 2T전부터  꽃을 주는것 처리
 	 (3) 최장기간이 한개일경우와 다수일경우로 케이스분류
	 (4) 한개일경우 3T전부터 꽃주는값처리
	 (5) 다수일경우 각각의 최장기간에 3T만큼 처리하고 최댓값을 추출
	 (6) 최댓값 출력*/

        /*꽃을 주는 최댓값 계산 함수 시작*/

	/*우울한 날 추출*/
	for(i=0 ; i<day ; i++){
		if(arr[i]>0) /*우울하지 않은 날*/ 
		arr[i]=0;
		else if(arr[i]<0)
		arr[i]=-1; /*우울한 날*/ 
	}
	for(i=0 ; i<day ; i++){
		int j =1;
		if(arr[i]==-1){ /*우울한 날 탐색*/ 
			p=i;
			while(1){
				i++;
				sadDay[p]=j;/*sadDay[우울기간 시작 인덱스] = 우울한 기간*/ 
				if(p+j==day)/*배열이 끝날길이만큼 세기*/ 
				break;
				j++;
				if(arr[i]==0)/*우울기간이 끝나면 무한루프 탈출*/ 
				break;
			}
		}
	}
	int MDay,F;
	/*우울기간중 최장기간의 길이가 똑같은날이있는지 계산*/
	for(i=0 ; i<day;i++){
		if(sadDay[i]>MDay){
		MDay = sadDay[i];/*MDay는 최장기간 값*/
		MIndex = i;
		}
	}
	for(i=0;i<day;i++){
		if(MDay==sadDay[i]){
		a1 = a1 + 1;/*우울기간중 최장기간의 길이가 겹치는지 판별*/
		}
	}

	/*우울기간전 2T만큼 꽃주기 
 * 	flo[꽃주는 날짜 인덱스] = FLOWER;*/ 
	for(i=0;i<day;i++)
	{
		if(sadDay[i]!=0){
			for(a=1;a<=sadDay[i]*2;a++){
				if(i-a<0)/*배열이 끝나면 멈추기*/
				break;
				flo[i-a]=FLOWER;
			}
		}
	}

	if(a1==0)/*우울기간이 없는 경우*/
	F  =0;
	
	else if(a1==1) /*최장기간의 길이가 독보적일 경우*/
	{
		for(i=0; i<day;i++){
			if(i==MIndex){/*3T만큼 꽃할당하기*/
				for(a=1;a<=sadDay[i]*3;a++){
					if(i-a<0)
					break;
					flo[i-a]=FLOWER;
				}
			}
		}
		for(i=0;i<day;i++){
			if(flo[i]==FLOWER)
			F  = F + 1;/*총 꽃을 주는 날의 수 체크*/
		}
	}
	else/*최장기간이 겹칠 경우*/
	{

	/*꽃을 최대한으로 주기위한 함수 <-3T씩 할당해보고 각 경우의 최댓값 비교 */
		for(i=0;i<day;i++)
		{
	
			if(sadDay[i]==MDay)
				{
				for(n=0;n<day;n++){/*각 경우를 비교하기위해  배열에 0값할당*/
					sadDay2[n] =0;
					flo2[n] =flo[n];
				}
				/*우울기간 각각에  3T를 할당해보기*/
				sadDay2[i]=sadDay[i]; 
				for(a=1;a<=sadDay2[i]*3;a++){
					if(i-a<0)
					break;
					flo2[i-a] = FLOWER;
				}
				int flonum =0;
				for(b=0;b<day;b++){ 
				if(flo2[b]==FLOWER)
				flonum++;
				}	
				if(flonum>F)/*최댓값이면 F에 저장*/
				F= flonum;
				}
		}
	}
	printf("\n상범이에게 꽃을 주어야하는 날의 최댓값 : %d ",F);	
	return 0;
} 

