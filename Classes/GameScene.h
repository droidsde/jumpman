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
 
#include "cocos2d.h"
#include "MainScene.h"
#include "SharedData.h"



class GameScene : public MainScene
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
	void didAccelerate(CCAcceleration* pAccelerationValue);

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();

    // implement the "static node()" method manually
    CREATE_FUNC(GameScene);

	virtual void registerWithTouchDispatcher(void);
	virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
	bool ccTouchBegan(CCTouch* touch, CCEvent* event);

	CCPoint jumper_pos;
	ccVertex2F jumper_vel;
	ccVertex2F jumper_acc;	

	float currentPlatformY;
	int currentPlatformTag;
	float currentMaxPlatformStep;
	int currentBonusPlatformIndex;
	int currentBonusType;
	int platformCount;
	int target_Score;
    int coin50Count;
    int coin100Count;
    int coinJumpCount;
	bool gameSuspended;
	bool jumperLookingRight;
    bool isPowerPicked;
    CCAnimate *  jumpAnimate;
//    CCAnimate * coin50Animate;
//    CCAnimate * coin100Animate;
//    CCAnimate * coinJumpAnimate;
    CCSprite *jumper;
	int score;
    int coin50Platform;
    int coin100Platform;
    int coinJumpPlatform;
    CCArray * coin50Anim;
    CCArray * coin100Anim;
    CCArray * coinJumpAnim;

	void	initPlatforms(void);
	void	initPlatform(void);
    void    initTree(void);
	void	startGame(void);
	void	resetPlatforms(void);
	void	resetPlatform(void);
	void	resetjumper(void);
	void	resetBonus(void);
    void    resetTree(void);
	void	step(float dt);
	void	jump(void);
	void	showHighscores(void);
    void    powerPicked(void);
    void    powerTimeOut(void);
    int     randomValueBtween(int max, int min);
    
private:
    CCParticleFireworks *particles;
    float                particles_counter;

};

