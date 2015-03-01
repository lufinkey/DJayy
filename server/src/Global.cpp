
#include "Global.h"

namespace DJayy
{
	PrefManager Global::config = PrefManager();
	
	void Global::init()
	{
		Global::config.addValue("port", (String)"" + 8080);
		Global::config.addValue("vote_queue_boost", (String)"" + 5);
		Global::config.addValue("vote_queue_remove", (String)"" + (-5));
		Global::config.loadFromFile("config.ini",true);
	}
}
