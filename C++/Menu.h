#ifndef MENU_H_
#define MENU_H_

#include <iostream>
#include <vector>

using namespace std;

/**
 * This class represents a simple menu, where players
 * are presented with a list of options and can choose
 * only one.  This is a template class, so you can do
 * menus of ints, menus of strings, menus of menus etc.
 * I built it with audio games in mind, but it's general
 * enough that it can be used for other stuff too.
 * @todo Implement an iterator. I didn't need it for the
 * project I built it for, but I might someday.
 * @date 07/30/2017
 */
template<class T>
class Menu
{
public:

    /**
     * This property can be used to set up the menu so that if
     * you reach the end of the list, Current() is moved to the
     * beginning of the list.  Same goes for the other way
     * around; if Loop is true and you reach the beginning of
     * the list, Current() is moved to the last option.
     */
    bool Loop = false;

    /**
     * Adds an option to the menu
     * @param[in] The option
     */
    void AddOption(T option)
    {
        Options.push_back(option);
    }

    /**
     * Gets the currently selected option in the menu
     */
    T Current()
    {
        return Options.at(Index);
    }

    /**
     * Selects the next option in the menu
     */
    T Next()
    {
        // Update the index
        Index++;
        if (Index == Options.size())
            if (Loop)
                Index = 0;
            else
                Index--;

        // And return the string in that position in the vector
        return Options.at(Index);
    }

    /**
     * Selects the previous option in the menu
     */
    T Previous()
    {
        // Update the index
        Index--;
        int Length = Options.size();
        if (Index == -1)
            if (Loop)
                Index = Length - 1;
            else
                Index++;

        // And return the string in that position in the vector
        return Options.at(Index);
    }

private:

    // This is used to track which option in the menu is selected
    int Index = 0;

    // And this is the actual list of options
    vector<T> Options;
};

#endif
