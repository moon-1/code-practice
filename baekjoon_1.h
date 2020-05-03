/*배열리스트 헤더파일 문해원2019.04.04*/
#ifndef __ARRAY_LIST_H__
#define __ARRAY_LIST_H__

#define TRUE	1
#define FALSE	0

/*배열리스트  정의 */
typedef int LData;

typedef struct __ArrayList
{
	LData *array;
	int curPosition;
	int numOfData;
	int n;
} ArrayList;

/*배열리스트와 관련된 연산*/
typedef ArrayList List;

void ListInit(List * plist);
void LInsert(List * plist, LData data);

int LFirst(List * plist, LData * pdata);
int LNext(List * plist, LData * pdata);

int LCount(List * plist);

#endif
