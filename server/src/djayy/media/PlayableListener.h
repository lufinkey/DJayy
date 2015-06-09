
#pragma once

namespace djayy
{
	class Playable;
	
	class PlayableListener
	{
	public:
		virtual ~PlayableListener(){}
		
		virtual void onPlay(Playable* playable) = 0;
		virtual void onPause(Playable* playable) = 0;
		virtual void onStop(Playable* playable) = 0;
		virtual void onSeek(Playable* playable, double position) = 0;
		virtual void onFinish(Playable* playable) = 0;
	};
}
