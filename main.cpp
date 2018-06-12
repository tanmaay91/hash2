#include <iostream>
#include <stdlib.h>
#include <vector>
#include <sstream>
using namespace std;

struct node
{
    string name;
    node* next;
};
typedef struct node* Node;

struct _list
{
    Node head;
    int data;
};
typedef struct _list* List;

struct table
{
    _list arr[128];
};
typedef struct table* Table;

Table create()
{
    Table t = (Table)malloc(sizeof(struct table));
    for(int i=0; i<128; i++)
    {
        t->arr[i].data = i;
        t->arr[i].head = NULL;
    }
    return t;
}
int chash(string str)
{
    int result = (int)str[0];
    int length = str.size();
    for(int i=1; i<length; i++)
    {
        if(i%2)
        {
            result = result & (int)str[i];
        }
        else
        {
            result = result | (int)str[i];
        }
    }

    if(result<0)
    {
        result+=128;
        return result;
    }
    else
        return result;
}
Table insert_Node(Table t, string data)
{
    Node n = (Node)malloc(sizeof(struct node));
    n->name = data;
    n->next = NULL;
    int value = chash(data);
    if(t->arr[value].head==NULL)
    {
        t->arr[value].head = n;
        return t;
    }
    else
    {
        Node temp = t->arr[value].head;
        while(temp->next!=NULL)
        {
            temp = temp->next;
        }
        temp->next = n;
        return t;
    }
}
void printList(Node n, int index)
{
    Node temp = n;
    int i = index;
    if(n==NULL)
    {
        return;
    }
    else if(n->next==NULL)
    {
        cout<<i;
        return;
    }
    else
    {
        while(temp->next!=NULL)
        {
            cout<<i;
            temp = temp->next;
        }
        cout<<temp->name;
        return;
    }
}
void print(Table t)
{
    for(int i=0; i<128; i++)
    {
        printList(t->arr[i].head, i);
    }
}
int main()
{
    Table ct = create();
    //string y = "abcd";
    //ct = insert_Node(ct, y);
    //print(ct);
    //string z = "dcba";
    //ct = insert_Node(ct, z);
    //print(ct);
    int x = chash("abcd");
    cout << x << endl;
    cout<<"enter a sentence"<<endl;
    string a;
    getline(cin, a);
    vector<string> v;
    istringstream buf(a);
    for(string word; buf >> word; )
        v.push_back(word);
    int b = v.size();
    for(int m=0; m<b; m++)
    {
        ct = insert_Node(ct, v[m]);
    }
    cout<<"word wise hash code is:";
    print(ct);
    cout<<endl;
    ct = insert_Node(ct, a);

    return 0;
}
