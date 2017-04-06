template<class T>
void Stack<T>::push(T data)
{
   Node* n = std::make_shared<Node<T>>;
   n->data_ = data;
   n->next_ = NULL;
   if (top != NULL)
      n->next_ = top_;
   top_ = n;
}

template<class T>
T Stack<T>::pop()
{
   Node* tmp = std::make_shared<Node<T>>;
   if (top!=NULL)
      tmp = top;


