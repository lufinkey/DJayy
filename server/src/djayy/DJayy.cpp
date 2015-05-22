
#include "DJayy.h"
#include "WebUtils.h"
#include <server_http.hpp>
#include <fstream>

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
		indexes.resize(4);
		indexes[0] = "index.html";
		indexes[1] = "index.htm";
		indexes[2] = "home.html";
		indexes[3] = "home.htm";
		
		HttpServer* httpserver = (HttpServer*)server;
		httpserver->default_resource["GET"] = [this](HttpServer::Response& response, std::shared_ptr<HttpServer::Request> request){
			std::string path = webutils::path_clean_backward_token(request->path);
			std::string fullpath = webutils::path_combine(this->web_root, path);
			std::ifstream ifs;
			bool success = webutils::path_open(fullpath, this->indexes, &ifs);
			if(success && ifs)
			{
				ifs.seekg(0, std::ios::end);
				std::streamoff length=ifs.tellg();
				ifs.seekg(0, std::ios::beg);
				
				response << "HTTP/1.1 200 OK\r\nContent-Length: " << length << "\r\n\r\n";
				
				size_t buffer_size=131072;
				if(length>buffer_size)
				{
					std::vector<char> buffer(buffer_size);
					size_t read_length;
					while((read_length=ifs.read(&buffer[0], buffer_size).gcount())>0)
					{
						response.stream.write(&buffer[0], read_length);
						response << HttpServer::flush;
					}
				}
				else
				{
					response << ifs.rdbuf();
				}

				ifs.close();
			}
			else
			{
				if(ifs.is_open())
				{
					ifs.close();
				}
				std::string content = "Could not open file " + request->path;
				response << "HTTP/1.1 400 Bad Request\r\nContent-Length: " << content.length() << "\r\n\r\n" << content;
			}
		};
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
