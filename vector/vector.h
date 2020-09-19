#ifndef VECTOR_H
#define VECTOR_H

template<class T>
class vector
{
    int _n;
    T* _v;
public:
    vector();
    explicit vector(int n);
    vector(int n,const T& v);
    vector(int n,const T* v);
    vector(const vector& v);
    ~vector();
    
    vector& operator=(const vector& v);
    inline T& operator[](int i);
    inline const T& operator[](int i)const;
    inline int size()const;
    void resize(int n);
    void assign(int n,const T& v);  
    typedef T value_type;

    template<class U,class V> friend vector<U> operator*(const V& s,const vector<U>& v);
    template<class U> friend U dot(const vector<U>& u,const vector<U>& v);

};

#include"vector.cpp"
#endif
