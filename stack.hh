#pragma once

template<class T>
struct Node
{
   T data_;
   struct Node* next_;
};

template<class T>
class Stack
{
public:
   Stack()
   {
      top_ = NULL;
   }
   
   void push(T data);
   T pop();
   bool is_empty();
   
protected:
   struct Node* top_;
};

#include "stack.hxx"
