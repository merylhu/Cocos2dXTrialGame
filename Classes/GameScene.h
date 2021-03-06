#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "Enemy.h"
#include "Player.h"
#include "Bullet.h"

class GameScene : public cocos2d::Layer
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(GameScene);

private:
	void SetPhysicsWorld(cocos2d::PhysicsWorld *world) { sceneWorld = world; };

	void SpawnEnemy(float dt);

	bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);

	void update(float dt);

	void resetGame();

	void reset(float dt);

	cocos2d::PhysicsWorld *sceneWorld;

	std::vector<Enemy*> enemy;

	Player *player;

	std::vector<Bullet*> bullet;
	
	unsigned int score;

	cocos2d::Label *scoreLabel;

	cocos2d::Size visibleSize;

	cocos2d::Vec2 origin;

	float isInReset;
};

#endif // __Game_SCENE_H__