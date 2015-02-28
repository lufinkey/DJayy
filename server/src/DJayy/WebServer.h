
#pragma once

#include <server_http.hpp>
#include <string>

namespace DJayy
{
	class WebServer
	{
	public:
		typedef SimpleWeb::Server<SimpleWeb::HTTP> HttpServer;

		WebServer(const std::string&webRoot, unsigned int port);

		void start();

	private:
		HttpServer*server;
	};
}
