//
//  Queue.h
//  Tarea4
//
//  Created by Gustavo Ferrufino on 9/29/13.
//  Copyright (c) 2013 Gustavo Ferrufino. All rights reserved.
//

#ifndef Tarea4_Queue_h
#define Tarea4_Queue_h

#include <iostream>
using namespace std;
#include "FerrufinoNode.h"

template <class T>
class queue{
private:
	Node<T> *frente, *final;
    int queueSize;
    
    
public:
	queue(){ frente= NULL; final = NULL; queueSize=0;};
	bool push(T d);
	bool pop();
	T front();
    int size(){return queueSize;};
	bool empty(){return (final == NULL);};
	~queue(){
        
        Node<T> *aux=frente;
        
        while(queueSize>0){
        
            frente=aux->next;
        
            delete aux;
            
            aux=frente;
            queueSize-=1;
        
        }
        
    }

    
};


template <class T>
bool queue<T>::push(T d){
    
	Node<T> *newNode= new Node<T>(d);
    Node<T> *aux;
	if(queueSize == 0){
		
		frente = newNode;
        final = newNode;
        queueSize+=1;
        return true;
	}
	else{
        
		
			
            
            final->next=newNode;
            //aux=final->next;
            newNode->prev=final;
            final = newNode;
            
            //aux=NULL;
            
            queueSize+=1;
        
            return true;
       }
}

template <class T>
bool queue<T>::pop(){
	Node<T> *aux = frente;
    if (queueSize == 0)
    {
        //frente=NULL;
        //final=NULL;
        return false;
    }
	else
    {
		if(aux->next==NULL)
			frente=final=NULL;
        else
        {
        frente=aux->next;
        frente->prev=NULL;
		
        }
        
        delete aux;
        queueSize-=1;
        return true;
	}
}



template <class T>
T queue<T>::front(){
    
	return frente->info;
}




#endif
