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

#include "MainMenuScene.h"
#include "GameScene.h"

#include "SimpleAudioEngine.h"


CCScene* MainMenuScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    MainMenuScene *layer = MainMenuScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

bool MainMenuScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("MainMenuMusic.mp3", true);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(MainMenuScene::startGameCliked), "restartgame", NULL);
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
//    CCLabelTTF* gameName = CCLabelTTF::create("Jumper", "Arial", 40.0);
//    gameName->setPosition(ccp(size.width/2.0,size.height-100.0));
//    this->addChild(gameName);
    CCSprite * mainBg = CCSprite::create("background.png");
    mainBg->setPosition(ccp(size.width/2, size.height/2));
    this->addChild(mainBg);
    
    CCSprite * mainLogo = CCSprite::create("MainMenuLogo.png");
    mainLogo->setPosition(ccp(size.width/2, size.height*0.65));
    this->addChild(mainLogo);

    CCSprite * normalImage = CCSprite::create("start.png");
    CCSprite * selectedImage = CCSprite::create("start.png");
    selectedImage->setColor(ccc3(128, 128, 128));
    startGame = CCMenuItemSprite::create(normalImage, selectedImage, this, menu_selector(MainMenuScene::startGameCliked));
    CCMenu * startMenu = CCMenu::create(startGame,NULL);
    startMenu->setPosition(ccp(size.width/2.0,size.height*0.4));
    this->addChild(startMenu);
    
    return true;
}

void MainMenuScene::startGameCliked(cocos2d::CCMenuItem *sender)
{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("ButtonClick.mp3");
    CCScene *pScene = CCScene::create();
	pScene->addChild(GameScene::create());
    
    CCDirector::sharedDirector()->pushScene(pScene);
}