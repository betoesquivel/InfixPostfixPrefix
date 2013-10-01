#include <iostream>

using namespace std;

template <class T>
class NodoQ {
	public:
		T dato;
		NodoQ<T> *sig;
		NodoQ() {dato=NULL; sig=NULL;}
		NodoQ(T info) {dato=info; sig=NULL;} 
	
};

template <class T>
class queue {
	private:
		NodoQ<T> *final;
	public:
		queue() {final=NULL;}
		void push(T dato);
		void pop();
		T front();
		bool empty();
		~queue() {
			
			while(!empty()){
				pop();
			}
			
		}
			
};

template <class T>
void queue<T>::push(T dato){
	NodoQ<T> *aux = new NodoQ<T>(dato);
	if(final==NULL) {
		final=aux;
		final->sig = final;
	} else {
		aux->sig=final->sig;
		final->sig=aux;
		final=aux;
	}
	
}

template <class T>
void queue<T>::pop(){
	if(final!=NULL){
		NodoQ<T> *aux=final->sig;
		if(final!=aux){
			final->sig=aux->sig;
			delete aux;
		} else {
			delete aux;
			final=NULL;
		}
	}
}

template <class T>
T queue<T>::front(){
		NodoQ<T> *aux=final->sig;
		return aux->dato;
	

}

template <class T>
bool queue<T>::empty(){
	return (final==NULL);
}

	
	
