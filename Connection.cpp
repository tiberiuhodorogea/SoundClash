#include "Connection.h"

Connection::Connection(int port, LPCWSTR ipAddress,MusicPlayer player)
{
	_port = port;
	_ipAddress = ipAddress;
	_player = player;
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
	else
	{
		std::cout << "The Winsock dll found!" << std::endl;
		std::cout << "The status" << wsaData.szSystemStatus << std::endl;
	}

	_serverSocket = INVALID_SOCKET;
	_serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (_serverSocket == INVALID_SOCKET)
	{
		std::cout << "Error at socket(): " << WSAGetLastError() << std::endl;
		WSACleanup();
		return 0;
	}
	else
	{
		std::cout << "Socket() is OK!" << std::endl;
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
	else
	{
		std::cout << "bind() is OK!" << std::endl;
	}
	//Listen
	if (listen(_serverSocket, 1) == SOCKET_ERROR)
	{
		std::cout << "listen(): Error listening on socket" << WSAGetLastError << std::endl;
		return 0;
	}
	else
	{
		std::cout << "Listen(): is OK, I'm waiting for connections..." << std::endl;
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

void Connection::Send(const std::string message)
{
	int byteCount = send(_acceptSocket, message.c_str(), message.size(), 0);

	if (byteCount == SOCKET_ERROR)
	{
		// If sending fails, print an error message
		std::cerr << "Failed to send message. Error: " << WSAGetLastError() << std::endl;
	}
	else
	{
		// Confirm message has been sent
		std::cout << "Message sent to client: " << message << std::endl;
		std::cout << "Bytes sent: " << byteCount << std::endl;
	}
}

void Connection::uninit()
{
	
		// Shutdown the connection, stopping further send/receive operations
		if (_serverSocket != INVALID_SOCKET)
		{
			// Shutdown the server socket
			int result = shutdown(_serverSocket, SD_BOTH);
			if (result == SOCKET_ERROR) {
				std::cout << "shutdown failed: " << WSAGetLastError() << std::endl;
			}

			// Close the socket
			closesocket(_serverSocket);
			std::cout << "Server socket closed successfully." << std::endl;

			// Invalidate the socket so it can't be used again
			_serverSocket = INVALID_SOCKET;
		}

		// Clean up Winsock
		WSACleanup();
		std::cout << "Winsock cleanup done." << std::endl;
	
}

