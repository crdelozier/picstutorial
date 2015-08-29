Templates
-----------

* C++ provides templates to allow programmers to write code that is largely independent 
  of the type of object being used in their code.  For example, templates allow
  programmers to write data structures that can store any type of data without having 
  to resort to void pointers.  This capability allows C++ code (that uses templates) to 
  be better typed than C code.

* To demonstrate the power of templates, let's try to write a linked list that only 
  stores integers.

```
class LinkedListNode{
public:
  int data;
  LinkedListNode *next;
};

int main(){
  LinkedListNode node;
  int d = 5;
  node.data = d;
  int c = node.data;
  return 0;
}
```

* This linked list node will accomplish the task of storing integers in a linked
  list, but it will only store integers.  We can change this structure to store 
  any type of data using void pointers.

```
class LinkedListNode{
public:
  void *data;
  LinkedListNode *next;
};

int main(){
  LinkedListNode node;
  int d = 5;
  node.data = (void*)d;
  int c = (int)node.data;
  return 0;
}
```

* This structure is more flexible because it can store any type of data in the 
  void pointer, but it requires unchecked type-casts that may cause type-safety 
  errors if used incorrectly.

```
template <class T>
class LinkedListNode{
public:
  T data;
  LinkedListNode *next;
};

int main(){
  LinkedListNode<int> node;
  int d = 5;
  node.data = d;
  int c = node.data;
  return 0;
}
```

* Templates allow us to both store anything in our linked list data structure
  while also avoiding unchecked type casts.

* Classes can be templated on either types or on integers.  Templates on integers
  allow interesting tricks like template metaprogramming (to be shown later!).
  Integer templates also allow us to template on the values "true" and "false" 
  implicitly (1 and 0).  Thus, we can design classes that are specialized for 
  specific implementations.

Template Specialization
-----------

* Template specialization allows us to generate specific code for a certain type.
  Instead of using the generic code provided by a templated class, a template 
  specialization will use specialized code for a specified type.

* For example, if we have an array template that stores any 
  type of data, we might want to specialize a copy function 
  to allow optimized copying of primitive data types.  
  (Recall that copy constructors must be called for class
  and struct data types.)

```
template <class T>
class array{
  T *data;
  unsigned int size;

public:
  array() : data(nullptr) {}

  array(unsigned int _size) : data(nullptr), size(_size){
    data = new T[size];
  }

  void copyFrom(array<T> &other){
    assert(size < other.size);
    std::cout << "Using copyFrom<T>\n";
    for(int c = 0; c < other.size; c++){
      data[c] = other.data[c];
    }
  }

  ~array(){
    if(data != nullptr){
      delete [] data;
    }
  }

  T& operator[] (unsigned int index){
    assert(index < size);
    return data[index];
  }
};

template<>
class array<int>{
  int *data;
  unsigned int size;

public:
  array() : data(nullptr) {}

  array(unsigned int _size) : data(nullptr), size(_size){
    data = new int[size];
  }

  ~array(){
    if(data != nullptr){
      delete [] data;
    }
  }

  void copyFrom(array<int> &other){
    assert(other.size <= size);
    std::cout << "Using copyFrom<int>\n";
    memcpy(data,other.data,other.size * sizeof(int));
  }

  int& operator[] (unsigned int index){
    assert(index < size);
    return data[index];
  }
};
```

* We can also do partial template specialization if we only
  want to specialize some of the template parameters.

* For example, we might want to specialize a template for 
  just the "values" type in a hash map.

```
template <class T, class U>
class HashMap{
  U *values;
  ...
};

template <class T>
class HashMap<T,int>{
  int *values;
  ...
};
```

Function Templates
-----------

* Functions (outside of classes) can also be templated.  Function 
  template act similarly to class templates.

* For example, we can template a "swap" function that uses
  a temporary value to swap the values in two variables of any type.

```
template<class T> void swap(T &lhs, T &rhs){
  T tmp = lhs;
  lhs = rhs;
  rhs = tmp;
}
```

* When we call this function, we don't always have to provide the 
  template parameters.  We can certainly call it using "swap<int>(args)", 
  but the compiler can also infer which version of the templated 
  function we want to call by examining the parameters.

* Function templates can also be specialized and partially specialized
  similarly to class templates.

Default Template Parameters
-----------

* Like function arguments, templates can also have default parameters.

* For example, many of the C++ STL container classes have a template 
  parameter that specifies the memory allocator that the container will 
  call into to allocate memory.  The default value for this template
  parameter is the standard allocator, but users of the container can 
  easily substitute their own allocator for better performance.

