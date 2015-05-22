
#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <stdexcept>

namespace djayy
{
	namespace webutils
	{
		std::string urlencode(const std::string& value);
		std::string urldecode(const std::string& value);
		
		std::vector<std::string> string_split(const std::string& str, std::string::value_type deliminator);
		
		std::string path_clean_backward_token(const std::string& path);
		std::string path_combine(const std::string& root, const std::string& path);
		
		bool path_open(const std::string& path, const std::vector<std::string>& indexes, std::ifstream* input_stream);
	}
}
