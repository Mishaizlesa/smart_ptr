#ifndef List_h
#define List_h

#include <stdio.h>
#include <unordered_map>
#include <exception>
#include <stdexcept>
using namespace std;
template <class T> class List{
private:
    struct node{
        T val;
        node* next;
        node(T a){
            val=a;
            next=nullptr;
        }
        node (const node& a){
            val=a.val;
            next=a.next;
        }
    };
    node* first=nullptr;
    size_t size_=0;
public:
    class iterator{
    public:
        node* inode;
        iterator() = default;
        iterator(const iterator& other) = default;
        iterator(node* node_) noexcept{
            inode = node_;
        }
        bool operator ==(const iterator& it)const noexcept {
            return inode == it.node;
        }
        bool operator !=(const iterator& it)const noexcept{
            return inode != it.inode;
        }
        T operator*() {
            return inode->val;
        }
        iterator& operator ++(){
            if (!inode) throw std::out_of_range("out_of_range");
            inode=inode->next;
            return *this;
        }
    };
    
    
    List()=default;
    List(const List& a) noexcept;
    List(List&& a) noexcept{
        swap(*this, a);
    }
    List& operator = (const List& a) noexcept;
    List& operator =(List&& a)noexcept;
    void push_front(const T& val) noexcept;
    void pop_front();
    void insert_after(node* el, const T& val) noexcept;
    void erase_after(node* el);
    void insert_after(iterator it, const T& val) noexcept;
    void erase_after(iterator it);
    void unique() noexcept;
    void clear()noexcept;
    bool operator ==(const List& a) const noexcept;
    bool operator !=(const List& a) const noexcept;
    void resize (const size_t& sz) noexcept;
    void remove (const T& a) noexcept;
    void reverse () noexcept;
    size_t size() const noexcept;
    T& front() const;
    bool empty() const noexcept;
    template<class T1>
    friend void swap(List<T1>& a, List<T1>& b) noexcept;
    iterator begin() const noexcept;
    iterator end() const noexcept;
    ~List() noexcept;
};


template <class T>
inline List<T>::List(const List<T>& a)noexcept{
    if (a.first){
        size_=a.size_;
        first=new node(*a.first);
        auto tmp1=a.first;
        auto tmp2=first;
        while(tmp1->next){
            tmp2->next=new node(*(tmp1->next));
            tmp2=tmp2->next;
            tmp1=tmp1->next;
        }
    }
}


template<class T>
inline void swap(List<T>& a, List<T>& b) noexcept{
    std::swap(b.size_ ,a.size_);
    std::swap(b.first, a.first);
}


template <class T>
inline List<T>& List<T>::operator = (List<T>&& a) noexcept{
    if (this==&a){
        return *this;
    }
    clear();
    swap(*this,a);
    return *this;
}


template <class T>
inline List<T>& List<T>::operator = (const List<T>& a) noexcept{
    if (first==a.first){
        return *this;
    }
    clear();
    size_=a.size_;
    first=new node(*a.first);
    auto tmp1=a.first;
    auto tmp2=first;
    while(tmp1->next){
        tmp2->next=new node(*(tmp1->next));
        tmp2=tmp2->next;
        tmp1=tmp1->next;
    }
    return *this;
}


template<class T>
inline void List<T>::push_front(const T& val) noexcept{
    size_++;
    if (!first){
        first=new node(val);
    }else{
        auto tmp=first;
        first=new node(val);
        first->next=tmp;
        
    }
}


template <class T>
inline void List<T>::pop_front(){
    if (!first) throw std::out_of_range("empty List");
    size_--;
    auto tmp=first;
    first=first->next;
    delete tmp;
}

template <class T>

inline T& List<T>::front() const {
    if (!first) std::logic_error("List is empty");
    return first->val;
}

template <class T>
inline void List<T>::insert_after(node* el, const T& val) noexcept{
    size_++;
    if (!el){
        push_front(val);
        return;
    }
    auto tmp=el->next;
    el->next=new node(val);
    el->next->next=tmp;
}


template <class T>
inline void List<T>::erase_after(node* el){
    if (!el || !el->next) throw std::out_of_range("cannot erase not filled cell");
    size_--;
    node* erase_elem=el->next;
    el->next=erase_elem->next;
    delete erase_elem;
}

template<class T>
inline void List<T>::insert_after(iterator it, const T& val) noexcept{
    insert_after(it.inode,val);
}


template <class T>
inline void List<T>::erase_after(iterator it){
    erase_after(it.inode);
}



template <class T>
inline void List<T>::resize(const size_t& sz) noexcept{
    if (sz==0){
        clear();
        return;
    }
    auto tmp=first;
    auto prev=first;
    size_t tmp_sz=1;
    while(tmp_sz<sz && tmp){
        prev=tmp;
        tmp=tmp->next;
        tmp_sz++;
    }
    if (!tmp){
        insert_after(prev,T());
        tmp=prev->next;
        while(size_<sz){
            insert_after(tmp,T());
        }
        
    }
    else{
        while(tmp->next){
            erase_after(tmp);
        }
    }
}



template <class T>
inline void List<T>::unique() noexcept{
    unordered_map<T,int>used;
    node* prev=nullptr;
    for(node* it=first;it;){
        if (used[it->val]){
            erase_after(prev);
            it=prev->next;
            
        }else{
            used[it->val]=1;
            prev=it;
            it=it->next;
        }
    }
}


template <class T>
inline void List<T>::clear() noexcept{
    while(first){
        pop_front();
    }
    size_=0;
    first=nullptr;
}

template<class T>
inline void List<T>::remove(const T& a)noexcept{
    node* prev=nullptr;
    for(node* it=first;it;){
        if (it->val==a){
            if (it==first){
                pop_front();
                it=first;
            }
            else{
                erase_after(prev);
                it=prev->next;
            }
            
        }else{
            prev=it;
            it=it->next;
        }
    }
    
}


template<class T>
void List<T>::reverse()noexcept {
    node* prev=nullptr;
    auto tmp=first;
    while (tmp) {
        auto x1=tmp;
        auto x2=tmp->next;
        tmp->next=prev;
        tmp=x2;
        prev=x1;
    }
    first=prev;
}

template <class T>
inline bool List<T>::operator ==(const List& a) const noexcept{
    auto tmp1=a.first;
    auto tmp2=first;
    while (tmp1 || tmp2) {
        if (!tmp1 || !tmp2) return false;
        if (tmp2->val!=tmp1->val) return false;
        tmp1=tmp1->next;
        tmp2=tmp2->next;
    }
    return true;
}



template <class T>
inline bool List<T>::operator !=(const List& a) const noexcept{
    return !(*this==a);
}


template <class T>
inline typename List<T>::iterator List<T>::begin() const noexcept{
    return iterator(first);
}


template <class T>
inline typename List<T>::iterator List<T>::end() const noexcept{
    return iterator(nullptr);
}



template<class T>
inline size_t List<T>::size () const noexcept{
    return size_;
}

template <class T>
inline bool List<T>::empty () const noexcept{
    return size_==0;
}

template <class T>
inline List<T>::~List() noexcept{
    clear();
}
#endif /* List_hpp */
