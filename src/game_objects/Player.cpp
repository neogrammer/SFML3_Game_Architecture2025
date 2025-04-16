#include "Player.h"

Player::Player() : AnimObject{Cfg::Textures::MegaManSheet1x48x48x1,{{0,0},{48,48}},{0.f,0.f},{48.f,48.f},{0.f,0.f}}
{
	loadInFile("Player.anim");
}

Player::~Player()
{

}