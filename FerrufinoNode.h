//
//  Node.h
//  Tarea4
//
//  Created by Gustavo Ferrufino on 9/29/13.
//  Copyright (c) 2013 Gustavo Ferrufino. All rights reserved.
//

#ifndef Tarea4_Node_h
#define Tarea4_Node_h

template <class T>
class Node
{
public:
    T info;
    Node<T> *next;
    Node<T> *prev;
    Node() { next=NULL; prev=NULL; }
    Node(T data) { info = data; next=NULL; prev=NULL; }
};


#endif
