
#include "DummyProgram.h"

namespace DJayy
{
	DummyProgram::DummyProgram(WebServer*server) : ProgramInterface(server)
	{
		//
	}
	
	void DummyProgram::load()
	{
		Track track1;
		track1.track_id = "aa3";
		track1.title = "Power";
		track1.artist = "Kanye West";
		track1.album = "My Beautiful Dark Twisted Fantasy";
		track1.album_artist = "Kanye West";

		Track track2;
		track2.track_id = "bc2";
		track2.title = "Somatic Serenade";
		track2.artist = "Bluetech";
		track2.album = "Matt please add album name";
		track2.album_artist = "Bluetech";

		Track track3;
		track3.track_id = "7e2";
		track3.title = "Kick the Rock!";
		track3.artist = "Hunnid-P";
		track3.album = "Sonic Adventure 2 Multi-Dimensional Original Soundtrack";
		track3.album_artist = "Various Artists";

		Track track4;
		track4.track_id = "da3";
		track4.title = "Power";
		track4.artist = "Kanye West";
		track4.album = "My Beautiful Dark Twisted Fantasy";
		track4.album_artist = "Kanye West";

		Track track5;
		track5.track_id = "ec5";
		track5.title = "Somatic Serenade";
		track5.artist = "Bluetech";
		track5.album = "Matt please add album name";
		track5.album_artist = "Bluetech";

		Track track6;
		track6.track_id = "fe2";
		track6.title = "Kick the Rock!";
		track6.artist = "Hunnid-P";
		track6.album = "Sonic Adventure 2 Multi-Dimensional Original Soundtrack";
		track6.album_artist = "Various Artists";

		Track track7;
		track7.track_id = "ga3";
		track7.title = "Power";
		track7.artist = "Kanye West";
		track7.album = "My Beautiful Dark Twisted Fantasy";
		track7.album_artist = "Kanye West";

		Track track8;
		track8.track_id = "hc8";
		track8.title = "Somatic Serenade";
		track8.artist = "Bluetech";
		track8.album = "Matt please add album name";
		track8.album_artist = "Bluetech";

		Track track9;
		track9.track_id = "ie2";
		track9.title = "Kick the Rock!";
		track9.artist = "Hunnid-P";
		track9.album = "Sonic Adventure 2 Multi-Dimensional Original Soundtrack";
		track9.album_artist = "Various Artists";
		
		library.add(track1);
		library.add(track2);
		library.add(track3);
		library.add(track4);
		library.add(track5);
		library.add(track6);
		library.add(track7);
		library.add(track8);
		library.add(track9);

		//this shouldn't be put here; this is just for testing
		queue.add(track1.track_id);
		queue.add(track2.track_id);
		queue.add(track3.track_id);
		queue.add(track1.track_id);
		queue.add(track2.track_id);
		queue.add(track1.track_id);
		queue.add(track3.track_id);
		queue.add(track2.track_id);
		queue.add(track3.track_id);
		queue.add(track1.track_id);
		queue.add(track3.track_id);
		queue.add(track3.track_id);
		queue.add(track2.track_id);
		queue.add(track1.track_id);
		queue.add(track3.track_id);
		queue.add(track3.track_id);
		queue.add(track2.track_id);
		queue.add(track3.track_id);
		queue.add(track1.track_id);
		queue.add(track3.track_id);
		queue.add(track3.track_id);
		queue.add(track2.track_id);
		queue.add(track1.track_id);
		queue.add(track3.track_id);
	}
	
	Track DummyProgram::getTrackByTrackID(const String&track_id) const
	{
		return library.getTrackByTrackID(track_id);
	}
	
	TrackCollection DummyProgram::search(const String&query, size_t startIndex, size_t endIndex) const
	{
		return library;
	}
}
