#include <registrar.h>


Registrar_t::Registrar_t()
{
	m_map = new map<const string, vector<Ilistener_t*> >;
	if(pthread_mutex_init(&m_mutex, NULL) != 0)
    {
        //throw exception;
    }
}


Registrar_t::~Registrar_t()
{
	delete m_map;
	m_map = 0;
	pthread_mutex_destroy(&m_mutex);
}

void Registrar_t::Subscribe(Ilistener_t* _pListiner, const string& _eventType)
{
	pthread_mutex_lock(&m_mutex);
	(*m_map)[_eventType].push_back(_pListiner); //error
	//(*m_map).insert(std::pair<char,int>('a',100) );

	pthread_mutex_unlock(&m_mutex);
}

void Registrar_t::UnSubscribe(Ilistener_t* _pListiner, const string& _eventType)
{
	pthread_mutex_lock(&m_mutex);
	//vector<Ilistener_t*>::iterator itb;
	vector<Ilistener_t*>::iterator itb = ((*m_map)[_eventType]).begin();
	vector<Ilistener_t*>::iterator ite = ((*m_map)[_eventType]).end();
	
	while(itb != ite)
	{
		if(*itb == _pListiner)
		{
			((*m_map)[_eventType]).erase(itb);
			break;
		}
		++itb;
	}
	pthread_mutex_unlock(&m_mutex);
}


size_t Registrar_t::GetSubscribersNum() 
{
	pthread_mutex_lock(&m_mutex);
	size_t size = (*m_map).size();
	pthread_mutex_unlock(&m_mutex);
	return size;
}


vector<Ilistener_t*>& Registrar_t::GetSubscribers(const string& _key) 
{
	pthread_mutex_lock(&m_mutex);
	vector<Ilistener_t*>& temp = (*m_map)[_key];
	pthread_mutex_unlock(&m_mutex);
	return temp;
}


size_t Registrar_t::GetSubscribersOnType(const string& _type) 
{
	pthread_mutex_lock(&m_mutex);
	size_t size = (*m_map)[_type].size();
	pthread_mutex_unlock(&m_mutex);
	return size;
}


