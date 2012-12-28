/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus's Graphical User Interface
// Copyright (C) 2012 Bruno Van de Velde (VDV_B@hotmail.com)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef _TGUI_TAB_INCLUDED_
#define _TGUI_TAB_INCLUDED_


/// \todo  Add an optional close button to the tabs.
/// \todo  Add an extra tab that can be used to open a new tab.

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    struct TGUI_API Tab : public OBJECT
    {
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Default constructor
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Tab();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Copy constructor
        ///
        /// \param copy  Instance to copy
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Tab(const Tab& copy);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Destructor
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual ~Tab();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Overload of assignment operator
        ///
        /// \param right  Instance to assign
        ///
        /// \return Reference to itself
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Tab& operator= (const Tab& right);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // This function is called when the object is created (when it is added to a group).
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void initialize();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Makes a copy of the tab by calling the copy constructor.
        // This function calls new and if you use this function then you are responsible for calling delete.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual Tab* clone();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Creates the Tab object.
        ///
        /// \param pathname  The path to the folder that contains the images for the tabs.
        ///                  The folder must also contain an info.txt file, which will give more information about the tab.
        ///
        /// \return
        ///        - true on success
        ///        - false when the pathname was empty
        ///        - false when the info.txt file was not found
        ///        - false when the images couldn't be loaded
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual bool load(const std::string& pathname);


        //////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Changes the size of a tab.
        ///
        /// \param width   The maximum width for a single tab.
        /// \param height  The height of all the tabs.
        ///
        /// The \a width parameter will just change \a maximumTabWidth.
        /// The \a height parameter will just change the tab height with setTabHeight.
        ///
        /// \see maximumTabWidth
        /// \see setTabHeight
        ///
        //////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void setSize(float width, float height);


        //////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Returns the size of the tabs, unaffected by scaling.
        ///
        /// \return Size of the tabs
        ///
        //////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual Vector2u getSize() const;


        //////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Returns the size of the tabs, after the scaling transformation.
        ///
        /// \return Size of the tabs
        ///
        //////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual Vector2f getScaledSize() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Returns the pathname that was used to load the tab.
        ///
        /// \return Pathname used to load the tab.
        ///         When the tab has not been loaded yet then this function will return an empty string.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual std::string getLoadedPathname() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Adds a new tab.
        ///
        /// \param name    The name of the tab (this is the text that will be drawn on top of the tab).
        /// \param select  Do you want the new tab to be selected immediately?
        ///
        /// \return  The index of the tab in the list.
        ///
        /// \warning The index returned by this function may no longer be correct when a tab is removed.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual unsigned int add(const sf::String& name, bool select = true);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Selects the tab with a given name.
        ///
        /// \param name  The name of the tab to select.
        ///
        /// When the name doen't match any tab then nothing will be changed.
        /// If there are multiple tabs with the same name then the first one will be selected.
        ///
        /// \see select(int)
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void select(const sf::String& name);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Selects the tab with a given index.
        ///
        /// \param index  The index of the tab to select.
        ///
        /// When the index is too high then nothing will happen.
        ///
        /// \see select(sf::String)
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void select(unsigned int index);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Deselects the selected tab.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void deselect();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Removes a tab with a given name.
        ///
        /// \param name  The name of the tab to remove.
        ///
        /// When multiple tabs have the same name, only the first will be removed.
        ///
        /// \see remove(unsigned int)
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void remove(const sf::String& name);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Removes a tab with a given index.
        ///
        /// \param index  The index of the tab to remove.
        ///
        /// When the index is too high then nothing will happen.
        ///
        /// \see remove(sf::String)
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void remove(unsigned int index);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Removes all tabs.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void removeAll();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Get the name of the currently selected tab.
        ///
        /// \return The name of the tab.
        ///         When no tab is selected then this function returns an empty string.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual sf::String getSelected() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Get the index of the currently selected tab.
        ///
        /// \return The index of the tab.
        ///         When no tab is selected then this function returns -1.
        ///
        /// \warning The index returned by this function may no longer be correct when a tab is removed.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual int getSelectedIndex() const;


        //////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Changes the font of the tabs.
        ///
        /// When you don't call this function then the global font will be use.
        /// This global font can be changed by changing \a gloabalFont from the parent.
        ///
        /// \param font  The new font.
        ///
        //////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void setTextFont(const sf::Font& font);


        //////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Returns the font of the tabs.
        ///
        /// \return  A pointer to the font that is currently being used.
        ///
        //////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual const sf::Font* getTextFont() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Set the text color that will be used inside the tabs.
        ///
        /// \param color  The new text color.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void setTextColor(const sf::Color& color);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Get the text color that is currently being used inside the tabs.
        ///
        /// \return The text color that is currently being used.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual const sf::Color& getTextColor() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Changes the character size of the text.
        ///
        /// \param textSize  The new size of the text.
        ///                  If the size is 0 (default) then the text will be scaled to fit in the tab.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void setTextSize(unsigned int size);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Returns the character size of the text.
        ///
        /// \return The text size.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual unsigned int getTextSize() const;


        //////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Changes the height of the tabs.
        ///
        /// \param height
        ///
        /// By default, it is the height of the tab image that is loaded with the load function.
        ///
        //////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void setTabHeight(unsigned int height);


        //////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Returns the height of the tabs.
        ///
        /// \return Tab height
        ///
        //////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual unsigned int getTabHeight() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // These functions are used to receive callback from EventManager.
        // You normally don't need them, but you can use these functions to simulate an event.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual bool mouseOnObject(float x, float y);
        virtual void leftMousePressed(float x, float y);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    protected:


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Because this struct is derived from sf::Drawable, you can just call the draw function from your sf::RenderTarget.
        // This function will be called and it will draw the tab object on the render target.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    public:

        /// The distance between the side of the tab and the text that is drawn on top of the tab.
        unsigned int distanceToSide;

        /// The maximum width of a single tab.
        /// By default, this number is 0 which means that there is no limitation.
        unsigned int maximumTabWidth;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    protected:

        std::string   m_LoadedPathname;
        bool          m_SplitImage;
        bool          m_SeparateSelectedImage;

        unsigned int  m_TabHeight;
        unsigned int  m_TextSize;

        int  m_SelectedTab;

        std::vector<sf::String> m_TabNames;
        std::vector<float>      m_NameWidth;

        sf::Texture*  m_TextureNormal_L;
        sf::Texture*  m_TextureNormal_M;
        sf::Texture*  m_TextureNormal_R;
        sf::Texture*  m_TextureSelected_L;
        sf::Texture*  m_TextureSelected_M;
        sf::Texture*  m_TextureSelected_R;

        sf::Sprite    m_SpriteNormal_L;
        sf::Sprite    m_SpriteNormal_M;
        sf::Sprite    m_SpriteNormal_R;
        sf::Sprite    m_SpriteSelected_L;
        sf::Sprite    m_SpriteSelected_M;
        sf::Sprite    m_SpriteSelected_R;

        sf::Text      m_Text;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    };

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif //_TGUI_TAB_INCLUDED_
