#include <cstdlib>

#include <iostream>
#include <unordered_set>

#include "karaoke.hpp"
#include "list.hpp"

const int START_TIME = 1800;
const int END_TIME = 2330;

int main(int argc, char **argv){
  SongSet sungSongs;
  SingerList singers;
  SingerList currentSingers;
  EventList events;

  if (argc != 4){
    std::cerr << "Usage: " << argv[0] << " [singers file] [events file] [seed]\n";
    exit(-1);
  }

  ScanSingers(argv[1], singers);
  ScanEvents(argv[2], events);
  srand(atoi(argv[3]));

  int currentTime = START_TIME;

  LinkedListNode *currentEvent = events.getFirst();

  while(currentTime < END_TIME){
    if(currentEvent != nullptr && 
       ((Event*)currentEvent->_data)->eventTime == currentTime){
      Event *event = (Event*)currentEvent->_data;
      if(event->action.compare("ENTER") == 0){
        SingerEnters(singers,currentSingers,event->singer);
        std::cout << currentTime << " - " << event->singer << " arrives\n";
      }else{
        SingerLeaves(currentSingers,event->singer);
        std::cout << currentTime << " - " << event->singer << " leaves\n";
      }
      currentEvent = currentEvent->_next;
    }else{
      if(!currentSingers.empty()){
        Singer *singer = (Singer*)currentSingers.front();
        currentSingers.pop_front();
        Sing(singer,sungSongs,currentTime);
        
        // Put the person who just sang at the back of the line
        currentSingers.push_back(singer);
        currentTime = IncrementTime(currentTime);
      }
    }
  }

  LinkedListNode *currentSinger = singers.getFirst();

  while(currentSinger != nullptr){
    delete (Singer*)currentSinger->_data;
    currentSinger = currentSinger->_next;
  }

  currentEvent = events.getFirst();

  while(currentEvent != nullptr){
    delete (Event*)currentEvent->_data;
    currentEvent = currentEvent->_next;
  }

  return 0;
}
