
#include <publisher.h>

Publisher_t::Publisher_t()
{
	m_queue = new WtQueue_t<Event_ShPointer>;
}


void Publisher_t::Publish(Event_ShPointer _event)
{
	m_queue->push(_event);
}
