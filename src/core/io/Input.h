#pragma once
#include <SFML/Window/Keyboard.hpp>
#include <unordered_map>
#include <SFML/Window/Event.hpp>
#include <optional>

namespace Input {

    enum class Key {
        Left,
        Right,
        Jump,
        Shoot
    };

    void update(); // Call this every frame in PlayState or Game loop

    bool isKeyPressed(Key key);  // Key is down (held)
    bool isKeyJustPressed(Key key); // Key was pressed this frame
    bool isKeyJustReleased(Key key); // Key was released this frame
    void processEvent(const sf::Event& event);

    // Optional: Mapping setup (for remapping keys)
    void setKeyMapping(Key key, sf::Keyboard::Scancode mappedKey);

}