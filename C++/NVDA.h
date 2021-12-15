#include <string>
#include "nvdaController.h"
using std::string;

#ifndef NVDA_H
#define NVDA_H

/**
 * My object-oriented approach to the NVDA Controller Client API
 * @author Mike Fox
 */
class NVDA
{
public:

    /**
     * Checks to see if NVDA is running
     * @return True if it is, false if it isn't
     */
    static bool IsRunning()
    {
        int r = nvdaController_testIfRunning();
        return r == 0 ? true : false;
    }

    /**
     * Tells NVDA to speak a string of text
     * @param {std::string} txt - The text to speak
     * @param {bool} [interrupt] - Set to true to make NVDA speak the text immediately; if this is left off, NVDA will finish whatever it's currently speaking before speaking the contents of txt.
     */
    static void Say(string txt, bool interrupt = false)
    {
        if (interrupt)
            NVDA::Stop();
        std::wstring widestr = std::wstring(txt.begin(), txt.end());
        const wchar_t* widecstr = widestr.c_str();
        nvdaController_speakText(widecstr);
    }

    /**
     * Tells NVDA to Braille a string of text
     * @param {std::string} txt - The text to Braille
     * @param {bool} [interrupt] - Same as for the Say method
     * @remarks This is untested, because I don't actually own a Braille device to try it on.
     */
    static void Braille(string txt, bool interrupt = false)
    {
        if (interrupt)
            NVDA::Stop();
        std::wstring widestr = std::wstring(txt.begin(), txt.end());
        const wchar_t* widecstr = widestr.c_str();
        nvdaController_brailleMessage(widecstr);
    }

    /**
     * Makes NVDA stop talking
     */
    static void Stop()
    {
        nvdaController_cancelSpeech();
    }
};

#endif
