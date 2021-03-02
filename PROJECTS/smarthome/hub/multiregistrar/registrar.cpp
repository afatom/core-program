#include <multiregistrar.h>


typedef std::map<const string, vector<Ilistener_t*> > SingleMap;
typedef std::map<const string, map <const string, vector<Ilistener_t*> > > DualMap;
typedef std::map<const string, map < const string, map <const string, vector<Ilistener_t*> > > > TrippleMap;


MRegistrar_t::MRegistrar_t()
{
	m_container = new IlistenersContainer;
	if(pthread_mutex_init(&m_mutex, NULL) != 0)
    {
        //throw exception;
    }
}


MRegistrar_t::~MRegistrar_t()
{
	delete m_container;
	m_container = 0;
	pthread_mutex_destroy(&m_mutex);
}


void MRegistrar_t::Subscribe(Ilistener_t* _pListiner, SubscribingSet& _set)
{
	pthread_mutex_lock(&m_mutex);
	
	if(_set.m_floor != "all" && _set.m_room != "all")
	{
		//specific type,floor,room subscribing
		((((*m_container)[_set.m_eventType])[_set.m_floor])[_set.m_room]).push_back(_pListiner);
	}
	
	else if(_set.m_floor != "all" && _set.m_room == "all")
	{
		SubscribeOnAllRooms(_set.m_eventType, _set.m_floor, _pListiner);
	}
	
	else
	{
		//all floors and all rooms
		SubscribeOnAllFloors(_set.m_eventType ,_pListiner);
	} 
	
	pthread_mutex_unlock(&m_mutex);
}



void MRegistrar_t::SubscribeOnAllRooms(const string& _eventType, const string& _floor, Ilistener_t* _pListiner)
{
	SingleMap::iterator itb = (((*m_container)[_eventType])[_floor]).begin();
	SingleMap::iterator ite = (((*m_container)[_eventType])[_floor]).end();
	while(itb!=ite)
	{
		//push the _pListiner to itb vector
		(*(itb->second)).push_back(_pListiner);
		++itb;
	}
}


void MRegistrar_t::SubscribeOnAllFloors(const string& _eventType ,Ilistener_t* _pListiner)
{
	std::map<const string, map < const string, vector<Ilistener_t*> > >::iterator itb = (((*m_container)[_eventType])).begin();
	std::map<const string, map < const string, vector<Ilistener_t*> > >::iterator ite = (((*m_container)[_eventType]).end();
	while(itb != ite)
	{
		//push the _pListiner to itb vector
		SubscribeOnAllRooms(_eventType, (*(itb->first)), _pListiner);
		++itb;
	}
}



map<Ilistener_t*,int>* MRegistrar_t::GetSubscribers(SubscribingSet& _set)
{
	pthread_mutex_lock(&m_mutex);
	map<Ilistener_t*,int>* retval = new map<Ilistener_t*,int>;
		
	if(_set.m_floor != "all" && _set.m_room != "all")
	{
		retval = VectorToMap(&((((*m_container)[_set.m_eventType])[_set.m_floor])[_set.m_room]));
	}
	
	else if(_set.m_floor != "all" && _set.m_room == "all")
	{
		SingleMap::iterator itb = (((*m_container)[_set.m_eventType])[_set.m_floor]).begin();
		SingleMap::iterator ite = (((*m_container)[_set.m_eventType])[_set.m_floor]).end();
		RoomsMapToMyMap(itb, ite, retval);
	}
	
	else
	{
		DualMap::iterator itb = ((*m_container)[_set.m_eventType]).begin();
		DualMap::iterator ite = ((*m_container)[_set.m_eventType]).end();
		FloorsMapToMyMap(itb, ite, retval);
	} 
	
	pthread_mutex_unlock(&m_mutex);
	return retval;
} 




void VectorTurnToMyMap(vector<Ilistener_t*>* _pvec, map<Ilistener_t*,int>* _pmap)
{
	size_t size = _pvec->size();
	for(size_t j=0;j<size;++j)
	{
		_pmap->insert(std::pair<Ilistener_t*, int>((*_pvec)[j], 0));
	}
}

void RoomsMapToMyMap(SingleMap::iterator _begin, SingleMap::iterator _end, map<Ilistener_t*,int>* _pmap)
{	
	while(_begin != _end)
	{
		VectorTurnToMap(_begin->second, _pmap);
		++_begin;
	}
}


void FloorsMapToMyMap(DualMap::iterator _begin, DualMap::iterator _end, map<Ilistener_t*,int>* _pmap)
{
	while(_begin != _end)
	{
		SingleMap::iterator itb = (*(_begin->second)).begin();
		SingleMap::iterator ite = (*(_begin->second)).end();
		
		RoomsMapToMyMap(itb, ite, _pmap);
		++_begin;
	}
}


//void MRegistrar_t::UnSubscribe(Ilistener_t* _pListiner, SubscribingSet& _set)
