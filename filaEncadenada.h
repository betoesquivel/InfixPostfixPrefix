template <class T>
class Node
{
	public:
		T data;
		Node<T> *next;
		Node(){ next = NULL; }
		Node(T param){ data = param; next = NULL; 
};

template <class T>
class queue
{
	private:
		Node<T> *front;
		Node<T> *back;
		int size;
	public:
		queue() { front = NULL; back = NULL; size = 0; }
		void pop();
		void push(T param);
		T front();
		int size();
		bool empty();
		~queue()
		{
			Node<T> *aux = front;
			while(aux != NULL)
			{
				front = aux->next;
				delete aux;
				aux = front;	
			}
		}
};
template <class T>
void queue<T>::pop()
{
	Nodo<T> *aux = front;
	front = front->next; 
	delete aux;
	size-=1;
}
template <class T>
void queue<T>::push(T param)
{
	Node<T> *newNode = new Node<T>(param);
	back->next = newNode; 
	back = newNode;
	size+=1;
}
template <class T>
T queue<T>::front()
{
	return front->data; 
}
template <class T>
int queue<T>::size()
{
	return size; 
}
template <class T>
bool queue<T>::empty()
{
	return (front==NULL && back==NULL); 
}

