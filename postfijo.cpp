#include <iostream>
#include <fstream>
#include <stack>
#include <queue>


using namespace std; 

bool debug = true;

const char arithmeticOperators[5] = {'+','-','*','/','%'};
const char relationalOperators[3] = {'<','>','='};
const char logicalOperators[2] = {'&','|'};

int get_precedence(char op)
{
	char operators[10] = {'+','-','*','/','%','<','>','=','&','|'};
	int precedence[10] = {3,3,4,4,4,2,2,2,1,1};
	for(int i = 0; i<10; i++)
	{
		if(op==operators[i])
		{
			return precedence[i];
		}
	}
	if(op == ')' || op == '(')
		return -1;
	return -1;
}

bool is_number(char x)
{
	return (x=='0'||x=='1'||x=='2'||x=='3'||x=='4'||
		x=='5'||x=='6'||x=='7'||x=='8'||x=='9');
}

queue<char> infix_to_postfix(string exp)
{
	stack<char> postfixStack;
	queue<char> postfixQueue;
	int size = exp.length(), operatorPrecedence = 0, nextOperatorInStackPrecedence = 0, opIndex;
	char c;
	for(int i = 0; i<size; i++)
	{
		c = exp.c_str()[i];	
		if(debug)
			cout<<"DEBUG::Evaluating char... "<<c<<endl;
		switch(c)
		{
			case '(': postfixStack.push(c);
				if(debug)
					cout<<"DEBUG:: Found (, pushed to stack... "<<postfixStack.top()<<endl;
				break;
			case ')': 
				  while(postfixStack.size()>0 && postfixStack.top()!='(')
				  {
					if(debug)
						cout<<"DEBUG:: Concatenating: "<<postfixStack.top()<<endl;
					postfixQueue.push(postfixStack.top());
					postfixStack.pop();
				  }
				  postfixStack.pop();
				 if(debug)
				 {
				 	cout<<"DEBUG:: Found (, popped to final string... "<<endl;
				 }
				break;
			default:
				if(is_number(c))
				{
					if(debug) cout<<"DEBUG:: found an operand. Concatenating it."<<endl;
					postfixQueue.push(c);
					if(debug) cout<<"DEBUG:: Concatenated the operand."<<endl;
				}
				else
				{
					if(postfixStack.size()==0)
						postfixStack.push(c);
					else
					{
						operatorPrecedence = get_precedence(c);
						nextOperatorInStackPrecedence = get_precedence(postfixStack.top());
						while(postfixStack.size()>0 && c!='(' && operatorPrecedence<=nextOperatorInStackPrecedence)
						{
							postfixQueue.push(postfixStack.top());
							postfixStack.pop();
						}
						postfixStack.push(c);
					}
				}
				break;
				
		}//End of switch block...
	}//End of for loop
	while(postfixStack.size()>0)
	{
		postfixQueue.push(postfixStack.top());
		postfixStack.pop();
	}
	if(debug) cout<<"DEBUG::Postfix conversion finished, "<<endl;
	return postfixQueue; 
}

queue<char> infix_to_prefix(string exp)
{
	stack<char> prefixStack;
	queue<char> prefixQueue;
	
	return prefixQueue;
}	

int main()
{
	string inputFileName;
	//string expression = "1/(4+2)-3";
	//string expression = "4+5*6";
	//string expression = "2*3-4/5";
	string expression = "(5-6)*7";
	queue<char> my_postfix, my_prefix;
	my_postfix = infix_to_postfix(expression);
	cout<<"Esta es la expresión convertida a postfix: "<<endl;
	while(my_postfix.size()>0)
	{
		cout<<my_postfix.front()<<' ';
		my_postfix.pop();
	}
	cout<<endl;
}
