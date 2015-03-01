
#include "Global.h"

namespace DJayy
{
	PrefManager Global::config = PrefManager();
	
	void Global::init()
	{
		Global::config.loadFromFile("config.ini",true);
	}
}
