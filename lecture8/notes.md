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