#include "Player.h"
#include "Definitions.h"

USING_NS_CC;

Player::Player()
{
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
}

void Player::SpawnPlayer(cocos2d::Layer *layer)
{
	CCLOG("SPAWN Player");

	auto PlayerSprite = Sprite::create("home.png");

	auto PlayerBody = PhysicsBody::createBox(PlayerSprite->getContentSize());
	
	PlayerBody->setDynamic(false);
	PlayerSprite->setPhysicsBody(PlayerBody);

	PlayerSprite->setPosition(Point(visibleSize.width/2, visibleSize.height/2));

	layer->addChild(PlayerSprite);

}