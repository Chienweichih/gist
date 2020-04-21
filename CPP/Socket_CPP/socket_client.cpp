#pragma comment(lib, "wsock32.lib")
#include <winsock.h>
#include <iostream>
#include <cassert>
#include <string>

using namespace std;

#define NUM_CLIENTS 5
#define INPUT_MAX 10000
#define PORT 1234

void connect(WSADATA &,SOCKET &,unsigned short,string &);

void main()
{
	cout << "[Client Start!!]" << endl;
	
	string hostIP;

	cout << "請輸入server IP:";
	cin >> hostIP;
	
	WSADATA wsadata;
	SOCKET server;
	connect(wsadata,server,PORT,hostIP);
	
	char *input = new char[INPUT_MAX];
	char *ans = new char[INPUT_MAX];

	while(true)
	{	
		int check = 0;

		cout << "請輸入字串(輸入0結束)：";
		fflush(stdin);
		gets(input);

		//送
		assert( send(server,input,strlen(input) + 1,0) != SOCKET_ERROR);
		
		if(!strncmp(input,"0",strlen("0") + 1))
			break;

		//收
		while(check == 0)	
			check = recv(server,ans,INPUT_MAX,0);

		cout << ans << endl;
	}

	closesocket(server);
	WSACleanup();

	delete[] input;
	delete[] ans;
}

//超麻煩
void connect(WSADATA &wsadata,SOCKET &server,unsigned short port,string &hostIP)
{	
	//start WinSock
	assert(WSAStartup(MAKEWORD(2,0), &wsadata) == 0);
	
	sockaddr_in sin;
	memset(&sin, 0, sizeof(sin));
	sin.sin_family = PF_INET;
	sin.sin_port = htons(port) ;
	
	//設定IP
	hostent *host;
	if(host = gethostbyname(hostIP.c_str()))
		memcpy(&sin.sin_addr, host->h_addr, host->h_length);
	else
		assert((sin.sin_addr.s_addr = inet_addr(hostIP.c_str())) != INADDR_NONE);

	//設定TCP Portocol
	protoent *ppe;
	assert((ppe = getprotobyname("tcp")) != 0);
	int type = SOCK_STREAM;

	//OPEN!
	server = socket(PF_INET, type, ppe->p_proto);
	assert(server != INVALID_SOCKET);

	cout << "[Created Server socket.]" << endl;

	//association
	assert(connect(server, (sockaddr *)&sin, sizeof(sin)) != SOCKET_ERROR);
}