The C++ STL
-----------

* The C++ STL (Standard Template Library) consists of a collection of 
  containers, algorithms, and iterators.  It provides much of the standard
  programming functionality for the C++ programming language and is 
  essential to most C++ projects.

* Aside from the classes provided by the C++ STL, many other C++ projects
  follow the same design principles as used in the STL.

* The containers portion of the STL provides standard data structures such 
  as vectors, lists, sets, and maps.

* The iterators portion of the STL provides a standard mechanism for 
  traversing containers.

* The algorithms portion of the STL provides common algorithms that 
  make use of the iterators and containers provided by the STL (and 
  can work with user-defined containers and iterators as well).

Iterators, Tags, and Traits
-----------

* Most containers will have an associated "iterator" that makes it 
  easier to examine or perform actions on all or some of the elements 
  stored in the container.  For example, an array class may provide an 
  iterator that sequentially iterates over the elements stored in the 
  array.

```
array<int> arr(10);

for(int c = 0; c < 10; c++){
  // Do something on the array
  arr[c] = ...;
}

for(array<int>::iterator it = arr.begin(), end = arr.end(); it != end; it++){
  // Do something on the array
  *it = ...;
}
```

* The iterator code above may look slightly more complicated than the version that 
  uses explicit indices, but it has the advantage of not relying on any actual knowledge
  of the internal layout of the array class.  For more complicated data structures, such 
  as lists and double-ended queues, this simplicity becomes more important.

* C++ iterators generally fall into one of several categories that denote the  
  "capabilities" of the iterator.  These capabilities generally mirror the 
  structure of the underlying container.

* "Input" iterators point to read only data.  The iterator can be dereferenced but only
  as an "rvalue" (something on the right-hand side of an assignment operation).

* "Output" iterators point to data that can be assigned into.

* "Forward" iterators allow input, output, and can be incremented.  However, forward
  iterators cannot be decremented.  For example, a singly linked list would only 
  allow a forward iterator because it is not possible to traverse a singly 
  linked list in reverse.

* "Bidirectional" iterators allow input, output, increment, and decrement.  A doubly 
  linked list allows a bidirectional iterator because it can be traversed in both 
  directions.

* "Random access" iterators support the same operations as bidirectional iterators, and 
  they also allow addition, subtraction, inequality comparisons, and indexing.  An 
  array or vector class may allow a random access iterator because the underlying 
  data-structure allows random access.  However, data structures like lists, which generally 
  do not permit random access, cannot allow a random access iterator.

```
struct input_iterator_tag {};

struct output_iterator_tag {};

struct forward_iterator_tag : public input_iterator_tag {};

struct bidirectional_iterator_tag : public forward_iterator_tag {};

struct random_access_iterator_tag : public bidirectional_iterator_tag {};
```

* Iterators are defined to have traits, which give some basic information 
  about how the iterator should be used.

```
template <class T>
struct iterator_traits {
  typedef typename T::value_type value_type;
  typedef typename T::difference_type difference_type;
  typedef typename T::iterator_category iterator_category;
  typedef typename T::pointer pointer;
  typedef typename T::reference reference; 
};
```

* These "trait" templates allow easy specialization for special types 
  of iterators.  For example, pointers have specialized iterator traits.

```
template <class T>
struct iterator_traits<T*> {
  typedef T value_type;
  typedef ptrdiff_t difference_type;
  typedef random_access_iterator_tag iterator_category;
  typedef T* pointer;
  typedef T& reference;
};
```

* The iterator_category tag allows us to specialize code for specific 
  types of iterators.  For example, we can implement searching and 
  sorting much more efficiently for random access iterators than we 
  can for iterators that can only increment.

* We can check the iterator_category tag by having a wrapper function 
  that calls into an internal function with the iterator_category tag 
  as an argument.  This way, the compiler can statically check to make 
  sure that we have an iterator of the proper type.