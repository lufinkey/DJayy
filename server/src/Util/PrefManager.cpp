
#define _CRT_SECURE_NO_WARNINGS

#include "PrefManager.h"

#if defined(__APPLE__)
	#include "TargetConditionals.h"
#endif

PrefManager::PrefManager()
{
#if defined(TARGET_OS_IPHONE) || defined(TARGET_IPHONE_SIMULATOR) || defined (__ANDROID__)
	char*path = getenv("HOME");
	if(path==NULL)
	{
		Console::WriteLine("Error getting home directory");
	}
	else
	{
		prefPath = path;
		prefPath += "/Library/Preferences/";
		//TODO change prefpath for android
	}
#else
	prefPath = "";
#endif
}
	
PrefManager::~PrefManager()
{
	prefs.clear();
}
	
bool PrefManager::loadFromFile(const String&fileName, bool dynamic)
{
	ArrayList<String> lines;
		
	FILE*file = std::fopen(prefPath + fileName, "rb");
	if(file==NULL)
	{
		return false;
	}
	else
	{
		std::fseek(file,0,SEEK_END);
		size_t total = (size_t)std::ftell(file);
		std::fseek(file,0,SEEK_SET);
		char*fileText = new char[total+1];
		fileText[total] = '\0';
		std::fread(fileText,1,total+1, file);
		String currentLine = "";
		for(size_t i=0; i<total; i++)
		{
			char c = fileText[i];
			if(c!='\0' && ((int)c)>=0)
			{
				currentLine+=c;
			}
			if(c=='\n' || c=='\r' || c=='\0' || ((int)c)<0 || i==(total-1))
			{
				if(currentLine.length()>1)
				{
					lines.add(currentLine);
				}
				currentLine.clear();
			}
		}
		delete[] fileText;
	}
		
	for(size_t i=0; i<lines.size(); i++)
	{
		String line = lines.get(i);
			
		String name;
		String value;
			
		bool leftSide = true;
		
		for(size_t j=0; j<line.length(); j++)
		{
			char c = line.charAt(j);
			if(leftSide)
			{
				if(c=='=')
				{
					leftSide = false;
				}
				else
				{
					name+=c;
				}
			}
			else
			{
				if(c=='=')
				{
					leftSide = true;
					j = line.length();
				}
				else if(c!='\n' && c!='\r')
				{
					value+=c;
				}
			}
		}
			
		if(!leftSide)
		{
			name = name.trim();
			value = value.trim();
				
			if(name.charAt(0)=='\"' && name.charAt(name.length()-1)=='\"')
			{
				name = name.substring(1,name.length()-1);
			}
			if(value.charAt(0)=='\"' && value.charAt(value.length()-1)=='\"')
			{
				value = value.substring(1,value.length()-1);
			}
				
			if (dynamic)
			{
				addValue(name, value);
			}
			else
			{
				setValue(name,value);
			}
		}
	}
		
	if(file!=NULL)
	{
		std::fclose(file);
	}
	return true;
}
	
bool PrefManager::saveToFile(const String&fileName) const
{
	FILE*file = std::fopen(prefPath + fileName, "w");
	if(file == NULL)
	{
		return false;
	}
		
	for(size_t i=0; i<prefs.size(); i++)
	{
		const Pref&pref = prefs.get(i);
		String buf = pref.name + '=' + pref.value + '\n';
		if(std::fwrite((const char*)buf,1,buf.length(),file)<(size_t)buf.length())
		{
			//something went wrong, but I don't care
		}
	}
		
	std::fclose(file);
}
	
void PrefManager::addValue(const String&name, const String&value)
{
	for(size_t i=0; i<prefs.size(); i++)
	{
		Pref&pref = prefs.get(i);
		if(pref.name.equals(name))
		{
			pref.value = value;
			return;
		}
	}
	Pref pref = {name, value};
	prefs.add(pref);
}
	
void PrefManager::setValue(const String&name, const String&value)
{
	for(size_t i=0; i<prefs.size(); i++)
	{
		Pref&pref = prefs.get(i);
		if(pref.name.equals(name))
		{
			pref.value = value;
			return;
		}
	}
}

bool PrefManager::hasValue(const String&name) const
{
	for(size_t i=0; i<prefs.size(); i++)
	{
		const Pref&pref = prefs.get(i);
		if(pref.name.equals(name))
		{
			return true;
		}
	}
	return false;
}
	
bool PrefManager::getBooleanValue(const String&name) const
{
	return String::asBool(getStringValue(name));
}
	
int PrefManager::getIntValue(const String&name) const
{
	return String::asInt(getStringValue(name));
}
	
float PrefManager::getFloatValue(const String&name) const
{
	return String::asFloat(getStringValue(name));
}
	
long PrefManager::getLongValue(const String&name) const
{
	return String::asLong(getStringValue(name));
}
	
double PrefManager::getDoubleValue(const String&name) const
{
	return String::asDouble(getStringValue(name));
}
	
String PrefManager::getStringValue(const String&name) const
{
	for(size_t i=0; i<prefs.size(); i++)
	{
		const Pref&pref = prefs.get(i);
		if(pref.name.equals(name))
		{
			return pref.value;
		}
	}
		
	return "";
}
	
ArrayList<String> PrefManager::getKeys()
{
	ArrayList<String> keys;
	for (int i = 0; i < prefs.size(); i++)
	{
		keys.add(prefs.get(i).name);
	}
	return keys;
}
