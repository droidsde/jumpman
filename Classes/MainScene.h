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
 
#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;

//#define RESET_DEFAULTS

#define kFPS 60

#define kNumClouds			12

#define kTree1Tag            1500
#define kTree2Tag            1501
#define kTree3Tag            1502
#define kTree11Tag            1600
#define kTree22Tag            1601
#define kTree33Tag            1602
// Fist platform is 30 pixels from the bottom of the screen
#define kStartingCurrentPlatformY	30

#define kMinPlatformStep	50
#define kMaxPlatformStep	300		// This is the top of the screen (SHOULD BE RESOLUTION INDEPENDANT)
#define kNumPlatforms		10		// Number of platforms
#define kPlatformTopPadding 10
#define kNumCoines           20
#define kKillerPlatformTag   205

#define kMinBonusStep		20
#define kMaxBonusStep		40


#define k50CoinStartPlatform  12
#define k100CoinStartPlatform  18
#define kJumpCoinStartPlatform  30


enum 
{
	kSpriteManager = 0,
	kjumper,
	kScoreLabel,
	kCloudsStartTag = 100,
	kPlatformsStartTag = 200,
	kBonusStartTag = 300
};

enum 
{
	kBonus50 =0,
	kBonus100,
    kBonusPower,
	kNumBonuses
};

class MainScene : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();
    
    // implement the "static node()" method manually
    CREATE_FUNC(MainScene);

	cocos2d::CCSpriteBatchNode* spriteSheet ;

    // a selector callback
    virtual void menuCloseCallback(CCObject* pSender);

	void initClouds(void);
	void initCloud(void);
	void resetClouds(void);
	void resetCloud(void);
	void step(float dt);

protected:
	CCSprite * background;

	float currentCloudY;
	int currentCloudTag;
};

#endif  // __MAIN_SCENE_H__