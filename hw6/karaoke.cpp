#include <cassert>

#include <fstream>
#include <iostream>

#include "karaoke.hpp"

/*body for increment time function*/
int IncrementTime(int time)
{
  /* increment time by five minutes */
  time += 5;

  /* if minutes are now 60 */
  if ((time % 100) == 60)
  {
    /* reset minutes to 0 and increment hour */
    time += 40;
  }
  return time;
}

/*function to scan singers into an array*/
void ScanSingers(char *singerFile, SingerList& singers){
  std::string name;
  std::string songName;

  std::fstream file(singerFile,std::ios_base::in);

  if (!file.is_open()){
    std::cerr << "Error: " << singerFile << " could not be opened\n";
    exit(-1);
  }

  while(!file.eof()){
    Singer *singer = new Singer;

    if(singer == nullptr){
      std::cerr << "Error: Out of memory!\n";
      exit(-1);
    }
    
    file >> singer->name;
    file >> singer->numSongs;

    if(singer->numSongs == 0){
      delete singer;
      continue;
    }

    singer->songs = new Song[singer->numSongs];

    if(singer->songs == nullptr){
      std::cerr << "Error: Out of memory!\n";
      exit(-1);
    }

    for(int c = 0; c < singer->numSongs; c++){
      file >> singer->songs[c].title;
    }

    singers.push_back((void*)singer);
  }

  file.close();
}

void ScanEvents(char *eventsFileName, EventList& events){
  int numEvents;

  std::fstream file(eventsFileName,std::ios_base::in);

  if (!file.is_open()){
    std::cerr << "Error: " << eventsFileName << " could not be opened\n";
    exit(-1);
  }

  file >> numEvents;

  for(int c = 0; c < numEvents; c++){
    Event *event = new Event;
    if (event == nullptr){
      std::cerr << "Error: Out of memory!\n";
      exit(-1);
    }
    file >> event->eventTime;
    file >> event->singer;
    file >> event->action;
    events.push_back((void*)event);
  }

  file.close();
}

void SingerEnters(SingerList& singers, SingerList& currentSingers,
                  std::string singerName){
  LinkedListNode *current = singers.getFirst();
  while(current != nullptr){
    if(((Singer*)current->_data)->name.compare(singerName) == 0){
      currentSingers.push_back(current->_data);
    }
    current = current->_next;
  }
}

void SingerLeaves(SingerList& currentSingers,
                  std::string singerName){
  LinkedListNode *current = currentSingers.getFirst();
  while(current != nullptr){
    if(((Singer*)current->_data)->name.compare(singerName) == 0){
      currentSingers.erase(current);
      return;
    }
    current = current->_next;
  }
}

/*function to choose a song to sing*/
void Sing(Singer *singer, SongSet& sungSongs, 
          int currentTime) {
  int randomNum = rand() % (singer->numSongs);
  Song *song = &singer->songs[randomNum];
  bool finishedSinging = false;

  while(!finishedSinging){
    if(HasBeenSung(sungSongs, song)){
      randomNum = rand() % (singer->numSongs);
      song = &singer->songs[randomNum];
    }else{
      song->sung = true;
      sungSongs.insert(song->title);      
      std::cout << currentTime << " - " << singer->name
                << " sings " << song->title << "\n";
      finishedSinging = true;
    }
  }
}

/*function to check if song has been sung already*/
bool HasBeenSung(SongSet& sungSongs, Song *song){
  return song->sung == true || sungSongs.count(song->title) > 0;
}
