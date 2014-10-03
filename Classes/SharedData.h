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


#ifndef __Jumper__SharedData__
#define __Jumper__SharedData__

#include <iostream>


#include "cocos2d.h"

using namespace cocos2d;

USING_NS_CC;

class SharedData: public CCObject
{
public:
    static SharedData* getSharedInstance();
    
    SharedData();
    ~SharedData();
    
    const char * gameover_Text;
    
};


#endif /* defined(__Jumper__SharedData__) */
