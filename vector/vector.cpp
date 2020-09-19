#ifndef VECTOR_CPP
#define VECTOR_CPP
#include"vector.h"

template<class T>
vector<T>::vector()
{
    _v=nullptr;
    _n=0;
}

template<class T>
vector<T>::vector(int n)
{
    _v=new T[n];
    _n=n;
}

template<class T>
vector<T>::vector(int n,const T& v)
{
    _v=new T[n];
    _n=n;
    for(int i=0;i<_n;i++)
	_v[i]=v;
}

template<class T>
vector<T>::vector(int n,const T* v)
{
    _v=(T*)v;
    _n=n;
}

template<class T>
vector<T>::vector(const vector<T>& v)
{
    _v=v._v;
    _n=v._n;
}

template<class T>
vector<T>::~vector(){}
	
template<class T>
vector<T>& vector<T>::operator=(const vector& v)
{
    _v=v._v;
    _n=v._n;
    return *this;
}

template<class T>
T& vector<T>::operator[](int i)
{
    return _v[i];
}

template<class T>
int vector<T>::size()const
{
    return _n;
}

template<class T>
void vector<T>::resize(int n)
{
   _v=new T[n];
   _n=n;	    
}

template<class T>
void vector<T>::assign(int n,const T& v)
{
    _v=new T[n];
    _n=n;
    for(int i=0;i<_n;i++)
	_v[i]=v;
}

template<class T,class U>
vector<T> operator*(const U& s,const vector<T>& v)
{
    vector<T> local;
    local._v=new T[v._n];
    local._n=v._n;
    for(int i=0;i<local._n;i++)
    {
        local._v[i]=v._v[i]*(T)s;
    }
    return local;
}

template<class T>
T dot(const vector<T>& u,const vector<T>& v)
{
    if(u._n==v._n)
    {
	vector<T> local;
        local._v=new T[v._n];
	T product=(T)0;
	for(int i=0;i<v._n;i++)
	{
	    product+=v._v[i]*u._v[i];
	}
    return product;
    }
    //I know I should eventually retrun something but this is physics not volleyball
}

#endif


