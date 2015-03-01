
#pragma once

#include <server_http.hpp>
#include <string>
#include <mutex>

#include "ProgramInterface.h"

namespace DJayy
{
	class WebServer
	{
	public:
		typedef SimpleWeb::Server<SimpleWeb::HTTP> HttpServer;

		WebServer(const std::string&webRoot, unsigned short port);

		void setProgramInterface(ProgramInterface*program);

		void start();
		
		std::mutex& getMutex();

	private:
		void setup_GET();
		void setup_queue();
		void setup_queuevote();
		void setup_search();
		void setup_addqueue();
		void setup_nowplaying();

		String webRoot;
		HttpServer*server;
		ProgramInterface*program;
		std::mutex m_lock;
	};
}
