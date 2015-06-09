
#pragma once

#include <string>

namespace djayy
{
	class MusicFile
	{
		friend class MusicEventHandler;
	public:
		MusicFile();
		MusicFile(const MusicFile&) = delete;
		~MusicFile();
		MusicFile& operator=(const MusicFile&) = delete;
		
		bool openFromFile(const std::string& path, std::string*error);
		bool openFromFile(const std::wstring& path, std::string*error);
		void close();
		
		void play();
		void pause();
		void stop();
		void wait();
		void setPosition(double position);
		double getPosition() const;
		
	private:
		void* musicdata;
	};
}
