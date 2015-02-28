
#pragma once

#include <server_http.hpp>
#include <string>
#include "../Util/String.h"

namespace DJayy
{
	class WebServer
	{
	public:
		typedef SimpleWeb::Server<SimpleWeb::HTTP> HttpServer;

		WebServer(const std::string&webRoot, unsigned short port);

		void start();

	private:
		void setup_GET();
		void setup_tracks();

		String webRoot;
		HttpServer*server;
	};
}
