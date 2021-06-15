#include"SetScene.h"

int SetScene::present = 50;

Scene* SetScene::CreateScene()
{
	return SetScene::create();
}


static void problemLoading(string filename)
{
	cerr << "Error while loading:" << filename << endl;
	cerr << "Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n";
}

bool SetScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();

	//set_backgrund
	auto SetBackground = Sprite::create("Scene\SetScene.png");
	if (SetBackground == nullptr)
		problemLoading("Scene\\SetScene.png");
	else
	{
		SetBackground->setScale(1.35);
		SetBackground->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
		this->addChild(SetBackground, 0);
	}
	//set_music_lab

	auto bkMusicLab = Label::createWithTTF("Background Music : ", "fonts/arial.ttf", 50);
	bkMusicLab->setPosition(600, 440);
	this->addChild(bkMusicLab, 1);

	auto volumelab = Label::createWithTTF("Volume : ", "fonts/arial.ttf", 50);
	if (volumelab == nullptr)
		problemLoading("fonts/arial.ttf");
	else
	{
		volumelab->setPosition(480, 340);
		this->addChild(volumelab, 1);
	}


	//set_exit
	auto exitImg = MenuItemImage::create("menu//exit.png", "menu//exit01.png", CC_CALLBACK_1(SetScene::menuCloseCallbackEnd, this));
	exitImg->setScale(0.75);
	auto exitmenu = Menu::create(exitImg, NULL);
	exitmenu->setPosition(Vec2(visibleSize.width - 80, visibleSize.height - 100));
	this->addChild(exitmenu, 1);

	//set_music_button
	auto changeLabOn = Label::createWithTTF("ON", "fonts/arial.ttf", 24);
	auto changeLabOff = Label::createWithTTF("OFF", "fonts/arial.ttf", 24);
	if (changeLabOn == nullptr)
		problemLoading("fonts/arial.ttf");
	else
	{
		changeLabOn->setPosition(Point(1000, 440));
		changeLabOn->setColor(Color3B(0, 0, 255));
		this->addChild(changeLabOn, 2);
	}
	if (changeLabOff == nullptr)
		problemLoading("fonts/arial.ttf");
	else
	{
		changeLabOff->setPosition(Point(900, 440));
		changeLabOff->setColor(Color3B(0, 0, 255));
		this->addChild(changeLabOff, 2);
	}

	auto button1 = Button::create("menu\\Button_Normal.png", "menu\\Button_Press.png", "menu\\Button_Disable.png");
	button1->setTitleText("Button");
	button1->setPosition(Point(900, 440));
	button1->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:			
			break;
		case ui::Widget::TouchEventType::ENDED:
			AudioEngine::pause(audioID);
			break;
		default:
			break;
		}
		});
	this->addChild(button1, 1);

	auto button2 = Button::create("menu\\Button_Normal.png", "menu\\Button_Press.png", "menu\\Button_Disable.png");
	button2->setTitleText("Button");
	button2->setPosition(Point(1000, 440));
	button2->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			AudioEngine::resume(audioID);
			break;
		default:
			break;
		}
		});
	this->addChild(button2, 1);

	//set_vulume_slider

	slider = Slider::create();
	slider->loadBarTexture("menu\\Slider_Back.png"); // what the slider looks like
	slider->loadSlidBallTextures("menu\\SliderNode_Normal.png", "menu\\SliderNode_Press.png", "menu\\SliderNode_Disable.png");
	slider->loadProgressBarTexture("menu\\Slider_PressBar.png");
	slider->setPercent(present);
	slider->setPosition(Point(800,340));
	slider->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) 
		{
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			present = slider->getPercent();
			AudioEngine::setVolume(audioID,present/100.0f);
			break;
		}
		});
	this->addChild(slider, 1);

}


void SetScene::menuCloseCallbackEnd(Ref* pSender)
{
	Director::getInstance()->popScene();
}
