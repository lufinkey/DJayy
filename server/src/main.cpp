
#include "DJayy/WebServer.h"

using namespace DJayy;

int main(int argc, char *argv[])
{
	WebServer server("../web", 8080);
	server.start();

	std::system("PAUSE");

	return 0;
}
