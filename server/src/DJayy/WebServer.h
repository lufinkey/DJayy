
#pragma once

#include <server_http.hpp>
#include <string>

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

	private:
		void setup_GET();
		void setup_queue();
		void setup_queuevote();
		void setup_library();

		String webRoot;
		HttpServer*server;
		ProgramInterface*program;
	};
}
