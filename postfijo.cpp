#include <iostream>
#include <fstream>
#include <stack>


using namespace std; 

const char arithmeticOperators[5] = {'+','-','*','/','%'};
const char relationalOperators[3] = {'<','>','='};
const char logicalOperators[2] = {'&','|'};

template <class T>
bool find_in_array(T arr[], int length, T x)
{
	int i = 0;
	while(i<length)
	{
		if(arr[i]==x)
			return true;
		i++;
	}
	return false; 
}

bool is_number(char x)
{
	return (x=='0'||x=='1'||x=='2'||x=='3'||x=='4'||
		x=='5'||x=='6'||x=='7'||x=='8'||x=='9');
}

stack<char> infix_to_postfix(string exp, int &x)
{
	stack<char> postfix;
	int size = exp.length();
	for(int i = 0; i<size; i++)
	{
		if(is_number(exp[i]))
		{
			postfix.push(exp[i]);				
			exp.erase(i,1);
			size--;
		}
	}
	for(int i = 0; i<exp.length(); i++)
	{
		cout<<exp[i]<<endl;
		postfix.push(exp[i]);
	}
	return postfix; 
}

int main()
{
	string inputFileName;
	string expression = "2+4-8*3";
	int x; 
	stack<char> my_postfix;
	my_postfix = infix_to_postfix(expression, x);
	x = my_postfix.size();
	cout<<x<<" Este es el tamanio del stack regresado."<<endl;
	for(int i = 0; i<x; i++){
		cout<<my_postfix.top();
		my_postfix.pop();
	}
}
