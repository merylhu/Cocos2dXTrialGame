#include "Bullet.h"
#include "Definitions.h"

#define UPPER_SCREEN_PIPE_THRESHOLD 0.65
#define LOWER_SCREEN_PIPE_THRESHOLD 0.35
#define BULLET_SPEED 0.05

USING_NS_CC;

Bullet::Bullet()
{
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
}

void Bullet::SpawnBullet(cocos2d::Layer *layer,cocos2d::Vec2 Target)
{
	CCLOG("SPAWN Bullet");

	bulletSprite = Sprite::create("Bullet.png");

	auto BulletBody = PhysicsBody::createBox(bulletSprite->getContentSize());

	BulletBody->setDynamic(false);
	bulletSprite->setPhysicsBody(BulletBody);

	bulletSprite->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));

	//float magnitude = direction.x -
	direction = Point((direction.x -visibleSize.width / 2), direction.y - visibleSize.height / 2);

	layer->addChild(bulletSprite);
}

void Bullet::update()
{
	bulletSprite->setPositionY(bulletSprite->getPositionY() - (BULLET_SPEED * visibleSize.height));
}