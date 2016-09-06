#ifndef SHAREDSERVERHANDLER_H_
#define SHAREDSERVERHANDLER_H_

class Server {
public:
	Server();

	virtual ~Server();

    bool isRunning();

    void run();

private:
	bool runnning;
    struct mg_mgr manager; //Se usa si va con Mongoose 
};

#endif /* SHAREDSERVERHANDLER_H_ */