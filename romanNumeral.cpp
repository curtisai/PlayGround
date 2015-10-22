#include <string>
#include <iostream>
#include <stack>

using namespace std;

int getValue(char oneChar){
    switch(oneChar){
        case 'I':
        return 1;
        case 'V':
        return 5;
        case 'X':
        return 10;
        case 'L':
        return 50;
        case 'C':
        return 100;
        case 'D':
        return 500;
        case 'M':
        return 1000;
    }
}
int romanToInt(string s) {
        stack<int> myStack;
        for(int i=0;i<s.length();i++){
            myStack.push(getValue(s[i]));
        }
        int res =0;
        int currentTop = myStack.top();
        myStack.pop();
        res = currentTop;
        if(myStack.empty())return res;
        while(!myStack.empty()){
            
            if(currentTop <= myStack.top()){
                res+=myStack.top();
            }
            else{
                res-=myStack.top();
            }
            currentTop = myStack.top();
            myStack.pop();
        }
        return res;
    }


    int main(){

        cout<<romanToInt("DCXXI");
        return 0;
    }