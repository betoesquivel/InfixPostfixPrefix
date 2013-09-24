#include <iostream>
#include <fstream>
#include <stack>


using namespace std; 

bool debug = true;

const char arithmeticOperators[5] = {'+','-','*','/','%'};
const char relationalOperators[3] = {'<','>','='};
const char logicalOperators[2] = {'&','|'};

char operators[10] = {'+','-','*','/','%','<','>','=','&','|'};
int precedence[10] = {'3','3','4','4','4','2','2','2','1','1'};

template <class T>
int find_in_array(T arr[], int length, T x)
{
	//Returns the position at which it found the element.
	int i = 0;
	while(i<length)
	{
		if(arr[i]==x)
			return i;
		i++;
	}
	i = -1;
	return i; 
}

bool is_number(char x)
{
	return (x=='0'||x=='1'||x=='2'||x=='3'||x=='4'||
		x=='5'||x=='6'||x=='7'||x=='8'||x=='9');
}

string infix_to_postfix(string exp)
{
	stack<char> postfixStack;
	string postfixString = "";
	int size = exp.length(), prec1 = 0, prec2 = 0;
	char c;
	for(int i = 0; i<size; i++)
	{
		c = exp.c_str()[i];	
		if(debug)
			cout<<"DEBUG::Starting with char... "<<c<<endl;
		switch(c)
		{
			case '(': postfixStack.push(c);
				if(debug)
					cout<<"DEBUG:: Found (, pushed to stack... "<<postfixStack.top()<<endl;
				break;
			case ')': 
				  while(postfixStack.top()!='(')
				  {
					postfixString += postfixStack.top();
					postfixStack.pop();
				  }
				  postfixStack.pop();
				if(debug)
				{
					cout<<"DEBUG:: Found (, popped to final string... "<<postfixStack.top()<<endl;
					cout<<postfixString<<endl;
				}
				break;
			default:
				//The character read is an operand or an operator
				if(is_number(c))
				{
					if(debug) cout<<"DEBUG:: found an operand. Concatenating it."<<endl;
					//Concatenate to the return string.
					postfixString+=c;
					if(debug) cout<<"DEBUG:: Concatenated the operand."<<endl;
				}
				else
				{
					//the character read is an operator
					
					if(debug) cout<<"DEBUG:: found a operator. Checking size..."<<endl;
					if(postfixStack.size()==0)
					{
						if(debug) cout<<"DEBUG:: found a operator. Size is 0, pushing..."<<endl;
						postfixStack.push(c);
					}
					else
					{
						prec1 = precedence[find_in_array(operators, 10, c)];
						prec2 = precedence[find_in_array(operators, 10, postfixStack.top())];
						if(debug) cout<<"DEBUG:: Precedence of operator: "<<prec1<<' '<<prec2<<endl;
						while(postfixStack.size()>0 && prec1<=prec2)
						{
							postfixString+=postfixStack.top();
							postfixStack.pop();
							prec2 = (postfixStack.size()>0) ? precedence[find_in_array(operators, 10, postfixStack.top())]:-1;
						}	
						postfixStack.push(c);
					}

				}
				break;
				
		}//End of switch block...
	}//End of for loop
	while(postfixStack.size()>0)
	{
		postfixString += postfixStack.top();
		postfixStack.pop();
	}
	if(debug) cout<<"DEBUG::Postfix conversion finished, "<<postfixString<<endl;
	return postfixString; 
}

string infix_to_prefix(string exp)
{
	string prefixString = "";
	stack<char> prefixStack;
	int prec1 = 0, prec2 = 0;
	char c;
	for(int i = exp.length()-1; i>0; i--)
	{
		c = exp[i];	

		if(debug)
			cout<<"DEBUG::Starting with char... "<<c<<endl;
		switch(c)
		{
			case ')': prefixStack.push(c);
				if(debug)
					cout<<"DEBUG:: Found (, pushed to stack... "<<prefixStack.top()<<endl;
				break;
			case '(': 
				  while(prefixStack.top()!=')')
				  {
					prefixString += prefixStack.top();
					prefixStack.pop();
				  }
				  prefixStack.pop();
				if(debug)
				{
					cout<<"DEBUG:: Found (, popped to final string... "<<prefixStack.top()<<endl;
					cout<<prefixString<<endl;
				}
				break;
			default:
				//The character read is an operand or an operator
				if(is_number(c))
				{
					if(debug) cout<<"DEBUG:: found an operand. Concatenating it."<<endl;
					//Concatenate to the return string.
					prefixString+=c;
					if(debug) cout<<"DEBUG:: Concatenated the operand."<<endl;
				}
				else
				{
					//the character read is an operator
					
					if(debug) cout<<"DEBUG:: found a operator. Checking size..."<<endl;
					if(prefixStack.size()==0)
					{
						if(debug) cout<<"DEBUG:: found a operator. Size is 0, pushing..."<<endl;
						prefixStack.push(c);
					}
					else
					{
						prec1 = precedence[find_in_array(operators, 10, c)];
						prec2 = precedence[find_in_array(operators, 10, prefixStack.top())];
						if(debug) cout<<"DEBUG:: Precedence of operator: "<<prec1<<' '<<prec2<<endl;
						while(prefixStack.size()>0 && prec1<=prec2)
						{
							prefixString+=prefixStack.top();
							prefixStack.pop();
							prec2 = (prefixStack.size()>0) ? precedence[find_in_array(operators, 10, prefixStack.top())]:-1;
						}	
						prefixStack.push(c);
					}

				}
				break;
				
		}//End of switch block...
	}//End of for loop
	while(prefixStack.size()>0)
	{
		prefixString += prefixStack.top();
		prefixStack.pop();
	}
	if(debug) cout<<"DEBUG::Postfix conversion finished, "<<prefixString<<endl;
	
	return prefixString;
}	

int main()
{
	string inputFileName;
	//string expression = "1/(4+2)-3";
	//string expression = "4+5*6";
	string expression = "(5-6)*7";
	string my_postfix, my_prefix;
	my_postfix = infix_to_postfix(expression);
	my_prefix = infix_to_prefix(expression);
	cout<<"Esta es la expresión convertida a postfix: "<<my_postfix<<endl;
	cout<<"Esta es la expresión convertida a prefix: "<<my_prefix<<endl;
}
