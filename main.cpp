#include <iostream>

#include <list>
#include <vector>

#include <cstdlib>
#include <cstring>

#include <cstdio>

template<class T>
class CList;

//template<class T>
//class CListNodeIterator;

template<class T>
class CListNode{
    CListNode* prev_elem;
    CListNode* next_elem;
public:
    //friend CList<T>;

    //friend CListNodeIterator<T>;
    //typedef CListNodeIterator<T> iterator;

    typedef CListNode<T>  _Self;
    typedef CListNode<T>* _SelfPtr;

    explicit CListNode(const T _value_ = T()):
        prev_elem(nullptr), next_elem(nullptr), value(_value_)
    {}
    explicit CListNode(CListNode<T>* _prev_, CListNode<T>* _next_, const T _value_ = T()):
        prev_elem(_prev_), next_elem(_next_), value(_value_)
    {
        if (_prev_ != nullptr)
            _prev_->next_elem = this;
        if (_next_ != nullptr)
            _next_->prev_elem = this;
    }
    ~CListNode()
    {
        if (prev_elem != nullptr)
            prev_elem->next_elem = next_elem;
        if (next_elem != nullptr)
            next_elem->prev_elem = prev_elem;
    }

    T value;

    inline CListNode<T>* next() {return next_elem;}
    inline CListNode<T>* prev() {return prev_elem;}

    void connect(CListNode<T>* _prev_, CListNode<T>* _next_){
        _prev_->next_elem =  this;
         this ->prev_elem = _prev_;
        _next_->prev_elem =  this;
         this ->next_elem = _next_;
    }

    static void swap(CListNode<T>& left, CListNode<T>& right) {std::swap(left.value, right.value);}
    //static void copy(std::pair<_SelfPtr, _SelfPtr> dest, std::pair<_SelfPtr, _SelfPtr> src);
    //static void copy(CListNode<T>* dest_head, CListNode<T>* dest_tail, CListNode<T>* src_head, CListNode<T>* src_tail))
    //    {copy(std::make_pair(dest_head, dest_tail), std::make_pair(src_head, src_tail))}

    void* operator new(size_t size);
    void  operator delete(void* p);
};

/*
template<class T>
void CListNode<T>::copy(std::pair<CListNode<T>*, CListNode<T>*> dest, std::pair<CListNode<T>*, CListNode<T>*> src){
    typedef _SelfPtr CListNode<T>*;
    _SelfPtr it = src.first;
    dest.first = new CListNode<T>(*it);
    dest.second = dest.first;
    while(it != src.second){
        dest.second->next = new CListNode<T>(*it);
        ++it; ++dest.second;
    }
}

template<class T>
void CList<T>::copy(CListNode<T>* dest_head, CListNode<T>* dest_tail, CListNode<T>* src_head, CListNode<T>* src_tail)
*/

template<class T>
void* CListNode<T>::operator new(size_t size){
    void *retval = calloc(1, size);
    if (retval == nullptr){
        printf("no free memory");
        throw std::bad_alloc();
    }
    else
        printf("allocated at address %p\n", retval);
    return retval;
}

template<class T>
void CListNode<T>::operator delete(void* p){
    printf("free at address %p\n", p);
    free(p);
}

/*
template<class T>
class CListNodeIterator{
    CListNode<T>* curr;
public:
    typedef CListNodeIterator<T> _Self;

    CListNodeIterator(): curr(nullptr) {}
    CListNodeIterator(CListNode<T>* element): curr(element) {}
    CListNodeIterator(CListNodeIterator& another): curr(another.curr) {}

    const T& operator* () const {return curr->value;}
          T& operator* ()       {return curr->value;}
    const T* operator->() const {return curr;}
          T* operator->()       {return curr;}
    const T*       data() const {return curr;}
          T*       data()       {return curr;}

    _Self& move_forward(size_t dist) {
        while((dist)&&(curr != nullptr)){
            curr = curr->next;
            --dist;
        }
        return *this;
    }
    _Self& move_backward(size_t dist){
        while((dist)&&(curr != nullptr)){
            curr = curr->prev;
            --dist;
        }
        return *this;
    }

    _Self& operator++(){
        if (curr != nullptr)
        curr = curr->next;
        return *this;
    }
    _Self  operator++(int){
        _Self tmp = *this;
        if (curr != nullptr)
            curr = curr->next;
        return tmp;
    }
    _Self& operator--(){
        if (curr != nullptr)
        curr = curr->prev;
        return *this;
    }
    _Self  operator--(int){
        _Self tmp = *this;
        if (curr != nullptr)
            curr = curr->next;
        return tmp;
    }

    template<class Tp>
    friend bool operator==(const _Self& left, const _Self& right);
    template<class Tp>
    friend bool operator!=(const _Self& left, const _Self& right);
};

template<class T>
inline bool operator==(const CListNodeIterator<T>& left, const CListNodeIterator<T>& right){
    return left.curr == right.curr;
}

template<class T>
inline bool operator!=(const CListNodeIterator<T>& left, const CListNodeIterator<T>& right){
    return left.curr != right.curr;
}
*/

template<class T>
class CList{
    CListNode<T>* head;
    CListNode<T>* tail;
    size_t size;

    CListNode<T>* first_element(CListNode<T>* element)
        {return head = tail = insert(nullptr, nullptr, element);}
    CListNode<T>* first_element(const T value = T())
        {return head = tail = insert(nullptr, nullptr, value);}

    CListNode<T>* insert(CListNode<T>* prev, CListNode<T>* next, CListNode<T>* element) //do not make public
        {element->connect(prev, next); ++size; return element;}
    CListNode<T>* insert(CListNode<T>* prev, CListNode<T>* next, const T value = T()) //do not make public
        {++size; return new CListNode<T>(prev, next, value);}
public:
    CList():
        head(nullptr), tail(nullptr), size(0)
    {}
    CList(const CList<T>& another);
    ~CList();

    inline CListNode<T>* insert_after (CListNode<T>* prev, CListNode<T>* element) {return insert(      prev  , prev->next(), element);}
    inline CListNode<T>* insert_before(CListNode<T>* next, CListNode<T>* element) {return insert(next->prev(), next        , element);}
    inline CListNode<T>* insert_after (CListNode<T>* prev, const T value = T())   {return insert(      prev  , prev->next(), value);}
    inline CListNode<T>* insert_before(CListNode<T>* next, const T value = T())   {return insert(next->prev(), next        , value);}
    inline void push_back(CListNode<T>* element){
        if (tail == nullptr)
            first_element(element);
        else
            tail = insert_after(tail, element);
    }
    inline void push_back(const T value = T()){
        if (tail == nullptr)
            first_element(value);
        else
            tail = insert_after(tail, value);
    }
    inline void push_front(CListNode<T>* element){
        if (head == nullptr)
            first_element(element);
        else
            head = insert_before(head, element);
    }
    inline void push_front(const T value = T()){
        if (head == nullptr)
            first_element(value);
        else
            head = insert_before(head, value);
    }

    void dump();
};

template<class T>
CList<T>::CList(const CList<T>& another):
    head(nullptr), tail(nullptr), size(0)
{
    if (another.head == nullptr){
        CList();
        return;
    }
    CListNode<T>* it = another.head;
    while(it != nullptr){
        push_back(it->value);
        it = it->next();
    }
}

template<class T>
CList<T>::~CList(){
    CListNode<T>* it = head;
    CListNode<T>* next = it->next();
    while(it != nullptr){
        delete it;
        it = next;
        next = (next != nullptr)? next->next() : nullptr;
    }
}

template<class T>
void CList<T>::dump(){
    printf("dumping of CList at address %p\n", this);
    CListNode<T>* it = head;
    CListNode<T>* prev = it->prev();
    CListNode<T>* next = it->next();
    while(it != nullptr){
        printf("\telement:\n");
        if (it == head) printf("\t\thead element\n");
        if (it == tail) printf("\t\ttail element\n");
        printf("\t\tprev  = %p; %s\n", it->prev(), (it->prev() == prev)? "ok": "panic");
        printf("\t\tnext  = %p; %s\n", it->next(), (it->next() == next)? "ok": "panic");
        printf("\t\tvalue = %d\n", it->value);
        prev = it;
        it = next;
        next = (next != nullptr)? next->next() : nullptr;
    }
}


int main()
{
    CList<int> a;
    a.push_back(1);
    a.push_back(2);
    a.push_back(3);
    a.push_back(4);
    a.push_back(5);
    a.dump();
    CList<int> b(a);
    b.dump();
    return 0;
}
