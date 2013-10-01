#include <iostream>
#include <fstream>
#include <stack>
#include <queue>
#include <cstdlib>


using namespace std; 
//My implementation
//#include "Node.h"
//#include "filaEncadenada.h"
//#include "pilaDoblementeEncadenadaCircular.h"
//My friend Ferrufino's implementation
//#include "FerrufinoQueue.h"
//#include "FerrufinoStack.h"
//My friend Hugo's implementation
//#include "HugoQueue.h"
//#include "HugoStack.h"

bool debug = false;
queue<char> postfixQueue;
queue<char> prefixQueue;
queue<char> recycleBin;

void clear_recycleBin()
{
	while(!recycleBin.empty())
	{
		recycleBin.pop();
	}
}
void recover_postfixQueue()
{
	while(!recycleBin.empty())
	{
		postfixQueue.push(recycleBin.front());
		recycleBin.pop();
	}
}
void recover_prefixQueue()
{
	while(!recycleBin.empty())
	{
		prefixQueue.push(recycleBin.front());
		recycleBin.pop();
	}
}

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

void infix_to_postfix(string exp)
{
	stack<char> postfixStack;
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
				  while(!postfixStack.empty() && postfixStack.top()!='(')
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
					if(!postfixStack.empty())
						postfixStack.push(c);
					else
					{
						if(debug) cout<<"DEBUG:: Found operator "<<c<<endl;
						operatorPrecedence = get_precedence(c);
						if(debug) cout<<"DEBUG:: Checked precedence of operator "<<c<<endl;
						if(!postfixStack.empty())
							nextOperatorInStackPrecedence = get_precedence(postfixStack.top());
						while(!postfixStack.empty() && c!='(' && operatorPrecedence<=nextOperatorInStackPrecedence)
						{
							postfixQueue.push(postfixStack.top());
							postfixStack.pop();
							nextOperatorInStackPrecedence = (!postfixStack.empty()) ? get_precedence(postfixStack.top()):-1;
							if(debug) cout<<"DEBUG:: Precedence of operator is "<<nextOperatorInStackPrecedence<<endl;
						}
						postfixStack.push(c);
					}
				}
				break;
				
		}//End of switch block...
	}//End of for loop
	while(!postfixStack.empty())
	{
		postfixQueue.push(postfixStack.top());
		postfixStack.pop();
	}
	if(debug) cout<<"DEBUG::Postfix conversion finished, "<<endl;
}

void infix_to_prefix(string exp)
{
	stack<char> prefixOperatorStack;
	stack<char> prefixPreStack;
	int size = exp.length(), operatorPrecedence = 0, nextOperatorInStackPrecedence = 0, opIndex;
	char c;
	for(int i = (size-1); i>=0; i--)
	{
		c = exp.c_str()[i];	
		if(debug) cout<<"DEBUG::Evaluating char... "<<c<<endl;
		switch(c)
		{
			case ')': prefixOperatorStack.push(c);
				if(debug)
					cout<<"DEBUG:: Found (, pushed to stack... "<<prefixOperatorStack.top()<<endl;
				break;
			case '(': 
				  while(!prefixOperatorStack.empty() && prefixOperatorStack.top()!=')')
				  {
					if(debug) cout<<"DEBUG:: Concatenating: "<<prefixOperatorStack.top()<<endl;
					prefixPreStack.push(prefixOperatorStack.top());
					prefixOperatorStack.pop();
				  }
				  if(debug) cout<<"DEBUG:: Popping ), right?: "<<prefixOperatorStack.top()<<endl;
				  prefixOperatorStack.pop();
				 if(debug)
				 {
				 	cout<<"DEBUG:: Found (, popped to final string... "<<endl;
				 }
				break;
			default:
				if(is_number(c))
				{
					if(debug) cout<<"DEBUG:: found an operand. Concatenating it."<<endl;
					prefixPreStack.push(c);
					if(debug) cout<<"DEBUG:: Concatenated the operand."<<endl;
				}
				else
				{
					if(debug) cout<<"DEBUG:: found an operator. Checking size."<<endl;
					if(prefixOperatorStack.empty())
					{
						prefixOperatorStack.push(c);
						if(debug) cout<<"DEBUG:: Size is 0, pushing "<<c<<" to operator stack."<<endl;
					}
					else
					{
						operatorPrecedence = get_precedence(c);
						nextOperatorInStackPrecedence = get_precedence(prefixOperatorStack.top());
						if(debug) cout<<"DEBUG:: Stack is not empty, checking precedence of operators."<<endl;
						while(!prefixOperatorStack.empty()  && operatorPrecedence<=nextOperatorInStackPrecedence)
						{
							prefixPreStack.push(prefixOperatorStack.top());
							if(debug) cout<<"DEBUG:: Pushing operator in stack "<<prefixOperatorStack.top()<<" to prefix prestack."<<endl;
							prefixOperatorStack.pop();
							nextOperatorInStackPrecedence = (!prefixOperatorStack.empty()) ? get_precedence(prefixOperatorStack.top()):-1;
						}
						prefixOperatorStack.push(c);
					}
				}
				break;
				
		}//End of switch block...
		if(debug) cout<<"DEBUG:: End of switch block for "<<c<<endl;
	}//End of for loop
	if(debug) cout<<"DEBUG:: End of for loop."<<endl;
	while(!prefixOperatorStack.empty())
	{
		prefixPreStack.push(prefixOperatorStack.top());
		if(debug) cout<<"DEBUG:: Adding rest of operators in stack to prestack "<<prefixOperatorStack.top()<<"."<<endl;
		prefixOperatorStack.pop();
	}
	if(debug) cout<<"DEBUG:: End of first while loop."<<endl;
	while(!prefixPreStack.empty())
	{
		prefixQueue.push(prefixPreStack.top());
		if(debug) cout<<"DEBUG:: Passing "<<prefixPreStack.top()<<" in prestack, to the queue."<<endl;
		prefixPreStack.pop();
	}
	if(debug) cout<<"DEBUG::Prefix conversion finished, "<<endl;
}	

bool evaluate_postfix(int &solution)
{
	bool is_boolean = false;
	stack<int> operandStack;
	string temp = "";
	char c;
	int x, y;
	while(!postfixQueue.empty())
	{
		temp = "";
		temp+=postfixQueue.front();
		recycleBin.push(postfixQueue.front());
		postfixQueue.pop();
		c = temp.c_str()[0];
		switch(c)
		{
			case '+':
				x = operandStack.top(); operandStack.pop();
				y = operandStack.top(); operandStack.pop();
				operandStack.push(y+x);
				break;
			case '-':
				x = operandStack.top(); operandStack.pop();
				y = operandStack.top(); operandStack.pop();
				operandStack.push(y-x);
				break;
			case '*':
				x = operandStack.top(); operandStack.pop();
				y = operandStack.top(); operandStack.pop();
				operandStack.push(y*x);
				break;
			case '/':
				x = operandStack.top(); operandStack.pop();
				y = operandStack.top(); operandStack.pop();
				operandStack.push(y/x);
				break;
			case '%':
				x = operandStack.top(); operandStack.pop();
				y = operandStack.top(); operandStack.pop();
				operandStack.push(y%x);
				break;
			case '<':
				x = operandStack.top(); operandStack.pop();
				y = operandStack.top(); operandStack.pop();
				operandStack.push(y<x);
				is_boolean=true;
				break;
			case '>':
				x = operandStack.top(); operandStack.pop();
				y = operandStack.top(); operandStack.pop();
				operandStack.push(y>x);
				is_boolean=true;
				break;
			case '=':
				x = operandStack.top(); operandStack.pop();
				y = operandStack.top(); operandStack.pop();
				operandStack.push(y==x);
				is_boolean=true;
				break;
			case '&':
				x = operandStack.top(); operandStack.pop();
				y = operandStack.top(); operandStack.pop();
				operandStack.push(y&&x);
				is_boolean=true;
				break;
			case '|':
				x = operandStack.top(); operandStack.pop();
				y = operandStack.top(); operandStack.pop();
				operandStack.push(y||x);
				is_boolean=true;
				break;
			default:
				x = atoi(temp.c_str());
				if (debug) cout<<"DEBUG::This is the variable to push: "<<x<<endl;
				operandStack.push(x);	
				break;
		}
	}
	solution = operandStack.top();	
	if (debug) cout<<"DEBUG::This is the value of is_boolean: "<<is_boolean<<endl;
	return is_boolean;
}//End of evaluate_postfix

int main()
{
	int answer; 
	bool is_boolean;
	string inputFileName, expression;

	cout<<"Enter the name of the file where expressions are stored: (with .txt)"<<endl;
	cin>>inputFileName;
	cin.ignore();

	ifstream inputFile;
	ofstream outputFile;
	outputFile.open("RESULTADO.TXT");
	inputFile.open(inputFileName.c_str());
	while(!inputFile.eof())
	{
		getline(inputFile,expression);
		if(expression.c_str()[0]!=NULL)
		{
			outputFile<<"Infijo Original: "<<expression<<endl;

			infix_to_postfix(expression);
			infix_to_prefix(expression);

			is_boolean = evaluate_postfix(answer);
			recover_postfixQueue();

			outputFile<<"Postfijo: ";	
			while(!postfixQueue.empty())
			{
				outputFile<<postfixQueue.front();
				recycleBin.push(postfixQueue.front());
				postfixQueue.pop();
			}
			outputFile<<endl;

			outputFile<<"Prefijo: ";
			while(!prefixQueue.empty())
			{
				outputFile<<prefixQueue.front();
				recycleBin.push(prefixQueue.front());
				prefixQueue.pop();
			}
			outputFile<<endl;
			outputFile<<"Resultado: ";

			if(is_boolean)
			{
				string boolOutput = (answer==1)? "TRUE":"FALSE";
				outputFile<<boolOutput;
			}else
			{
				outputFile<< answer;

			}
			outputFile<<endl;
			outputFile<<endl;
		}else
		{
			if (debug) cout<<"DEBUG::The file had a blank line."<<endl;
		}
		clear_recycleBin();
	}
	inputFile.close();
	outputFile.close();
}
