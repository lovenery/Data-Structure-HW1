#include<iostream>
#include<sstream>
#include<string.h>
#include<cstdlib>
#include "linkliststack.h"
using namespace std;

int data[26] = {}; //store a~z number
int order(char op); // using in InfixToPostfix for ordering
string InfixToPostfix(string infix); // infix to postfix format
int PostfixComput(string postfix); // return the ans
bool checkiferror(string infix); // return the error ans

int main()
{
    //calculate times
    int cal_times=0;
    cin>>cal_times;
    cin.get();

    //input a~z number
    for(int i=0; i<26; i++)
    {
        cin>>data[i];
    }
    cin.get();

    //output the ans
    int ans[99]= {};
    for(int i=0; i<cal_times; i++)
    {
        string input;
        getline(cin, input);
        string postfix = InfixToPostfix(input);
        if(checkiferror(input))
        {
            ans[i]=NULL;
        }
        else
        {
            ans[i]=PostfixComput(postfix);
        }
    }
    cout<<"\nOutput:"<<endl;
    for(int i=0; i<cal_times; i++)
    {
        if(ans[i]==NULL)
        {
            cout<<"error"<<endl;
        }
        else
        {
            cout<<ans[i]<<endl;
        }
    }
    system("pause");
    return 0;
}

bool checkiferror(string infix)
{
    char infix_char[99];
    strcpy(infix_char, infix.c_str()); //copy string to char array
    int left=0,right=0;
    bool twoletter=false;
    for(int i=0 ; infix_char[i]!=NULL; i++)
    {
        switch(infix_char[i])
        {
        case '*':
        case '/':
        case '+':
        case '-':
            break;

        case '(':
            left++;
            break;

        case ')':
            right++;
            break;
        default:
            if((int)infix_char[i]>64 && (int)infix_char[i+1]>64)
            {
                twoletter=true;
            }
            break;
        }
    }
    if(left!=right || twoletter)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int order(char op)
{
    switch(op)
    {
    case '(' :
        return -1;
        break;
    case '+' :
    case '-' :
        return 0;
        break;
    default :// * / %
        return 1;
        break;
    }
}

string InfixToPostfix(string infix)
{
    ostringstream postfix;
    LinkedListStack<char> Stack;
    char infix_char[99];
    strcpy(infix_char, infix.c_str()); //copy string to char array
    for(int i=0 ; infix_char[i]!=NULL; i++)
    {
        switch(infix_char[i])
        {
        case '*':
        case '/':
        case '+':
        case '-':
            //壓不住所以彈出,再放入 or 直接放入
            while (Stack.count!=0 && Stack.top()!= '(' &&order(Stack.top()) > order(infix_char[i]))
            {
                postfix<<Stack.top();
                Stack.pop();
            }
            Stack.push(infix_char[i]);
            break;

        case '(': //左括號直接push到stack
            Stack.push(infix_char[i]);
            break;

        case ')': //右括號一直pop到左括號為止
            while (Stack.count!=0 &&Stack.top() != '(')
            {
                postfix<<Stack.pop();
            }
            Stack.pop();
            break;

        default: //數字直接放到postfix
            postfix<<infix_char[i];
            break;
        }
    }

    //剩下的全pop出來
    while (Stack.count!=0 )
    {
        if (Stack.top() == '(')
        {
            Stack.pop();
            continue;
        }
        postfix<<Stack.pop();
    }
    return postfix.str();
}

int PostfixComput(string postfix)
{
    int stack[1000]= {};
    int top = 0;
    char postfix_char[99];
    strcpy(postfix_char, postfix.c_str()); //copy string to char array
    for(int i=0 ; postfix_char[i]!=NULL; i++)
    {
        switch(postfix_char[i])
        {
        case '+' :
            stack[top-2] = stack[top-2] + stack[top-1];
            top -= 1;
            break;
        case '-' :
            stack[top-2] = stack[top-2] - stack[top-1];
            top -= 1;
            break;
        case '*' :
            stack[top-2] = stack[top-2] * stack[top-1];
            top -= 1;
            break;
        case '/' :
            stack[top-2] = stack[top-2] / stack[top-1];
            top -= 1;
            break;
        case '%' :
            stack[top-2] = stack[top-2] % stack[top-1];
            top -= 1;
            break;
        default :
            int index;
            if((int)postfix_char[i]>96) //小寫
            {
                index = (int)postfix_char[i]-97;
            }
            else //大寫
            {
                index = (int)postfix_char[i]-65;
            }
            stack[top] = data[index];
            top++;
            break;
        }
    }
    return stack[0];
}
