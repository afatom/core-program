#ifndef __IAGENT_T_H_
#define __IAGENT_T_H_

#include <string>
#include <ipublisher.h>
#include <iregistrar.h>


using namespace std;
class IAgent_t{
	
	private:
	
	
	public:
	IAgent_t(){}
	virtual ~IAgent_t(){}
	virtual void SetId(const string&) = 0;
	virtual void SetType(const string&) = 0;
	virtual void SetRoom(const string&) = 0;
	virtual void SetFloor(const string&) = 0;
	virtual void SetLog(const string&) = 0;
	virtual void SetConfig(const string&) = 0;
	
	virtual const string& GetId() const = 0;
	virtual const string& GetType() const = 0;
	virtual const string& GetRoom() const = 0;
	virtual const string& GetFloor() const = 0;
	virtual const string& GetLog() const = 0;
	virtual const string& GetConfig() const = 0;
	virtual void Run() = 0;


	};
#endif //__IAGENT_T_H_
