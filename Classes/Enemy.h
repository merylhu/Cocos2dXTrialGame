#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "cocos2d.h"
#include "Player.h"
#include "Bullet.h"

class Enemy
{
public:
	Enemy();

	void SpawnEnemy(cocos2d::Layer *layer);
	void update();
	cocos2d::CCRect getBoundingBox();
	void removeSpriteFromScene();

private:
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;
	cocos2d::Sprite* EnemySprite;
	bool isActive = false;
	cocos2d::PhysicsBody* EnemyBody;
};

#endif // __Enemy_H__