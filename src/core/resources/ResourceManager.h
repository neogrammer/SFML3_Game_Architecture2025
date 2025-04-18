#ifndef RESOURCEMANAGER_H__
#define RESOURCEMANAGER_H__

#include <unordered_map> //unordered_map
#include <string> //string
#include <memory> //unique_ptr
#include <SFML/Audio.hpp> //sf::Music

template<typename RESOURCE,typename IDENTIFIER = int>
struct ResourceManager
{
    ResourceManager() {  }
    ~ResourceManager<RESOURCE,IDENTIFIER>() {  };
    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;


    template<typename ... Args>
    void load(const IDENTIFIER& id,Args&& ... args);


    void unload(const IDENTIFIER& id);

    void unloadAll();

    RESOURCE& get(const IDENTIFIER& id)const;

    void clear() { this->_map.clear(); }

private:
    std::unordered_map<IDENTIFIER, std::unique_ptr<RESOURCE>> _map;
};

template<typename IDENTIFIER>
struct ResourceManager<sf::Music,IDENTIFIER>
{
    ResourceManager() {  }
    ~ResourceManager<sf::Music,IDENTIFIER>() {}
    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;


    template<typename ... Args>
    void load(const IDENTIFIER& id,Args&& ... args);

    sf::Music& get(const IDENTIFIER& id)const;

    void clear() {this-> _map.clear(); }

private:
    std::unordered_map<IDENTIFIER, std::unique_ptr<sf::Music>> _map;
};

template<typename IDENTIFIER>
struct ResourceManager<sf::Font, IDENTIFIER>
{
    ResourceManager() { }
    ~ResourceManager<sf::Font,IDENTIFIER>() {}
    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;


    template<typename ... Args>
    void load(const IDENTIFIER& id, Args&& ... args);

    sf::Font& get(const IDENTIFIER& id)const;
    void clear() {this-> _map.clear(); }
private:
    std::unordered_map<IDENTIFIER, std::unique_ptr<sf::Font>> _map;
};

#include "tpl/ResourceManager.tpl"
#endif
