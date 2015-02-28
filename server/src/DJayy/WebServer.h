
#pragma once

#include <server_http.hpp>
#include <string>

#include "../Util/String.h"

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

		String webRoot;
		HttpServer*server;
		ProgramInterface*program;
	};
}
