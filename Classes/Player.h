#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "cocos2d.h"

class Player
{
public:
	Player();

	void SpawnPlayer(cocos2d::Layer *layer);
	cocos2d::CCRect getBoundingBox();
	void removeSpriteFromScene();

private:
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;
	cocos2d::Sprite* PlayerSprite;
	cocos2d::PhysicsBody* PlayerBody;

};

#endif // __Player_H__