#pragma once
#include <cstdlib>
#include <new>
#include <utility>

template <class T>
class Vector{
  T* arr;
  size_t m_size;
  size_t m_capacity;

  void copy(const Vector& other){
    T* newArr;
  
    try{
      newArr = new T[m_capacity];
    }
    catch(const std::bad_alloc& e){
      throw;
    }

    delete[] arr;
    m_size = other.m_size;
    m_capacity = other.m_capacity;

    
    arr = newArr;

    for(size_t i = 0; i < m_size; i++){
      arr[i] = other.arr[i];
    }
    
  }

  void move(Vector&& other){
    std::swap(other.arr, arr);
    std::swap(m_size, other.m_size);
    std::swap(m_capacity, other.m_capacity);
  }

  void free(){
    delete[] arr;
    arr = nullptr;
    m_capacity = 0;
    m_size = 0;
  }

  void resize(){
    T* newArr;
    size_t newCapacity;

    if(m_capacity == 0) newCapacity = 1;
    else newCapacity = 2*m_capacity;

    try{
      newArr = new T[newCapacity];
    }
    catch(const std::bad_alloc& e){
      throw;
    }

    m_capacity = newCapacity;

    for(size_t i = 0; i < m_size; i++){
      newArr[i] = arr[i];
    }

    delete[] arr;

    arr = newArr;
  }


public:

  class iterator{
    T* pos;
  public:
    iterator(T* pos) : pos(pos) {}

    T& operator*(){
      return *pos;
    }

    const T& operator*() const{
      return *pos;
    }

    bool valid() const{
      return pos != nullptr;
    }

    bool operator!=(const iterator& other) const {
      return pos != other.pos;
    }

    bool operator==(const iterator& other) const {
      return pos == other.pos;
    }

    iterator& operator++(){
      return ++pos;
    }

    iterator operator++(int) {
      iterator temp = pos;
      ++pos;
      return temp;
    }

    // до тук са задължителните оператори

    T* operator->(){
      return pos;
    }

    const T* operator->() const{
      return pos;
    }
    
    iterator& operator--(){
      return --pos;
    }

    iterator operator--(int) {
      iterator temp = pos;
      --pos;
      return temp;
    }
  };

  Vector() : m_size(0), m_capacity(0), arr(nullptr) {}
  Vector(size_t capacity) : m_size(0), m_capacity(capacity), arr(new T[capacity]) {}

  Vector(const Vector& other) : Vector(){
    copy(other);
  }
  Vector(Vector&& other) : Vector(){
    move(std::move(other));
  }

  Vector& operator=(const Vector& other){
    if(this == &other) return *this;

    free();
    copy(other);

    return *this;
  }

  Vector& operator=(Vector&& other){
    if(this == &other) return *this;

    free();
    move(std::move(other));

    return *this;
  }

  ~Vector() {
    free();
  }

  size_t size() const {
    return m_size;
  }

  size_t capacity() const{
    return m_capacity;
  }

  bool empty() const {
    return m_size == 0;
  }

  void push(const T& el){
    if(m_size >= m_capacity) resize();

    arr[m_size++] = el;
  }

  void pop(){
    if(m_size <= 0) return;
    --m_size;
  }

  void insert(size_t index, const T& element){
    if(index >= m_capacity || index < 0) return;

    push(element);
    for(size_t i = m_size - 1; i > index ; i--){
      std::swap(arr[i], arr[i - 1]);
    }
  }

  void remove(size_t index){
    if(index >= m_capacity || index < 0) return;
    if(m_size <= 0) return;

    for(size_t i = index; i < m_size - 1 ; i++){
      std::swap(arr[i], arr[i + 1]);
    }

    pop();
  }

  T& operator[](size_t index){
    return arr[index];
  }

  const T& operator[](size_t index) const {
    return arr[index];
  }


};