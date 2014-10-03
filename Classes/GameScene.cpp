/****************************************************************************
 
 Jumper Source Code
 
 Copyright (c) 2014 GameAcademy.com
 
 www.GameAcademy.com
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 
 ****************************************************************************/
 
#include "GameScene.h"
#include "MainScene.h"
#include "GameOverScene.h"

#include "SimpleAudioEngine.h"

//  Bonus prize Images
const char * bonus_image[]=
{
	"50.png",
	"100.png",
    "power.png"
};

// Initialize the GameScene
bool GameScene::init()
{
//	CCLog("GameScene::init");
    bool bRet = false;
    do 
    {
        coin50Platform = 12;
        coin100Platform = 15;
        coinJumpPlatform = 25;
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("GameFieldMusic.mp3", true);
        target_Score = 10000;
        //////////////////////////////////////////////////////////////////////////
        // super init first
        //////////////////////////////////////////////////////////////////////////
        CC_BREAK_IF(! CCLayer::init());

		// Initialize the parent - gets the sprite sheet loaded, sets the background and inits the clouds
		MainScene::init();

		// Start off as game suspended
		gameSuspended = true;

		// Get the jumper sprite
		jumper = CCSprite::create("jumper_0.png");
        this->addChild(jumper, 4, kjumper);
        CCArray * animArr = CCArray::create();
        for (int i = 0 ; i < 16; i++)
        {
            CCString * tempString  = CCString::createWithFormat("jumper_%d.png",i);
            CCSpriteFrame * tempFrame = CCSpriteFrame::create(tempString->getCString(),CCRectMake(jumper->getPosition().x, jumper->getPosition().y, jumper->getContentSize().width, jumper->getContentSize().height));
            animArr->addObject(tempFrame);
        }
        CCAnimation * jumpAnimation = CCAnimation::createWithSpriteFrames(animArr,0.1);
        jumpAnimate = CCAnimate::create(jumpAnimation);
        jumpAnimate->retain();

        coin50Anim = CCArray::create();
        coin100Anim = CCArray::create();
        coinJumpAnim = CCArray::create();
        
        CCSprite * coin1  = CCSprite::create("coin_1/coin50_1.png");
        for (int i = 1;i < 20 ; i++)
        {
            CCString * tempString  = CCString::createWithFormat("coin_1/coin50_%d.png",i);
            CCSpriteFrame * tempFrame = CCSpriteFrame::create(tempString->getCString(),CCRectMake(coin1->getPosition().x, coin1->getPosition().y, coin1->getContentSize().width, coin1->getContentSize().height));
            coin50Anim->addObject(tempFrame);
        }
        
        coin50Anim->retain();
        
        CCSprite * coin2  = CCSprite::create("coin_2/coin100_1.png");

        for (int i = 1;i < 20 ; i++)
        {
            CCString * tempString  = CCString::createWithFormat("coin_2/coin100_%d.png",i);
            CCSpriteFrame * tempFrame = CCSpriteFrame::create(tempString->getCString(),CCRectMake(coin2->getPosition().x, coin2->getPosition().y, coin2->getContentSize().width, coin2->getContentSize().height));
            coin100Anim->addObject(tempFrame);
        }
        coin100Anim->retain();
      

        
        
        CCSprite * coin3  = CCSprite::create("powerup/coinJump_1.png");
        for (int i = 1;i < 20 ; i++)
        {
            CCString * tempString  = CCString::createWithFormat("powerup/coinJump_%d.png",i);
            CCSpriteFrame * tempFrame = CCSpriteFrame::create(tempString->getCString(),CCRectMake(coin3->getPosition().x, coin3->getPosition().y, coin3->getContentSize().width, coin3->getContentSize().height));
            coinJumpAnim->addObject(tempFrame);
        }
        coinJumpAnim->retain();
        
        CCTexture2D *texture = CCTextureCache::sharedTextureCache()->addImage("fx-leafe.png");
        particles = CCParticleFireworks::create();
        particles->setTexture( texture );
        particles->setLife(0.5);
        particles->setEmissionRate(100);
        particles->setPosVar(ccp(10,5));
        particles->setSpeed(60);
        particles->setPosition(0, 0);
        particles->setAngle(90);
        particles->setAngleVar(270);
        particles->setStartSize(10.0);
        particles->setStartSizeVar(5);
        particles->setStartColor( ccc4f(1.0,1.0,1.0,1.0) );
        particles->setEndColor(ccc4f(1.0,1.0,1.0,0.0) );
        particles->setStartSpin(-90);
        particles->setStartSpinVar(30);
        particles->setEndSpin(-90);
        particles->setEndSpinVar(30);
        particles->setSpeedVar(30);
        particles->setPositionType(	kCCPositionTypeGrouped );
        this->addChild(particles, 10);
        particles_counter = 1;
        
		// Initialize the platforms
       
        
        for(int i=0; i<kNumCoines; i++)
		{
            CCSprite *bonus = CCSprite::create("coin_1/coin50_1.png");
            this->addChild(bonus,4, kBonusStartTag+i);
            bonus->setScale(2.0);
            CCAnimation * coin50Animation = CCAnimation::createWithSpriteFrames(coin50Anim,0.03);
            CCAnimate * coin50Animate = CCAnimate::create(coin50Animation);
            
            bonus->runAction(CCRepeatForever::create(coin50Animate));
                bonus->setVisible(false);
            bonus = NULL;
		}
        for(int i=0; i<kNumCoines; i++)
		{
            CCSprite *bonus = CCSprite::create("coin_2/coin100_1.png");
            bonus->setScale(2.0);
            this->addChild(bonus,4, kBonusStartTag+i+30);
            CCAnimation * coin100Animation = CCAnimation::createWithSpriteFrames(coin100Anim,0.03);
             CCAnimate * coin100Animate = CCAnimate::create(coin100Animation);
             bonus->runAction(CCRepeatForever::create(coin100Animate));
            bonus->setVisible(false);
            bonus = NULL;
		}
        for(int i=0; i<kNumCoines; i++)
		{
            CCSprite *bonus = CCSprite::create("powerup/coinJump_1.png");
            this->addChild(bonus,4, kBonusStartTag+i+60);
            bonus->setScale(2.0);
            CCAnimation * coinJumpAnimation = CCAnimation::createWithSpriteFrames(coinJumpAnim,0.03);
            CCAnimate * coinJumpAnimate = CCAnimate::create(coinJumpAnimation);

             bonus->runAction(CCRepeatForever::create(coinJumpAnimate));
            bonus->setVisible(false);
            bonus = NULL;
		}
		initPlatforms();
        initTree();
		// Create the bonus sprite
		

		// Load in the bonus images, 5, 10, 50, 100
		

		// Create the Score Label
		CCLabelTTF* scoreLabel = CCLabelTTF::create("0",  "Arial", 15.0);
		this->addChild(scoreLabel, 5, kScoreLabel);

		// Center the label
		scoreLabel->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width/2,CCDirector::sharedDirector()->getWinSize().height - 50));

		// Start the GameScene stepping
		schedule(schedule_selector(GameScene::step));

		// Enable the touch events
		setTouchEnabled(true);
		// Enable accelerometer events
		setAccelerometerEnabled(true);

		// Start the game
		startGame();

        bRet = true;
    } while (0);

    return bRet;
}


// Initialize the platforms that the jumper jumps on
void GameScene::initPlatforms(void)
{
//	CCLog("initPlatforms");
	isPowerPicked = false;
	currentPlatformTag = kPlatformsStartTag;
	while(currentPlatformTag < kPlatformsStartTag + kNumPlatforms) 
	{
		initPlatform();
		currentPlatformTag++;
	}
	
	resetPlatforms();
}
void GameScene::initTree(void)
{
    CCSprite * tree1;
    tree1 = CCSprite::create("tree.png");
    tree1->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width*0.5, CCDirector::sharedDirector()->getWinSize().height*.5));
    tree1->setTag(kTree1Tag);
    this->addChild(tree1,2);
    
    CCSprite * tree11;
    tree11 = CCSprite::create("tree2.png");
    tree11->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width*0.5, CCDirector::sharedDirector()->getWinSize().height*.5));
    tree11->setTag(kTree11Tag);
    this->addChild(tree11,2);
    
    CCSprite * tree2;
    tree2 = CCSprite::create("tree.png");
    tree2->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width*0.5, CCDirector::sharedDirector()->getWinSize().height*1.5));
    tree2->setTag(kTree2Tag);
    this->addChild(tree2,2);
    
    
    CCSprite * tree22;
    tree22 = CCSprite::create("tree2.png");
    tree22->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width*0.5, CCDirector::sharedDirector()->getWinSize().height*1.5));
    tree22->setTag(kTree22Tag);
    this->addChild(tree22,2);
    
    CCSprite * tree3;
    tree3 = CCSprite::create("tree.png");
    tree3->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width*0.5, CCDirector::sharedDirector()->getWinSize().height*2.5));
    tree3->setTag(kTree3Tag);
    this->addChild(tree3,2);
    
    CCSprite * tree33;
    tree33 = CCSprite::create("tree2.png");
    tree33->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width*0.5, CCDirector::sharedDirector()->getWinSize().height*2.5));
    tree33->setTag(kTree33Tag);
    this->addChild(tree33,2);
}
// Supports Two types of platforms although only one exists in the art.
void GameScene::initPlatform(void)
{
	CCSprite *platform;
    
    CCLog("currentPlatformTag  %d",currentPlatformTag);
    if (currentPlatformTag == kKillerPlatformTag)
    {
        platform = CCSprite::create("platform3.png");
        this->addChild(platform, 3, currentPlatformTag);
    }
    else
    {
        switch(rand()%2)
        {
            case 0: 
                platform = CCSprite::create("platform1.png");
                this->addChild(platform, 3, currentPlatformTag);

                break;
            case 1: 
                platform = CCSprite::create("platform2.png");
                this->addChild(platform, 3, currentPlatformTag);
                break;
        }
    }
}

// Initializes everything and then starts the game by setting the gameSuspend
void GameScene::startGame(void)
{
//	CCLog("startGame");

	score = 0;
	
	resetClouds();
	resetPlatforms();
	resetjumper();
//	resetBonus();
//    resetTree();
	
	gameSuspended = false;
}

// Reset the platforms as they move off the screen
void GameScene::resetPlatforms(void)
{
//	CCLog("resetPlatforms");
	
	currentPlatformY = -1;						// Set the current platform y to -1 so it gets initialized
	currentPlatformTag = kPlatformsStartTag;	// set starting platform
	currentMaxPlatformStep = 60.0f;				// maximum space between platforms
	currentBonusPlatformIndex = 0;
	currentBonusType = 0;
	platformCount = 0;
    coin100Count = kBonusStartTag+30;
    coin50Count = kBonusStartTag;
    coinJumpCount = kBonusStartTag+60;
	while(currentPlatformTag < kPlatformsStartTag + kNumPlatforms) 
	{
		resetPlatform();
		currentPlatformTag++;
//        coin50Count++;
//        coin100Count++;
//        coinJumpCount++;
//        if (coin50Count == (kBonusStartTag + kNumCoines))
//        {
//            coin50Count--;
//        }
//        if (coin100Count == (kBonusStartTag + kNumCoines+30))
//        {
//            coin100Count--;
//            
//        }
//        if (coinJumpCount == (kBonusStartTag + kNumCoines + 60))
//        {
//            coinJumpCount--;
//        }
	}
}
void GameScene::resetTree(void)
{
    for (int i = kTree1Tag; i <= kTree3Tag; i++)
    {
        float delta = jumper_pos.y - ((float)CCDirector::sharedDirector()->getWinSize().height / 2);
        CCSprite * tree = (CCSprite *)this->getChildByTag(i);
        tree->setPosition(ccp(tree->getPosition().x,tree->getPosition().y-delta));
        if (tree->getPosition().y <= -0.5*CCDirector::sharedDirector()->getWinSize().height )
        {
            float posY;
            if (i == kTree1Tag)
            {
                CCSprite * temp = (CCSprite *)this->getChildByTag(kTree3Tag);
                if (isPowerPicked)
                {
                    posY = temp->getPosition().y + temp->getContentSize().height*0.94;
                }
                else
                {
                    posY = temp->getPosition().y + temp->getContentSize().height*0.97;
                }
                
                tree->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width*0.5, posY));
            }
            else if (i == kTree2Tag)
            {
                CCSprite * temp = (CCSprite *)this->getChildByTag(kTree1Tag);
                if (isPowerPicked)
                {
                    posY = temp->getPosition().y + temp->getContentSize().height*0.94;
                }
                else
                {
                    posY = temp->getPosition().y + temp->getContentSize().height*0.97;
                }
                tree->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width*0.5, posY));
            }
            else if (i == kTree3Tag)
            {
                CCSprite * temp = (CCSprite *)this->getChildByTag(kTree2Tag);
                if (isPowerPicked)
                {
                    posY = temp->getPosition().y + temp->getContentSize().height*0.94;
                }
                else
                {
                    posY = temp->getPosition().y + temp->getContentSize().height*0.97;
                }
                tree->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width*0.5, posY));
            }
            
        }
    }
    
    for (int j = kTree11Tag; j <= kTree33Tag; j++)
    {
        float delta = jumper_pos.y - ((float)CCDirector::sharedDirector()->getWinSize().height / 2);
        CCSprite * tree = (CCSprite *)this->getChildByTag(j);
        tree->setPosition(ccp(tree->getPosition().x,tree->getPosition().y-delta*0.5));
        if (tree->getPosition().y <= -0.5*CCDirector::sharedDirector()->getWinSize().height )
        {
            float posY;
            if (j == kTree11Tag)
            {
                CCSprite * temp = (CCSprite *)this->getChildByTag(kTree33Tag);
                posY = temp->getPosition().y + temp->getContentSize().height*0.98;
                tree->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width*0.5, posY));
            }
            else if (j == kTree22Tag)
            {
                CCSprite * temp = (CCSprite *)this->getChildByTag(kTree11Tag);
                posY = temp->getPosition().y + temp->getContentSize().height*0.98;
                tree->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width*0.5, posY));
            }
            else if (j == kTree33Tag)
            {
                CCSprite * temp = (CCSprite *)this->getChildByTag(kTree22Tag);
                posY = temp->getPosition().y + temp->getContentSize().height*0.98;
                tree->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width*0.5, posY));
            }
            
        }
    }

}

void GameScene::resetPlatform(void)
{	
	// We set this to -1 to initialize the first platform y coordinate
	if(currentPlatformY < 0) 
	{
		currentPlatformY = (float) kStartingCurrentPlatformY;
	} 
	else 
	{	
		// If not the first one then randomly determine a y coordinate for the platform
		currentPlatformY += rand() % (int)(currentMaxPlatformStep - kMinPlatformStep) + kMinPlatformStep;

		// If the current platofmr step is less than the max (top of screen) then increment it
		if(currentMaxPlatformStep < kMaxPlatformStep) 
		{
			currentMaxPlatformStep += 0.5f;
		}
	}
	
	CCSprite *platform = (CCSprite*)getChildByTag(currentPlatformTag);
    CCSprite * tree = CCSprite::create("tree.png");

	if ( rand() % 2 == 1) platform->setScaleX(-1.0f);

	float x;
	CCSize size = platform->getContentSize();

	// If the current platform is the first one initialized then just center it
	if (currentPlatformY == (float)kStartingCurrentPlatformY) 
	{
		x = (float) CCDirector::sharedDirector()->getWinSize().width/2;
	}
    else
    {
        if ( rand() % 2 == 1)
        {
            x = (float) CCDirector::sharedDirector()->getWinSize().width/2+ tree->getContentSize().width*0.7;
        }
        else
        {
           x = (float) CCDirector::sharedDirector()->getWinSize().width/2- tree->getContentSize().width*0.7;
        }
    }
	
	platform->setPosition(ccp(x,currentPlatformY));
    
	
	// If the platform is to have to bonus then put it there.
    if (platformCount == coin50Platform)
    {
        CCSprite *coin1 = (CCSprite*)getChildByTag(coin50Count);
        
		coin1->setPosition(ccp(x, currentPlatformY+30));
		coin1->setVisible(true);
        coin50Platform += k50CoinStartPlatform+randomValueBtween(5, 2);
        if (platformCount == coin100Platform)
        {
            coin100Platform += k100CoinStartPlatform+randomValueBtween(5, 2);

        }
        if (platformCount == coinJumpPlatform)
        {
            coinJumpPlatform += kJumpCoinStartPlatform+randomValueBtween(5, 2);
        }
        coin50Count++;
        if (coin50Count >= kBonusStartTag + kNumCoines)
        {
            coin50Count = kBonusStartTag;
        }
    }
    else if (platformCount == coin100Platform)
    {
        CCSprite *coin1 = (CCSprite*)getChildByTag(coin100Count);
        
		coin1->setPosition(ccp(x, currentPlatformY+30));
		coin1->setVisible(true);
        coin100Count++;
        if (coin100Count >= kBonusStartTag + kNumCoines+30)
        {
            coin100Count = kBonusStartTag+30;
        }
        coin100Platform += k100CoinStartPlatform+randomValueBtween(5, 2);
        if (platformCount == coinJumpPlatform)
        {
            coinJumpPlatform += kJumpCoinStartPlatform+randomValueBtween(5, 2);
        }
    }
    else if (platformCount == coinJumpPlatform)
    {
        CCSprite *coin1 = (CCSprite*)getChildByTag(coinJumpCount);
        coin1->setPosition(ccp(x, currentPlatformY+30));
		coin1->setVisible(true);
        coinJumpPlatform += kJumpCoinStartPlatform+randomValueBtween(5, 2);
        coinJumpCount++;
        if (coinJumpCount >= kBonusStartTag + kNumCoines+60)
        {
            coinJumpCount = kBonusStartTag+60;
        }
		
    }
    platformCount++;
    
}

// Reset the jumper to its home location
void GameScene::resetjumper(void)
{
    score = 0;
    char scoreStr[10] = {0};
    sprintf(scoreStr, "%d", score);
    CCLabelTTF* scoreLabel = (CCLabelTTF*) getChildByTag(kScoreLabel);
    scoreLabel->setString(scoreStr);
    
	CCSprite *jumper = (CCSprite*)getChildByTag(kjumper);

	// Place jumper in center
	jumper_pos.x = (float) CCDirector::sharedDirector()->getWinSize().width/2;
	jumper_pos.y = (float) CCDirector::sharedDirector()->getWinSize().width/2;
	jumper->setPosition(jumper_pos);
	
	jumper_vel.x = 0;
	jumper_vel.y = 0;
	
	jumper_acc.x = 0;
	jumper_acc.y = -550.0f;	// -250.0f makes the jumper jump higher, -950.0f makes the jumper jump lower
	
	jumperLookingRight = true;
	jumper->setScaleX(1.0f);
}

// Reset the bonus types based on the current score
void GameScene::resetBonus(void)
{
//    this->removeChildByTag(kBonusStartTag+coin50Count);
//	CCSprite *bonus = (CCSprite*)getChildByTag(kBonusStartTag);
//
//	// Set the bonus to not be visible
//	bonus->setVisible(false);
//
//	// Randomly determine which platform will get the bonus next by adding a random amount
//	currentBonusPlatformIndex += 0.45*(rand() % ( kMaxBonusStep - kMinBonusStep ) + kMinBonusStep);
//    CCLog(" currentBonusPlatformIndex   %d",currentBonusPlatformIndex);
////////
//    
//   
////     if(score < 1000)
////	{
////		currentBonusType = 0;
////	} 
////	else if(score < 2000)
////	{
////		currentBonusType = rand() % 2;
////	} 
////	else if ( score < 10000 )
////	{
////		currentBonusType = rand() % 3;
////	}
////    else
////	{
////		currentBonusType = rand() % 2 + 3;
////	}
//
//    currentBonusType = rand() % 3;
}

/////////////////////////////////////////////////////////
// Main game loop

void GameScene::step(float dt)
{
    
    particles_counter += dt;
    if (particles_counter > 0.15) {
        particles->setEmissionRate(0);
    }
    
	// Return if game suspended
	if(gameSuspended) return;

	// Get the jumper sprite
	CCSprite *jumper = (CCSprite*)getChildByTag(kjumper);
	
	// Update the player x position based on velocity and delta time
	jumper_pos.x += jumper_vel.x * dt;
	
	jumper->setRotation(jumper_vel.x);

	// Flip the player based on it's x velocity and current looking direction
	if(jumper_vel.x < -30.0f && jumperLookingRight) 
	{
		jumperLookingRight = false;
		jumper->setScaleX(-1.0f);
	}
	else if (jumper_vel.x > 30.0f && !jumperLookingRight) 
	{
		jumperLookingRight = true;
		jumper->setScaleX(1.0f);
	}

	// Calculate the max and min x values for the jumper
	// based on the screen and jumper widths
	CCSize jumper_size = jumper->getContentSize();
//	float max_x = (float)CCDirector::sharedDirector()->getWinSize().width - jumper_size.width/2;
//	float min_x = jumper_size.width/2;
	
	// Limit the jumper position based on max and min values allowed
//	if(jumper_pos.x>max_x) jumper_pos.x = max_x;
//	if(jumper_pos.x<min_x) jumper_pos.x = min_x;
    
    float max_x = (float)CCDirector::sharedDirector()->getWinSize().width + jumper_size.width/2.0;
	float min_x = -jumper_size.width/2.0;
    
    
	// Limit the character position based on max and min values allowed
	if(jumper_pos.x>max_x)
        jumper_pos.x = jumper_size.width/2.0;
	if(jumper_pos.x<min_x)
        jumper_pos.x = (float)CCDirector::sharedDirector()->getWinSize().width - jumper_size.width/2.0;

	// Update the jumper velocity based on acceleration and time
//    if (isPowerPicked)
//    {
//        jumper_vel.y += (jumper_acc.y * dt)*3;
//    }
//    else
    {
      jumper_vel.y += jumper_acc.y * dt;
    }
	

	// Update the jumper y positin based on velocity and time
	jumper_pos.y += jumper_vel.y * dt;
	
	////////////////////////////////////////////////////////////////////////////
	// Handle the bonus scoring
    
    
    
    float delta = jumper_pos.y - ((float)CCDirector::sharedDirector()->getWinSize().height / 2);
    

	// If bonus is visible then see if the jumper is within range to get the bonus
	

	// If the jumper has stopped moving then make it jump from the platform it is on
	int t;
	if(jumper_vel.y < 0) 
	{
		t = kPlatformsStartTag;

		// Search through all the platforms and compare the jumpers position with the platfor position
        
		for(t; t < kPlatformsStartTag + kNumPlatforms; t++) 
		{
			CCSprite *platform = (CCSprite*)getChildByTag(t);

			CCSize platform_size = platform->getContentSize();
			CCPoint platform_pos = platform->getPosition();
			
			max_x = platform_pos.x - platform_size.width/2 - 2;
			min_x = platform_pos.x + platform_size.width/2 + 2;

			float min_y = platform_pos.y + (platform_size.height+jumper_size.height)/2 - kPlatformTopPadding;
			
			if(jumper_pos.x > (max_x) &&
			   jumper_pos.x < (min_x) &&
			   jumper_pos.y > platform_pos.y &&
			   jumper_pos.y < min_y) 
			{
                if (platform->getTag() == kKillerPlatformTag)
                {
                    coin50Platform = 12;
                    coin100Platform = 15;
                    coinJumpPlatform = 25;
                    SharedData::getSharedInstance()->gameover_Text = "Gameover";
                    CCScene *pScene = GameOverScene::scene();
                    CCDirector::sharedDirector()->pushScene(pScene);
                    this->unscheduleAllSelectors();
                }
                else
                {
				jump();
				break;	// Can only jump from one platform at a time to break out of the loop
                }
			}
		}
	
		// If the jumper has fallen below the screen then game over
		if(jumper_pos.y < - jumper_size.height/2) 
		{
            coin50Platform = 12;
            coin100Platform = 15;
            coinJumpPlatform = 25;
            SharedData::getSharedInstance()->gameover_Text = "Gameover";
            CCScene *pScene = GameOverScene::scene();
            CCDirector::sharedDirector()->pushScene(pScene);
            this->unscheduleAllSelectors();
            
//			resetjumper();
		}
	} 
	else if ( jumper_pos.y > ((float)CCDirector::sharedDirector()->getWinSize().height / 2)) 
	{
        
		// If jumper position is greater than the middle of the screen then move the platforms
		// the difference between the jumper y position and middle point of the screen
		
        resetTree();
		// Set the jumper y position to the middle of the screen
		jumper_pos.y = (float)CCDirector::sharedDirector()->getWinSize().height / 2;

		// Move the current platform y by the delta amount
		currentPlatformY -= delta;

		// Move the clouds vertically and reset if necessary
		t = kCloudsStartTag;
		for (t; t < kCloudsStartTag + kNumClouds; t++) 
		{
			CCSprite *cloud = (CCSprite*) getChildByTag(t);

			CCPoint pos = cloud->getPosition();

			// Calculate new position for cloud
			pos.y -= delta * cloud->getScaleY() * 0.8f;

			// If the cloud is off the screen then need to reset this cloud else set its new position
			if (pos.y < -cloud->getContentSize().height/2) 
			{
				currentCloudTag = t;
				resetCloud();
			} 
			else 
			{	// Update the new y position for the cloud.
				cloud->setPosition(pos);
			}
		}

		// Move the platforms vertically and reset if necessary
		t = kPlatformsStartTag;
        int t_coin = kBonusStartTag;
		for (t; t < kPlatformsStartTag + kNumPlatforms; t++) 
		{
			CCSprite *platform = (CCSprite*)getChildByTag(t);
			
			CCPoint pos = platform->getPosition();

			// Calculate new position for platform
			pos = ccp(pos.x, pos.y - delta);

			// If the platform is off the screen then reset the platform else set its new position
			if(pos.y < - platform->getContentSize().height/2) 
			{
				currentPlatformTag = t;
				resetPlatform();
                
			} 
			else 
			{
				platform->setPosition(pos);
                
			}
		}

       
        //move particle system
        if (particles) {
            CCPoint pos = particles->getPosition();
            pos.y -= delta;
            particles->setPosition(pos);
        }
        
		// If the bonus is visible then adjust it's y position
		
		
		// Update score based on how much the jumper has moved
		score += (int)delta*0.3 ;
        
//        if (score >= target_Score)
//        {
//            SharedData::getSharedInstance()->gameover_Text = "Level Cleared";
//            CCScene *pScene = GameOverScene::scene();
//            CCDirector::sharedDirector()->pushScene(pScene);
//            this->unscheduleAllSelectors();
//        }

		// Display the new score value
		char scoreStr[10] = {0};
		sprintf(scoreStr, "%d", score);
		CCLabelTTF* scoreLabel = (CCLabelTTF*) getChildByTag(kScoreLabel);
		scoreLabel->setString(scoreStr);
        
        int t_coins = kBonusStartTag;
        for (t_coins; t_coins < (kNumCoines + kBonusStartTag); t_coins++)
        {
            
            ////////////////////////////////////////////////////////////////////////////
            // Handle the coin scoring
            CCSprite *coin = (CCSprite*)getChildByTag(t_coins);
            
            // If coin is visible then see if the character is within range to get the coin
            if(coin->isVisible() )
            {
                CCPoint coin_pos = coin->getPosition();
                float range = 30.0f;
                
                CCPoint pos = coin->getPosition();
                {
                    // Calculate new position of coin
                    pos.y -= delta;
                    
                    // If the coin is off the screen then reset the coin else set its new position
                    if(pos.y < -coin->getContentSize().height/2 )
                    {
                        //                        resetCoin();
                    }
                    else
                    {
                        coin->setPosition(pos);
                    }
                }
                
            }
            
        }
        t_coins = kBonusStartTag+30;
        for (t_coins; t_coins < (kNumCoines + kBonusStartTag+30); t_coins++)
        {
            
            ////////////////////////////////////////////////////////////////////////////
            // Handle the coin scoring
            CCSprite *coin = (CCSprite*)getChildByTag(t_coins);
            
            // If coin is visible then see if the character is within range to get the coin
            if(coin->isVisible() )
            {
                CCPoint coin_pos = coin->getPosition();
                float range = 30.0f;
                
                CCPoint pos = coin->getPosition();
                {
                    // Calculate new position of coin
                    pos.y -= delta;
                    
                    // If the coin is off the screen then reset the coin else set its new position
                    if(pos.y < -coin->getContentSize().height/2 )
                    {
                        //                        resetCoin();
                    }
                    else
                    {
                        coin->setPosition(pos);
                    }
                }
                
            }
            
        }
        t_coins = kBonusStartTag+60;
        for (t_coins; t_coins < (kNumCoines + kBonusStartTag+60); t_coins++)
        {
            
            ////////////////////////////////////////////////////////////////////////////
            // Handle the coin scoring
            CCSprite *coin = (CCSprite*)getChildByTag(t_coins);
            
            // If coin is visible then see if the character is within range to get the coin
            if(coin->isVisible() )
            {
                CCPoint coin_pos = coin->getPosition();
                float range = 30.0f;
                
                CCPoint pos = coin->getPosition();
                {
                    // Calculate new position of coin
                    pos.y -= delta;
                    
                    // If the coin is off the screen then reset the coin else set its new position
                    if(pos.y < -coin->getContentSize().height/2 )
                    {
                        //                        resetCoin();
                    }
                    else
                    {
                        coin->setPosition(pos);
                    }
                }
                
            }
            
        }
        
	}
    
    int t_coins = kBonusStartTag;
    for (t_coins; t_coins < (kNumCoines + kBonusStartTag); t_coins++)
    {
        
        ////////////////////////////////////////////////////////////////////////////
        // Handle the coin scoring
        CCSprite *coin = (CCSprite*)getChildByTag(t_coins);
        
        // If coin is visible then see if the character is within range to get the coin
        if(coin->isVisible() )
        {
            CCPoint coin_pos = coin->getPosition();
            float range = 30.0f;
            
            
            // If the player is within range of the coin value then award the prize
            if(jumper_pos.x > coin_pos.x - range &&
               jumper_pos.x < coin_pos.x + range &&
               jumper_pos.y > coin_pos.y - range &&
               jumper_pos.y < coin_pos.y + range )
            {
        
                // Build the score string to display
                char scoreStr[10] = {0};
                score += 50;
                sprintf(scoreStr, "%d", score);
                CCLabelTTF* scoreLabel = (CCLabelTTF*) getChildByTag(kScoreLabel);
                scoreLabel->setString(scoreStr);
                coin->setVisible(false);
            }
        }
        
    }
    t_coins = kBonusStartTag+30;
    for (t_coins; t_coins < (kNumCoines + kBonusStartTag+30); t_coins++)
    {
        
        ////////////////////////////////////////////////////////////////////////////
        // Handle the coin scoring
        CCSprite *coin = (CCSprite*)getChildByTag(t_coins);
        
        // If coin is visible then see if the character is within range to get the coin
        if(coin->isVisible() )
        {
            CCPoint coin_pos = coin->getPosition();
            float range = 30.0f;
            
            
            // If the player is within range of the coin value then award the prize
            if(jumper_pos.x > coin_pos.x - range &&
               jumper_pos.x < coin_pos.x + range &&
               jumper_pos.y > coin_pos.y - range &&
               jumper_pos.y < coin_pos.y + range )
            {
                
                // Build the score string to display
                char scoreStr[10] = {0};
                score += 100;
                sprintf(scoreStr, "%d", score);
                CCLabelTTF* scoreLabel = (CCLabelTTF*) getChildByTag(kScoreLabel);
                scoreLabel->setString(scoreStr);
                coin->setVisible(false);
            }
        }
        
    }
    t_coins = kBonusStartTag+60;
    for (t_coins; t_coins < (kNumCoines + kBonusStartTag+60); t_coins++)
    {
        
        ////////////////////////////////////////////////////////////////////////////
        // Handle the coin scoring
        CCSprite *coin = (CCSprite*)getChildByTag(t_coins);
        
        // If coin is visible then see if the character is within range to get the coin
        if(coin->isVisible() )
        {
            CCPoint coin_pos = coin->getPosition();
            float range = 30.0f;
            
            
            // If the player is within range of the coin value then award the prize
            if(jumper_pos.x > coin_pos.x - range &&
               jumper_pos.x < coin_pos.x + range &&
               jumper_pos.y > coin_pos.y - range &&
               jumper_pos.y < coin_pos.y + range )
            {
                
                // Build the score string to display
                this->powerPicked();
                coin->setVisible(false);
            }
        }
        
    }
    
    for (int i = kTree1Tag; i <= kTree3Tag; i++)
    {
        float delta = jumper_pos.y - ((float)CCDirector::sharedDirector()->getWinSize().height / 2);
        CCSprite * tree = (CCSprite *)this->getChildByTag(i);
        if ( jumper_pos.y > ((float)CCDirector::sharedDirector()->getWinSize().height / 2))
        {
            tree->setPosition(ccp(tree->getPosition().x,tree->getPosition().y-delta));
        }
        
       
        
        if (tree->getPosition().y <= -0.5*CCDirector::sharedDirector()->getWinSize().height )
        {
            float posY;
            if (i == kTree1Tag)
            {
                CCSprite * temp = (CCSprite *)this->getChildByTag(kTree3Tag);
                posY = temp->getPosition().y + temp->getContentSize().height*0.99;
                tree->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width*0.5, posY));
            }
            else if (i == kTree2Tag)
            {
                CCSprite * temp = (CCSprite *)this->getChildByTag(kTree1Tag);
                posY = temp->getPosition().y + temp->getContentSize().height*0.99;
                tree->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width*0.5, posY));
            }
            else if (i == kTree3Tag)
            {
                CCSprite * temp = (CCSprite *)this->getChildByTag(kTree2Tag);
                posY = temp->getPosition().y + temp->getContentSize().height*0.99;
                tree->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width*0.5, posY));
            }
            
        }
    }
    for (int i = kTree11Tag; i <= kTree33Tag; i++)
    {
        float delta = jumper_pos.y - ((float)CCDirector::sharedDirector()->getWinSize().height / 2);
        CCSprite * tree = (CCSprite *)this->getChildByTag(i);
        if ( jumper_pos.y > ((float)CCDirector::sharedDirector()->getWinSize().height / 2))
        {
            tree->setPosition(ccp(tree->getPosition().x,tree->getPosition().y-delta*0.1));
        }
        
        
        
        if (tree->getPosition().y <= -0.5*CCDirector::sharedDirector()->getWinSize().height )
        {
            float posY;
            if (i == kTree11Tag)
            {
                CCSprite * temp = (CCSprite *)this->getChildByTag(kTree33Tag);
                posY = temp->getPosition().y + temp->getContentSize().height*0.99;
                tree->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width*0.5, posY));
            }
            else if (i == kTree22Tag)
            {
                CCSprite * temp = (CCSprite *)this->getChildByTag(kTree11Tag);
                posY = temp->getPosition().y + temp->getContentSize().height*0.99;
                tree->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width*0.5, posY));
            }
            else if (i == kTree33Tag)
            {
                CCSprite * temp = (CCSprite *)this->getChildByTag(kTree22Tag);
                posY = temp->getPosition().y + temp->getContentSize().height*0.99;
                tree->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width*0.5, posY));
            }
            
        }
    }

    
	// Set the jumpers position
	jumper->setPosition(jumper_pos);
}

/////////////////////////////////////////////////////////
// Update the player y velocity for jumping
// Base the y velocity on the x velocity
void GameScene::jump(void)
{
    jumper->stopAllActions();
    jumper->runAction(jumpAnimate);
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("tmp.mp3");
    if (isPowerPicked)
    {
        jumper_vel.y = (350.0f + fabsf(jumper_vel.x))*3.0;
    }
    else
    {
        //jumper_vel.y = 350.0f + fabsf(jumper_vel.x);
	jumper_vel.y = 350.0f - jumper_vel.y;
    }
	
    CCPoint pos = particles->getPosition();
    particles->setSourcePosition(ccp(jumper_pos.x, jumper_pos.y-20 - pos.y));
    particles->setEmissionRate(150);
    particles_counter = 0;
}


void GameScene::registerWithTouchDispatcher(void)
{
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority + 1, true);

}

bool GameScene::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
	return true;
}

/////////////////////////////////////////////////////////
// Touch on left side of screen moves player left
// Touch on right side of screen moves player right
void GameScene::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
	CCPoint touchLocation = touch->getLocationInView(  );	
	touchLocation = CCDirector::sharedDirector()->convertToGL(touchLocation);
	touchLocation =  convertToNodeSpace(touchLocation);

	float touchCenter =  CCDirector::sharedDirector()->getWinSize().width/2 - touchLocation.x;
	float accel_filter = 0.1f;
	jumper_vel.x = jumper_vel.x * accel_filter - touchCenter;  
}

/////////////////////////////////////////////////////////
// Acceleramoter routine to move the player object
void GameScene::didAccelerate(CCAcceleration* pAccelerationValue)
{
	if(gameSuspended) return;

	float accel_filter = 0.1f;
	jumper_vel.x = jumper_vel.x * accel_filter + pAccelerationValue->x * (1.0f - accel_filter) * 500.0f;

	// CCLog("GameScene::didAccelerate %f",jumper_vel.x);
}
void GameScene::powerPicked()
{
    CCSprite * white = CCSprite::create("white-bg.png");
    white->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width*0.5, CCDirector::sharedDirector()->getWinSize().height*0.5));
    this->addChild(white,12);
    white->runAction(CCFadeOut::create(1.0));
    isPowerPicked = true;
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("ButtonClick.mp3");
    CCDelayTime * delay = CCDelayTime::create(2.0);
    CCCallFunc * sel = CCCallFunc::create(this, callfunc_selector(GameScene::powerTimeOut));
    CCSequence * seq = CCSequence::create(delay, sel, NULL);
    this->runAction(seq);
    jump();
    
}
void GameScene::powerTimeOut()
{
    isPowerPicked = false;
}
int GameScene::randomValueBtween(int max, int min)
{
    return ((arc4random()%(max-min)) + min);
    
}
