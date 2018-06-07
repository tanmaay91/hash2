#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
typedef struct rec* Rec;
struct rec {
	int index;
	int count;
	Rec next;
};

struct hash {
	Rec* arr;
	int elementcount;
	int insertioncost;
};
typedef struct hash* Hash;
int hash(char *s, int size, int base)
{
	int max = strlen(s);
	int sum = 0;
	for(int i =0; i<max; i++)
	{
		int j = s[i];
		sum+=j;
	}
	int value = (((sum)%base)%size);
	return value;
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
Hash create(int tsize) {
	Hash h = (Hash)malloc(sizeof(struct hash));
	h->elementcount=0;
	h->insertioncost=0;
	h->arr = (Rec*)malloc(sizeof(Rec)*tsize);
	return h;
}

Hash insert(Hash h,char** s,int index) {
	int count=1;
	int ind = hash(s[index],10,10);
	Rec temp = (h->arr)[ind];
	Rec record = (Rec)malloc(sizeof(struct rec));
	record->next=NULL;
	record->index=index;
	record->count=1;
	if(temp==NULL) {
		(h->arr)[ind]=record;
		h->elementcount+=1;
		return h;
	}
	while(temp->next!=NULL) {
		if(strcmp(s[index],s[temp->index])==0) {
			temp->count+=1;
			free(record);
			return h;
		}
		temp=temp->next;
		count++;
	}
	if(strcmp(s[index],s[temp->index])==0) {
		temp->count+=1;
		free(record);
		return h;
	}
	h->insertioncost+=count;
	h->elementcount+=1;
	temp->next=record;
	return h;
}
int insertAll(Hash h, char** s) {
	for(int i=0;s[i]!=NULL;i++) {
		h = insert(h,s,i);
	}
	return h->insertioncost;
}
/*void print(Hash h, int size)
{
    for(int i=0; i<size; i++)
    {
        Rec temp = h->arr[i];
        while(temp->next!=NULL)
        {
            printf(temp->index);
        }
    }
}*/
int main()
{
    FILE* fp;
    fp = fopen("kyc.txt", "r");
    char** apple = parse(fp);
    Hash lite = create(10);
    int i = insertAll(lite, apple);
    //print(lite, 10);
    printf("Hello world!\n");
    return 0;
}
