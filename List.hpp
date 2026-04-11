#ifndef LIST_HPP
#define LIST_HPP
/* List.hpp
 *
 * doubly-linked, double-ended list with Iterator interface
 * EECS 280 List/Editor Project
 */

#include <iostream>
#include <iterator> //std::bidirectional_iterator_tag
#include <cassert>  //assert


template <typename T>
class List {
  //OVERVIEW: a doubly-linked, double-ended list with Iterator interface
public:

  //EFFECTS:  returns true if the list is empty
  bool empty() const{
    //if first is a nullptr returns true;
    //!ptr returns true if it is a nullptr
    return (!first);
  }

  //EFFECTS: returns the number of elements in this List
  //HINT:    Traversing a list is really slow. Instead, keep track of the size
  //         with a private member variable. That's how std::list does it.
  int size() const{
    //size_of is updated when nodes are added or deleted
    //or when list is copied/assigned in 
    return this->size_of;
  }

  //REQUIRES: list is not empty
  //EFFECTS: Returns the first element in the list by reference
  T & front(){
    assert(!empty());
    return first->datum;
  }

  //REQUIRES: list is not empty
  //EFFECTS: Returns the last element in the list by reference
  T & back(){
    assert(!empty());
    return last->datum;
  }

  //EFFECTS:  inserts datum into the front of the list
  void push_front(const T &datum){
    //see if i can rewrite this without he if statement
    Node* new_node = new Node;
    if (this->empty()){
      new_node->datum = datum;
      new_node->next = nullptr;
      new_node->prev = nullptr;
      first = last = new_node;
    } else {
      new_node->datum = datum;
      new_node->next = first;
      new_node->prev = nullptr;
      first->prev = new_node;
      this->first = new_node;
    }
    ++size_of;
  }

  //EFFECTS:  inserts datum into the back of the list
  void push_back(const T &datum){
    Node* new_node = new Node;
    new_node->datum = datum;
    if (empty()){
      //Node* new_node = new Node{nullptr, nullptr, datum};
      new_node->next = new_node->prev = nullptr;
      first = last = new_node;
    } else {
      new_node->prev = last;
      last = last->next = new_node;
    }
    ++size_of;
  }

  //REQUIRES: list is not empty
  //MODIFIES: invalidates all iterators to the removed element
  //EFFECTS:  removes the item at the front of the list
  void pop_front(){
    assert(!empty());
    if(size_of == 1){
      delete first;
      first = last = nullptr;
    } else {
      Node * second = first->next;
      delete first;
      first = second;
      first->prev = nullptr;
    }
    --size_of;
  }

  //REQUIRES: list is not empty
  //MODIFIES: invalidates all iterators to the removed element
  //EFFECTS:  removes the item at the back of the list
  void pop_back(){
    assert(!empty());
    if (size_of == 1){
      delete last;
      first = last = nullptr;
    } else {
      Node * second_to_last = last->prev;
      delete last;
      last = second_to_last;
      last->next = nullptr;
    }
    --size_of;
  }

  //MODIFIES: invalidates all iterators to the removed elements
  //EFFECTS:  removes all items from the list
  void clear(){
    Node* node_ptr = first;
    while (node_ptr){
      Node* temp = node_ptr->next;
      delete node_ptr;
      node_ptr = temp;
    }
    first = nullptr;
    last = nullptr;
    size_of = 0;
  }

  // You should add in a default constructor, destructor, copy constructor,
  // and overloaded assignment operator, if appropriate. If these operations
  // will work correctly without defining these, you should omit them. A user
  // of the class must be able to create, copy, assign, and destroy Lists.
  //default constructor
  List() : first(nullptr), last(nullptr){}

  //copy ctor
  List(const List &other) : first(nullptr), last(nullptr), size_of(0) {
    this->copy_all(other);
  };

  //assignment operator
  List & operator=(const List &other){
    if (this != &other){
      this->clear();
      this->copy_all(other);
    }
    return *this;
  };

  ~List(){
    this->clear();
  }

private:
  //a private type
  struct Node {
    Node *next;
    Node *prev;
    T datum;
  };

  //REQUIRES: list is empty
  //EFFECTS:  copies all nodes from other to this
  void copy_all(const List<T> &other){
    for (Node *node_ptr = other.first; node_ptr != nullptr; node_ptr = node_ptr->next){
      this->push_back(node_ptr->datum);
    }
  }

  Node *first;   // points to first Node in list, or nullptr if list is empty
  Node *last;    // points to last Node in list, or nullptr if list is empty
  int size_of = 0;

public:
  ////////////////////////////////////////
  class Iterator {
  public:
    //OVERVIEW: Iterator interface to List

    // Add a default constructor here. The default constructor must set both
    // pointer members to null pointers.
    Iterator() : list_ptr(nullptr), node_ptr(nullptr) {}

    // Add custom implementations of the destructor, copy constructor, and
    // overloaded assignment operator, if appropriate. If these operations
    // will work correctly without defining these, you should omit them. A user
    // of the class must be able to copy, assign, and destroy Iterators.

    //big three not necessary for iterator - nothing created on heap

    // Your iterator should implement the following public operators:
    // *, ++ (both prefix and postfix), == and !=.
    // Equality comparisons must satisfy the following rules:
    // - two default-constructed iterators must compare equal
    // - a default-constructed iterator must compare unequal to an
    //   iterator obtained from a list, even if it is the end iterator
    // - two iterators to the same location in the same list must
    //   compare equal
    // - two iterators to different locations in the same list must
    //   compare unequal
    // - comparing iterators obtained from different lists results in
    //   undefined behavior
    //   - Your implementation can handle this however you like, but
    //     don't assume any particular behavior in your test cases --
    //     comparing iterators from different lists essentially
    //     violates the REQURES clause.
    // Note: comparing both the list and node pointers should be
    // sufficient to meet these requirements.

    //prefix
    Iterator& operator++(){
      assert(node_ptr);
      node_ptr = node_ptr->next;
      return *this;
    }

    //postfix
    Iterator operator++(int /*dummy*/){
      assert(node_ptr);
      Iterator copy = *this;
      operator++();
      return copy;
    }

    bool operator!=(const List<T>::Iterator right) const{
      return node_ptr != right.node_ptr;
    }

    bool operator==(const List<T>::Iterator right) const{
      return node_ptr == right.node_ptr;
    }

    T& operator*() const{
      assert(node_ptr);
      return(node_ptr->datum);
    }
    // Type aliases required to work with STL algorithms. Do not modify these.
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using reference = T&;

    // This operator will be used to test your code. Do not modify it.
    // REQUIRES: Iterator is decrementable. All iterators associated with a
    //           list are decrementable, including end iterators, except for
    //           begin iterators (those equal to begin() on the list)
    // EFFECTS:  moves this Iterator to point to the previous element
    //           and returns a reference to this Iterator
    Iterator& operator--() { // prefix -- (e.g. --it)
      assert(list_ptr);
      assert(*this != list_ptr->begin());
      if (node_ptr) {
        node_ptr = node_ptr->prev;
      } else { // decrementing an end Iterator moves it to the last element
        node_ptr = list_ptr->last;
      }
      return *this;
    }

    // This operator will be used to test your code. Do not modify it.
    // REQUIRES: Iterator is decrementable. All iterators associated with a
    //           list are decrementable, including end iterators, except for
    //           begin iterators (those equal to begin() on the list)
    // EFFECTS:  moves this Iterator to point to the previous element
    //           and returns a copy of the original Iterator
    Iterator operator--(int /*dummy*/) { // postfix -- (e.g. it--)
      Iterator copy = *this;
      operator--();
      return copy;
    }

    // REQUIRES: Iterator is dereferenceable
    // EFFECTS: returns the underlying element by pointer
    // NOTE: T must be a class type to use the syntax it->. If T has a
    //       member variable f, then it->f accesses f on the
    //       underlying T element.
    T* operator->() const {
      return &node_ptr->datum;
    }

  private:
    const List *list_ptr; //pointer to the List associated with this Iterator
    Node *node_ptr; //current Iterator position is a List node
    // add any additional necessary member variables here


    // add any friend declarations here
    friend class List;

    // construct an Iterator at a specific position in the given List
    Iterator(const List *lp, Node *np) : list_ptr(lp), node_ptr(np){}

  };//List::Iterator
  ////////////////////////////////////////

  // return an Iterator pointing to the first element
  Iterator begin() const{
    return Iterator(this, first);
  }

  // return an Iterator pointing to "past the end"
  Iterator end() const{
    return Iterator(this, nullptr);
  }

  //REQUIRES: i is a valid, dereferenceable iterator associated with this list
  //MODIFIES: invalidates all iterators to the removed element
  //EFFECTS: Removes a single element from the list container.
  //         Returns An iterator pointing to the element that followed the
  //         element erased by the function call
  Iterator erase(Iterator i){
    assert(i.node_ptr);
    Node * node_prev = i.node_ptr->prev;
    Node * node_next = i.node_ptr->next;
    if (node_prev){
      node_prev->next = node_next;
    } else {
      first = node_next;
    }
    if (node_next){
      node_next->prev = node_prev;
    } else {
      last = node_prev;
    }
    Node* victim = i.node_ptr;
    Iterator* temp = &i;
    ++(*temp);
    delete victim;
    --size_of;
    return *temp;
  }

  //REQUIRES: i is a valid iterator associated with this list
  //EFFECTS: Inserts datum before the element at the specified position.
  //         Returns an iterator to the the newly inserted element.
  Iterator insert(Iterator i, const T &datum){
    Node * current_node = i.node_ptr;
    Node * new_node = new Node;
    new_node->datum = datum;
    new_node->next = nullptr;
    new_node->prev = nullptr;

    if (current_node){
        Node * node_prev = current_node->prev;
        new_node->next = current_node;
        new_node->prev = node_prev;
        current_node->prev = new_node;
        if (node_prev){
            node_prev->next = new_node;
        } else {
            first = new_node; 
        }
    } else {
      //if this is becoming the new last node
        new_node->prev = last;
        if (last){
            last->next = new_node;
        } else {
          //if the list is empty
            first = new_node;
        }
        last = new_node;
    }

    ++size_of;
    return Iterator(this, new_node);
  }

};//List


////////////////////////////////////////////////////////////////////////////////
// Add your member function implementations below or in the class above
// (your choice). Do not change the public interface of List, although you
// may add the Big Three if needed.  Do add the public member functions for
// Iterator.


#endif // Do not remove this. Write all your code above this line.
