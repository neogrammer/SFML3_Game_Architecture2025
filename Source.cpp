#include "imgui.h"
#include "imgui-SFML.h"
#include <core/app/AGameApp.h>
#include <iostream>
#include <core/resources/Cfg.h>
int main(int argc, char* argv[])
{
    Cfg::Initialize();

    AGameApp app{};

    try
    {
        app.run();
    }
    catch (std::exception& e)
    {
        const auto* message = e.what();
        std::cout << "\n" << e.what() << std::endl;
    }



	//sf::RenderWindow window(sf::VideoMode({ 1600, 900 }),"SFML3 Game", sf::Style::Titlebar | sf::Style::Close, sf::State::Windowed);
 //   bool soWhat = ImGui::SFML::Init(window, false);
 //   soWhat = false;

 //   auto& IO = ImGui::GetIO();
 //  IO.Fonts->Clear(); // clear fonts if you loaded some before (even if only default one was loaded)
 //   // IO.Fonts->AddFontDefault(); // this will load default font as well
 //   IO.Fonts->AddFontFromFileTTF("Assets\\Fonts\\Crusty.ttf", 18.f);

 //

 //   // change the position of the window (relatively to the desktop)
 //   window.setPosition({ 400, 200 });

 //   // change the title of the window
 //   window.setTitle("SFML window");
 //   // run the program as long as the window is open
 //   sf::Clock deltaClock;
 //  
 //   

 //   
 //   while (window.isOpen())
 //   {
 //       // check all the window's events that were triggered since the last iteration of the loop
 //       while (const std::optional event = window.pollEvent())
 //       {
 //           ImGui::SFML::ProcessEvent(window, *event);
 //           // "close requested" event: we close the window
 //           if (event->is<sf::Event::Closed>())
 //               window.close();
 //           else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
 //           {
 //               if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
 //                   window.close();
 //           }
 //       }


 //       soWhat = ImGui::SFML::UpdateFontTexture(); // important call: updates font texture
 //       ImGui::SFML::Update(window, deltaClock.restart());

 //       ImGui::Begin("Hello, world!");
 //       ImGui::Button("Look at this pretty button");
 //       ImGui::End();

 //       window.clear(sf::Color(47, 147, 247, 255));


 //       ImGui::SFML::Render(window);
 //       window.display();

 //   }

 //   ImGui::SFML::Shutdown();
	return 69;

}