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

	PlayerSprite = Sprite::create("home.png");

	PlayerBody = PhysicsBody::createBox(PlayerSprite->getContentSize());
	
	PlayerBody->setDynamic(false);
	PlayerSprite->setPhysicsBody(PlayerBody);

	PlayerSprite->setPosition(Point(visibleSize.width/2, visibleSize.height/2));

	layer->addChild(PlayerSprite);

}

CCRect Player::getBoundingBox()
{
	CCRect PlayerRect = CCRectMake(
		PlayerSprite->getPosition().x - (PlayerSprite->getContentSize().width / 2),
		PlayerSprite->getPosition().y - (PlayerSprite->getContentSize().height / 2),
		PlayerSprite->getContentSize().width,
		PlayerSprite->getContentSize().height);

	return PlayerRect;
}

void Player::removeSpriteFromScene()
{
	PlayerBody->getNode()->removeFromParent();
}