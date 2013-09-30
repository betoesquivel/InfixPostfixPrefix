bool debug_pila = true;

template <class T>
class stack
{
	private:
		Node<T> *stack_top;
		int stack_size;
	public:
		stack() { stack_top = NULL; stack_size = 0; }
		void push(T param);
		void pop();
		T top() { return stack_top->data; }
		int size(){ return stack_size; }
		bool empty(){ return (stack_top==NULL); }
		~stack() 
		{ 
			Node<T> *eraser;
			while(stack_size>0)
			{
				eraser = stack_top;
				stack_top = stack_top->next;

				delete eraser;

				stack_size--;
			}
			stack_top = NULL;
		}
};
template <class T>
void stack<T>::push(T param)
{
	Node<T> *newNode = new Node<T>(param);

	if(stack_size==0)
	{
		stack_top = newNode;
		stack_top->previous = newNode;
		stack_top->next = newNode;
		if(debug_pila) cout<<"Size is 0. New node pointing to itself."<<endl;		
	}else
	{
		Node<T> *aux = stack_top;	
		stack_top = newNode;
		stack_top->previous = aux;
		
		stack_top->next = aux->next;
		(aux->next)->previous = stack_top;
		
		aux->next = stack_top;
	}
	stack_size+=1;
}
template <class T>
void stack<T>::pop()
{
	if(stack_size==0)
	{
		if(debug_pila) cout<<"Stack size is 0. Popping nothing."<<endl;		
	}else
	{
		Node<T> *eraser = stack_top;
		stack_top = stack_top->next;	
		delete eraser;
	}
		stack_size-=1;
		if(stack_size == 0) stack_top = NULL;
}

