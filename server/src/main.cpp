
#define _CRT_SECURE_NO_WARNINGS

#include "DJayy/WebServer.h"
#include "DJayy/Programs/WinampProgram.h"
//#include "DJayy/Programs/DummyProgram.h"

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
	String homeDir = getenv("HOMEPATH");
	ArrayList<String> fileExtensions;
	fileExtensions.add("mp3");
	fileExtensions.add("m4a");
	fileExtensions.add("aac");

	WebServer server(getWebRoot(), 8080);
	WinampProgram* program = new WinampProgram(&server, homeDir + "/Music", fileExtensions);
	program->load();
	server.setProgramInterface(program);
	server.start();
	
	delete program;

	return 0;
}
