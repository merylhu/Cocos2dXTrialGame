#include "Bullet.h"
#include "Definitions.h"

#define UPPER_SCREEN_PIPE_THRESHOLD 0.65
#define LOWER_SCREEN_PIPE_THRESHOLD 0.35
#define BULLET_SPEED 1.5

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

	BulletBody = PhysicsBody::createBox(bulletSprite->getContentSize());

	BulletBody->setDynamic(false);
	bulletSprite->setPhysicsBody(BulletBody);

	bulletSprite->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));

	float magnitude = sqrt(pow( visibleSize.width / 2- Target.x, 2) + pow(visibleSize.height / 2 - Target.y, 2));
	//CCLOG("magnitude%f", direction);
	direction = Point((visibleSize.width / 2 - Target.x)/magnitude, (visibleSize.height / 2 - Target.y)/magnitude);

	layer->addChild(bulletSprite);
}

void Bullet::update()
{
	if (isShooting)
	{
		bulletSprite->setPositionX(bulletSprite->getPositionX() - (BULLET_SPEED * direction.x));
		bulletSprite->setPositionY(bulletSprite->getPositionY() + (BULLET_SPEED * direction.y));
		//CCLOG("direction %f %f", direction.x, direction.x);
	}
	else
	{
		// make it invisible
	}
}

cocos2d::CCRect Bullet::getBoundingBox()
{
	CCRect bulletRect = CCRectMake(
		bulletSprite->getPosition().x - (bulletSprite->getContentSize().width / 2),
		bulletSprite->getPosition().y - (bulletSprite->getContentSize().height / 2),
		bulletSprite->getContentSize().width,
		bulletSprite->getContentSize().height);

	return bulletRect;
}
void Bullet::removeSpriteFromScene()
{
	BulletBody->getNode()->removeFromParent();
}