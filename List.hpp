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
  bool empty() const;
  
  //EFFECTS: returns the number of elements in this List
  //HINT:    Traversing a list is really slow. Instead, keep track of the size
  //         with a private member variable. That's how std::list does it.
  int size() const;
  
  //REQUIRES: list is not empty
  //EFFECTS: Returns the first element in the list by reference
  T & front();
  
  //REQUIRES: list is not empty
  //EFFECTS: Returns the last element in the list by reference
  T & back();
  
  //EFFECTS:  inserts datum into the front of the list
  void push_front(const T &datum);
  
  //EFFECTS:  inserts datum into the back of the list
  void push_back(const T &datum);
  
  //REQUIRES: list is not empty
  //MODIFIES: invalidates all iterators to the removed element
  //EFFECTS:  removes the item at the front of the list
  void pop_front();
  
  //REQUIRES: list is not empty
  //MODIFIES: invalidates all iterators to the removed element
  //EFFECTS:  removes the item at the back of the list
  void pop_back();
  
  //MODIFIES: invalidates all iterators to the removed elements
  //EFFECTS:  removes all items from the list
  void clear();
  
  // You should add in a default constructor, destructor, copy constructor,
  // and overloaded assignment operator, if appropriate. If these operations
  // will work correctly without defining these, you should omit them. A user
  // of the class must be able to create, copy, assign, and destroy Lists.
  
  // DONE: declare default constructor
  List();
  
  // DONE: declare destructor
  ~List();
  
  // DONE: declare copy constructor
  List(const List &original);
  
  // DONE: declare assignment operator
  List &operator=(const List &original);
  
  private:
  //a private type
  struct Node {
    Node *next;
    Node *prev;
    T datum;
  };
  
  //REQUIRES: list is empty
  //EFFECTS:  copies all nodes from other to this
  void copy_all(const List<T> &other);
  
  Node *first;   // points to first Node in list, or nullptr if list is empty
  Node *last;    // points to last Node in list, or nullptr if list is empty
  int num_elements; // running count of elements in list
  
  public:
  ////////////////////////////////////////
  class Iterator {
    public:
    //OVERVIEW: Iterator interface to List
    
    // Add a default constructor here. The default constructor must set both
    // pointer members to null pointers.
    
    // DONE: declare Iterator default constructor
    Iterator();
    
    
    // Add custom implementations of the destructor, copy constructor, and
    // overloaded assignment operator, if appropriate. If these operations
    // will work correctly without defining these, you should omit them. A user
    // of the class must be able to copy, assign, and destroy Iterators.
    
    
    
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
    
    // DONE: declare operator*
    T &operator*() const;
    
    // DONE: declare prefix operator++
    Iterator &operator++();
    
    // DONE: declare postfix operator++
    Iterator operator++(int);
    
    // DONE: declare operator==
    bool operator==(const Iterator &original) const;
    
    // DONE: declare operator!=
    bool operator!=(const Iterator &original) const;
    
    
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
      return &operator*();
    }
    
    private:
    const List *list_ptr; //pointer to the List associated with this Iterator
    Node *node_ptr; //current Iterator position is a List node
    // add any additional necessary member variables here
    
    
    // add any friend declarations here
    friend class List; // allows List::begin() and List::() end to 
    // call private Iterator(const List*, Node*) ctr
    
    // construct an Iterator at a specific position in the given List
    Iterator(const List *lp, Node *np);
    
  };//List::Iterator
  ////////////////////////////////////////
  
  // return an Iterator pointing to the first element
  Iterator begin() const;
  
  // return an Iterator pointing to "past the end"
  Iterator end() const;
  
  //REQUIRES: i is a valid, dereferenceable iterator associated with this list
  //MODIFIES: invalidates all iterators to the removed element
  //EFFECTS: Removes a single element from the list container.
  //         Returns An iterator pointing to the element that followed the
  //         element erased by the function call
  Iterator erase(Iterator i);
  
  //REQUIRES: i is a valid iterator associated with this list
  //EFFECTS: Inserts datum before the element at the specified position.
  //         Returns an iterator to the the newly inserted element.
  Iterator insert(Iterator i, const T &datum);
  
};//List


////////////////////////////////////////////////////////////////////////////////
// Add your member function implementations below or in the class above
// (your choice). Do not change the public interface of List, although you
// may add the Big Three if needed.  Do add the public member functions for
// Iterator.

// *** PUBLIC IMPLEMENTATIONS ***

// DONE: implement default constructor
// EFFECTS: Initializes an empty list (Default Constructor)
template <typename T>
List<T>::List() : first(nullptr), last(nullptr), num_elements(0) {}

// DONE: implement destructor
// EFFECTS: Releases heap memory via clear() which handles walking nodes and deleting.
template <typename T>
List<T>::~List() {
  clear(); 
}

// DONE: implement copy constructor
// EFFECTS: Initializes to empty state first, then copies all nodes from original.
template <typename T>
List<T>::List(const List<T> &original) : first(nullptr), last(nullptr), 
num_elements(0) {
  copy_all(original);
}

// DONE: implement assignment operator
template <typename T>
List<T> &List<T>::operator=(const List<T> &original) {
  // Self-assignment check.
  if (this == &original) {
    return *this; // return 
  }
  
  clear(); // Clear existing nodes
  copy_all(original); // Copy from other 
  
  return *this;
}

// DONE: implement empty
// EFFECTS: Returns true if there is no elements in the list (empty), 
//   otherwise false.
template <typename T>
bool List<T>::empty() const {
  return num_elements == 0;
}

// DONE: implement size
// EFFECTS: Returns the size of the list as an int.
template <typename T> 
int List<T>::size() const {
  return num_elements;
}

// DONE: implement front
// EFFECTS: Return first item of list. 
template <typename T>
T &List<T>::front() {
  assert(!empty());
  return first->datum;
}

// DONE: implement back
// EFFECTS: Return last item of list.
template <typename T>
T &List<T>::back() {
  assert(!empty());
  return last->datum;
}

// DONE: implement push_front
template <typename T>
void List<T>::push_front(const T &datum) {
  // Allocate new node and set next of new node to current first.
  Node *new_node = new Node{first, nullptr, datum};
  
  // Check if list already has nodes.
  if (first) {
    // Case: list already has nodes.
    first->prev = new_node; // wire current head's prev backward to new node
  } else {
    // Case: list empty, first was nullptr and no prev. head to update.
    last = new_node; // must also point to new node since its the only element
  }
  
  // New node is now the head.
  first = new_node;
  ++num_elements;
}

// DONE: implement push_back
template <typename T>
void List<T>::push_back(const T &datum) {
  Node *new_node = new Node{nullptr, last, datum}; // prv. point -> crt. last
  
  // Check if list already has nodes.
  if (last) { 
    // Case: last is not null.
    last->next = new_node; // current tail next ptr gets wired to new node
  } else { 
    // Case: last is null.
    first = new_node; // list is empty so first also needs to point here
  }
  
  // Always update last->next unconditionally.
  last = new_node;
  ++num_elements;
}

// DONE: implement pop_front
template <typename T>
void List<T>::pop_front() {
  // assert(!empty());
  
  // Save node to delete and advance first to next node.
  Node *to_delete = first;
  first = first->next;
  
  // Check if head has a predecessor.
  if (first) {
    // Case: no predecessor.
    first->prev = nullptr;
  } else {
    // Case: first became nullptr, list is now empty.
    last = nullptr;
  }
  
  // Release heap memory.
  delete to_delete;
  --num_elements;
}

// DONE: implement pop_back
template <typename T>
void List<T>::pop_back() {
  // assert(!empty());
  
  // Save node to delete and retreat last to prev node.
  Node *to_delete = last;
  last = last->prev;
  
  // Check if tail has a successor.
  if (last) {
    // Case: new last is a real node.
    last->next = nullptr; // new tail has no successor, null it out
  } else {
    // Case: last became nullptr, list is now empty.
    first = nullptr;
  }
  
  // Release heap memory.
  delete to_delete;
  --num_elements;
}

// DONE: implement clear
// EFFECTS: Walks chain directly deleting each node, then resets last and
//   num_elements in one shot at the end.
template <typename T>
void List<T>::clear() {
  while (first) {
    Node *to_delete = first;
    first = first->next; // advance before delete — can't read next after freeing
    delete to_delete;
  }
  
  // Loop never touched last, null it explicitly.
  last = nullptr; 
  num_elements = 0; // reset count
}

// *** PRIVATE IMPLEMENTATIONS ***

// DONE: implement copy_all
// EFFECTS: walks list from first to the end, pushing each datum onto *this
//   via push_back.
template <typename T>
void List<T>::copy_all(const List<T> &other) {
  // Walk thru every node till nullptr is hit (end of list).
  for (Node *current = other.first; current; current = current->next) {
    push_back(current->datum); // Take node datum and push to back of *this
  }
}


// *** ITERATOR IMPLEMENTATIONS ***

// DONE: implement Iterator default constructor
// EFFECTS: Both pointers null, not associated with any list.
template <typename T>
List<T>::Iterator::Iterator() : list_ptr(nullptr), node_ptr(nullptr) {}

// DONE: implement operator*
// EFFECTS: Returns reference to datum at current node.
template <typename T>
T &List<T>::Iterator::operator*() const {
  // assert(node_ptr); // dereferencing past-the-end is undefined behavior
  return node_ptr->datum;
}

// DONE: implement prefix operator++
// EFFECTS: Advances to next node, returns reference to self.
template <typename T>
typename List<T>::Iterator &List<T>::Iterator::operator++() {
  // assert(node_ptr); // incrementing past the end is undefined behavior
  node_ptr = node_ptr->next; // nullptr: hit past the end
  return *this;
}

// DONE: implement postfix operator++
// EFFECTS: Save current state, advances, returns pre-increment snapshot
template <typename T>
typename List<T>::Iterator List<T>::Iterator::operator++(int) {
  Iterator copy = *this; // save position before advancing
  operator++();
  
  // Return old position, *this now one step forward.
  return copy;
}

// DONE: implement operator==
// EFFECTS: Both list_ptr and node_ptr must match for equality.
template <typename T>
bool List<T>::Iterator::operator==(const Iterator &original) const {
  return ((list_ptr == original.list_ptr) && (node_ptr == original.node_ptr));
}

// DONE: implement operator!=
template <typename T>
bool List<T>::Iterator::operator!=(const Iterator &original) const {
  return !(*this == original); // delegate to operator== and invert
}

// DONE: implement Iterator private constructor
// EFFECTS: Binds iterator to a specific list and position within it.
template <typename T>
List<T>::Iterator::Iterator(const List<T> *list_p, Node *node_p) : 
list_ptr(list_p), node_ptr(node_p) {}

// DONE: implement begin
// EFFECTS: Returns iterator to first node (nullptr if empty, same as end)
template <typename T>
typename List<T>::Iterator List<T>::begin() const {
  return Iterator(this, first);
}

// DONE: implement end
// EFFECTS: Returns past-the-end iterator; nullptr node, real list_ptr.
template <typename T>
typename List<T>::Iterator List<T>::end() const {
  return Iterator(this, nullptr);
}

// DONE: implement erase
// EFFECTS: Unlinks target from both directions, deletes it, returns
//   iterator to whatever followed it.
template <typename T>
typename List<T>::Iterator List<T>::erase(Iterator iterator) {
  // assert(i != end()); // erasing past th -end is undefined behavior
  
  Node *target = iterator.node_ptr;
  Node *after = target->next; // node that will follow the gap
  Node *before = target->prev; // node that will come before the gap
  
  if (before) {
    before->next = after; // predecessor skips over target
  } else {
    // Case: target was the head.
    first = after;
  }
  
  if (after) {
    after->prev = before; // successor skips back over target
  } else {
    // Case: target was the tail.
    last = before;
  }
  
  delete target;
  --num_elements;
  return Iterator(this, after); // after is nullptr if target was last, which 
  //   is end()
}

// DONE: implement insert
// EFFECTS: Inserts datum before position i. Handles head, tail, and middle
//   cases through null checks rather than branching on begin/end explicitly.
template <typename T>
typename List<T>::Iterator List<T>::insert(Iterator iterator, const T &datum) {
  Node *next_node = iterator.node_ptr;
  // Next_node exists, predecessor is its prev; at end(), predecessor is last.
  Node *prev_node;

  // Next and prev wired before touching anything else.
  if (next_node) {
    prev_node = next_node->prev;
  } else {
    prev_node = last;
  }

  Node *new_node = new Node{next_node, prev_node, datum}; 
  
  if (prev_node) {
    prev_node->next = new_node; // wire predecessor forward to new node
  } else {
    // Case: no predecessor, new node is the new head.
    first = new_node;
  }
  
  if (next_node) {
    next_node->prev = new_node; // wire successor backward to new node
  } else {
    // Case: no successor, new node is the new tail.
    last = new_node;
  }
  
  ++num_elements;
  return Iterator(this, new_node); // return iterator to new node
}

#endif // Do not remove this. Write all your code above this line.