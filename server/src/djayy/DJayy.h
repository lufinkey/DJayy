
#pragma once

#include <string>
#include <mutex>
#include <stdexcept>

namespace djayy
{
	class DJayy
	{
	public:
		DJayy(const DJayy&) = delete;
		DJayy& operator=(const DJayy&) = delete;
		
		DJayy(const std::string& web_root, unsigned short port, size_t num_threads=1U, size_t timeout_request=5U, size_t timeout_content=300U);
		virtual ~DJayy();
		
		void start();
		void stop();
		
	private:
		std::string web_root;
		void* server;
		std::mutex server_mutex;
		bool server_running;
	};
}
