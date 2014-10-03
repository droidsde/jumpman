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

#include "PauseMenuScene.h"

CCScene* PauseMenuScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    PauseMenuScene *layer = PauseMenuScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

bool PauseMenuScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    
    //resume
    CCSprite * normalImage = CCSprite::create("resume.png");
    CCSprite * selectedImage = CCSprite::create("resume.png");
    selectedImage->setColor(ccc3(128, 128, 128));
    resumeGame = CCMenuItemSprite::create(normalImage, selectedImage, this, menu_selector(PauseMenuScene::resumeGameCliked));
    
    //restart
    normalImage = CCSprite::create("restart.png");
    selectedImage = CCSprite::create("restart.png");
    selectedImage->setColor(ccc3(128, 128, 128));
    restartGame = CCMenuItemSprite::create(normalImage,selectedImage, this, menu_selector(PauseMenuScene::restartGameCliked));
    
    //MainMenu
    normalImage = CCSprite::create("mainMenu.png");
    selectedImage = CCSprite::create("mainMenu.png");
    selectedImage->setColor(ccc3(128, 128, 128));
    gotoMainMenu = CCMenuItemSprite::create(normalImage,selectedImage, this, menu_selector(PauseMenuScene::gotoMainMenuCliked));
    
    CCMenu * menu = CCMenu::create(resumeGame,restartGame,gotoMainMenu,NULL);
    menu->setPosition(ccp(size.width/2.0,size.height/2.0));
    this->addChild(menu);
    menu->alignItemsVerticallyWithPadding(20.0);
    
    return true;
}

void PauseMenuScene::restartGameCliked(cocos2d::CCMenuItem *sender)
{
    CCDirector::sharedDirector()->popToRootScene();
    CCNotificationCenter::sharedNotificationCenter()->postNotification("restartgame");
}

void PauseMenuScene::gotoMainMenuCliked(cocos2d::CCMenuItem *sender)
{
    CCDirector::sharedDirector()->popScene();
    CCDirector::sharedDirector()->popScene();
}

void PauseMenuScene::resumeGameCliked(cocos2d::CCMenuItem *sender)
{
    CCDirector::sharedDirector()->popScene();
}