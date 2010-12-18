#ifndef CHESS_CEGUI_H_INCLUDED
#define CHESS_CEGUI_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <CEGUI/CEGUI.h>
#include <map>

typedef std::map<sf::Key::Code, CEGUI::Key::Scan> t_keyMap;
typedef std::map<sf::Mouse::Button, CEGUI::MouseButton> t_mouseMap;

class t_chessCegui
{
public:
   void init();
   
   CEGUI::MouseButton mouse(sf::Mouse::Button);

private:
   t_keyMap keyMap;
   t_mouseMap mouseMap;
};


#endif
