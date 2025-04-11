#ifndef STATEBASE_H__
#define STATEBASE_H__

#include <SFML/Graphics/RenderWindow.hpp>
#include <string>
class GStateMgr;


class StateBase
{
protected:
	GStateMgr* pStateMgr;
	sf::RenderWindow* pWnd;
	float* pGameTime;

	void removeMe();
	void pushState(int index);
	void changeState(int index);
public:
	StateBase();
	StateBase(GStateMgr& stateMgr, sf::RenderWindow* wnd_, float* dt_);
	virtual ~StateBase() = 0;
	StateBase(const StateBase& o);
	StateBase& operator=(const StateBase& o);
	StateBase(StateBase&& o) noexcept;
	StateBase& operator=(StateBase&& o) noexcept;

	virtual std::string processEvents();
	virtual std::string runScripts();
	virtual std::string handleInput();
	virtual std::string update() = 0;
	virtual std::string finalize() = 0;
	virtual std::string render() = 0;
	virtual std::string tick() = 0;

};

#endif