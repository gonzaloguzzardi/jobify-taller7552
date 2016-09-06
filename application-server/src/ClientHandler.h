#ifndef CLIENTHANDLER_H
#define CLIENTHANDLER_H

#include <sstream>
#include <string>
#include "../src/3rdparty/mongoose/mongoose.h"

#define DEFAULT_PORT 8000
#define POLL_MILISECONDS 1000

class ClientHandler {
    public:
        ClientHandler();
	
        virtual ~ClientHandler();

        bool isRunning();
	
        void run();
    
    private:
        static void handleEvent(struct mg_connection* connection, int event, void* eventData);
        bool runnning;
        struct mg_mgr manager;
        struct mg_connection* connection;
};

#endif // CLIENTHANDLER_H