#include <thread>
#include <mutex>
#include "utils/Logger.h"

#include "SharedServerHandler.h"

using namespace std;


int main(){
	//Setup
	SharedServerHandler* sharedServerHandler = new SharedServerHandler();

	sharedServerHandler->connectToUrl("http://jobify.professional.herokuapp.com", NULL, NULL);
	sharedServerHandler->run();

	delete sharedServerHandler;
	Logger::Instance()->Close();
	return 0;
}
