#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
int hash(int size, int base, char *s)
{
	int max = strlen(s);
	int sum = 0;
	for(int i =0; i<max; i++)
	{
		int j = s[i];
		sum+=j;
	}
	int value = (((sum)%base)%size);
}

char** parse(FILE *fp)
{
	char** book = (char**)malloc(sizeof(char*)*50);
	int max = 50;
	int i = 0, j = 0;
	char *a = (char*)malloc(sizeof(char)*30);
	while(fscanf(fp, "%s",a)!=-1)
	{
		int size = strlen(a);
		int flag = 0;
		for(i=0; i<size; i++)
		{
			if(!isalpha(a[i]))
			{
				flag = 1;
				break;
			}
		}
		if(i>=max)
		{
			max*=2;
			char** book = (char**)realloc(book,(sizeof(char*)*max));}
		if(!flag)
		{
			book[j] = a;
			j++;
		}
	}
	return book;
}

int main()
{
    FILE* fp;
    fp = fopen("kyc.txt", "r");
    char** apple = parse(fp);
    printf("Hello world!\n");
    return 0;
}
