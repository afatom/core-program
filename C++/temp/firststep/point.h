#ifndef __POINT_H_
#define __POINT_H_

#include <stdio.h>


class Point{
	public:
	Point();
	void Init(){
		mx=0;
		my=0;
	return;
	};
	void SetVal(int ax, int ay){
		if(ax >= 0 && ay >= 0 )
	{
		mx=ax; my=ay;
		return;
	}

	return;
	}
	
	void PrintPoint(){
			cout << "mx = "<< mx <<" my="<< my << end1;
		}
	~Point();
	
	private:
	int mx;
	int my;
	
	};




#endif //__POINT_H_
