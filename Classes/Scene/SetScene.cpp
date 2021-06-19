#include"SetScene.h"

int SetScene::present = 50;
bool SetScene::Soundeffect = true;
bool SetScene::buttonchange = true;

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
	bkMusicLab->setPosition(600, 540);
	this->addChild(bkMusicLab, 1);

	auto volumelab = Label::createWithTTF("Volume : ", "fonts/arial.ttf", 50);
	if (volumelab == nullptr)
		problemLoading("fonts/arial.ttf");
	else
	{
		volumelab->setPosition(480, 340);
		this->addChild(volumelab, 1);
	}

	auto SoundeffectLab = Label::createWithTTF("Sound effect  :", "fonts/arial.ttf", 50);
	SoundeffectLab->setPosition(530, 440);
	this->addChild(SoundeffectLab, 1);

	//set_exit
	auto exitImg = MenuItemImage::create("menu//exit.png", "menu//exit01.png", CC_CALLBACK_1(SetScene::menuCloseCallbackEnd, this));
	exitImg->setScale(0.75);
	auto exitmenu = Menu::create(exitImg, NULL);
	exitmenu->setPosition(Vec2(visibleSize.width - 80, visibleSize.height - 100));
	this->addChild(exitmenu, 1);

	//set_music_button_lab
	auto changeLabOn = Label::createWithTTF("ON", "fonts/arial.ttf", 24);
	auto changeLabOff = Label::createWithTTF("OFF", "fonts/arial.ttf", 24);
	if (changeLabOn == nullptr)
		problemLoading("fonts/arial.ttf");
	else
	{
		changeLabOn->setPosition(Point(1000, 540));
		changeLabOn->setColor(Color3B(0, 0, 255));
		this->addChild(changeLabOn, 2);
	}
	if (changeLabOff == nullptr)
		problemLoading("fonts/arial.ttf");
	else
	{
		changeLabOff->setPosition(Point(900, 540));
		changeLabOff->setColor(Color3B(0, 0, 255));
		this->addChild(changeLabOff, 2);
	}

	auto changeLabOn1 = Label::createWithTTF("ON", "fonts/arial.ttf", 24);
	auto changeLabOff1 = Label::createWithTTF("OFF", "fonts/arial.ttf", 24);
	if (changeLabOn1 == nullptr)
		problemLoading("fonts/arial.ttf");
	else
	{
		changeLabOn1->setPosition(Point(1000, 440));
		changeLabOn1->setColor(Color3B(255, 0, 0));
		this->addChild(changeLabOn1, 2);
	}
	if (changeLabOff1 == nullptr)
		problemLoading("fonts/arial.ttf");
	else
	{
		changeLabOff1->setPosition(Point(900, 440));
		changeLabOff1->setColor(Color3B(255, 0, 0));
		this->addChild(changeLabOff1, 2);
	}
	//set_music_button

	button1 = Button::create("menu\\Button_Normal.png", "menu\\Button_Press.png", "menu\\Button_Disable.png");
	button1->setTitleText("Button");
	button1->setPosition(Point(900, 540));
	if (!buttonchange)
		button1->setColor(Color3B(0, 255, 0));
	button1->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:			
			break;
		case ui::Widget::TouchEventType::ENDED:
			AudioEngine::pause(audioID);
			buttonchange = false;
			if (!buttonchange)
			{
				button1->setColor(Color3B(0, 255, 0));
				button2->setColor(Color3B(255, 255, 255));
			}
			break;
		default:
			break;
		}
		});
	this->addChild(button1, 1);

	button2 = Button::create("menu\\Button_Normal.png", "menu\\Button_Press.png", "menu\\Button_Disable.png");
	button2->setTitleText("Button");
	button2->setPosition(Point(1000, 540));
	if (buttonchange)
		button2->setColor(Color3B(0, 255, 0));
	button2->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			AudioEngine::resume(audioID);
			buttonchange = true;
			if (buttonchange)
			{
				button2->setColor(Color3B(0, 255, 0));
				button1->setColor(Color3B(255, 255, 255));
			}
			break;
		default:
			break;
		}
		});
	this->addChild(button2, 1);

	button3 = Button::create("menu\\Button_Normal.png", "menu\\Button_Press.png", "menu\\Button_Disable.png");
	button3->setTitleText("Button");
	button3->setPosition(Point(900, 440));
	if (!Soundeffect)
		button3->setColor(Color3B(0, 255, 0));
	button3->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			Soundeffect = false;
			if (!Soundeffect)
			{
				button3->setColor(Color3B(0, 255, 0));
				button4->setColor(Color3B(255, 255, 255));
			}
			break;
		default:
			break;
		}
		});
	this->addChild(button3, 1);

	button4 = Button::create("menu\\Button_Normal.png", "menu\\Button_Press.png", "menu\\Button_Disable.png");
	button4->setTitleText("Button");
	button4->setPosition(Point(1000, 440));
	if (Soundeffect)
		button4->setColor(Color3B(0, 255, 0));
	button4->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			Soundeffect = true;
			if (Soundeffect)
			{
				button4->setColor(Color3B(0, 255, 0));
				button3->setColor(Color3B(255, 255, 255));
			}
			break;
		default:
			break;
		}
		});
	this->addChild(button4, 1);
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
	if (Soundeffect)
	{
		auto audiobutton = AudioEngine::play2d("music\\button.mp3", false);
		AudioEngine::setVolume(audiobutton, present / 100.0f);
	};
	Director::getInstance()->popScene();
}
