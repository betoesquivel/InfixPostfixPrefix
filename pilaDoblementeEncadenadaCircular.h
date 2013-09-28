template <class T>
class Node
{
	public:
		T data;
		Node<T> *next;
		Node<T> *previous;
		Node() { next=NULL; previous=NULL; }
		Node(T param) { data = param; next=NULL; previous=NULL; }
};
template <class T>
class stack
{
	private:
		Node<T> *stack_top;
		int stack_size;
	public:
		stack() { stack_top = NULL; }
		T top() { return stack_top->data; }
		void push(T param);
		void pop();
		int size(){ return stack_size; }
		bool empty();
};

void stack<T>::push(T param)
{
	Node<T> *temp = new Node<T>(param);
	Node<T> *aux = stack_top;	

	stack_top = temp;
	stack_top->prev = aux;

	stack_top->next = aux->next;
	(aux->next)->prev = stack_top;

	aux->next = stack_top;
}
void stack<T>::pop()
{
}

