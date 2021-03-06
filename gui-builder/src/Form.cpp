/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus' Graphical User Interface
// Copyright (C) 2012-2017 Bruno Van de Velde (vdv_b@tgui.eu)
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


#include "Form.hpp"
#include "GuiBuilder.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Form::Form(GuiBuilder* guiBuilder, const std::string& filename, tgui::ChildWindow::Ptr formWindow) :
    m_guiBuilder      {guiBuilder},
    m_formWindow      {formWindow},
    m_scrollablePanel {formWindow->get<tgui::ScrollablePanel>("ScrollablePanel")},
    m_widgetsContainer{m_scrollablePanel->get<tgui::Group>("WidgetContainer")},
    m_filename        {filename}
{
    m_widgets["form"] = nullptr;

    m_formWindow->setTitle(filename);
    m_formWindow->connect("Closed", [this]{ m_guiBuilder->closeForm(this); });
    m_formWindow->connect("SizeChanged", [this]{ m_scrollablePanel->setSize(m_formWindow->getSize()); });

    auto eventHandler = tgui::ClickableWidget::create();
    eventHandler->connect("MousePressed", [=](sf::Vector2f pos){ onFormMousePress(pos); });
    m_scrollablePanel->add(eventHandler, "EventHandler");

    m_scrollablePanel->setSize(m_formWindow->getSize());
    setSize(sf::Vector2i{m_formWindow->getSize()});

    tgui::Theme selectionSquareTheme{"resources/SelectionSquare.txt"};
    for (auto& square : m_selectionSquares)
    {
        square = tgui::Button::create();
        square->setRenderer(selectionSquareTheme.getRenderer("Square"));
        square->setSize(square->getRenderer()->getTexture().getImageSize());
        square->hide();
        square->connect("MousePressed", [=](sf::Vector2f pos){ onSelectionSquarePress(square, pos); });
        m_scrollablePanel->add(square);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

std::string Form::addWidget(tgui::Widget::Ptr widget)
{
    const std::string id = tgui::to_string(widget.get());
    m_widgets[id] = widget;

    const std::string name = "Widget" + tgui::to_string(++m_idCounter);
    m_widgetsContainer->add(widget, name);
    selectWidget(widget);

    setChanged(true);
    return name;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Form::removeWidget(const std::string& id)
{
    const auto widget = m_widgets[id];
    m_widgets.erase(id);

    m_widgetsContainer->remove(widget);

    setChanged(true);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

tgui::Widget::Ptr Form::getSelectedWidget() const
{
    return m_selectedWidget;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Form::setSelectedWidgetName(const std::string& name)
{
    bool widgetFound = false;
    auto widgets = m_widgetsContainer->getWidgets();
    for (auto& widget : widgets)
    {
        if (widgetFound)
        {
            // These widgets appeared after the selected widgets and thus have to be displayed in front of it.
            // By removing and re-adding the selected widget we however changed the order, which we are correcting here.
            widget->moveToFront();
        }
        else
        {
            if (widget == m_selectedWidget)
            {
                // Remove the selected widget and add it again with a different name
                m_widgetsContainer->remove(m_selectedWidget);
                m_widgetsContainer->add(m_selectedWidget, name);
                widgetFound = true;
            }
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

std::string Form::getSelectedWidgetName() const
{
    return m_widgetsContainer->getWidgetName(m_selectedWidget);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Form::updateSelectionSquarePositions()
{
    const auto& widget = m_selectedWidget;
    const auto position = widget->getPosition();
    m_selectionSquares[0]->setPosition({position.x,                               position.y});
    m_selectionSquares[1]->setPosition({position.x + (widget->getSize().x / 2.f), position.y});
    m_selectionSquares[2]->setPosition({position.x + widget->getSize().x,         position.y});
    m_selectionSquares[3]->setPosition({position.x + widget->getSize().x,         position.y + (widget->getSize().y / 2.f)});
    m_selectionSquares[4]->setPosition({position.x + widget->getSize().x,         position.y + widget->getSize().y});
    m_selectionSquares[5]->setPosition({position.x + (widget->getSize().x / 2.f), position.y + widget->getSize().y});
    m_selectionSquares[6]->setPosition({position.x,                               position.y + widget->getSize().y});
    m_selectionSquares[7]->setPosition({position.x,                               position.y + (widget->getSize().y / 2.f)});

    // The positions given to the squares where those of its center
    for (auto& square : m_selectionSquares)
        square->setPosition(square->getPosition() - (square->getSize() / 2.f));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Form::selectWidgetById(const std::string& id)
{
    selectWidget(m_widgets[id]);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

std::vector<std::pair<tgui::Widget::Ptr, std::string>> Form::getWidgetsAndNames() const
{
    std::vector<std::pair<tgui::Widget::Ptr, std::string>> pairs;

    const auto& widgets = m_widgetsContainer->getWidgets();
    const auto& names = m_widgetsContainer->getWidgetNames();

    for (std::size_t i = 0; i < widgets.size(); ++i)
        pairs.push_back(std::make_pair(widgets[i], names[i]));

    return pairs;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Form::mouseMoved(sf::Vector2i pos)
{
    if (m_draggingWidget || m_draggingSelectionSquare)
        onDrag(pos);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Form::mouseReleased()
{
    m_draggingWidget = false;
    m_draggingSelectionSquare = nullptr;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Form::setFilename(const sf::String& filename)
{
    m_filename = filename;
    setChanged(m_changed);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

sf::String Form::getFilename() const
{
    return m_filename;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Form::setSize(sf::Vector2i size)
{
    m_size = size;

    m_scrollablePanel->setContentSize(sf::Vector2f{m_size});
    m_widgetsContainer->setSize(sf::Vector2f{m_size});
    m_scrollablePanel->get("EventHandler")->setSize(sf::Vector2f{m_size});
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

sf::Vector2i Form::getSize() const
{
    return m_size;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Form::setChanged(bool changed)
{
    if (changed)
        m_formWindow->setTitle("*" + m_filename);
    else
        m_formWindow->setTitle(m_filename);

    m_changed = changed;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Form::isChanged() const
{
    return m_changed;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Form::load()
{
    m_widgetsContainer->loadWidgetsFromFile(getFilename());

    const auto& widgets = m_widgetsContainer->getWidgets();
    const auto& widgetNames = m_widgetsContainer->getWidgetNames();
    for (std::size_t i = 0; i < widgets.size(); ++i)
    {
        const std::string id = tgui::to_string(widgets[i].get());
        m_widgets[id] = widgets[i];

        // Keep track of the highest id found in widgets with default names, to avoid creating new widgets with confusing names
        if ((widgetNames[i].getSize() >= 7) && (widgetNames[i].substring(0, 6) == "Widget"))
        {
            const std::string potentialNumber = widgetNames[i].substring(6);
            if (std::all_of(potentialNumber.begin(), potentialNumber.end(), ::isdigit))
                m_idCounter = std::max<unsigned int>(m_idCounter, tgui::stoi(potentialNumber));
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Form::save()
{
    setChanged(false);
    m_widgetsContainer->saveWidgetsToFile(getFilename());
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Form::onSelectionSquarePress(tgui::Button::Ptr square, sf::Vector2f pos)
{
    m_draggingSelectionSquare = square;
    m_draggingPos = square->getPosition() + pos;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Form::onFormMousePress(sf::Vector2f pos)
{
    const auto& widgets = m_widgetsContainer->getWidgets();
    for (auto it = widgets.rbegin(); it != widgets.rend(); ++it)
    {
        if (sf::FloatRect{(*it)->getPosition().x, (*it)->getPosition().y, (*it)->getSize().x, (*it)->getSize().y}.contains(pos))
        {
            selectWidget(*it);

            m_draggingWidget = true;
            m_draggingPos = pos;

            return;
        }
    }

    selectWidget(nullptr);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Form::onDrag(sf::Vector2i mousePos)
{
    const sf::Vector2f pos = sf::Vector2f{mousePos} - m_formWindow->getPosition() - m_formWindow->getChildWidgetsOffset() + m_scrollablePanel->getContentOffset();
    const float step = 10;

    bool updated = false;

    if (m_draggingWidget)
    {
        while (pos.x - m_draggingPos.x >= step)
        {
            m_selectedWidget->setPosition({m_selectedWidget->getPosition().x + step, m_selectedWidget->getPosition().y});
            m_draggingPos.x += step;
            updated = true;
        }

        while (m_draggingPos.x - pos.x >= step)
        {
            m_selectedWidget->setPosition({m_selectedWidget->getPosition().x - step, m_selectedWidget->getPosition().y});
            m_draggingPos.x -= step;
            updated = true;
        }

        while (pos.y - m_draggingPos.y >= step)
        {
            m_selectedWidget->setPosition({m_selectedWidget->getPosition().x, m_selectedWidget->getPosition().y + step});
            m_draggingPos.y += step;
            updated = true;
        }

        while (m_draggingPos.y - pos.y >= step)
        {
            m_selectedWidget->setPosition({m_selectedWidget->getPosition().x, m_selectedWidget->getPosition().y - step});
            m_draggingPos.y -= step;
            updated = true;
        }
    }

    if (m_draggingSelectionSquare)
    {
        if (m_draggingSelectionSquare == m_selectionSquares[1]) // Top
        {
            while (pos.y - m_draggingPos.y >= step)
            {
                m_selectedWidget->setPosition({m_selectedWidget->getPosition().x, m_selectedWidget->getPosition().y + step});
                m_selectedWidget->setSize({m_selectedWidget->getSize().x, m_selectedWidget->getSize().y - step});
                m_draggingPos.y += step;
                updated = true;
            }

            while (m_draggingPos.y - pos.y >= step)
            {
                m_selectedWidget->setPosition({m_selectedWidget->getPosition().x, m_selectedWidget->getPosition().y - step});
                m_selectedWidget->setSize({m_selectedWidget->getSize().x, m_selectedWidget->getSize().y + step});
                m_draggingPos.y -= step;
                updated = true;
            }
        }
        else if (m_draggingSelectionSquare == m_selectionSquares[3]) // Right
        {
            while (pos.x - m_draggingPos.x >= step)
            {
                m_selectedWidget->setSize({m_selectedWidget->getSize().x + step, m_selectedWidget->getSize().y});
                m_draggingPos.x += step;
                updated = true;
            }

            while (m_draggingPos.x - pos.x >= step)
            {
                m_selectedWidget->setSize({m_selectedWidget->getSize().x - step, m_selectedWidget->getSize().y});
                m_draggingPos.x -= step;
                updated = true;
            }
        }
        else if (m_draggingSelectionSquare == m_selectionSquares[5]) // Bottom
        {
            while (pos.y - m_draggingPos.y >= step)
            {
                m_selectedWidget->setSize({m_selectedWidget->getSize().x, m_selectedWidget->getSize().y + step});
                m_draggingPos.y += step;
                updated = true;
            }

            while (m_draggingPos.y - pos.y >= step)
            {
                m_selectedWidget->setSize({m_selectedWidget->getSize().x, m_selectedWidget->getSize().y - step});
                m_draggingPos.y -= step;
                updated = true;
            }
        }
        else if (m_draggingSelectionSquare == m_selectionSquares[7]) // Left
        {
            while (pos.x - m_draggingPos.x >= step)
            {
                m_selectedWidget->setPosition({m_selectedWidget->getPosition().x + step, m_selectedWidget->getPosition().y});
                m_selectedWidget->setSize({m_selectedWidget->getSize().x - step, m_selectedWidget->getSize().y});
                m_draggingPos.x += step;
                updated = true;
            }

            while (m_draggingPos.x - pos.x >= step)
            {
                m_selectedWidget->setPosition({m_selectedWidget->getPosition().x - step, m_selectedWidget->getPosition().y});
                m_selectedWidget->setSize({m_selectedWidget->getSize().x + step, m_selectedWidget->getSize().y});
                m_draggingPos.x -= step;
                updated = true;
            }
        }
        else // Corner
        {
            const float ratio = m_selectedWidget->getSize().y / m_selectedWidget->getSize().x;

            sf::Vector2f change;
            if (ratio <= 1)
                change = sf::Vector2f(step, step * ratio);
            else
                change = sf::Vector2f(step / ratio, step);

            if (m_draggingSelectionSquare == m_selectionSquares[0]) // Top left
            {
                while ((pos.x - m_draggingPos.x >= change.x) && (pos.y - m_draggingPos.y >= change.y))
                {
                    m_selectedWidget->setPosition({m_selectedWidget->getPosition().x + change.x, m_selectedWidget->getPosition().y + change.y});
                    m_selectedWidget->setSize({m_selectedWidget->getSize().x - change.x, m_selectedWidget->getSize().y - change.y});
                    m_draggingPos.x += change.x;
                    m_draggingPos.y += change.y;
                    updated = true;
                }

                while ((m_draggingPos.x - pos.x >= change.x) && (m_draggingPos.y - pos.y >= change.y))
                {
                    m_selectedWidget->setPosition({m_selectedWidget->getPosition().x - change.x, m_selectedWidget->getPosition().y - change.y});
                    m_selectedWidget->setSize({m_selectedWidget->getSize().x + change.x, m_selectedWidget->getSize().y + change.y});
                    m_draggingPos.x -= change.x;
                    m_draggingPos.y -= change.y;
                    updated = true;
                }
            }
            else if (m_draggingSelectionSquare == m_selectionSquares[2]) // Top right
            {
                while ((m_draggingPos.x - pos.x >= change.x) && (pos.y - m_draggingPos.y >= change.y))
                {
                    m_selectedWidget->setPosition({m_selectedWidget->getPosition().x, m_selectedWidget->getPosition().y + change.y});
                    m_selectedWidget->setSize({m_selectedWidget->getSize().x - change.x, m_selectedWidget->getSize().y - change.y});
                    m_draggingPos.x -= change.x;
                    m_draggingPos.y += change.y;
                    updated = true;
                }

                while ((pos.x - m_draggingPos.x >= change.x) && (m_draggingPos.y - pos.y >= change.y))
                {
                    m_selectedWidget->setPosition({m_selectedWidget->getPosition().x, m_selectedWidget->getPosition().y - change.y});
                    m_selectedWidget->setSize({m_selectedWidget->getSize().x + change.x, m_selectedWidget->getSize().y + change.y});
                    m_draggingPos.x += change.x;
                    m_draggingPos.y -= change.y;
                    updated = true;
                }
            }
            else if (m_draggingSelectionSquare == m_selectionSquares[4]) // Bottom right
            {
                while ((m_draggingPos.x - pos.x >= change.x) && (m_draggingPos.y - pos.y >= change.y))
                {
                    m_selectedWidget->setSize({m_selectedWidget->getSize().x - change.x, m_selectedWidget->getSize().y - change.y});
                    m_draggingPos.x -= change.x;
                    m_draggingPos.y -= change.y;
                    updated = true;
                }

                while ((pos.x - m_draggingPos.x >= change.x) && (pos.y - m_draggingPos.y >= change.y))
                {
                    m_selectedWidget->setSize({m_selectedWidget->getSize().x + change.x, m_selectedWidget->getSize().y + change.y});
                    m_draggingPos.x += change.x;
                    m_draggingPos.y += change.y;
                    updated = true;
                }
            }
            else if (m_draggingSelectionSquare == m_selectionSquares[6]) // Bottom left
            {
                while ((pos.x - m_draggingPos.x >= change.x) && (m_draggingPos.y - pos.y >= change.y))
                {
                    m_selectedWidget->setPosition({m_selectedWidget->getPosition().x + change.x, m_selectedWidget->getPosition().y});
                    m_selectedWidget->setSize({m_selectedWidget->getSize().x - change.x, m_selectedWidget->getSize().y - change.y});
                    m_draggingPos.x += change.x;
                    m_draggingPos.y -= change.y;
                    updated = true;
                }

                while ((m_draggingPos.x - pos.x >= change.x) && (pos.y - m_draggingPos.y >= change.y))
                {
                    m_selectedWidget->setPosition({m_selectedWidget->getPosition().x - change.x, m_selectedWidget->getPosition().y});
                    m_selectedWidget->setSize({m_selectedWidget->getSize().x + change.x, m_selectedWidget->getSize().y + change.y});
                    m_draggingPos.x -= change.x;
                    m_draggingPos.y += change.y;
                    updated = true;
                }
            }
        }
    }

    if (updated)
    {
        setChanged(true);
        updateSelectionSquarePositions();
        m_guiBuilder->reloadProperties();
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Form::selectWidget(tgui::Widget::Ptr widget)
{
    if (m_selectedWidget != widget)
    {
        m_selectedWidget = widget;

        if (widget)
        {
            updateSelectionSquarePositions();
            for (auto& square : m_selectionSquares)
                square->show();
        }
        else // No widget selected
        {
            for (auto& square : m_selectionSquares)
                square->hide();
        }
    }

    m_guiBuilder->widgetSelected(widget);
}
