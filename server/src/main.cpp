
#include "DJayy/WebServer.h"
//#include "DJayy/Programs/iTunesProgram.h"
#include "DJayy/Programs/DummyProgram.h"

#include <stdio.h>
#ifdef _WIN32
	#include <direct.h>
#else
	#include <unistd.h>
#endif

using namespace DJayy;

String getCurrentWorkingDirectory()
{
	char buffer[FILENAME_MAX];
#ifdef _WIN32
	_getcwd(buffer, FILENAME_MAX);
#else
	getcwd(buffer, FILENAME_MAX);
#endif
	return buffer;
}

String getWebRoot()
{
	String workingDir = getCurrentWorkingDirectory();
	char slash = '/';
	size_t lastSlash = workingDir.lastIndexOf('/');
	if(lastSlash == STRING_NOTFOUND)
	{
		lastSlash = workingDir.lastIndexOf('\\');
		slash = '\\';
	}
	return workingDir.substring(0,lastSlash) + slash + "web";
}

int main(int argc, char *argv[])
{
	//iTunesProgram* program = new iTunesProgram();
	DummyProgram* program = new DummyProgram();
	program->loadLibrary();
	
	WebServer server(getWebRoot(), 8080);
	server.setProgramInterface(program);
	server.start();
	
	delete program;

	return 0;
}
