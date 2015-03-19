#pragma once

#include <cassert>
#include <cstdlib>

#include <iostream>

struct LinkedListNode{
  void *_data;
  LinkedListNode *_prev;
  LinkedListNode *_next;

  LinkedListNode() : _data(), _prev(nullptr), _next(nullptr) {}
  LinkedListNode(void *data) : _data(data), _prev(nullptr), _next(nullptr) {}
};

class LinkedList;

class LinkedListIterator{
  LinkedListNode *_current;

public:
  friend class LinkedList;
  // TODO: Implement an iterator class for LinkedList
};

class LinkedList{
  LinkedListNode *_first;
  LinkedListNode *_last;

public:
  LinkedList() : _first(nullptr), _last(nullptr) {}

  ~LinkedList(){
    LinkedListNode *current = _first;
    while(current != nullptr){
      LinkedListNode *tmp = current;
      current = current->_next;
      delete tmp;
    }
  }

  void push_back(void *data){
    LinkedListNode *tmp = new LinkedListNode(data);
    if(tmp == nullptr){
      std::cerr << "Error: Out of memory!\n";
      exit(-1);
    }

    if(_first == nullptr){
      _first = tmp;
      _last = tmp;
      return;
    }

    if(_first == _last){
      _last = tmp;
      _first->_next = _last;
      _last->_prev = _first;
      return;
    }

    tmp->_prev = _last;
    _last->_next = tmp;
    _last = tmp;
  }

  bool empty(){
    return _first == nullptr;
  }

  void pop_front(){
    assert(_first != nullptr);
    LinkedListNode *tmp = _first;
    _first = tmp->_next;
    delete tmp;

    if(_first == nullptr){
      _last = nullptr;
    }
  }

  void* front(){
    assert(_first != nullptr);
    return _first->_data;
  }

  void erase(LinkedListNode *node){
    // Case: Single node in the linked list
    if(node == _first && node == _last){
      delete _first;
      _first = nullptr;
      _last = nullptr;
      return;
    }

    // Case: Erasing the first node in the linked list, 
    // but not the only node
    if(node == _first){
      LinkedListNode *tmp = _first;
      _first = tmp->_next;
      delete tmp;
      return;
    }

    // Case: Erasing the last node in the linked list, 
    // but not the only node
    if(node == _last){
      LinkedListNode *tmp = _last;
      _last = tmp->_prev;
      delete tmp;
      return;
    }

    // Case: Erasing some middle node
    node->_prev->_next = node->_next;
    node->_next->_prev = node->_prev;
    delete node;
  }

  void erase(LinkedListIterator& iterator){
    erase(iterator._current);
  }

  LinkedListNode* getFirst(){
    return _first;
  }
};
