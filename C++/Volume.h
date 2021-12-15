#include <windows.h>
#include <mmdeviceapi.h>
#include <devicetopology.h>
#include <functiondiscoverykeys.h>
#include <endpointvolume.h>

#ifndef VOLUME_CONTROL_H
#define VOLUME_CONTROL_H

/*
 * This class controls the master volume
 */
class Volume
{
public:
	static HRESULT hr;
	static IAudioEndpointVolume * endpointvolume;
	
	/*
 	 * The whole point of all this mess is to get a pointer to the default audio device.
 	 * Someday I might learn how it all works, but for now I get the gist and know it gets the job done. :)
 	 */
	static void Start()
	{
		CoInitialize(NULL);
		IMMDeviceEnumerator *deviceEnumerator = NULL;
		hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_INPROC_SERVER,
			__uuidof(IMMDeviceEnumerator), (LPVOID *)&deviceEnumerator);
		IMMDevice *defaultDevice = NULL;

		hr = deviceEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &defaultDevice);
		deviceEnumerator->Release();
		deviceEnumerator = NULL;

		Volume::endpointvolume = NULL;
		hr = defaultDevice->Activate(__uuidof(IAudioEndpointVolume),
			CLSCTX_INPROC_SERVER, NULL, (LPVOID *)&Volume::endpointvolume);
		defaultDevice->Release();
		defaultDevice = NULL;
	}

	// Getter/setter for the "level" (a float from 0.0 to 1.0)
	static float GetLevel()
	{
		float temp = 0;
		Volume::endpointvolume->GetMasterVolumeLevelScalar(&temp);
		return temp;
	}
	static void SetLevel(float value)
	{
		Volume::endpointvolume->SetMasterVolumeLevelScalar(value, NULL);
	}

	// Getter/setter for "mute" (bool)
	static bool GetMute()
	{
		return Volume::endpointvolume->GetMute(NULL);
	}
	static void SetMute(bool value)
	{
		Volume::endpointvolume->SetMute(value, NULL);
	}

	// Pretty self-explanatory
	static void ToggleMute()
	{
		bool muted = Volume::endpointvolume->GetMute(NULL);
		Volume::endpointvolume->SetMute(!muted, NULL);
	}

	// Release the objects needed to make this class work
	static void Finish()
	{
		Volume::endpointvolume->Release();
		CoUninitialize();
	}
};

// Initial definitions for the static class properties
HRESULT Volume::hr = NULL;
IAudioEndpointVolume * Volume::endpointvolume = NULL;

#endif