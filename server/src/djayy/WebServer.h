
#pragma once

#include <string>
#include <server_http.hpp>

namespace djayy
{
	class WebServer
	{
	public:
		WebServer(const WebServer&) = delete;
		WebServer& operator=(const WebServer&) = delete;
		
		WebServer(const std::string&root, unsigned short port, size_t numthreads);
		~WebServer();
		
	private:
		typedef SimpleWeb::Server<SimpleWeb::HTTP> HttpServer;
		void addRoute(const std::string& route_regex, const std::string&method, void(WebServer::*function)(HttpServer::Response& response, std::shared_ptr<HttpServer::Request> request));
		void setDefaultRoute(void(WebServer::*function)(HttpServer::Response& response, std::shared_ptr<HttpServer::Request> request));
		
		HttpServer* server;
	};
}
