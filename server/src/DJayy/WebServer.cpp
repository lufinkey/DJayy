
#include "WebServer.h"

#include <fstream>
#include <memory>
#include <iostream>

namespace DJayy
{
	WebServer::WebServer(const std::string&webRoot, unsigned short port)
	{
		server = new HttpServer(port, 4);

		server->default_resource["GET"]=[webRoot](HttpServer::Response& response, std::shared_ptr<HttpServer::Request> request) {
			std::string filename=webRoot;
			
			std::string path=request->path;
			
			//Replace all ".." with "." (so we can't leave the web-directory)
			size_t pos;
			while((pos=path.find(".."))!=std::string::npos)
			{
				path.erase(pos, 1);
			}
			
			filename+=path;
			std::ifstream ifs;
			//A simple platform-independent file-or-directory check do not exist, but this works in most of the cases:
			if(filename.find('.')==std::string::npos)
			{
				if(filename[filename.length()-1]!='/')
				{
					filename+='/';
				}
				filename+="index.html";
			}
			ifs.open(filename, std::ifstream::in);
			
			if(ifs)
			{
				ifs.seekg(0, std::ios::end);
				size_t length=ifs.tellg();
			
				ifs.seekg(0, std::ios::beg);

				std::string str((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());

				response << "HTTP/1.1 200 OK\r\nContent-Length: " << str.length() << "\r\n\r\n" << str.c_str();
			
				//read and send 128 KB at a time if file-size>buffer_size
				/*size_t buffer_size=131072;
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
				}*/

				ifs.close();
			}
			else
			{
				std::string content="Could not open file "+filename;
				response << "HTTP/1.1 400 Bad Request\r\nContent-Length: " << content.length() << "\r\n\r\n" << content;
			}
		};
	}
	
	void WebServer::start()
	{
		server->start();
	}
}
