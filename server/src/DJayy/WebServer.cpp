
#include "WebServer.h"

#include "Queue/QueueTrackPacket.h"

#include <fstream>
#include <memory>
#include <iostream>

#include <boost/property_tree/json_parser.hpp>

namespace DJayy
{
	WebServer::WebServer(const std::string&webroot, unsigned short port)
	{
		program = nullptr;
		webRoot = webroot;
		server = new HttpServer(port, 4);

		setup_GET();
		//setup_library();
		setup_queue();
		setup_queuevote();
	}

	void WebServer::setup_GET()
	{
		std::string webRoot((const char*)this->webRoot);
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
				std::streamoff length=ifs.tellg();
				
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

	void WebServer::setup_queue()
	{
		server->resource["^/queue$"]["POST"]=[this](HttpServer::Response& response, std::shared_ptr<HttpServer::Request> request) {
			try
			{
				std::istreambuf_iterator<char> eos;
				std::string str(std::istreambuf_iterator<char>(request->content), eos);
				std::cout << "recieved queue request:" << std::endl << str << std::endl;
				
				String result;
				if(this->program != nullptr)
				{
					const Queue& queue = this->program->getQueue();
					const ArrayList<QueueTrack>& tracks = queue.getTracks();
					result = "{\"queue\":[";
					for(size_t i=0; i<queue.size(); i++)
					{
						QueueTrackPacket packet(tracks.get(i),this->program);
						result += packet.toJson();
						if(i != (tracks.size()-1))
						{
							result += ",";
						}
					}
					result += "]}";
				}
				else
				{
					result = "{\"queue\":[]}";
				}

				std::cout << "Sending queue data:" << std::endl << result << std::endl;

				response << "HTTP/1.1 200 OK\r\nContent-Length: " << result.length() << "\r\n\r\n" << result;
			}
			catch(const std::exception& e)
			{
				response << "HTTP/1.1 400 Bad Request\r\nContent-Length: " << strlen(e.what()) << "\r\n\r\n" << e.what();
			}
		};
	}
	
	void WebServer::setup_queuevote()
	{
		server->resource["^/queuevote$"]["POST"]=[this](HttpServer::Response& response, std::shared_ptr<HttpServer::Request> request) {
			try
			{
				std::istreambuf_iterator<char> eos;
				std::string str(std::istreambuf_iterator<char>(request->content), eos);
				std::cout << "recieved queuevote:" << std::endl << str << std::endl;
				
				boost::property_tree::ptree pt;
				read_json(std::istringstream(str), pt);

				String queue_id = pt.get<std::string>("queue_id");
				String user_id = pt.get<std::string>("user_id");
				signed char vote = (signed char)String::asInt(pt.get<std::string>("vote"));
				long long totalVotes = 0;
				
				if(this->program != nullptr)
				{
					this->program->getQueue().vote(queue_id, user_id, vote);
					const QueueTrack& track = this->program->getQueue().getTrackByQueueID(queue_id);
					totalVotes = track.votes.sum();
					vote = track.votes.getVote(user_id);
				}

				String reply = "{\"queue_id\":\"" + queue_id + "\",\"vote\":" + ((int)vote) + ",\"totalVotes\":" + totalVotes + "}";

				std::cout << "sending queuevote data:" << std::endl << reply << std::endl;
				
				response << "HTTP/1.1 200 OK\r\nContent-Length: " << reply.length() << "\r\n\r\n" << reply;
			}
			catch(const std::exception& e)
			{
				response << "HTTP/1.1 400 Bad Request\r\nContent-Length: " << strlen(e.what()) << "\r\n\r\n" << e.what();
			}
		};
	}

	/*void WebServer::setup_library()
	{
		server->resource["^/library$"]["GET"]=[this](HttpServer::Response& response, std::shared_ptr<HttpServer::Request> request) {
			try
			{
				std::istreambuf_iterator<char> eos;
				std::string str(std::istreambuf_iterator<char>(request->content), eos);
				std::cout << "recieved library request:" << std::endl << str << std::endl;
				
				String result;
				if(this->program != nullptr)
				{
					result = this->program->getLibrary().toJson();
				}
				else
				{
					result = "[]";
				}

				std::cout << "Sending library data:" << std::endl << result << std::endl;

				response << "HTTP/1.1 200 OK\r\nContent-Length: " << result.length() << "\r\n\r\n" << result;
			}
			catch(const std::exception& e)
			{
				response << "HTTP/1.1 400 Bad Request\r\nContent-Length: " << strlen(e.what()) << "\r\n\r\n" << e.what();
			}
		};
	}*/

	void WebServer::setProgramInterface(ProgramInterface*programInterface)
	{
		program = programInterface;
	}
	
	void WebServer::start()
	{
		std::cout << "starting web server" << std::endl;
		server->start();
	}
}
