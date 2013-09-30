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

