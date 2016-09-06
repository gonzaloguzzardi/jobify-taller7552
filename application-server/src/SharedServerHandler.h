#ifndef SHAREDSERVERHANDLER_H_
#define SHAREDSERVERHANDLER_H_

#include "../src/3rdparty/mongoose/mongoose.h"
#include <string>

#define DEFAULT_MAX_SLEEPTIME 1000

class SharedServerHandler {
public:
	SharedServerHandler();

	virtual ~SharedServerHandler();



	/* ConnectToUrl
	 *
	 * url: URL al cual intentara conectarse
	 *
	 * postData: si es NULL, se crea un GET request. En caso contrario se crea un POST request
	 * 			 con los datos pasados como parametro (se debe pasar los extra header correspondientes).
	 */
	void connectToUrl(const std::string& url, const char* extraHeader, const char* postData);

    bool isRunning();

    void run();


private:

	bool m_running;

	//maximo tiempo que puede dormir entre polls, en milisegundos
	int m_maxSleepTime;

    //variables de mangoose
    struct mg_mgr m_manager; //Se usa si va con Mongoose
    struct mg_connection *m_nc;

    void printConnectingMsg();

    //variables estaticas que se usan en el event handler
    static void eventHandler(struct mg_connection* connection, int event, void* eventData);
    static int s_exit_flag;
    static std::string s_url;

};

#endif /* SHAREDSERVERHANDLER_H_ */
