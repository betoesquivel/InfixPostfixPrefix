template <class T>
class queue
{
	private:
		Node<T> *queue_front;
		Node<T> *queue_back;
		int queue_size;
	public:
		queue() { queue_front = NULL; queue_back = NULL; queue_size = 0; }
		void pop();
		void push(T param);
		T front();
		int size();
		bool empty();
		~queue()
		{
			Node<T> *aux = queue_front;
			while(aux != NULL)
			{
				queue_front = aux->next;
				delete aux;
				aux = queue_front;	
			}
		}
};
template <class T>
void queue<T>::pop()
{
	Node<T> *aux = queue_front;
	queue_front = queue_front->next; 
	delete aux;
	queue_size-=1;
}
template <class T>
void queue<T>::push(T param)
{
	Node<T> *newNode = new Node<T>(param);
	if(queue_size==0)
	{
		queue_front = newNode;
		queue_back = newNode;
	}else
	{
		queue_back->next = newNode; 
		queue_back = newNode;
	}
	queue_size+=1;
}
template <class T>
T queue<T>::front()
{
	return queue_front->data; 
}
template <class T>
int queue<T>::size()
{
	return queue_size; 
}
template <class T>
bool queue<T>::empty()
{
	return (queue_front==NULL && queue_back==NULL); 
}

