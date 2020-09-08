//알파벳 개수
#include <iostream>
#include <stack>
#include <string>
#include <cstring>
#define MAX 100
using namespace std;
int main()
{
	int i,j=0;
	char word[MAX];
	char buf;
	int count[28] = {0,};
	memset(word,0,sizeof(word));
	stack<char> alpha;
	cout << "단어를 입력하시오";
	cin >> word;
	for(i = 122 ; i >= 97 ; i--)
	{
		buf = (char)(i);
		alpha.push(buf);
	}
	i=0;
	while(i<26)
	{
		j=0;
		buf=alpha.top();
		alpha.pop();
		while(word[j]!=0)
		{
			if(buf==word[j]) count[j]++;
			j++;
		}	
		cout << count[i] << " ";
		i++;
	}
	return 0;
}
