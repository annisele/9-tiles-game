#ifndef MYLIST_H
#define MYLIST_H

#include <iostream>
#include <string>
#include <stdexcept>

template <typename T>

class mylist
{
public:
 mylist();
 ~mylist();
 int listsize() const;
 void push_back( T newval);
void change(int loc, int num);
  T& at(int loc);
 bool remove( T val);
  T pop(int loc);
  T& operator [] (int loc);
  
 
 protected:
   T *list;
  int reitem;
  int size;
  int length;
 };
 
 
 template <typename  T>
 mylist< T>::mylist()
 {
 list= new  T[25];
 size=25;
 length=0;
 }
 
 template <typename  T>
 T& mylist <T>::operator[] (int loc)
 {
return this->at(loc);
}

template <typename  T>
 mylist< T>::~mylist()
 {

 }
 
 template <typename  T>
  T& mylist< T>::at(int loc)
 {
 return list[loc];
 }
 
 template <typename  T>
 int mylist< T>::listsize() const
 {
return this->length;
 }
 
   
 template <typename  T>
 T mylist< T>::pop(int loc)
 {
 int reitem= list[loc];
 return reitem;
 }
 template <typename  T>
 void mylist< T>::change(int loc, int num)
 {
 list[loc]=num;

 }
 
 template <typename  T>
 bool mylist< T>::remove( T val)
 {
int loc;

for(loc=0;loc<length;loc++)
	if (list[loc]==val)
	{
	for(int i =loc;i<length-1; i++)
		list[i]=list[i+1];
	
	length--;
	return true;
	}
	else
	return false;
	

 }

 /*template <typename  T>
 void mylist< T>::print( )
 {
 
 for(int index=0;index<size;++index)
 {
cout<<list[index]
 
 }
 li
 
 }*/
 template <typename  T>
 void mylist< T>::push_back( T newval)
 {
 
 if (length==size)
 {
  T *morespace=new  T[size*2];
 for(int index=0;index<size;++index)
 {
 morespace[index]=list[index];
 
 }
 delete[] list;
 list=morespace;
 size *= 2;
 
 }
 
 list[length]=newval;
 length++;
 
 
 }

#endif
