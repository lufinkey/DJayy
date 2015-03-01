
#pragma once

#include "Queue/Queue.h"
#include "Library/TrackCollection.h"
#include <mutex>

namespace DJayy
{
	class WebServer;
	
	class ProgramInterface
	{
	public:
		ProgramInterface(WebServer*server)
		{
			ProgramInterface::server = server;
		}
		virtual ~ProgramInterface(){}

		virtual void load() = 0;
		
		Queue& getQueue();
		const Queue& getQueue() const;
		WebServer* getWebServer() const;
		void setNowPlaying(const Track&track);
		const Track& getNowPlaying() const;
		
		String addToQueue(const String&track_id);
		
		virtual Track getTrackByTrackID(const String&track_id) const = 0;
		virtual TrackCollection search(const String&query, size_t startIndex, size_t endIndex) const = 0;
		
	protected:
		Queue queue;
		
	private:
		WebServer*server;
		Track nowplaying;
		std::mutex m_lock;
	};
}
