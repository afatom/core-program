
#ifndef __NODE_T_H_
#define __NODE_T_H_


using namespace std;

template<class T>
class Node_t{
public:
	Node_t() : m_item(NULL), m_prev(NULL), m_next(NULL) {}
	Node_t(T* _item, Node_t<T>* _prev = NULL, Node_t<T>* _next = NULL) : m_item(_item), m_prev(_prev), m_next(_next) {};
	Node_t(const Node_t<T>& _node) : m_item(_node.m_item), m_prev(_node.m_prev), m_next(_node.m_next) {}; // copy CTOR
	virtual ~Node_t() 
	{
		m_prev = NULL;
		m_next = NULL;
	}

	virtual void SetItem(T* _item) {m_item = _item;}
	virtual T* GetItem() const {return m_item;}
	
	virtual Node_t<T>* Prev() const {return m_prev;};
	virtual Node_t<T>* Next() const {return m_next;};
	
	virtual void SetPrev(Node_t<T>* _prev) {m_prev = _prev;}
	virtual void SetNext(Node_t<T>* _next) {m_next = _next;}

	virtual Node_t<T>& operator= (const Node_t<T>& _node)
	{
		if (this != &_node)
		{
			m_item = _node.m_item;
			m_prev = _node.m_prev;
			m_next = _node.m_next;			
		}
		return *this;
	};

private:
	T* m_item;
	Node_t<T>* m_prev;
	Node_t<T>* m_next;
};

#endif //__NODE_T_H_
