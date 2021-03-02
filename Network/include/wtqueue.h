#ifndef __WT_QUEUE_T_H_
#define __WT_QUEUE_T_H_

#include <tr1/memory>
#include <TException_t.h>
#include <iostream>
#include <pthread.h>
#include <queue>
#include <cstdlib>
#include <exception>      // std::exception
/** 
 *  @file wtqueue.h
 *  @brief Create a Generic(Template) thread safe Queue wich can growth on demmand.
 * 
 *  @details Implemented Over STL queue, wich can provides thread safe mechanism. 
 *  @author Author Adham (faresadham@gmail.com) 
 * 
 *  @bug No known bugs.
 * 
 *  @comments WtQ size() and empty() functions are not const funcs because locking/unlocking mutex action
 */ 

using namespace std;

template<typename T>
class WtQueue_t{
    private:
    queue<T> m_queue;
    pthread_cond_t 	m_readersCv;
    pthread_mutex_t m_mutex;
    void CvAndMutexDestroy();
    bool CvAndMutexInit();
	void pop();                 //Removes the next element in the queue, effectively reducing its size by one
    WtQueue_t(const WtQueue_t& _wtqueue);
    WtQueue_t& operator = (const WtQueue_t& _wtqueue);

    public:
    WtQueue_t();
    ~WtQueue_t();
    void push (T& _item); //Inserts a new element at the end of the queue
    size_t size();        		//Returns the number of elements in the queue.
    T Popfront();               //Returns a reference to the next element in the queue.
    bool empty();         		//Returns whether the queue is empty: i.e. whether its size is zero.
    T back();                   //Returns a reference to the last element in the queue. This is the "newest" 
                                //element in the queue (i.e. the last element pushed into the queue).
};


template<typename T>
WtQueue_t<T>::WtQueue_t()
{
    queue<T> temp;
    m_queue = temp;
    if(!this->CvAndMutexInit()) //init fails
    {
		string msg("CV_AND_MUTEX_INIT_ERROR");
        throw(TException_t<int>(1, __LINE__, __FILE__,__func__,msg));
    }
}


template<typename T>
void WtQueue_t<T>::CvAndMutexDestroy()
{
    pthread_cond_destroy(&m_readersCv);
	pthread_mutex_destroy(&m_mutex);
}
	
    
template<typename T>
bool WtQueue_t<T>::CvAndMutexInit()
{
    if(pthread_mutex_init(&m_mutex, NULL) != 0)
    {
        return false;
    }  

    if(pthread_cond_init(&m_readersCv, NULL)!= 0)
	{
        pthread_mutex_destroy(&m_mutex);
        return false;
	}

    return true;
}


template<typename T>
WtQueue_t<T>::~WtQueue_t(){this->CvAndMutexDestroy();}

template<typename T>
size_t WtQueue_t<T>::size()
{
	//pthread_mutex_lock(&m_mutex);
    size_t ret = m_queue.size();
    //pthread_mutex_unlock(&m_mutex);
    //pthread_cond_broadcast(&m_readersCv);
    return ret;
}

template<typename T>
bool WtQueue_t<T>::empty()
{
	pthread_mutex_lock(&m_mutex);
    bool ret = m_queue.empty();
    pthread_mutex_unlock(&m_mutex);
    pthread_cond_broadcast(&m_readersCv);
    return ret;
}

template<typename T>
void  WtQueue_t<T>::push (T& _item)
{
	pthread_mutex_lock(&m_mutex);
	try
	{
		//cout<<"Push Intrance 1 WtQueue msg"<<endl;
		m_queue.push(_item);
		//cout<<"Push Intrance 2 WtQueue msg"<<endl;
	}
	catch (exception& e)
	{
		pthread_mutex_unlock(&m_mutex);  
		throw(e);
	}
    pthread_mutex_unlock(&m_mutex);
   // cout<<"Push Intrance 3 WtQueue msg"<<endl;
    pthread_cond_broadcast(&m_readersCv);
   // cout<<"Push Intrance 4 WtQueue msg"<<endl;
}

template<typename T>
void WtQueue_t<T>::pop()
{
	//pthread_mutex_lock(&m_mutex);
    m_queue.pop();
    //pthread_mutex_unlock(&m_mutex);
	//pthread_cond_broadcast(&m_readersCv);
}


template<typename T>
T WtQueue_t<T>::Popfront()
{
    pthread_mutex_lock(&m_mutex);
    while(this->size() == 0)
	{
		pthread_cond_wait(&m_readersCv, &m_mutex);
	}
  
	T temp = m_queue.front();
	this->pop();
    pthread_mutex_unlock(&m_mutex);
    
    return temp;
}


template<typename T>
T WtQueue_t<T>::back()
{
	pthread_mutex_lock(&m_mutex);

	T temp = m_queue.back();

    pthread_mutex_unlock(&m_mutex);
    return temp;
}
#endif //__WT_QUEUE_T_H_
