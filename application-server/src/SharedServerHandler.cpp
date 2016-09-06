#include "SharedServerHandler.h"
#include "utils/Logger.h"
#include "sstream"

int SharedServerHandler::s_exit_flag = 0;
std::string SharedServerHandler::s_url = "";

SharedServerHandler::SharedServerHandler(): m_running(false),
											m_maxSleepTime(DEFAULT_MAX_SLEEPTIME)
{
	m_nc = NULL;

	mg_mgr_init(&m_manager, NULL);

	//m_manager.user_data = this;
}

SharedServerHandler::~SharedServerHandler()
{
   mg_mgr_free(&m_manager);
}

bool SharedServerHandler::isRunning()
{
	m_running = (s_exit_flag == 0? true: false);
	return m_running;
}

void SharedServerHandler::connectToUrl(const std::string& url, const char* extraHeader, const char* postData)
{
	s_url = url;

	//Se conecta a la url especificada
	m_nc = mg_connect_http(&m_manager, eventHandler, s_url.c_str(), extraHeader, postData);
	mg_set_protocol_http_websocket(m_nc);

	printConnectingMsg();
}

void SharedServerHandler::run()
{
	while(isRunning())
	{
		mg_mgr_poll(&m_manager, m_maxSleepTime);
	}
}

void SharedServerHandler::eventHandler(struct mg_connection* connection, int event, void* eventData)
{
	struct http_message *hm = (struct http_message *) eventData;
	int connectionStatus;

	//utilizado para informar sobre el body de la pagina. No se puede declarar dentro de switch
	std::string bodyMessage;

	switch (event)
	{
		case MG_EV_CONNECT:
			connectionStatus = *(int *) eventData;
			if (connectionStatus != 0)
			{
				std::stringstream ss;
				ss << "Error connecting to " << s_url.c_str() << ": " << strerror(connectionStatus) << "\n";
				printf("Error connecting to %s: %s\n", s_url.c_str(), strerror(connectionStatus));
				Logger::Instance()->Log(ss.str(), LOGTYPE_ERROR);
				s_exit_flag = 1;
			}
			else
			{
				std::stringstream ss;
				ss << "Connected to " << s_url.c_str() << ".\n";
				printf("Connected to %s.\n", s_url.c_str());
				Logger::Instance()->Log(ss.str(), LOGTYPE_INFO);
			}
			break;

		case MG_EV_HTTP_REPLY:
			bodyMessage = std::string(hm->body.p, (int) hm->body.len);
			Logger::Instance()->Log(bodyMessage, LOGTYPE_INFO);
			printf("Got reply:\n%.*s\n", (int) hm->body.len, hm->body.p);

			connection->flags |= MG_F_SEND_AND_CLOSE;
			s_exit_flag = 1;
			break;

		default:
			break;
	}
}

void SharedServerHandler::printConnectingMsg()
{
	std::stringstream ss;
	ss << "Connecting to " << s_url.c_str() << "\n";
	Logger::Instance()->Log(ss.str(), LOGTYPE_INFO);
	printf("Connecting to %s\n", s_url.c_str());
}

