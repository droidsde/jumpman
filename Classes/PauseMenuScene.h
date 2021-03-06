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

#ifndef __Jumper__PauseMenuScene__
#define __Jumper__PauseMenuScene__

#include <iostream>
#include "cocos2d.h"
using namespace cocos2d;

class PauseMenuScene : public cocos2d::CCLayer
{
public:
    virtual bool init();
    static cocos2d::CCScene* scene();
    CREATE_FUNC(PauseMenuScene);
    
    void restartGameCliked(CCMenuItem* sender);
    void resumeGameCliked(CCMenuItem* sender);
    void gotoMainMenuCliked(CCMenuItem* sender);
    
    //
    CCMenuItemSprite * restartGame;
    CCMenuItemSprite * resumeGame;
    CCMenuItemSprite * gotoMainMenu;
};
#endif /* defined(__Jumper__PauseMenuScene__) */
