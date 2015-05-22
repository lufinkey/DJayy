
#include "DJayy.h"
#include <server_http.hpp>

namespace djayy
{
	typedef SimpleWeb::Server<SimpleWeb::HTTP> HttpServer;
	typedef HttpServer::Response Response;
	typedef HttpServer::Request Request;
	
	DJayy::DJayy(const std::string& web_root, unsigned short port, size_t num_threads, size_t timeout_request, size_t timeout_content)
		: web_root(web_root),
		server_running(false),
		server((void*)(new HttpServer(port, num_threads, timeout_request, timeout_content)))
	{
		//
	}
	
	DJayy::~DJayy()
	{
		stop();
		delete server;
	}
	
	void DJayy::start()
	{
		server_mutex.lock();
		if(!server_running)
		{
			((HttpServer*)server)->start();
			server_running = true;
		}
		else
		{
			server_mutex.unlock();
			throw std::logic_error("server is already running");
		}
		server_mutex.unlock();
	}
	
	void DJayy::stop()
	{
		server_mutex.lock();
		if(server_running)
		{
			((HttpServer*)server)->stop();
			server_running = false;
		}
		else
		{
			server_mutex.unlock();
			throw std::logic_error("server is not running");
		}
		server_mutex.unlock();
	}
}
