#include "chessCegui.h"

void t_chessCegui::init()
{
//   mouseMap[sf::Mouse::Butt
   mouseMap[sf::Mouse::Button::Left] = CEGUI::MouseButton::LeftButton;
   mouseMap[sf::Mouse::Button::Right] = CEGUI::MouseButton::RightButton;
   mouseMap[sf::Mouse::Button::Middle] = CEGUI::MouseButton::MiddleButton;
   mouseMap[sf::Mouse::Button::XButton1] = CEGUI::MouseButton::X1Button;
   mouseMap[sf::Mouse::Button::XButton2] = CEGUI::MouseButton::X2Button;
   mouseMap[sf::Mouse::Button::ButtonCount] = CEGUI::MouseButton::MouseButtonCount;
}
   

CEGUI::MouseButton t_chessCegui::mouse(sf::Mouse::Button code)
{
   return mouseMap[code];
}
