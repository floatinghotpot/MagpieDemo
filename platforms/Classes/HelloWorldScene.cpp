#include "HelloWorldScene.h"
#include "Magpie.h"

USING_NS_CC;

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(HelloWorld::menuCloseCallback));
    
	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width ,
                                origin.y + visibleSize.height - pCloseItem->getContentSize().height));

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Arial", 24);
    
    // position the label on the center of the screen
    pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - pLabel->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(pLabel, 1);

    // add "HelloWorld" splash screen"
    CCSprite* pSprite = CCSprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(pSprite, 0);
    
    // add UI layer
    UILayer* ui = UILayer::create();
    this->addChild(ui, 1);

    const char *apis[] = {
    	"setOptions", "",
        "createBanner", "removeBanner",
        "showBanner", "hideBanner",
        "prepareInterstitial", "showInterstitial"
    };

    int btn_per_row = 2;
    int btn_col_num = 5;
    int btn_x = 0, btn_y = 0;
    int btn_num = sizeof(apis)/sizeof(char *);
    for( int i=0; i< btn_num; i++){
    	if(strlen(apis[i]) > 0) {
            UIButton *btn = UIButton::create();
            btn->setTouchEnabled(true);
            btn->loadTextures("img/button-green.png", "img/button-green1.png", "img/button-green2.png");
            btn->setTitleFontSize(18);
            btn->setTitleText(apis[i]);
            btn->setPosition(ccp(visibleSize.width / (btn_per_row+1) * (btn_x+1), visibleSize.height / btn_col_num * (btn_col_num - btn_y - 1)));
            btn->addTouchEventListener(this, toucheventselector(HelloWorld::onClickTestButton));
            btn->setName(apis[i]);
            ui->addWidget(btn);
    	}

        btn_x++;
        if ( (btn_x + 1) > btn_per_row ) {
            btn_x = 0;
            btn_y ++;
        }
    }

    return true;
}

#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#define BANNER_ADID 		"ca-app-pub-6869992474017983/9375997553"
#define INTERSTITIAL_ADID	"ca-app-pub-6869992474017983/1657046752"

#elif(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#define BANNER_ADID 		"ca-app-pub-6869992474017983/4806197152"
#define INTERSTITIAL_ADID	"ca-app-pub-6869992474017983/7563979554"

#else
#error need get adId for this platform

#endif

void HelloWorld::onClickTestButton(CCObject *pSender, TouchEventType type)
{
    if(type != TOUCH_EVENT_ENDED) return;

	UIButton* btn = static_cast<UIButton*> (pSender);
	string name = btn->getName();
	CCLOG("button '%s' touched", name.c_str());

	if(name == "setOptions") {
		string args = "";
		args = args + "[{"
				"\"bannerId\":\"" + BANNER_ADID + "\","
				"\"interstitialId\":\"" + INTERSTITIAL_ADID + "\","
				"\"isTesting\":true,"
				"\"overlap\":true,"
				"\"autoShow\":true"
				"}]";
		Magpie::instance()->execute("AdMob", "setOptions", args.c_str(), NULL, NULL);

	} else if(name == "createBanner") {
		string args = "";
		args = args + "[{\"adId\":\"" + BANNER_ADID + "\",\"overlap\":true,\"autoShow\":true}]";
		Magpie::instance()->execute("AdMob", "createBanner", args.c_str(), NULL, NULL);

	} else if(name == "removeBanner") {
		Magpie::instance()->execute("AdMob", "removeBanner", "[]", NULL, NULL);

	} else if(name == "showBanner") {
		Magpie::instance()->execute("AdMob", "showBanner", "[2]", NULL, NULL);

	} else if(name == "hideBanner") {
		Magpie::instance()->execute("AdMob", "hideBanner", "[]", NULL, NULL);

	} else if(name == "prepareInterstitial") {
		string args = "";
		args = args + "[{\"adId\":\"" + INTERSTITIAL_ADID + "\"}]";
		Magpie::instance()->execute("AdMob", "prepareInterstitial", args.c_str(), NULL, NULL);

	} else if(name == "showInterstitial") {
		Magpie::instance()->execute("AdMob", "showInterstitial", "[]", NULL, NULL);

	}
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}
