
#include "WebUtils.h"
#include <iomanip>
#include <sstream>

namespace djayy
{
	namespace webutils
	{
		std::string urlencode(const std::string& value)
		{
			std::ostringstream escaped;
			escaped.fill('0');
			escaped << std::hex;

			for (std::string::const_iterator i = value.begin(), n = value.end(); i != n; ++i)
			{
				std::string::value_type c = (*i);
				
				// Keep alphanumeric and other accepted characters intact
				if (isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~')
				{
					escaped << c;
				}
				// Any other characters are percent-encoded
				else
				{
					escaped << '%' << std::setw(2) << int((unsigned char)c);
				}
			}
			
			return escaped.str();
		}
		
		std::string urldecode(const std::string& value)
		{
			std::ostringstream unescaped;
			
			for (std::string::const_iterator i = value.begin(), n = value.end(); i != n; i++)
			{
				std::string::value_type c = (*i);
				
				if(c == '+')
				{
					unescaped << ' ';
				}
				else if(c == '%')
				{
					char hex_val[3] = {0,0,0};
					bool cancelled = false;
					for(size_t j = 0; j < 2; j++)
					{
						i++;
						if(i == n)
						{
							unescaped << '%' << hex_val;
							j = 2;
							cancelled = true;
						}
						else
						{
							std::string::value_type c2 = (*i);
							if((c2 >= '0' && c<='9') || (c>='a' && c<='f') || (c>='A' && c<='F'))
							{
								hex_val[j] = c2;
							}
							else
							{
								unescaped << '%' << hex_val << c2;
								j = 2;
								cancelled = true;
							}
						}
					}
					if(!cancelled)
					{
						std::stringstream ss;
						ss << std::hex << hex_val;
						int val = 0;
						ss >> val;
						unescaped << ((std::string::value_type)val);
					}
				}
				else
				{
					unescaped << c;
				}
			}
			return unescaped.str();
		}
		
		std::vector<std::string> string_split(const std::string&str, std::string::value_type deliminator)
		{
			std::vector<std::string> tokens;
			size_t token_start = 0;
			size_t length = str.length();
			for(size_t i=0; i<length; i++)
			{
				std::string::value_type c = str.at(i);
				if(c == deliminator)
				{
					if(i != 0)
					{
						tokens.push_back(str.substr(token_start, i-token_start));
					}
					token_start = i+1;
				}
			}
			if(token_start != length)
			{
				tokens.push_back(str.substr(token_start, length-token_start));
			}
			return tokens;
		}
		
		std::string path_clean_backward_token(const std::string& path)
		{
			std::vector<std::string> path_tokens = webutils::string_split(path, '/');
			std::ostringstream cleansed_path;
			if(path.length()>0 && path.at(0) == '/')
			{
				cleansed_path << '/';
			}
			for(size_t i=0, length=path_tokens.size(), last=(length-1); i<length; i++)
			{
				const std::string token = path_tokens.at(i);
				bool non_period = false;
				for(size_t j=0, tok_length=token.length(); j<tok_length; j++)
				{
					std::string::value_type c = token.at(j);
					if(c != '.')
					{
						non_period = true;
						j = tok_length;
					}
				}
				if(token.length() == 0)
				{
					non_period = true;
				}
				if(!non_period)
				{
					cleansed_path << '.';
				}
				if(i != last)
				{
					cleansed_path << '/';
				}
			}
			if(path.length()>1 && path.at(path.length() - 1) == '/')
			{
				cleansed_path << '/';
			}
			return cleansed_path.str();
		}
		
		std::string path_combine(const std::string& root, const std::string& path)
		{
			size_t root_length = root.length();
			size_t path_length = path.length();
			if(root_length > 0)
			{
				std::string::value_type root_last = root.at(root_length-1);
				if(root_last=='/' || root_last=='\\')
				{
					if(path_length > 0)
					{
						std::string::value_type path_first = path.at(0);
						if(path_first=='/' || path_first=='\\')
						{
							return root + path.substr(1, path_length-1);
						}
						else
						{
							return root + path;
						}
					}
					else
					{
						return root;
					}
				}
				else if(path_length > 0)
				{
					std::string::value_type path_first = path.at(0);
					if(path_first=='/' || path_first=='\\')
					{
						return root + path;
					}
					else
					{
						return root + '/' + path;
					}
				}
				else
				{
					return root;
				}
			}
			else
			{
				if(path_length > 0)
				{
					std::string::value_type path_first = path.at(0);
					if(path_first=='/' || path_first=='\\')
					{
						return "." + path;
					}
					else
					{
						return "./" + path;
					}
				}
				else
				{
					return root;
				}
			}
		}
		
		bool path_open_asdir(const std::string& path, const std::vector<std::string>& indexes, std::ifstream* input_stream)
		{
			size_t i=0;
			size_t indexes_size = indexes.size();
			bool succeeded = false;
			while(!succeeded && i<indexes_size)
			{
				bool failed = false;
				std::string filepath = webutils::path_combine(path, indexes[i]);
				try
				{
					input_stream->open(filepath, std::ifstream::in);
				}
				catch(const std::ios_base::failure&)
				{
					failed = true;
				}
				if(!failed && input_stream->good())
				{
					succeeded = true;
				}
				i++;
			}
			if(succeeded)
			{
				return true;
			}
			return false;
		}
		
		bool path_open_asfile(const std::string& path, std::ifstream* input_stream)
		{
			bool failed = false;
			try
			{
				input_stream->open(path, std::ifstream::in);
			}
			catch(const std::ios_base::failure&)
			{
				failed = true;
			}
			if(!failed && input_stream->good())
			{
				return true;
			}
			return false;
		}
		
		bool path_open(const std::string& path, const std::vector<std::string>& indexes, std::ifstream* input_stream)
		{
			if(input_stream == nullptr)
			{
				throw std::invalid_argument("input_stream: null");
			}
			else if(input_stream->is_open())
			{
				throw std::invalid_argument("input_stream: is open");
			}
			
			bool is_dir = false;
			size_t path_length = path.length();
			if(path_length > 0)
			{
				std::string::value_type path_last = path.at(path_length-1);
				if(path_last=='/' || path_last=='\\')
				{
					is_dir = true;
				}
			}
			
			if(is_dir)
			{
				if(path_open_asdir(path, indexes, input_stream))
				{
					return true;
				}
				else if(path_length>1)
				{
					return path_open_asfile(path.substr(0, path_length-1), input_stream);
				}
				return false;
			}
			else
			{
				bool succeeded = path_open_asfile(path, input_stream);
				if(succeeded)
				{
					return true;
				}
				return path_open_asdir(path, indexes, input_stream);
			}
		}
		
		std::string http_build_query(const std::map<std::string, std::string>& query_data)
		{
			std::ostringstream query_string;
			std::map<std::string, std::string>::const_iterator begin = query_data.begin();
			std::map<std::string, std::string>::const_iterator end=query_data.end();
			for(std::map<std::string, std::string>::const_iterator it=begin; it != end; it++)
			{
				if(it != begin)
				{
					query_string << '&';
				}
				query_string << urlencode(it->first) << '=' << urlencode(it->second);
			}
			return query_string.str();
		}
		
		std::map<std::string, std::string> parse_querystring(const std::string& query_string)
		{
			std::map<std::string, std::string> params;
			std::vector<std::string> pairs = string_split(query_string, '&');
			size_t pairs_length = pairs.size();
			for(size_t i=0; i<pairs_length; i++)
			{
				std::vector<std::string> key_value = string_split(pairs[i], '=');
				if(key_value.size() > 0)
				{
					if(key_value.size() < 2)
					{
						params[urldecode(key_value[0])] = "";
					}
					else
					{
						params[urldecode(key_value[0])] = urldecode(key_value[1]);
					}
				}
			}
			return params;
		}
	}
}
