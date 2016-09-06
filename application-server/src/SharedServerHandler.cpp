#include "SharedServerHandler.h"

SharedServerHandler::SharedServerHandler(){
	//setear running
}

SharedServerHandler::~SharedServerHandler() {
   mg_mgr_free(&manager);
}

SharedServerHandler::isRunning(){
	return SharedServerHandler::running;
}

void SharedServerHandler::run() {
	while(running)
}