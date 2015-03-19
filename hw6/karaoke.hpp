#pragma once

#include <string>
#include <unordered_set>

#include "list.hpp"

class Song{
public:
  std::string title;
  bool sung;

  Song() : title(), sung(false) {}
};

class Singer{
public:
  std::string name;
  Song *songs;
  int numSongs;

  Singer() : name(), songs(nullptr), numSongs(0) {}
  
  ~Singer(){
    if(songs != nullptr){
      delete [] songs;
    }
  }
};

class Event{
public:
  int eventTime;
  std::string singer;
  std::string action;

  Event() : eventTime(0), singer(), action() {}
};

typedef LinkedList SingerList;
typedef LinkedList EventList;

typedef std::unordered_set<std::string> SongSet;

int IncrementTime(int time);

void ScanEvents(char *eventsFileName, EventList& events);

void ScanSingers(char *singerFileName, SingerList& singers);

void SingerEnters(SingerList& singers, SingerList& currentSingers,
                  std::string singerName);

void SingerLeaves(SingerList& currentSingers,std::string singerName);

void Sing(Singer *singer, SongSet& sungSongs,
          int currentTime);

bool HasBeenSung(SongSet& sungSongs, Song *song);
