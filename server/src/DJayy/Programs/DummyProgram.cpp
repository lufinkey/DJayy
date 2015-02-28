
#include "DummyProgram.h"

namespace DJayy
{
	DummyProgram::DummyProgram()
	{
		//
	}
	
	void DummyProgram::loadLibrary()
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
		
		library.add(track1);
		library.add(track2);
		library.add(track3);

		//this shouldn't be put here; this is just for testing
		queue.add(track1.track_id);
		queue.add(track2.track_id);
		queue.add(track3.track_id);
	}
}
