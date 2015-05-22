
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
	}
}
