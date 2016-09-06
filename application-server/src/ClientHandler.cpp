#include "ClientHandler.h"

ClientHandler::ClientHandler(){
	mg_mgr_init(&manager, NULL);
    std::string port;
	intToString(DEFAULT_PORT, port);
	printf("Starting server on port %s\n", port);
	connection = mg_bind(&manager, port.c_str(), eventHandler);
    if (connection == NULL){
    	printf("Failed to create listener\n");
    	running = false;
    }
    mg_set_protocol_http_websocket(connection);
    //mg_enable_multithreading(connection);
    running = true;
}

ClientHandler::~ClientHandler() {
   mg_mgr_free(&manager);
}

ClientHandler::isRunning(){
	return ClientHandler::running;
}

void ClientHandler::eventHandler(struct mg_connection* connection, int event, void* eventData) {
	
	struct http_message *httpMsg = (struct http_message *) eventData;

	switch (event) {
		case MG_EV_HTTP_REQUEST:
			mg_send_head(connection, 200, httpMsg.message.len, "Content-Type: text/plain");
			mg_printf(connection, "%.*s", httpMsg.message.len, httpMsg.message.eventData);
			break;
		default:
			break;
	}
}


void ClientHandler::run() {
	while(running)
		mg_mgr_poll(&manager, POLL_MILISECONDS);	
}

