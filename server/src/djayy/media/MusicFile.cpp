
#ifdef _WIN32
	#define _CRT_SECURE_NO_WARNINGS
#endif

#include "MusicFile.h"
#include <stdio.h>

#ifdef _WIN32
	extern "C" { FILE _iob[3] = {__iob_func()[0], __iob_func()[1], __iob_func()[2]}; }
#endif

namespace djayy
{
	std::wstring string_to_wstring(const std::string&str)
	{
		size_t size = (str.length()*sizeof(char));
		wchar_t* characters = (wchar_t*)std::calloc(size+1, sizeof(wchar_t));
		if(characters == nullptr)
		{
			throw std::bad_alloc();
		}
		size = std::mbstowcs(characters, str.c_str(), size+1);
		if(size == (size_t)-1)
		{
			size = 0;
		}
		characters[size] = NULL;
		std::wstring wstr(characters, characters+size);
		std::free(characters);
		return wstr;
	}
	
	std::string wstring_to_string(const std::wstring&wstr)
	{
		size_t size = (wstr.length()*sizeof(wchar_t));
		char* characters = (char*)std::calloc(size+1, sizeof(char));
		if(characters == nullptr)
		{
			throw std::bad_alloc();
		}
		size = std::wcstombs(characters, wstr.c_str(), size+1);
		if(size == (size_t)-1)
		{
			size = 0;
		}
		characters[size] = NULL;
		std::string str(characters, characters+size);
		std::free(characters);
		return str;
	}
}

#include <audiere.h>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>

namespace djayy
{
	bool MusicFile_initted = false;
	audiere::AudioDevicePtr MusicFile_device;
	std::mutex MusicFile_currentlyplaying_mutex;
	std::vector<MusicFile*> MusicFile_currentlyplaying;
	audiere::Callback* MusicFile_callback = nullptr;

#define BLIP_OFFSET 1150
	
	void MusicFile_registerCallbacks();
	
	void MusicFile_init()
	{
		if(!MusicFile_initted)
		{
			audiere::AudioDevice* device = audiere::OpenDevice();
			if(device == nullptr)
			{
				throw std::runtime_error("unable to open sound device");
			}
			MusicFile_device = device;
			MusicFile_registerCallbacks();
			MusicFile_initted = true;
		}
	}

	void MusicFile_removeCurrentlyPlaying(MusicFile*music)
	{
		MusicFile_currentlyplaying_mutex.lock();
		size_t playing_size = MusicFile_currentlyplaying.size();
		for(size_t i=0; i<playing_size; i++)
		{
			if(music == MusicFile_currentlyplaying[i])
			{
				MusicFile_currentlyplaying.erase(MusicFile_currentlyplaying.begin()+i);
				MusicFile_currentlyplaying_mutex.unlock();
				return;
			}
		}
		MusicFile_currentlyplaying_mutex.unlock();
	}

	class MusicData
	{
	public:
		audiere::OutputStream* sound;
		audiere::OutputStreamPtr soundptr;
		bool paused;
		int lastpos;
		std::mutex waiting_mutex;
		std::vector<std::condition_variable*> waiting;
		bool closing;
		
		MusicData() : sound(nullptr), soundptr(nullptr), paused(false), lastpos(0), closing(false)
		{
			//
		}
	};
	
	class MusicEventHandler : public audiere::StopCallback
	{
	public:
		ADR_METHOD(void) streamStopped(audiere::StopEvent *event) override
		{
			MusicFile_currentlyplaying_mutex.lock();
			MusicFile* music = nullptr;
			size_t playing_size = MusicFile_currentlyplaying.size();
			for(size_t i=0; i<playing_size; i++)
			{
				MusicFile* music_cmp = MusicFile_currentlyplaying[i];
				if(((MusicData*)music_cmp->musicdata)->sound == event->getOutputStream())
				{
					music = music_cmp;
					i = playing_size;
				}
			}
			MusicData* musdat = nullptr;
			if(music!=nullptr)
			{
				musdat = (MusicData*)music->musicdata;
			}
			if(musdat!=nullptr && (event->getReason()==audiere::StopEvent::Reason::STREAM_ENDED || musdat->closing))
			{
				if(musdat->sound->getLength() > (BLIP_OFFSET*2))
				{
					musdat->sound->setPosition(BLIP_OFFSET);
				}
				else
				{
					musdat->sound->setPosition(0);
				}
				size_t waiting_size = musdat->waiting.size();
				musdat->waiting_mutex.lock();
				for(size_t i=0; i<waiting_size; i++)
				{
					musdat->waiting[i]->notify_all();
				}
				musdat->waiting.clear();
				musdat->waiting_mutex.unlock();
				MusicFile_currentlyplaying_mutex.unlock();
			}
			else
			{
				MusicFile_currentlyplaying_mutex.unlock();
			}
		}
		
		ADR_METHOD(void) ref() override
		{
			//
		}
		
		ADR_METHOD(void) unref() override
		{
			//
		}
	};
	
	void MusicFile_registerCallbacks()
	{
		MusicFile_callback = new MusicEventHandler();
		MusicFile_device->registerCallback(MusicFile_callback);
	}
	
	MusicFile::MusicFile()
		: musicdata(nullptr)
	{
		MusicFile_init();
	}
	
	MusicFile::~MusicFile()
	{
		if(musicdata != nullptr)
		{
			close();
		}
	}
	
	bool MusicFile::openFromFile(const std::wstring& path, std::string*error)
	{
		return openFromFile(wstring_to_string(path), error);
	}
	
	bool MusicFile::openFromFile(const std::string& path, std::string*error)
	{
		audiere::OutputStream* sound = audiere::OpenSound(MusicFile_device, path.c_str(), true);
		if(sound == nullptr)
		{
			if(error != nullptr)
			{
				*error = "unable to open stream";
			}
			return false;
		}
		if(musicdata != nullptr)
		{
			close();
		}
		MusicData* musicdata_load = new MusicData();
		musicdata_load->sound = sound;
		musicdata_load->soundptr = sound;
		if(sound->getLength() > (BLIP_OFFSET*2))
		{
			sound->setPosition(BLIP_OFFSET);
		}
		else
		{
			sound->setPosition(0);
		}
		musicdata = musicdata_load;
		return true;
	}
	
	void MusicFile::close()
	{
		if(musicdata==nullptr)
		{
			return;
		}
		MusicData* musdat = (MusicData*)musicdata;
		musdat->closing = true;
		musdat->sound->stop();
		MusicFile_removeCurrentlyPlaying(this);
		delete ((MusicData*)musicdata);
		musicdata = nullptr;
	}
	
	void MusicFile::play()
	{
		if(musicdata == nullptr)
		{
			return;
		}
		MusicData* musdat = (MusicData*)musicdata;
		if(!musdat->sound->isPlaying())
		{
			if(musdat->paused)
			{
				musdat->sound->setPosition(musdat->lastpos);
			}
			musdat->paused = false;
			MusicFile_currentlyplaying_mutex.lock();
			MusicFile_currentlyplaying.push_back(this);
			MusicFile_currentlyplaying_mutex.unlock();
			musdat->sound->play();
		}
	}
	
	void MusicFile::pause()
	{
		if(musicdata == nullptr)
		{
			return;
		}
		MusicData* musdat = (MusicData*)musicdata;
		if(!musdat->paused)
		{
			musdat->sound->stop();
			musdat->lastpos = musdat->sound->getPosition();
			MusicFile_removeCurrentlyPlaying(this);
			musdat->paused = true;
		}
	}
	
	void MusicFile::stop()
	{
		if(musicdata == nullptr)
		{
			return;
		}
		MusicData* musdat = (MusicData*)musicdata;
		musdat->sound->stop();
		MusicFile_removeCurrentlyPlaying(this);
		musdat->waiting_mutex.lock();
		size_t waiting_size = musdat->waiting.size();
		for(size_t i=0; i<waiting_size; i++)
		{
			musdat->waiting[i]->notify_all();
		}
		musdat->waiting.clear();
		musdat->waiting_mutex.unlock();
		if(musdat->sound->getLength() > (BLIP_OFFSET*2))
		{
			musdat->sound->setPosition(BLIP_OFFSET);
		}
		else
		{
			musdat->sound->setPosition(0);
		}
		musdat->paused = false;
		musdat->lastpos = 0;
	}
	
	void MusicFile::wait()
	{
		if(musicdata == nullptr)
		{
			return;
		}
		MusicData* musdat = (MusicData*)musicdata;
		if(!musdat->sound->isPlaying())
		{
			return;
		}
		std::mutex mutex;
		std::unique_lock<std::mutex> lock(mutex);
		std::condition_variable cv;
		musdat->waiting_mutex.lock();
		if(!musdat->sound->isPlaying())
		{
			musdat->waiting_mutex.unlock();
			return;
		}
		musdat->waiting.push_back(&cv);
		musdat->waiting_mutex.unlock();
		cv.wait(lock);
	}
	
	void MusicFile::setPosition(double pos)
	{
		if(musicdata == nullptr)
		{
			return;
		}
		MusicData* musdat = (MusicData*)musicdata;
		long offset = BLIP_OFFSET;
		int length = musdat->sound->getLength();
		if(length <= (offset*2))
		{
			offset = 0;
		}
		int actualLength = (length-1)-offset;
		int posOff = (int)(((double)actualLength)*pos);
		int new_frame = offset+posOff;
		musdat->sound->setPosition(new_frame);
	}
	
	double MusicFile::getPosition() const
	{
		if(musicdata == nullptr)
		{
			return 0;
		}
		MusicData* musdat = (MusicData*)musicdata;
		long offset = BLIP_OFFSET;
		int length = musdat->sound->getLength();
		if(length <= (offset*2))
		{
			offset = 0;
		}
		int actualLength = (length-1)-offset;
		int position = musdat->sound->getPosition()-offset;
		return ((double)position)/((double)actualLength);
	}
}
