#ifndef SERVER_H_
#define SERVER_H_

#include "ClientHandler.h"
#include "SharedServerHandler.h"

class Server {
public:
	Server();

	bool isReady();

	void run();

	virtual ~Server();

private:
	ClientHandler* clientHandler;
	void startClientHandler();
	SharedServerHandler* sharedServerHandler;
	void startSharedServerHandler();
};

#endif /* SERVER_H_ */