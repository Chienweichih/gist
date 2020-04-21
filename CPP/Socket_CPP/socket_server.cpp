#pragma comment(lib, "wsock32.lib")
#include <winsock.h>
#include <iostream>
#include <cstring>
#include <cassert>

using namespace std;

#define NUM_CLIENTS 5
#define INPUT_MAX 10000
#define PORT 1234

void connect(WSADATA &,SOCKET &,SOCKET &,unsigned short);

void main()
{
  cout << "[Server Start!!]" << endl;

	WSADATA wsadata;

	SOCKET server,client;
	connect(wsadata,server,client,PORT);

	char *input = new char[INPUT_MAX];
	char *output = new char[INPUT_MAX];
	
	while(true)
	{	
		
		int check = 0;
		double a = 0.0,b;
		char op;
		char *reader = input;

		//收
		while(check == 0)	
			check = recv(client,input,INPUT_MAX,0);

		if(!strncmp(input,"0",strlen("0") + 1))
			break;
		
		//讀資料
		while(*reader == ' ')reader++;
		a = atof(reader);
		while(*reader != ' ')reader++;
		while(*reader == ' ')reader++;
		op = *reader;
		while(*reader != ' ')reader++;
		while(*reader == ' ')reader++;
		b = atof(reader);

		switch(op)
		{
			case '+':	a += b;	break;
			case '-':	a -= b;	break;
			case '*':	a *= b;	break;
			case '/':	a /= b;	break;
			default:	a = 0.0;
		}
		
		sprintf(output,"%lf",a);

		//送
		assert( send(client,output,strlen(output) + 1,0) != SOCKET_ERROR);
	}

	closesocket(client);
	closesocket(server);
	WSACleanup();

	delete[] input;
	delete[] output;
}

//超麻煩
void connect(WSADATA &wsadata,SOCKET &server,SOCKET &client,unsigned short port)
{

	//start WinSock
	assert(WSAStartup(MAKEWORD(2,0), &wsadata) == 0);
	
	sockaddr_in sin;
	memset(&sin, 0, sizeof(sin));
	sin.sin_family = PF_INET;
	sin.sin_addr.s_addr = INADDR_ANY;
	sin.sin_port = htons(port) ;
	
	//設定TCP Portocol
	protoent *ppe;
	assert((ppe = getprotobyname("tcp")) != 0);
	int type = SOCK_STREAM;

	//OPEN!
	server = socket(PF_INET, type, ppe->p_proto);
	assert(server != INVALID_SOCKET);

	cout << "[Created Server socket.]" << endl;

	//named
	assert( bind(server,(sockaddr *)&sin, sizeof(sin)) != SOCKET_ERROR);

	cout << "[Bind.]" << endl;

	//association
	assert( type != SOCK_STREAM || listen(server,NUM_CLIENTS) != SOCKET_ERROR);

	cout << "[Listen.]" << endl;
	
	sockaddr_in fsin;
	int length = sizeof(fsin);
	client = accept(server, (sockaddr *) &fsin, &length);
	assert(client != INVALID_SOCKET);
	cout << "[client connected.]" << endl;
}