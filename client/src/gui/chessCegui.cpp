#include "chessCegui.h"

void t_chessCegui::init()
{
   mouseMap[sf::Mouse::Button::Left] = CEGUI::MouseButton::LeftButton;
   mouseMap[sf::Mouse::Button::Right] = CEGUI::MouseButton::RightButton;
   mouseMap[sf::Mouse::Button::Middle] = CEGUI::MouseButton::MiddleButton;
   mouseMap[sf::Mouse::Button::XButton1] = CEGUI::MouseButton::X1Button;
   mouseMap[sf::Mouse::Button::XButton2] = CEGUI::MouseButton::X2Button;
   mouseMap[sf::Mouse::Button::ButtonCount] = CEGUI::MouseButton::MouseButtonCount;

   keyMap[sf::Key::Code::A] = CEGUI::Key::Scan::A;
   keyMap[sf::Key::Code::B] = CEGUI::Key::Scan::B;
   keyMap[sf::Key::Code::C] = CEGUI::Key::Scan::C;
   keyMap[sf::Key::Code::D] = CEGUI::Key::Scan::D;
   keyMap[sf::Key::Code::E] = CEGUI::Key::Scan::E;
   keyMap[sf::Key::Code::F] = CEGUI::Key::Scan::F;
   keyMap[sf::Key::Code::G] = CEGUI::Key::Scan::G;
   keyMap[sf::Key::Code::H] = CEGUI::Key::Scan::H;
   keyMap[sf::Key::Code::I] = CEGUI::Key::Scan::I;
   keyMap[sf::Key::Code::J] = CEGUI::Key::Scan::J;
   keyMap[sf::Key::Code::K] = CEGUI::Key::Scan::K;
   keyMap[sf::Key::Code::L] = CEGUI::Key::Scan::L;
   keyMap[sf::Key::Code::M] = CEGUI::Key::Scan::M;
   keyMap[sf::Key::Code::N] = CEGUI::Key::Scan::N;
   keyMap[sf::Key::Code::O] = CEGUI::Key::Scan::O;
   keyMap[sf::Key::Code::P] = CEGUI::Key::Scan::P;
   keyMap[sf::Key::Code::Q] = CEGUI::Key::Scan::Q;
   keyMap[sf::Key::Code::R] = CEGUI::Key::Scan::R;
   keyMap[sf::Key::Code::S] = CEGUI::Key::Scan::S;
   keyMap[sf::Key::Code::T] = CEGUI::Key::Scan::T;
   keyMap[sf::Key::Code::U] = CEGUI::Key::Scan::U;
   keyMap[sf::Key::Code::V] = CEGUI::Key::Scan::U;
   keyMap[sf::Key::Code::W] = CEGUI::Key::Scan::U;
   keyMap[sf::Key::Code::X] = CEGUI::Key::Scan::U;
   keyMap[sf::Key::Code::Y] = CEGUI::Key::Scan::U;
   keyMap[sf::Key::Code::Z] = CEGUI::Key::Scan::U;

   keyMap[sf::Key::Code::Up] = CEGUI::Key::Scan::ArrowUp;
   keyMap[sf::Key::Code::Left] = CEGUI::Key::Scan::ArrowLeft;
   keyMap[sf::Key::Code::Right] = CEGUI::Key::Scan::ArrowRight;
   keyMap[sf::Key::Code::Down] = CEGUI::Key::Scan::ArrowDown;


   keyMap[sf::Key::Code::Back] = CEGUI::Key::Scan::Backspace;

}
   

CEGUI::MouseButton t_chessCegui::mouse(sf::Mouse::Button code)
{
   return mouseMap[code];
}
   
CEGUI::Key::Scan t_chessCegui::key(sf::Key::Code code)
{
   return keyMap[code];
}
