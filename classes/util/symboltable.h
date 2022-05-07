#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include <deque>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

using namespace std;

template <typename T> class SymbolTable {
  deque<unordered_map<string, T *>> stack_;

public:
  SymbolTable();
  ~SymbolTable();
  T *&operator[](string const &name);
  T *&lookup(string const &name);
  T *&lookupOne(string const &name);
  void push(string const &name, T *const val);
  void pop(string const &name);
  void popOne(string const &name);
  void enter();
  void exit();
  void reset();
};

template <typename T> SymbolTable<T>::SymbolTable() { enter(); }

template <typename T> SymbolTable<T>::~SymbolTable() { exit(); }

template <typename T> T *&SymbolTable<T>::operator[](const string &name) {
  return lookup(name);
}

template <typename T> T *&SymbolTable<T>::lookup(const string &name) {
  for (unordered_map<std::string, T *> stack : stack_)
    if (stack[name])
      return stack[name];
  return stack_.front()[name];
}

template <typename T> T *&SymbolTable<T>::lookupOne(const string &name) {
  if (stack_.front()[name])
    return stack_.front()[name];
  return stack_.front()[name];
}

template <typename T>
void SymbolTable<T>::push(const string &name, T *const val) {
  stack_.front()[name] = val;
}

template <typename T> void SymbolTable<T>::popOne(const string &name) {
  stack_.front().erase(name);
}

template <typename T> void SymbolTable<T>::enter() {
  stack_.push_front(unordered_map<string, T *>());
}

template <typename T> void SymbolTable<T>::exit() { stack_.pop_front(); }

template <typename T> void SymbolTable<T>::reset() {
  stack_.clear();
  enter();
}

#endif // SYMBOLTABLE_H
