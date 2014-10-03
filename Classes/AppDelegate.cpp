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
 

#include "AppDelegate.h"

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "MainMenuScene.h"
#include "Soomla.h"


USING_NS_CC;
using namespace CocosDenshion;

AppDelegate::AppDelegate()
{
	handler = new ExampleEventHandler();
}

AppDelegate::~AppDelegate()
{
	soomla::CCSoomla::sharedSoomla()->removeEventHandler(handler);
}

bool AppDelegate::applicationDidFinishLaunching()
{
    
	soomla::CCSoomla::sharedSoomla()->addEventHandler(handler);

MuffinRushAssets *assets = MuffinRushAssets::create();
    CCDictionary *storeParams = CCDictionary::create();
    storeParams->
        setObject(CCString::create("ExampleSoomSecret"), "soomSec");
    storeParams->
        setObject(CCString::create("ExamplePublicKey"), "androidPublicKey");
    storeParams->
        setObject(CCString::create("ExampleCustomSecret"), "customSecret");

    // This is the call to initialize CCStoreController
soomla::CCStoreController::createShared(assets, storeParams);



// initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());

    // turn on display FPS
//    pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 90);
    
    
    
    //  ------------------------------------------------------------------------- //
    //  --------------      FOR Different Screen Resolution     ----------------- //
    //  ------------------------------------------------------------------------- //
    
    CCSize frameSize =pDirector->getWinSizeInPixels();
    
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();
    // Set the design resolution
    pEGLView->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, kResolutionExactFit);
    
    
    std::vector<std::string> searchPath;
    if (frameSize.width > mediumResource.size.width)
    {
        searchPath.push_back(largeResource.directory);
        pDirector->setContentScaleFactor(largeResource.size.height/designResolutionSize.height);

    }
    // if the frame's height is larger than the height of small resource size, select medium resource.
    else if (frameSize.width > smallResource.size.width)
    {
        searchPath.push_back(mediumResource.directory);
        pDirector->setContentScaleFactor(mediumResource.size.height/designResolutionSize.height);

    }
    // if the frame's height is smaller than the height of medium resource size, select small resource.
    else
    {
        searchPath.push_back(smallResource.directory);
        pDirector->setContentScaleFactor(smallResource.size.height/designResolutionSize.height);
    }
    
    CCFileUtils::sharedFileUtils()->setSearchPaths(searchPath);

    

    // create a scene. it's an autorelease object
    CCScene *pScene = MainMenuScene::scene();
    // run
    pDirector->runWithScene(pScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{

    CCDirector::sharedDirector()->stopAnimation();
    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
    SimpleAudioEngine::sharedEngine()->pauseAllEffects();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->startAnimation();
    SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
    SimpleAudioEngine::sharedEngine()->resumeAllEffects();
}
