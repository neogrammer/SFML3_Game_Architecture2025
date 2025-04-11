#include "Input.h"
#include <SFML/Window/Keyboard.hpp>

namespace {
    std::unordered_map<Input::Key, sf::Keyboard::Scancode> keyMapping = {
        { Input::Key::Left, sf::Keyboard::Scancode::A },
        { Input::Key::Right, sf::Keyboard::Scancode::D },
        { Input::Key::Jump, sf::Keyboard::Scancode::Space },
        { Input::Key::Shoot, sf::Keyboard::Scancode::J }
    };

    std::unordered_map<sf::Keyboard::Scancode, bool> currentKeys;
    std::unordered_map<sf::Keyboard::Scancode, bool> previousKeys;
}

namespace Input {

    void update() {
        // Copy current to previous for transition tracking
        previousKeys = currentKeys;

        for (auto& [key, sfKey] : keyMapping) {
            currentKeys[sfKey] = sf::Keyboard::isKeyPressed(sfKey);
        }



    }

    void processEvent(const sf::Event& event) {
        // KeyPressed Event
        if (event.is<sf::Event::KeyPressed>()) {
            const auto* keyPressed = event.getIf<sf::Event::KeyPressed>();
            if (!keyPressed) return;

            for (const auto& [actionKey, mappedScancode] : keyMapping) {
                if (keyPressed->scancode == mappedScancode) {
                    currentKeys[mappedScancode] = true;
                    break; // Found a match, exit loop
                }
            }
        }

        // KeyReleased Event
        else if (event.is<sf::Event::KeyReleased>()) {
            const auto* keyReleased = event.getIf<sf::Event::KeyReleased>();
            if (!keyReleased) return;

            for (const auto& [actionKey, mappedScancode] : keyMapping) {
                if (keyReleased->scancode == mappedScancode) {
                    currentKeys[mappedScancode] = false;
                    break; // Found a match, exit loop
                }
            }
        }
   
        // Ignore non-keyboard events (do nothing)
    }


    bool isKeyPressed(Key key) {
        sf::Keyboard::Scancode sfKey = keyMapping[key];
        return currentKeys[sfKey];
    }

    bool isKeyJustPressed(Key key) {
        sf::Keyboard::Scancode sfKey = keyMapping[key];
        return currentKeys[sfKey] && !previousKeys[sfKey];
    }

    bool isKeyJustReleased(Key key) {
        sf::Keyboard::Scancode sfKey = keyMapping[key];
        return !currentKeys[sfKey] && previousKeys[sfKey];
    }

    void setKeyMapping(Key key, sf::Keyboard::Scancode mappedKey) {
        keyMapping[key] = mappedKey;
    }

}