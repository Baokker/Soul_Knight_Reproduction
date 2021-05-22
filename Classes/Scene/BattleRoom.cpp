#include "BattleRoom.h"
#include "Const.h"
#include "cocos2d.h"

USING_NS_CC;

Scene* BattleRoom::createScene()
{
    return BattleRoom::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool BattleRoom::init()
{
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }
    auto winSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    auto keyListener = EventListenerKeyboard::create();
    keyListener->onKeyPressed = CC_CALLBACK_2(BattleRoom::onKeyPressed, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyListener, this);

    _player = Sprite::create("player.png");
    _player->setPosition(Vec2(winSize.width * 0.1, winSize.height * 0.5));
    this->addChild(_player);

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            scene[i][j] = false;
        }
    }
    createBattleScene(scene[0],5);
    return true;
}

void BattleRoom::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event) {
    log("Key with keycode %d pressed", keyCode);
    switch (keyCode) {
    case EventKeyboard::KeyCode::KEY_D:
    {
        auto moveBy = MoveBy::create(0.5f, Vec2(20, 0));
        _player->runAction(Sequence::create(moveBy, nullptr));
        break;
    }
    case EventKeyboard::KeyCode::KEY_A:
    {
        auto moveBy = MoveBy::create(0.5f, Vec2(-20, 0));
        _player->runAction(Sequence::create(moveBy, nullptr));
        break;
    }
    case EventKeyboard::KeyCode::KEY_W:
    {
        auto moveBy = MoveBy::create(0.5f, Vec2(0, 20));
        _player->runAction(Sequence::create(moveBy, nullptr));
        break;
    }
    case EventKeyboard::KeyCode::KEY_S:
    {
        auto moveBy = MoveBy::create(0.5f, Vec2(0, -20));
        _player->runAction(Sequence::create(moveBy, nullptr));
        break;
    }
    default:
        break;
    }
}


void BattleRoom::createDoor(int X, int Y, int layer)
{
    Sprite* door = Sprite::create("Scene/Room/doorOpen.png");
    this->addChild(door);
    door->setGlobalZOrder(layer);
    door->setPosition(Point(X, Y));
}
void BattleRoom::createFloor(int X, int Y, int layer)
{
    int floor = rand();

    Sprite* temp = nullptr;


    if (floor % 4 == 0)
        temp = Sprite::create("Scene/Room/Forest/floor3.png");
    else if (floor % 3 == 0)
        temp = Sprite::create("Scene/Room/Forest/floor2.png");
    else
        temp = Sprite::create("Scene/Room/Forest/floor1.png");

    this->addChild(temp);
    temp->setGlobalZOrder(layer);
    temp->setPosition(Point(X, Y));
    //vecFloor.pushBack(tmpSprite);
}

void BattleRoom::createWall(int X, int Y, int layer)
{
    int wall = rand();

    Sprite* temp = nullptr;
    if (wall % 6 == 0)
        temp = Sprite::create("Scene/Room/Forest/wall2.png");
    else
        temp = Sprite::create("Scene/Room/Forest/wall1.png");

    this->addChild(temp, layer);
    temp->setGlobalZOrder(layer);
    temp->setPosition(Point(X, Y + (WALLHEIGHT - FLOORHEIGHT)));
    //vecWall.pushBack(tmpSprite);
    // Upside of whe wall

    /*
    if (wall % 6 == 0)
        temp = Sprite::create("Scene/Room/Forest/wall2.png");
    else
        temp = Sprite::create("Scene/Room/Forest/wall1.png");
    this->addChild(temp, layer - 2);
    temp->setGlobalZOrder(layer - 2);
    temp->setPosition(Point(X, Y + (WALLHEIGHT - FLOORHEIGHT) - 30));
    */


    //vecWall.pushBack(tmpSprite);
    // downside of the wall

    /*if (addShadow) {  //Ìí¼ÓÒõÓ°
        auto shadow = Sprite::create("Room//RectShadow.png");
        shadow->setGlobalZOrder(LayerPlayer - 1);
        shadow->setPosition(Point(20, -8));
        shadow->setOpacity(140);
        tmpSprite->addChild(shadow);
    }
    */
}

void BattleRoom::createRoom(int X, int Y)
{
    int LayerPlayer = 3;
    srand(time(nullptr));
    float curX = X, curY = Y;
    for (int y = ROOMHEIGHT - 1; y >= 0; y--)
    {  // for height and width
        for (int x = 0; x <= ROOMWIDTH - 1; x++) 
        {
            if (y == 0 || y == ROOMHEIGHT - 1)
            {
                if (y == 0)
                    createWall(curX, curY, LayerPlayer + 1);
                else
                    createWall(curX, curY, LayerPlayer - 1);
            }
            else if (x == 0 || x == ROOMWIDTH - 1)
            {
                createWall(curX, curY, LayerPlayer + 1);
            }
            else 
            {
                createFloor(curX, curY, LayerPlayer -2);
            }
            // randomly generate floor and Wall

            curX += FLOORWIDTH;
        }
        curX = X, curY -= FLOORHEIGHT;
    }
}

void BattleRoom::createHall(int X, int Y,int dir)//dir 1 means || dir 0 means --
{
    int LayerPlayer = 2;
    srand(time(nullptr));
    float curX = X, curY = Y;
    int xEnd, yStart;
    if (dir == 0)
    {
        yStart = HALLHEIGHT - 1;
        xEnd = HALLWIDTH - 1;
    }
    else
    {
        yStart = HALLWIDTH - 1;
        xEnd = HALLHEIGHT - 1;

    }
    for (int y = yStart; y >= 0; y--)
    {  // for height and width
        for (int x = 0; x <= xEnd; x++)
        {
            if (y == 0 || y == yStart)
            {
                if (y == 0)
                    createWall(curX, curY, LayerPlayer + 1);
                else
                    createWall(curX, curY, LayerPlayer -1);
            }
            else if (x == 0 || x == xEnd)
            {
                createWall(curX, curY, LayerPlayer - 1);
            }
            else
            {
                createFloor(curX, curY, LayerPlayer - 2);
            }
            // randomly generate floor and Wall
            curX += FLOORWIDTH;
        }
        curX = X, curY -= FLOORHEIGHT;
    }
}

void BattleRoom::createBattleScene(bool* scene, int num)
{
    auto winSize = Director::getInstance()->getVisibleSize();
    int curX = (winSize.width - ROOMWIDTH * FLOORWIDTH) / 2;
    int curY = winSize.height-(winSize.height - ROOMHEIGHT * FLOORHEIGHT) / 2;

    bool* curp = scene;
    srand(time(nullptr));
    int cur = rand() % MAPSIZE * MAPSIZE;
    while (cur / MAPSIZE != 0 && cur / MAPSIZE != MAPSIZE - 1 && cur % MAPSIZE != 0 && cur % MAPSIZE != MAPSIZE - 1)
    {
        int cur = rand() % MAPSIZE * MAPSIZE;
    }
    curp = scene + cur;
    *curp = true;
    createRoom(curX, curY);
    int count = 1;
    while (count < num)  //create the array map
    {
        int next = rand() %4;  //0 means up,1 means right, 2 means down, 3 means left
        switch (next)
        {
        case 0:if (cur - MAPSIZE >= 0 && *(curp - MAPSIZE) != false)
            {
                curp = curp - MAPSIZE; 
                *curp = true; 
                curX = curX + (ROOMWIDTH * FLOORWIDTH - HALLHEIGHT * FLOORWIDTH) / 2;
                for (int i = 1; i <= 5; i++)
                {
                    createDoor(curX + i * WALLWIDTH, curY, 3);
                }
                curY = curY + HALLWIDTH * FLOORHEIGHT;
                createHall(curX, curY, 1);
                for (int i = 1; i <= 5; i++)
                {
                    createDoor(curX + i*WALLWIDTH, curY, 3);
                }
                curX = curX - (ROOMWIDTH * FLOORWIDTH - HALLHEIGHT * FLOORWIDTH) / 2;
                curY = curY + ROOMHEIGHT * FLOORHEIGHT;
                createRoom(curX, curY);
            }break;
        case 1:if ((cur + 1) % MAPSIZE != 0 && *(curp + 1) != false) 
            { 
                curp = curp + 1;
                *curp = true;
                curX = curX + ROOMWIDTH * FLOORWIDTH;
                curY = curY - (ROOMHEIGHT * FLOORHEIGHT - HALLHEIGHT * FLOORHEIGHT) / 2;
                for (int i = 1; i <= 5; i++)
                {
                    createDoor(curX, curY - i * WALLHEIGHT, 3);
                }
                createHall(curX, curY, 0);
                curX = curX + HALLWIDTH * FLOORWIDTH;
                for (int i = 1; i <= 5; i++)
                {
                    createDoor(curX, curY - i * WALLHEIGHT, 3);
                }
                curY=curY+ (ROOMHEIGHT * FLOORHEIGHT - HALLHEIGHT * FLOORHEIGHT) / 2;
                createRoom(curX, curY);
            }break;
        case 2:if ((cur + MAPSIZE) / MAPSIZE < MAPSIZE && *(curp + MAPSIZE) != false) 
            {
                curp = curp + MAPSIZE;
                *curp = true;
                curX = curX + (ROOMWIDTH * FLOORWIDTH - HALLHEIGHT * FLOORWIDTH) / 2;
                curY = curY - HALLWIDTH * FLOORHEIGHT;
                for (int i = 1; i <= 5; i++)
                {
                    createDoor(curX + i * WALLWIDTH, curY, 3);
                }
                createHall(curX, curY, 1);
                curX = curX - (ROOMWIDTH * FLOORWIDTH - HALLHEIGHT * FLOORWIDTH) / 2;
                curY = curY - ROOMHEIGHT * FLOORHEIGHT;
                for (int i = 1; i <= 5; i++)
                {
                    createDoor(curX + i * WALLWIDTH, curY, 3);
                }
                createRoom(curX, curY);
            }break;
        case 3:if (cur % MAPSIZE != 0 && *(curp - 1) != false) 
            {
                curp = curp - 1; 
                *curp = true;
                curp = curp + 1;
                *curp = true;
                curY = curY - (ROOMHEIGHT * FLOORHEIGHT - HALLHEIGHT * FLOORHEIGHT) / 2;
                for (int i = 1; i <= 5; i++)
                {
                    createDoor(curX, curY - i * WALLHEIGHT, 3);
                }
                curX = curX - HALLWIDTH * FLOORWIDTH;
                createHall(curX, curY, 0);
                curX = curX - ROOMWIDTH * FLOORWIDTH;
                for (int i = 1; i <= 5; i++)
                {
                    createDoor(curX, curY - i * WALLHEIGHT, 3);
                }
                curY = curY + (ROOMHEIGHT * FLOORHEIGHT - HALLHEIGHT * FLOORHEIGHT) / 2;
                createRoom(curX, curY);
            }break;
        }
        count++;
    }
}

void BattleRoom::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}
