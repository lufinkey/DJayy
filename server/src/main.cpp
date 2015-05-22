
#include "djayy/DJayy.h"

int main(int argc, char* argv[])
{
	djayy::DJayy* dj = new djayy::DJayy("../web", 8080, 4);
	dj->start();
	return 0;
}
