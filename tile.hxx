template<class T>
Tile<T>::Tile()
{}

template<class T>
Tile<T>::Tile(T s, T e, T n, T w)
{
   south_ = s;
   east_ = e;
   north_ = n;
   west_ = w;
}

template<class T>
Tile<T>::~Tile()
{}

template<class T>
void Tile<T>::set_north(T n)
{
   north_ = n;
}

template<class T>
void Tile<T>::set_east(T e)
{
   east_ = e;
}

template<class T>
void Tile<T>::set_south(T s)
{
   south_ = s;
}

template<class T>
void Tile<T>::set_west(T w)
{
   west_ = w;
}

template<class T>
T Tile<T>::get_north() const
{
   return north_;
}

template<class T>
T Tile<T>::get_east() const
{
   return east_;
}

template<class T>
T Tile<T>::get_south() const
{
   return south_;
}

template<class T>
T Tile<T>::get_west() const
{
   return west_;
}

template<class T>
void Tile<T>::print(std::ofstream& ofs) const
{
   ofs << get_south() << " "
       << get_east() << " "
       << get_north() << " "
       << get_west();
}

/*template<class T>
bool Tile<T>::match_left(Tile& T, Tile& left)
{
   if (T.get_west() == left.get_east())
      return true;
   else
      return false;
}

template<class T>
bool Tile<T>::match_top(Tile& T, Tile& top)
{
   if (T.get_north() == left.get_south())
      return true;
   else
      return false;
}

template<class T>
bool Tile<T>::match_both(Tile& T, Tile& left, Tile& top)
{
   if ((T.get_west() == left.get_east()) && (T.get_north() == top.get_south()))
      return true;
   else
      return false;
}*/
