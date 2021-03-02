#include "server.h"



int main(int argc, char const *argv[])
{
	Server serv(5000);
	serv.Run();
	return 0;
}


