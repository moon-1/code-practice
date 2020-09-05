//알파벳 개수
#include <iostream>
#include <stack>
#include <string>
#define MAX 100
using namespace std;
int main()
{
	int i;
	char word[MAX];
	char buf;
	int count[23] = {0,};
	stack<char> alpha;
	cout << "단어를 입력하시오";
	cin >> word;
	for(i = 97 ; i <= 122 ; i++)
	{
		buf = (char)i;
		alpha.push(buf);
	}
	i=0;
	while(!alpha.empty())
	{
		buf=alpha.top();
		alpha.pop();
		int j =0;
		while(word[j]!='\n')
		{
			if(buf==word[j]) count[j]++;
			j++;
		}
		cout << count[i] + " ";
		i++;
	}
	return 0;
}
