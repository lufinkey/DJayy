
#include "DJayy.h"
#include "WebUtils.h"
#include <server_http.hpp>
#include <fstream>
#include <iostream>

namespace djayy
{
	typedef SimpleWeb::Server<SimpleWeb::HTTP> HttpServer;
	typedef HttpServer::Response Response;
	typedef HttpServer::Request Request;
	
	void DJayy_respond_with(HttpServer::Response& response, const std::string& header, FILE*file)
	{
		std::fseek(file, 0, SEEK_END);
		size_t length = std::ftell(file);
		std::fseek(file, 0, SEEK_SET);
		
		response << header << "\r\nContent-Length: " << length << "\r\n\r\n";
		
		size_t buffer_size=131072;
		if(length>buffer_size)
		{
			char* buffer = new char[length];
			size_t read_length;
			while((read_length=std::fread(buffer, sizeof(char), buffer_size, file))>0)
			{
				response.stream.write(buffer, read_length);
				response << HttpServer::flush;
			}
			delete buffer;
		}
		else
		{
			char* buffer = new char[length];
			std::fread(buffer, sizeof(char), length, file);
			response.stream.write(buffer, length);
			response << HttpServer::flush;
			delete buffer;
		}
	}
	
	std::string DJayy_determine_mime_type(const std::string& extension)
	{
		if(extension == "" || extension=="txt")
		{
			return "text/plain";
		}
		else if(extension == "html" || extension == "htm")
		{
			return "text/html";
		}
		else if(extension == "css")
		{
			return "text/css";
		}
		else if(extension == "js")
		{
			return "text/javascript";
		}
		else
		{
			return "";
		}
	}
	
	void DJayy_respond_with(HttpServer::Response& response, const std::string& header, const std::string&content)
	{
		response << header << "\r\nContent-Length: " << content.length() << "\r\n\r\n";
		response.stream.write(content.c_str(), content.length());
	}
	
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
			FILE* file = nullptr;
			std::string actualpath;
			bool success = webutils::path_open(fullpath, this->indexes, &file, &actualpath);
			if(success)
			{
				DJayy_respond_with(response, "HTTP/1.1 200 OK", file);
				std::fclose(file);
			}
			else
			{
				std::string path404 = webutils::path_combine(this->web_root, "404.html");
				success = webutils::path_open_asfile(path404, &file);
				if(success)
				{
					DJayy_respond_with(response, "HTTP/1.1 400 Bad Request\r\nContent-Type: text/html", file);
					std::fclose(file);
				}
				else
				{
					DJayy_respond_with(response, "HTTP/1.1 400 Bad Request", "Could not open file "+request->path);
				}
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
		if(!server_running)
		{
			server_running = true;
			((HttpServer*)server)->start();
			server_running = false;
		}
		else
		{
			throw std::logic_error("server is already running");
		}
	}
	
	void DJayy::stop()
	{
		if(server_running)
		{
			((HttpServer*)server)->stop();
			server_running = false;
		}
		else
		{
			throw std::logic_error("server is not running");
		}
	}
}
