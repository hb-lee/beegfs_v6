#ifndef POLLLIST_H_
#define POLLLIST_H_

#include <common/toolkit/poll/Pollable.h>
#include <common/Common.h>

#include <boost/scoped_array.hpp>

typedef std::map<int, Pollable*> PollMap;
typedef PollMap::iterator PollMapIter;
typedef PollMap::value_type PollMapVal;

class PollList
{
   public:
      PollList();

      void add(Pollable* pollable);
      void remove(Pollable* pollable);
      void removeByFD(int fd);
      Pollable* getPollableByFD(int fd);
      void getPollArray(struct pollfd** pollArrayOut, unsigned* outLen);
      
   private:
      PollMap pollMap;
      boost::scoped_array<struct pollfd> pollArray;
      unsigned arrayLen;
      bool arrayOutdated;
      
      void updatePollArray();
      
      
   public:
      // getters & setters
      PollMap* getPollMap()
      {
         return &pollMap;
      }

      
};

#endif /*POLLLIST_H_*/
