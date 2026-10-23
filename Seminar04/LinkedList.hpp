#pragma once
#include <cstdlib>

template <class T>
class LinkedList{
  struct Node{
    T data;
    Node* next;

    Node(const T& data, Node* next = nullptr) : data(data), next(next) {}
  };

  Node* m_begin;
  Node* m_end;
  size_t m_size;

  void copy(const LinkedList& other){
    
  }
  void move(LinkedList&& other){

  }
  void free(){

  }

public:

  LinkedList() : m_begin(nullptr), m_end(nullptr), m_size(0) {}

  bool empty() const {
    return m_size == 0;
  }

  size_t size() const {
    return m_size;
  }

  void push_back(const T& el){
    Node* toAdd = new Node(el);

    if(empty()){
      m_begin = toAdd;
      m_end = m_begin;
    }

    m_end->next = toAdd;
    m_end = toAdd;
    m_size++;
  }

  void push_front(const T& el){
    Node* toAdd = new Node(el, m_begin);

    if(empty()){
      m_begin = toAdd;
      m_end = m_begin;
    }

    m_begin = toAdd;
    m_size++;
  }

  void pop_front(){
    Node* toDelete = m_begin;
    m_begin = m_begin->next;
    delete toDelete;
    m_size--;
  }
};