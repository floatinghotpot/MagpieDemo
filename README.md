MagpieDemo: Call Cordova Plugins in Cocos2d-X Game
==========

Demo Project for Magpie Framework.

This Demo will show how to call Cordova AdMob Plugin from Cocos2d-X C++ code.

# Required #

## IDE and Basic Tools ##

- XCode v5.1 or later
- Eclipse v4.3 R2 or later
- Android SDK v4.4.2 (API 19)
- node.js
- git

## Cocos2d-X ##

- Cocos2d-X v2.2.x

> So far, only v2.2.1 tested.

## Cordova ##

- Cordova v3.5.0

## Magpie ##

- Magpie v1.0
```
git clone https://github.com/HandyWit/magpie ~/magpie
```

# How to Use? #

```
cd <cocos2d-x>
git clone https://github.com/HandyWit/MagpieDemo.git
```

# How to Run? #

iOS
- Double-click ./MagpieDemo/platforms/ios/MagpieDemo.xcodeproj, Xcode will open the project.
- Build (Ctrl+B)
- (connect iPhone/iPad)
- Run (Ctrl+R)

Android
- Open Eclipse, import existing android project ./MagpieDemo/platforms/android
- Change Android API to 4.4+
- Build Project
- (connect android device)
- Run As Android Application 

# Sample Code #

```cpp
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

```

# Screenshot #

Android

![Screenshot](android_admob.jpg)

iPad

![Screenshot](ipad_admob.jpg)
