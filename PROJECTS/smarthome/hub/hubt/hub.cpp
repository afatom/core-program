#include <hub.h>
#include <pthread.h>

Hub_t::Hub_t(): m_queue(new WtQueue_t<Event_ShPointer>) 
{
	m_pPregistrar = new Registrar_t;
	m_pPublisher = new Publisher_t(m_queue);
	m_pDistributer = new Distributor_t(m_queue, m_pPregistrar);
}


Hub_t::~Hub_t()
{
	delete m_queue;
	delete m_pPregistrar;
	delete m_pPublisher;
	delete m_pDistributer;

	m_queue = 0;
	m_pPregistrar = 0;
	m_pPublisher = 0;
	m_pDistributer = 0;
}



void* DisperseThreadFunc(void* ptr)
{
	Distributor_t* dis = (Distributor_t*)ptr;
	dis->Disperse();

	return 0;
}




void Hub_t::Activate()
{
	pthread_t dis;
	pthread_create(&dis, 0, DisperseThreadFunc, m_pDistributer);
	pthread_join(dis, 0);
}
