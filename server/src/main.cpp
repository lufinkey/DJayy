
#include "server_http.hpp"
#include "client_http.hpp"

#include <fstream>
#include <memory>

typedef SimpleWeb::Server<SimpleWeb::HTTP> HttpServer;
typedef SimpleWeb::Client<SimpleWeb::HTTP> HttpClient;

int main(int argc, char *argv[])
{
	HttpServer server(8080, 4);

	server.resource["^/string$"]["POST"]=[](HttpServer::Response& response, std::shared_ptr<HttpServer::Request> request) {
		stringstream ss;
		request->content >> ss.rdbuf();
		string content=ss.str();
        
		response << "HTTP/1.1 200 OK\r\nContent-Length: " << content.length() << "\r\n\r\n" << content;
	};

	return 0;
}
