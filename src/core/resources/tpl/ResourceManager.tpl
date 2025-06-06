#include <stdexcept> //runtime_error
#include <utility> //forward


template<typename RESOURCE,typename IDENTIFIER>
template<typename ... Args>
void ResourceManager<RESOURCE,IDENTIFIER>::load(const IDENTIFIER& id,Args&& ... args)
{
    std::unique_ptr<RESOURCE> ptr(new RESOURCE);
    if(not ptr->loadFromFile(std::forward<Args>(args)...))
        throw std::runtime_error("Impossible to load file");
    _map.emplace(id,std::move(ptr));
}

template<typename RESOURCE,typename IDENTIFIER>
void ResourceManager<RESOURCE,IDENTIFIER>::unload(const IDENTIFIER& id)
{
    _map.at(id).reset();
}

template<typename RESOURCE,typename IDENTIFIER>
void ResourceManager<RESOURCE,IDENTIFIER>::unloadAll()
{
   
}

template<typename RESOURCE,typename IDENTIFIER>
RESOURCE& ResourceManager<RESOURCE,IDENTIFIER>::get(const IDENTIFIER& id)const
{
    return *_map.at(id);
}

//sf::Music special case
template<typename IDENTIFIER>
template<typename ... Args>
void ResourceManager<sf::Music,IDENTIFIER>::load(const IDENTIFIER& id,Args&& ... args)
{
    std::unique_ptr<sf::Music> ptr(new sf::Music);

    if(not ptr->openFromFile(std::forward<Args>(args)...))
        throw std::runtime_error("Impossible to load file");
    _map.emplace(id,std::move(ptr));
};

template<typename IDENTIFIER>
sf::Music& ResourceManager<sf::Music,IDENTIFIER>::get(const IDENTIFIER& id) const
{
    return *_map.at(id);
}

template<typename IDENTIFIER>
template<typename ... Args>
void ResourceManager<sf::Font,IDENTIFIER>::load(const IDENTIFIER& id,Args&& ... args)
{
    std::unique_ptr<sf::Font> ptr(new sf::Font);

    if(not ptr->openFromFile(std::forward<Args>(args)...))
        throw std::runtime_error("Impossible to load file");
    _map.emplace(id,std::move(ptr));
};

template<typename IDENTIFIER>
sf::Font& ResourceManager<sf::Font,IDENTIFIER>::get(const IDENTIFIER& id) const
{
    return *_map.at(id);
}

