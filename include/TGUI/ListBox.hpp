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


#ifndef _TGUI_LISTBOX_INCLUDED_
#define _TGUI_LISTBOX_INCLUDED_

/// \todo  ListBox shouldn't work with ids. Instead an index should be used like in Tab.

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    struct TGUI_API ListBox : public OBJECT, OBJECT_BORDERS
    {
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Default constructor
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        ListBox();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Copy constructor
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        ListBox(const ListBox& copy);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Destructor
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual ~ListBox();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Overload of assignment operator
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        ListBox& operator= (const ListBox& right);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void initialize();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual ListBox* clone();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Creates the list box.
        ///
        /// The list box may resize a little bit. It might be a little bit bigger or smaller than the size passed to this function.
        ///
        /// \param width              The width of the list box (borders included).
        /// \param height             The height of the list box (borders included).
        /// \param scrollbarPathname  The pathname needed to load the scrollbar.
        ///                           If not provided then there will be no possibility to scroll, thus no items will be added when the list box is full.
        /// \param itemHeight         The height of a single item in the list box. The text size will be based on this, but will be a little smaller.
        ///                           If ItemHeight is 0 then it will become a tenth of the height of the list box.
        ///
        /// \return
        ///        - true on success
        ///        - false when scrollbar couldn't be loaded (only if \a scrollbarPathname isn't empty)
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual bool load(unsigned int width,
                          unsigned int height,
                          const std::string& scrollbarPathname = "",
                          unsigned int itemHeight = 0);


        //////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Changes the size of the list box.
        ///
        /// \param width   The new width of the list box
        /// \param height  The new height of the list box
        //////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void setSize(float width, float height);


        //////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Returns the size of the list box, unaffected by scaling.
        //////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual Vector2u getSize() const;


        //////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Returns the size of the list box, after the scaling transformation.
        //////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual Vector2f getScaledSize() const;


        //////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Returns the pathname that was used to load the scrollbar.
        ///
        /// When no scrollbar was loaded then this function will return an empty string.
        //////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual std::string getLoadedScrollbarPathname() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Changes the colors used in the list box.
        ///
        /// \param backgroundColor          The color of the background of the list box
        /// \param textColor                The color of the text
        /// \param selectedBackgroundColor  The color of the background of the selected item
        /// \param selectedTextColor        The color of the text when it is selected
        /// \param borderColor              The color of the borders
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void changeColors(const sf::Color& backgroundColor         = sf::Color::White,
                                  const sf::Color& textColor               = sf::Color::Black,
                                  const sf::Color& selectedBackgroundColor = sf::Color(50, 100, 200),
                                  const sf::Color& selectedTextColor       = sf::Color::White,
                                  const sf::Color& borderColor             = sf::Color::Black);

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Set the background color that will be used inside the list box.
        ///
        /// \see changeColors
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void setBackgroundColor(const sf::Color& backgroundColor);

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Set the text color that will be used inside the list box.
        ///
        /// \see changeColors
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void setTextColor(const sf::Color& textColor);

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Set the background color of the selected text that will be used inside the list box.
        ///
        /// \see changeColors
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void setSelectedBackgroundColor(const sf::Color& selectedBackgroundColor);

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Set the text color of the selected text that will be used inside the list box.
        ///
        /// \see changeColors
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void setSelectedTextColor(const sf::Color& selectedTextColor);

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Set the border color text that will be used inside the list box.
        ///
        /// \see changeColors
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void setBorderColor(const sf::Color& borderColor);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Get the background color that is currently being used inside the list box.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual const sf::Color& getBackgroundColor() const;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Get the text color that is currently being used inside the list box.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual const sf::Color& getTextColor() const;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Get the background color of the selected text that is currently being used inside the list box.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual const sf::Color& getSelectedBackgroundColor() const;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Get the text color of the selected text that is currently being used inside the list box.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual const sf::Color& getSelectedTextColor() const;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Get the border color that is currently being used inside the list box.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual const sf::Color& getBorderColor() const;


        //////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Changes the font of the items.
        ///
        /// When you don't call this function then the global font will be use.
        /// This global font can be changed by changing \a gloabalFont from the parent.
        //////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void setTextFont(const sf::Font& font);


        //////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Returns the font of the items.
        //////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual const sf::Font* getTextFont() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Adds an item to the list.
        ///
        /// \param itemName The name of the item you want to add (this is the text that will be displayed inside the list box)
        ///
        /// \return
        ///         - 0 when the list box is full (you have set a maximum item limit and you are trying to add more items)
        ///         - 0 when there is no scrollbar and you try to have more items than fit inside the list box
        ///         - The id of the item when it was successfully added.
        ///
        /// \warning The id returned by this function is no longer correct when an item is removed. Use it immediately or don't use it at all.
        ///
        /// \see setMaximumItems
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual unsigned int addItem(const sf::String& itemName);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Selects an item in the list box.
        ///
        /// When adding items to the list box with the addItem function, none of them will be selected.
        /// If you want a default item selected then you can use this function to select it.
        /// The first item that matches the name will be selected.
        ///
        /// \return
        ///         - true on success
        ///         - false when none of the items matches the name
        ///
        /// \see setSelectedItem(unsigned int)
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual bool setSelectedItem(const sf::String& itemName);

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Selects an item in the list box.
        ///
        /// When adding items to the list box with the addItem function, none of them will be selected.
        /// If you want a default item selected then you can use this function to select it.
        ///
        /// The id starts counting from 1. If you pass 0 to this function then none of the items will be selected.
        ///
        /// \return
        ///         - true on success
        ///         - false when the id was too high
        ///
        /// \see setSelectedItem(sf::String)
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual bool setSelectedItem(unsigned int id);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Removes an item from the list with a given id.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void removeItem(unsigned int id);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Removes all items from the list with a given name.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void removeItem(const sf::String& itemName);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Removes all items from the list.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void removeAllItems();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Returns the item name of the given id.
        ///
        /// The string will be empty when the id was too high or when it was 0.
        ///
        /// \see getItemID
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual sf::String getItem(unsigned int id) const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Returns the id of the first item with the given name.
        ///
        /// If none of the items matches then the id will be 0.
        ///
        /// \warning This id will become wrong when an item is removed from the list. Use it immediately or don't use it at all.
        ///
        /// \see getItem
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual unsigned int getItemID(const sf::String& itemName) const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Returns the list that constains all the items.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual std::vector<sf::String>& getItems();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Returns the currently selected item.
        ///
        /// When no item was selected then this function will return an empty string.
        ///
        /// \see getSelectedItemID
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual sf::String getSelectedItem() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Get the id of the selected item.
        ///
        /// When no item was selected then this function returns 0.
        ///
        /// \warning This id will become wrong when an item is removed from the list. Use it immediately or don't use it at all.
        ///
        /// \see getSelectedItem
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual unsigned int getSelectedItemID() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Changes the scrollbar of the list box.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual bool setScrollbar(const std::string& scrollbarPathname);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Removes the scrollbar from the list box (if there is one).
        ///
        /// When there are too many items to fit in the list box then the items will be removed.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void removeScrollbar();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Changes the height of the items in the list box.
        ///
        /// This size is always a little big greater than the text size.
        /// When there is no scrollbar then the items will be removed when they no longer fit inside the list box.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void setItemHeight(unsigned int itemHeight);

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Returns the height of the items in the list box.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual unsigned int getItemHeight() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Changes the maximum items that the list box can contain.
        ///
        /// If this function returns 0 then there is no limit.
        /// If no scrollbar was loaded then there is always a limitation because the text can't go outside the list box.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void setMaximumItems(unsigned int maximumItems = 0);

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Returns the maximum items that the list box can contain. If 0 then there is no limit.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual unsigned int getMaximumItems() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Changes the size of the borders.
        ///
        /// \param leftBorder    The width of the left border
        /// \param topBorder     The height of the top border
        /// \param rightBorder   The width of the right border
        /// \param bottomBorder  The height of the bottom border
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void setBorders(unsigned int leftBorder   = 0,
                                unsigned int topBorder    = 0,
                                unsigned int rightBorder  = 0,
                                unsigned int bottomBorder = 0);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // These functions are used to receive callback from the EventManager.
        // You normally don't need them, but you can use them to simulate an event.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual bool mouseOnObject(float x, float y);
        virtual void leftMousePressed(float x, float y);
        virtual void leftMouseReleased(float x, float y);
        virtual void mouseMoved(float x, float y);
        virtual void mouseWheelMoved(int delta);
        virtual void mouseNotOnObject();
        virtual void mouseNoLongerDown();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    protected:

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Because this struct is derived from sf::Drawable, you can just call the draw function from your sf::RenderTarget.
        // This function will be called and it will draw the list box on the render target.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    protected:

        // This contains the different items in the list box
        std::vector<sf::String> m_Items;

        // What is the id of the selected item?
        unsigned int m_SelectedItem;

        // The size must be stored
        Vector2u m_Size;
        unsigned int m_ItemHeight;

        unsigned int m_TextSize;

        // This will store the maximum number of items in the list box (zero by default, meaning that there is no limit)
        unsigned int m_MaxItems;

        // When there are too many items a scrollbar will be shown
        Scrollbar* m_Scroll;

        // The pathname of the loaded scrollbar (if there is one)
        std::string m_LoadedScrollbarPathname;

        // These colors are used to draw the list box
        sf::Color m_BackgroundColor;
        sf::Color m_TextColor;
        sf::Color m_SelectedBackgroundColor;
        sf::Color m_SelectedTextColor;
        sf::Color m_BorderColor;

        // The font used to draw the text
        sf::Font m_TextFont;

        // ComboBox contains a list box internally and it should be able to adjust it.
        friend struct ComboBox;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    };

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif //_TGUI_LISTBOX_INCLUDED_
