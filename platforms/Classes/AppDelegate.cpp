#include "AppDelegate.h"
#include "HelloWorldScene.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

#define DESIGN_W	960
#define DESIGN_H	640

bool AppDelegate::applicationDidFinishLaunching() {
    
    CCDirector* pDirector = CCDirector::sharedDirector();
    
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();
    pDirector->setOpenGLView(pEGLView);
    
    CCSize screenSize = pEGLView->getFrameSize();
    
    float w = DESIGN_H * screenSize.width / screenSize.height;
    float h = DESIGN_W * screenSize.height / screenSize.width;
    
    CCSize designSize = (w > DESIGN_W)? CCSizeMake(w, DESIGN_H) : CCSizeMake(DESIGN_W,h);
    CCEGLView::sharedOpenGLView()->setDesignResolutionSize(designSize.width, designSize.height, kResolutionShowAll);
    
    // turn on display FPS
    pDirector->setDisplayStats(true);
    
    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);
    
    // create a scene. it's an autorelease object
    CCScene *pScene = HelloWorld::scene();
    
    // run
    pDirector->runWithScene(pScene);
    
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    CCDirector::sharedDirector()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    CCDirector::sharedDirector()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}


#include "Magpie.h"

// shared Magpie sington
static Magpie s_sharedMagpie;

