#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "cocos2d.h"

class Player
{
public:
	Player();

	void SpawnPlayer(cocos2d::Layer *layer);

private:
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;

};

#endif // __Player_H__