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

	EnemySprite = Sprite::create("Enemy.png");

	 EnemyBody = PhysicsBody::createBox(EnemySprite->getContentSize());

	Point TilePoints[10];

	TilePoints[0] = Point(origin.x + EnemySprite->getContentSize().width / 2, origin.y+EnemySprite->getContentSize().height/2);
	TilePoints[1] = Point(origin.x + EnemySprite->getContentSize().width , origin.y + EnemySprite->getContentSize().height / 2);
	TilePoints[2] = Point(origin.x + EnemySprite->getContentSize().width, origin.y + EnemySprite->getContentSize().height);
	TilePoints[3] = Point(origin.x + EnemySprite->getContentSize().width *1.5, origin.y + EnemySprite->getContentSize().height / 2);
	//TilePoints[0] = Point(origin.x + EnemySprite->getContentSize().width / 2, origin.y + EnemySprite->getContentSize().height / 2);
	//TilePoints[0] = Point(origin.x + EnemySprite->getContentSize().width / 2, origin.y + EnemySprite->getContentSize().height / 2);

	EnemyBody->setDynamic(false);
	EnemySprite->setPhysicsBody(EnemyBody);

	EnemySprite->setPosition(TilePoints[rand()%4]);
	isActive = true;

	layer->addChild(EnemySprite);
}

void Enemy::update()
{
	//Flag driven and update based;
	
	if (this->isActive && EnemySprite != NULL)
	{
		//send event to release and destroy and kill from game scene list;
	// update direction
		//CCLOG("isActive value %b", this->isActive);
		float magnitude = sqrt(pow(visibleSize.width / 2 - EnemySprite->getPositionX(), 2) + pow(visibleSize.height / 2 - EnemySprite->getPositionY(), 2));
		//CCLOG("magnitude%f", direction);
		Point direction = Point((visibleSize.width / 2 - EnemySprite->getPositionX()) / magnitude, (visibleSize.height / 2 - EnemySprite->getPositionY()) / magnitude);

		EnemySprite->setPositionX(EnemySprite->getPositionX() + direction.x * 0.5);
		EnemySprite->setPositionY(EnemySprite->getPositionY() + direction.y * 0.5);

	}
}

cocos2d::CCRect Enemy::getBoundingBox()
{

	CCRect enemyRect = CCRectMake(
		EnemySprite->getPosition().x - (EnemySprite->getContentSize().width / 2),
		EnemySprite->getPosition().y - (EnemySprite->getContentSize().height / 2),
		EnemySprite->getContentSize().width,
		EnemySprite->getContentSize().height);
	return enemyRect;
}

void Enemy::removeSpriteFromScene()
{
	EnemyBody->getNode()->removeFromParent();
}