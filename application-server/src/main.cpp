#include "Server.h"
#include <thread>
#include <mutex>

using namespace std;

#define OVER_KEY "exit"

void isItOver(){
	string s
	while (s.compare(OVER_KEY) != 0) {
		cin >> s;
	}
}

int main(){
	//Setup
	Server* server = new Server();
	if (server->isReady())
		server.run();
	isItOver();	
	delete server;
	return 0;
}