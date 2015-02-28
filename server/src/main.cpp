
#include "DJayy/WebServer.h"

using namespace DJayy;

int main(int argc, char *argv[])
{
	WebServer* server = new WebServer("../web", 8080);

	std::system("PAUSE");

	return 0;
}
