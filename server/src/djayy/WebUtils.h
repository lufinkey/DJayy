
#pragma once

#include <fstream>
#include <map>
#include <string>
#include <vector>
#include <stdexcept>

namespace djayy
{
	namespace webutils
	{
		template<typename T, typename U>
		bool isset(const std::map<T, U>& map, const T& key)
		{
			try
			{
				map.at(key);
			}
			catch(const std::out_of_range&)
			{
				return false;
			}
			return true;
		}
		
		std::string urlencode(const std::string& value);
		std::string urldecode(const std::string& value);
		
		std::vector<std::string> string_split(const std::string& str, std::string::value_type deliminator);
		
		std::string path_clean_backward_token(const std::string& path);
		std::string path_combine(const std::string& root, const std::string& path);
		std::string path_fileextension(const std::string& path);
		bool path_open_asfile(const std::string& path, FILE** file, std::string* fullpath=nullptr);
		bool path_open_asdir(const std::string& path, const std::vector<std::string>& indexes, FILE** file, std::string* fullpath=nullptr);
		bool path_open(const std::string& path, const std::vector<std::string>& indexes, FILE** file, std::string* fullpath=nullptr);
		
		std::string http_build_query(const std::map<std::string, std::string>& query_data);
		std::map<std::string, std::string> parse_querystring(const std::string& query_string);
	}
}
