template <class T>
class Nodo {
	public:
		T dato;
		Nodo<T> *sig, *ant;
		Nodo() {sig=NULL; ant=NULL;}
		Nodo(T info) {dato=info; sig=NULL; ant=NULL;} 
	
};

template <class T>
class stack {
	private:
		Nodo<T> *tope;
	public:
		stack(){ tope=NULL; }
		void push(T dato);
		void pop();
		bool empty();
		T top();
		~stack() {
			Nodo<T> *aux=tope;
			while(tope!=NULL){
				tope=tope->sig;
				delete aux;
				aux=tope;
			}
		}
		
};

template <class T>
bool stack<T>::empty(){
	return (tope==NULL);
}

template <class T>
T stack<T>::top(){
	if(tope!=NULL)
		return tope->dato;
}

template <class T>
void stack<T>::push(T dato){
	Nodo<T> *aux = new Nodo<T>(dato);
	if(tope==NULL){
		tope=aux;
		tope->ant=NULL;
		tope->sig=NULL;
	} else {
		tope->sig=aux;
		aux->ant=tope;
		aux->sig=NULL;
		tope=aux;
	}
}

template <class T>
void stack<T>::pop(){
	if(tope!=NULL){
		Nodo<T> *aux = tope;
		tope=tope->ant;
		delete aux;
	} 
}


