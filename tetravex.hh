#pragma once

#include <vector>
#include <queue>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdint>
#include "tile.hh"

// FIXME type definition, replace int by what you think is best
// Threshold 0
//template <class T>
//using Tile = int;

template <class T>
class Tetravex
{
	public:
		// Threshold 0
		Tetravex<T>(uint8_t size)
      {
         size_ = size;
      }

		void add_tile(const Tile<T>& tile)
      {
         tiles_.push_back (tile);
      }

      typename std::vector<Tile<T>>::iterator tiles_beg()
      {
         return tiles_.begin();
      }

      typename std::vector<Tile<T>>::iterator tiles_end()
      {
         return tiles_.end();
      }

      int tiles_length() const
      {
         return tiles_.size();
      }

		// Threshold 1
		int write(const std::string& output) const
      {
         if (output.substr(output.find_last_of(".") + 1) != "vex")
            return 3;
         std::ofstream stream;
         stream.open(output);
         if (!stream.is_open())
            return 3;
         stream << static_cast<int>(size_) << std::endl;
         auto it = tiles_.begin();
         for (int i = 0; i < size_ * size_; i++)
         {
            it->print(stream);
            stream << std::endl;
            it++;
         }
         stream.close();
         return 0;
      }

		int read(const std::string& input)
      {
         std::ifstream stream;
         stream.open(input);
         if (!stream)
            return 3;
         int s = 0;
         std::string line;
         getline(stream, line);
         std::istringstream ss(line);
         ss >> s;
         if (s < 1)
            return 3;
         else
         {
            size_ = static_cast<int>(s);
            for (int i = 0; i < s * s; i++)
            {
               getline(stream, line);
               std::istringstream subl(line);
               T north;
               T east;
               T south;
               T west;
               subl >> south >> east >> north >> west;
               auto to_add = Tile<T>(south, east, north, west);
               add_tile(to_add);
            }
         }
         return 0;
      }

		// Threshold > 2
		int solve(const std::string& output) const
      {
         int n = 0;
         for (int i = 0; i < size_ * size_; i++)
         {
            n = n + BFS(i, n, output);
         }
         if (n == 1)
         {
            char filenameo[255];
            sprintf(filenameo, "%s_0.vex", output.c_str());
            char filenamen[255];
            sprintf(filenamen, "%s.vex", output.c_str());
            rename(filenameo, filenamen);
         }
         return 0;
      }

      int BFS(int x, int n, std::string output) const
      {
         auto tv = Tetravex(size_);
         int n_deux = n;
         auto it = tiles_.begin();
         char filename[255];
         std::queue<Tile<T>> q;
         bool *visited = new bool[size_ * size_];
         for (int i = 0; i < size_ * size_; i++)
            visited[i] = false;
         q.push(*(it + x));
         visited[x] = true;
         while(!q.empty())
         {
            auto tt = q.front();
            tv.add_tile(tt);
            q.pop();
            for (int j = 0; j < size_ * size_; j++)
            {
               if (!visited[j])
               {
                  if (tv.tiles_length() < size_ && (it + j)->get_west() == (tv.tiles_end() - 1)->get_east())
                  {
                     visited[j] = true;
                     q.push(*(it + j));
                  }
                  if (tv.tiles_length() >= size_ && (tv.tiles_length()
                           % size_) == 0 && (it + j)->get_north()
                            == (tv.tiles_beg() + tv.tiles_length() - size_)->get_south())
                  {
                     visited[j] = true;
                     q.push(*(it + j));
                  }
                  if (tv.tiles_length() >= size_
                        && (tv.tiles_length() % size_) != 0
                        && (it + j)->get_north() == 
                           (tv.tiles_beg() + tv.tiles_length() - size_)->get_south()
                        && (it + j)->get_west() == 
                           (tv.tiles_end() - 1)->get_east())
                  {
                     visited[j] = true;
                     q.push(*(it + j));
                  }
               }
            }
            if (tv.tiles_length() == size_ * size_)
            {
               sprintf(filename, "%s_%d.vex", output.c_str(), n);
               tv.write(filename);
               n++;
            }
         }
         if (n_deux == n)
            return 0;
         else
            return n;
      }

	private:
		std::vector<Tile<T>> tiles_;
		uint8_t size_;
};

template <class T>
Tetravex<T> generate(uint8_t size);

template<>
Tetravex<int> generate<int>(uint8_t size)
{
   auto to_ret = Tetravex<int>(size);
   auto t = Tile<int>(rand() % 9 + 1, rand() % 9 + 1, rand() % 9 + 1, rand() % 9 + 1);
   to_ret.add_tile(t);
   for (int i = 1; i < size * size; i++)
   {
      int j = i % size;
      if (i < size)
      {
        auto it = to_ret.tiles_beg() + (i - 1);
        auto tt = Tile<int>(rand() % 9 + 1, rand() % 9 + 1, rand() % 9 + 1, it->get_east());
        to_ret.add_tile(tt);
      }
      else if (i >= size && j == 0)
      {
        auto it_up = to_ret.tiles_beg() + (i - size);
        auto tt = Tile<int>(rand() % 9 + 1, rand() % 9 + 1, it_up->get_south(), rand() % 9 + 1);
        to_ret.add_tile(tt);
      }
      else
      {
        auto it = to_ret.tiles_beg() + (i - 1);
        auto it_up = to_ret.tiles_beg() + (i - size);
        auto tt = Tile<int>(rand() % 9 + 1, rand() % 9 + 1, it_up->get_south(), it->get_east());
        to_ret.add_tile(tt);
      }
   }
   return to_ret;
}
