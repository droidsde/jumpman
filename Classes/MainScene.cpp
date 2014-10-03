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
 
#include "MainScene.h"
#include "GameScene.h"

using namespace cocos2d;

CCScene* MainScene::scene()
{
    CCScene * scene = NULL;
    do 
    {
        // Create our Scene
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        // Create and Add the MainScene Layer
		MainScene *layer = MainScene::create();
        CC_BREAK_IF(! layer);
        scene->addChild(layer);

        // Create and Add the GameScene Layer
		GameScene *layer1 = GameScene::create();
        CC_BREAK_IF(! layer1);
		scene->addChild(layer1);

    } while (0);

    return scene;
}

// on "init" you need to initialize your instance
bool MainScene::init()
{
    bool bRet = false;
    do 
    {
        /////////////////////
        // super init first
        /////////////////////

        CC_BREAK_IF(! CCLayer::init());

        // Get window size
        CCSize size = CCDirector::sharedDirector()->getWinSize();

//		// Get sprite sheet
//		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Images/spritesheet.plist");

		// Get background from sprite sheet
		background = CCSprite::create(("GamePlaybg.png"));
		this->addChild(background);

		// Center the background on the screen
		background->setPosition(ccp(size.width/2, size.height/2));	// center it

		// Initialze the clouds
		initClouds();
        

		// Start stepping
		schedule(schedule_selector(MainScene::step));
        bRet = true;
    } while (0);

    return bRet;
}

void MainScene::menuCloseCallback(CCObject* pSender)
{
    // "close" menu item clicked
#if (CC_TARGET_PLATFORM == CC_PLATFORM_AIRPLAY)
	s3eDeviceRequestQuit();	// Exit from Airplay SDK
#endif
    CCDirector::sharedDirector()->end();
}

/////////////////////////////////////////////////////////
// Create kNumClouds
void MainScene::initClouds(void) 
{
	CCLog("initClouds");

	currentCloudTag = kCloudsStartTag;

	// Create the clouds and add them to the layer
	while(currentCloudTag < kCloudsStartTag + kNumClouds) 
	{
		initCloud();
		currentCloudTag++;
	}

	// randomly size and place each cloud
	resetClouds();
}

/////////////////////////////////////////////////////////
// There are 3 types of clouds, randomly choose them
void MainScene::initCloud(void)
{
	CCSprite *cloud;
    
	switch(rand()%3) 
	{
		case 0: 
			// Get cloud from sprite sheet
			cloud = CCSprite::create(("cloud1.png"));
			break;
		case 1: 
			// Get cloud from sprite sheet
			cloud = CCSprite::create(("cloud2.png"));
			break;
		case 2: 
			// Get cloud from sprite sheet
			cloud = CCSprite::create(("cloud3.png"));
			break;
	}	
    
    
	this->addChild(cloud, 1, currentCloudTag);
	cloud->setOpacity(128);
}

/////////////////////////////////////////////////////////
// Loop through and reset the clouds on initialization
void MainScene::resetClouds(void)
{
	CCLog("resetClouds");

	currentCloudTag = kCloudsStartTag;
	
	while(currentCloudTag < kCloudsStartTag + kNumClouds) 
	{
		resetCloud();

		CCSprite *cloud = (CCSprite*)getChildByTag(currentCloudTag);
		CCPoint pos = cloud->getPosition();
		pos.y -= (float)CCDirector::sharedDirector()->getWinSize().height;
		cloud->setPosition(pos);
		currentCloudTag++;
	}
}

/////////////////////////////////////////////////////////
// For each cloud, randomly size and place them
void MainScene::resetCloud(void)
{
	CCSprite *cloud = (CCSprite*)getChildByTag(currentCloudTag);
	
	// Calculate a random distance for this cloud
	float distance = rand() % 20 + 5;
	
	// Scale the cloud based on the distance
	float scale = 5.0f / distance;

	// Scale the X and Y equally for the cloud
	cloud->setScaleX(scale);
	cloud->setScaleY(scale);

	// randomly invert the X scale for some of the clouds
	if(rand() % 2 == 1) cloud->setScaleX(-cloud->getScaleX());
	
	CCSize size = cloud->getContentSize();

	float scaled_width = size.width * scale;

	// Randomly place each cloud within our view 
	float x = rand() % (int)(CCDirector::sharedDirector()->getWinSize().width +  (int)scaled_width) - scaled_width/2;
	float y = rand() % (int)(CCDirector::sharedDirector()->getWinSize().height - (int)scaled_width) + scaled_width/2 + CCDirector::sharedDirector()->getWinSize().height;

	cloud->setPosition(ccp(x,y));
}

/////////////////////////////////////////////////////////
// For each cloud, move them in the x direction
// with a speed based on their size
void MainScene::step(float dt)
{
	// CCLog("Main::step");

	int t = 0;
    
    
    
	for(t = kCloudsStartTag; t < kCloudsStartTag + kNumClouds; t++)
	{
		CCSprite *cloud = (CCSprite*)getChildByTag(t);
		CCPoint pos = cloud->getPosition();
		CCSize size = cloud->getContentSize();

		// Control speed of clouds moving based on their size
		pos.x += 0.1f * cloud->getScaleY();

		if(pos.x > CCDirector::sharedDirector()->getWinSize().width + size.width/2) 
		{
			pos.x = -size.width/2;;
		}
		cloud->setPosition(pos);
	}
}


