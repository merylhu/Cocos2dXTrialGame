#include "Enemy.h"
#include "Definitions.h"

#define UPPER_SCREEN_PIPE_THRESHOLD 0.65
#define LOWER_SCREEN_PIPE_THRESHOLD 0.35

USING_NS_CC;

Enemy::Enemy()
{
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
}

void Enemy::SpawnEnemy(cocos2d::Layer *layer)
{
	CCLOG("SPAWN Enemy");

	auto EnemySprite = Sprite::create("Enemy.png");

	auto EnemyBody = PhysicsBody::createBox(EnemySprite->getContentSize());

	Point TilePoints[10];

	TilePoints[0] = Point(origin.x + EnemySprite->getContentSize().width / 2, origin.y+EnemySprite->getContentSize().height/2);

	EnemyBody->setDynamic(false);
	EnemySprite->setPhysicsBody(EnemyBody);

	EnemySprite->setPosition(TilePoints[0]);

	layer->addChild(EnemySprite);
}