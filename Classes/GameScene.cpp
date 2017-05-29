#include "GameScene.h"
#include "Definitions.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	// 'layer' is an autorelease object
	auto layer = GameScene::create();
	layer->SetPhysicsWorld(scene->getPhysicsWorld());

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	auto backgroundSprite = Sprite::create("Background.png");
	backgroundSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	this->addChild(backgroundSprite);

	auto edgeBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);

	auto edgeNode = Node::create();
	edgeNode->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	edgeNode->setPhysicsBody(edgeBody);

	player = new Player();
	player->SpawnPlayer(this);

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);

	score = 0;

	__String *tempScore = __String::createWithFormat("%i", score);

	scoreLabel = Label::createWithTTF(tempScore->getCString(), "fonts/Marker Felt.ttf", visibleSize.height * 0.2);
	scoreLabel->setColor(Color3B::WHITE);
	scoreLabel->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height * 0.75 + origin.y));
	
	this->addChild(edgeNode);

	this->schedule(schedule_selector(GameScene::SpawnEnemy), 1.5);

	this->addChild(scoreLabel, 10000);

	this->scheduleUpdate();

	return true;
}

void GameScene::SpawnEnemy(float dt)
{
	if (isInReset <= 0)
	{
		Enemy *e = new Enemy();
		e->SpawnEnemy(this);
		enemy.push_back(e);
	}
	isInReset = isInReset - dt;
}

bool GameScene::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
	Bullet *b = new Bullet();
	b->SpawnBullet(this, touch->getLocationInView());

	b->setIsShooting();
	bullet.push_back(b);

	return true;
}

void GameScene::update(float dt)
{
	// move objects
	for (auto b : bullet)
		b->update();

	for(auto e : enemy)
	 e->update();

	// Collision Checks after moving;

	std::vector<Enemy*> remove_enemy;
	std::vector<Bullet*> remove_bullet;

	for (auto e : enemy)
	{
		if (e->getBoundingBox().intersectsRect(player->getBoundingBox()))
		{
			resetGame();
			return;
		}
		for (auto b : bullet)
			if (e->getBoundingBox().intersectsRect(b->getBoundingBox()))
			{
				remove_enemy.push_back(e);
				remove_bullet.push_back(b);
			}
	}
	for (int i = 0; i < remove_bullet.size(); i++)
	{
		auto iter = std::find(bullet.begin(), bullet.end(), remove_bullet[i]);

		if (iter != bullet.end())
		{
			bullet.erase(iter);
		}
	}

	for (int j = 0; j < remove_enemy.size(); j++)
	{
		auto iter = std::find(enemy.begin(), enemy.end(), remove_enemy[j]);

		if (iter != enemy.end())
		{
			score++;
			enemy.erase(iter);
		}
	}

	//UpdateScore

	__String *tempScore = __String::createWithFormat("%i", score);

	scoreLabel->setString(tempScore->getCString());

	for (auto b : remove_bullet)
	{
		b->removeSpriteFromScene();
		delete b;
	}
	for (auto e : remove_enemy)
	{
		e->removeSpriteFromScene();
		delete e;
	}

	remove_bullet.clear();
	remove_enemy.clear();

}

void GameScene::resetGame()
{
	for (auto b : bullet)                                                                                              
	{
		b->removeSpriteFromScene();
		delete b;
	}

	for (auto e : enemy)
	{
		e->removeSpriteFromScene();
		delete e;
	}

	bullet.clear();
	enemy.clear();

	scoreLabel->setPosition(Point(visibleSize.width *0.25 + origin.x, visibleSize.height * 0.5 + origin.y));
	
	isInReset = 1.0;

	this->scheduleOnce(schedule_selector(GameScene::reset), 1.0);
}

void GameScene::reset(float dt)
{
	score = 0;

	__String *tempScore = __String::createWithFormat("%i", score);

	scoreLabel->setString(tempScore->getCString());

	scoreLabel->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height * 0.75 + origin.y));

}