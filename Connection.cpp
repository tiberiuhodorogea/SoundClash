#include "Connection.h"

Connection::Connection(int port, LPCWSTR ipAddress)
{
	_port = port;
	_ipAddress = ipAddress;
}

int Connection::init()
{
	WSADATA wsaData;
	int wsaerr;
	WORD wVersionRequested = MAKEWORD(2, 2);
	wsaerr = WSAStartup(wVersionRequested, &wsaData);
	if (wsaerr != 0)
	{
		std::cout << "The Winsock dll not found" << std::endl;
		return 0;
	}

	_serverSocket = INVALID_SOCKET;
	_serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (_serverSocket == INVALID_SOCKET)
	{
		std::cout << "Error at socket(): " << WSAGetLastError() << std::endl;
		WSACleanup();
		return 0;
	}

	sockaddr_in service;
	service.sin_family = AF_INET;
	InetPton(AF_INET, _ipAddress, &service.sin_addr.s_addr);
	service.sin_port = htons(_port);
	if (bind(_serverSocket, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR) {
		std::cout << "bind() failed" << WSAGetLastError() << std::endl;
		closesocket(_serverSocket);
		WSACleanup();
		return 0;
	}
	//Listen
	if (listen(_serverSocket, 1) == SOCKET_ERROR)
	{
		std::cout << "listen(): Error listening on socket" << WSAGetLastError << std::endl;
		return 0;
	}

}

void Connection::socketAccept()
{
	_acceptSocket = accept(_serverSocket, NULL, NULL);
	if (_acceptSocket == INVALID_SOCKET)
	{
		std::cout << "accept failed:" << WSAGetLastError() << std::endl;
	}
	else
	{
		std::cout << "Handshaking" << std::endl;
		std::cout << "Connection Accepted" << std::endl;
	}
}
