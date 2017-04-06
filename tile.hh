#pragma once

#include <iostream>

template<class T>
class Tile
{
public:
   Tile();
   Tile(T s, T e, T n, T w);
   ~Tile();

   void set_north(T n);
   void set_east(T e);
   void set_south(T s);
   void set_west(T w);

   T get_north() const;
   T get_east() const;
   T get_south() const;
   T get_west() const;

   void print(std::ofstream& ofs) const;

protected:
   T south_;
   T east_;
   T north_;
   T west_;
};

#include "tile.hxx"
