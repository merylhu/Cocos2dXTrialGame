#ifndef __BULLET_H__
#define __BULLET_H__

#include "cocos2d.h"

class Bullet
{
public:
	Bullet();

	void SpawnBullet(cocos2d::Layer *layer,cocos2d::Vec2 Target);
	void update();

private:
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;
	cocos2d::Point direction;
	cocos2d::Sprite* bulletSprite;

};

#endif // __Bullet_H__