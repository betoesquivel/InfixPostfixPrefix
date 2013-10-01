//
//  Stack.h
//  Tarea4
//
//  Created by Gustavo Ferrufino on 9/29/13.
//  Copyright (c) 2013 Gustavo Ferrufino. All rights reserved.
//
using namespace std;
#include <iostream>

//#include "FerrufinoNode.h"


bool DEBUGSTACK = false;

template <class T>
class stack
{
private:
    Node<T> *bottom;
    int stackSize;

public:
    stack() { bottom = NULL; stackSize = 0; }
    bool pop();
    void push(T var);
    T top() { return (bottom->next)->info; }
    int size(){ return stackSize; }
    bool empty(){ return (bottom == NULL); }
    ~stack()
    {
        Node<T> *eraser;
        while(stackSize>0)
        {
            eraser = bottom->next;
            bottom = (bottom->next)->next;
            
            delete eraser;
            
            stackSize--;
        }
        bottom = NULL;
    }
};

template <class T>
bool stack<T>::pop()
{
	if(stackSize == 0)
	{
        return false;
    }
    else if (stackSize == 1){
        Node<T> *aux = bottom;
        bottom = NULL;
        delete aux;
        
    
    
    }
    else
	{
		Node<T> *aux = bottom->next;
		bottom->next = aux->next;
        
		delete aux; //pointer being freed was not allocated
        //aux=NULL;
        
	}
    stackSize-=1;
    
    return true;
    
}

template <class T>
void stack<T>::push(T d)
{
	Node<T> *newNode = new Node<T>(d);
    
	if(stackSize==0)
	{
		
		newNode->next = newNode;
		bottom = newNode;
        
	}
    else
	{
		newNode->next = bottom->next;
		bottom->next = newNode;
	
	}
	stackSize+=1;
}


