/*-------------------------------------------------------------------------
This source file is a part of OGRE
(Object-oriented Graphics Rendering Engine)
For the latest info, see http://www.ogre3d.org/


Copyright (c) 2000-2013 Torus Knot Software Ltd
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:


The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.


THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE
-------------------------------------------------------------------------*/

#include "TutorialApplication.h"


//-------------------------------------------------------------------------------------
TutorialApplication::TutorialApplication() : mIntroActive(false),
    mSelectStage(false),
    mCaveScene(false),
    mCurrentButtonIndex(0),
    mIntroOverlay(nullptr),
    mCurrentButton(nullptr),
    SquirtleAnimation(nullptr),
    WartortleAnimation(nullptr),
    BlastoiseAnimation(nullptr),
    sceneMenu(nullptr),
    soundMgr(nullptr),
    device(nullptr),
    context(nullptr)
{
}


//-------------------------------------------------------------------------------------
TutorialApplication::~TutorialApplication(void)
{
    if (mTrayMgr) delete mTrayMgr;
}


//-------------------------------------------------------------------------------------
void TutorialApplication::createScene(void)
{

    setupIntroScene();

    mCameraNode->setPosition(-40, 20, 10);

    mSceneMgr->setAmbientLight(ColourValue(0.5, 0.5, 0.5));

    // Create a light and set its position
    Light* light = mSceneMgr->createLight("MainLight");
    SceneNode* lightNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("LightNode");
    lightNode->attachObject(light);
    lightNode->setPosition(100, 80, 100);
}


// Create Squirtle
void TutorialApplication::createSquirtle(void) {
    Squirtle = mSceneMgr->createEntity("Squirtle", "Squirtle.mesh");
    SquirtleNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("SquirtleNode");

    Vector3 Squirtle_currentScale = SquirtleNode->getScale();
    SquirtleNode->setScale(Squirtle_currentScale * Vector3(0.05f, 0.05f, 0.05f));
    SquirtleNode->setPosition(0, 0, 0);
    SquirtleNode->yaw(Degree(-60));

    Squirtle->getSkeleton()->setBlendMode(ANIMBLEND_CUMULATIVE);

    Animation::setDefaultInterpolationMode(Animation::IM_SPLINE);
    Animation::setDefaultRotationInterpolationMode(Animation::RIM_SPHERICAL);

    SquirtleAnimation = Squirtle->getAnimationState("my_animation");
    SquirtleAnimation->setLoop(true);
    SquirtleAnimation->setEnabled(true);
    SquirtleNode->attachObject(Squirtle);
}

// Create Wartortle
void TutorialApplication::createWartortle(void) {
    Wartortle = mSceneMgr->createEntity("Wartortle", "Wartortle.001.mesh");
    WartortleNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("WartortleNode");

    Vector3 Wartortle_currentScale = WartortleNode->getScale();
    WartortleNode->setScale(Wartortle_currentScale * Vector3(0.05f, 0.05f, 0.05f));
    WartortleNode->setPosition(0, 0, 0);
    Wartortle->getSkeleton()->setBlendMode(ANIMBLEND_CUMULATIVE);

    Animation::setDefaultInterpolationMode(Animation::IM_SPLINE);
    Animation::setDefaultRotationInterpolationMode(Animation::RIM_SPHERICAL);

    WartortleAnimation = Wartortle->getAnimationState("my_animation");
    WartortleAnimation->setLoop(true);
    WartortleAnimation->setEnabled(true);

    WartortleNode->attachObject(Wartortle);
}

// Create Blastoise
void TutorialApplication::createBlastoise(void) {
    Blastoise = mSceneMgr->createEntity("Blastoise", "Blastoise.mesh");
    BlastoiseNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("BlastoiseNode");

    //Blastoise_CannonA = mSceneMgr->createEntity("BlastoiseCannonA", "Blastoise_CannonsA.mesh");
    //Blastoise_CannonANode = mSceneMgr->getRootSceneNode()->createChildSceneNode("BlastoiseCannonANode");

    //Blastoise_CannonB = mSceneMgr->createEntity("BlastoiseCannonB", "Blastoise_CannonsB.mesh");
    //Blastoise_CannonBNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("BlastoiseCannonBNode");

    Vector3 Blastoise_currentScale = BlastoiseNode->getScale();
    //Vector3 currentScaleA = Blastoise_CannonANode->getScale();
    //Vector3 currentScaleB = Blastoise_CannonBNode->getScale();

    BlastoiseNode->setScale(Blastoise_currentScale * Vector3(0.05f, 0.05f, 0.05f));
    BlastoiseNode->setPosition(0, 0, 0);
    //Blastoise_CannonANode->setScale(currentScaleA * Vector3(0.2f, 0.2f, 0.2f));
    //Blastoise_CannonANode->setPosition(0, 0, 0);
    //Blastoise_CannonBNode->setScale(currentScaleB * Vector3(0.2f, 0.2f, 0.2f));
    //Blastoise_CannonBNode->setPosition(0, 0, 0);
    Blastoise->getSkeleton()->setBlendMode(ANIMBLEND_CUMULATIVE);

    Animation::setDefaultInterpolationMode(Animation::IM_SPLINE);
    Animation::setDefaultRotationInterpolationMode(Animation::RIM_SPHERICAL);

    BlastoiseAnimation = Blastoise->getAnimationState("my_animation");
    BlastoiseAnimation->setLoop(true);
    BlastoiseAnimation->setEnabled(true);

    BlastoiseNode->attachObject(Blastoise);
    //Blastoise_CannonANode->attachObject(Blastoise_CannonA);
    //Blastoise_CannonBNode->attachObject(Blastoise_CannonB);
}

void TutorialApplication::setupIntroScene(void) {
    setupSound(0, true);
    OverlayManager& overlayManager = OverlayManager::getSingleton();
    mIntroOverlay = overlayManager.create("IntroOverlay");

    // Create panel for image
    OverlayContainer* panel = static_cast<OverlayContainer*>(overlayManager.createOverlayElement("Panel", "IntroPanel"));
    panel->setMetricsMode(GMM_RELATIVE);
    panel->setPosition(0, 0);
    panel->setDimensions(1, 1); // Full screen

    //// Create material to show image
    MaterialPtr material = MaterialManager::getSingleton().create("IntroMaterial", "General");
    material->getTechnique(0)->getPass(0)->createTextureUnitState("intro.jpg");
    material->getTechnique(0)->getPass(0)->setDepthCheckEnabled(false);
    material->getTechnique(0)->getPass(0)->setDepthWriteEnabled(false);
    material->getTechnique(0)->getPass(0)->setLightingEnabled(false);

    //// set material to the panel
    panel->setMaterialName("IntroMaterial");

    // Add panel to overlay and show it
    mIntroOverlay->add2D(panel);
    mIntroOverlay->show();

    mIntroActive = true;
}

void TutorialApplication::createMenu(void) {
    soundMgr->stopAudio(audioId[0]);
    setupSound(1, true);

    caveButton = mTrayMgr->createButton(TL_RIGHT, "CaveButton", "Cave", 250);
    forestButton = mTrayMgr->createButton(TL_RIGHT, "ForestButton", "Forest", 250);
    squirtleButton = mTrayMgr->createButton(TL_RIGHT, "SquirtleButton", "Squirtle", 250);
    wartortleButton = mTrayMgr->createButton(TL_RIGHT, "WartortleButton", "Wartortle", 250);
    blastoiseButton = mTrayMgr->createButton(TL_RIGHT, "BlastoiseButton", "Blastoise", 250);

    caveButton = (Button*)mTrayMgr->getWidget(TL_RIGHT, "CaveButton");
    forestButton = (Button*)mTrayMgr->getWidget(TL_RIGHT, "ForestButton");
    squirtleButton = (Button*)mTrayMgr->getWidget(TL_RIGHT, "SquirtleButton");
    wartortleButton = (Button*)mTrayMgr->getWidget(TL_RIGHT, "WartortleButton");
    blastoiseButton = (Button*)mTrayMgr->getWidget(TL_RIGHT, "BlastoiseButton");

    mButtons.push_back(caveButton);
    mButtons.push_back(forestButton);
    mButtons.push_back(squirtleButton);
    mButtons.push_back(wartortleButton);
    mButtons.push_back(blastoiseButton);

    highlightCurrentButton();
    
    mIntroActive = false;
    mSelectStage = true;
}

void TutorialApplication::setupForestScene(void) {
    //mSceneMgr->clearScene();

    ////Button* goToCaveButton = (Button*)mTrayMgr->getWidget(TL_TOPRIGHT,"Go To Cave");
    ////Button* goBackButton = (Button*)mTrayMgr->getWidget(TL_TOPRIGHT, "Back to Intro");

    //Button* goToCaveButton = mTrayMgr->createButton(TL_TOPRIGHT, "Go To Cave","GoToCave",250);
    //Button* goBackButton = mTrayMgr->createButton(TL_TOPRIGHT, "Back to Intro","GoBackIntro",250);

    ////mTrayMgr->showAll();

    //mButtons.push_back(goToCaveButton);
    //mButtons.push_back(goBackButton);

    //highlightCurrentButton();
    //soundMgr->stopAudio(audioId[3]);
    setupSound(4,true);

    Forest_root_base = mSceneMgr->createEntity("ForestRootBase", "root_base.mesh");
    Forest_root_baseNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("ForestRootBaseNode");

    Forest_root_base1 = mSceneMgr->createEntity("ForestRootBase1", "root_base.001.mesh");
    Forest_root_base1Node = mSceneMgr->getRootSceneNode()->createChildSceneNode("ForestRootBase1Node");

    Forest_root_base2 = mSceneMgr->createEntity("ForestRootBase2", "root_base.002.mesh");
    Forest_root_base2Node = mSceneMgr->getRootSceneNode()->createChildSceneNode("ForestRootBase2Node");

    Forest_root_base3 = mSceneMgr->createEntity("ForestRootBase3", "root_base.003.mesh");
    Forest_root_base3Node = mSceneMgr->getRootSceneNode()->createChildSceneNode("ForestRootBase3Node");

    Forest_root_base4 = mSceneMgr->createEntity("ForestRootBase4", "root_base.004.mesh");
    Forest_root_base4Node = mSceneMgr->getRootSceneNode()->createChildSceneNode("ForestRootBase4Node");

    Forest_root_base5 = mSceneMgr->createEntity("ForestRootBase5", "root_base.005.mesh");
    Forest_root_base5Node = mSceneMgr->getRootSceneNode()->createChildSceneNode("ForestRootBase5Node");

    Forest_root_base6 = mSceneMgr->createEntity("ForestRootBase6", "root_base.006.mesh");
    Forest_root_base6Node = mSceneMgr->getRootSceneNode()->createChildSceneNode("ForestRootBase6Node");

    Forest_root_loopA = mSceneMgr->createEntity("ForestRootLoopA", "root_LoopA.mesh");
    Forest_root_loopANode = mSceneMgr->getRootSceneNode()->createChildSceneNode("ForestRootLoopANode");

    Forest_root_loopB = mSceneMgr->createEntity("ForestRootLoopB", "root_LoopB.mesh");
    Forest_root_loopBNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("ForestRootLoopBNode");

    Forest_root_loopC = mSceneMgr->createEntity("ForestRootLoopC", "root_LoopC.mesh");
    Forest_root_loopCNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("ForestRootLoopCNode");

    Forest_root_baseNode->setPosition(0, 0, 0);
    Forest_root_base1Node->setPosition(0, 0, 0);
    Forest_root_base2Node->setPosition(0, 0, 0);
    Forest_root_base3Node->setPosition(0, 0, 0);
    Forest_root_base4Node->setPosition(0, 0, 0);
    Forest_root_base5Node->setPosition(0, 0, 0);
    Forest_root_base6Node->setPosition(0, 0, 0);
    Forest_root_loopANode->setPosition(0, 0, 0);
    Forest_root_loopBNode->setPosition(0, 0, 0);
    Forest_root_loopCNode->setPosition(0, 0, 0);

    Forest_root_baseNode->yaw(Degree(-60));
    Forest_root_base1Node->yaw(Degree(-60));
    Forest_root_base2Node->yaw(Degree(-60));
    Forest_root_base3Node->yaw(Degree(-60));
    Forest_root_base4Node->yaw(Degree(-60));
    Forest_root_base5Node->yaw(Degree(-60));
    Forest_root_base6Node->yaw(Degree(-60));
    Forest_root_loopANode->yaw(Degree(-60));
    Forest_root_loopBNode->yaw(Degree(-60));
    Forest_root_loopCNode->yaw(Degree(-60));

    mCameraNode->setPosition(4, 10, -10);

    Forest_root_baseNode->attachObject(Forest_root_base);
    Forest_root_base1Node->attachObject(Forest_root_base1);
    Forest_root_base2Node->attachObject(Forest_root_base2);
    Forest_root_base3Node->attachObject(Forest_root_base3);
    Forest_root_base4Node->attachObject(Forest_root_base4);
    Forest_root_base5Node->attachObject(Forest_root_base5);
    Forest_root_base6Node->attachObject(Forest_root_base6);
    Forest_root_loopANode->attachObject(Forest_root_loopA);
    Forest_root_loopBNode->attachObject(Forest_root_loopB);
    Forest_root_loopCNode->attachObject(Forest_root_loopC);
}

void TutorialApplication::setupCaveScene(void) {
    //soundMgr->stopAllAudio();
    //soundMgr->stopAudio(audioId[4]);
    setupSound(3, true);

    Cave_crystalEntity = mSceneMgr->createEntity("CaveCrystal", "crystal1_mdl.mesh");
    Cave_crystalNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("CaveCrystalNode");

    Cave_floorEntity = mSceneMgr->createEntity("CaveFloor", "floor1_mdl.mesh");
    Cave_floorNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("CaveFloorNode");

    Cave_grassEntity = mSceneMgr->createEntity("CaveGrass", "grassland1_mdl.mesh");
    Cave_grassNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("CaveGrassNode");

    Cave_rootEntity = mSceneMgr->createEntity("CaveRoot", "root1_mdl.mesh");
    Cave_rootNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("CaveRootNode");

    Cave_stoneEntity = mSceneMgr->createEntity("CaveStone", "stone1_mdl.mesh");
    Cave_stoneNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("CaveStoneNode");

    Cave_wallEntity = mSceneMgr->createEntity("CaveWall", "wall1_mdl.mesh");
    Cave_wallNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("CaveWallNode");

    Cave_crystalNode->setPosition(0, 0, 0);
    Cave_floorNode->setPosition(0, 0, 0);
    Cave_grassNode->setPosition(0, 0, 0);
    Cave_rootNode->setPosition(0, 0, 0);
    Cave_stoneNode->setPosition(0, 0, 0);
    Cave_wallNode->setPosition(0, 0, 0);

    Cave_crystalNode->yaw(Degree(-60));
    Cave_floorNode->yaw(Degree(-60));
    Cave_grassNode->yaw(Degree(-60));
    Cave_rootNode->yaw(Degree(-60));
    Cave_stoneNode->yaw(Degree(-60));
    Cave_wallNode->yaw(Degree(-60));

    mCameraNode->setPosition(10, 15, -5);

    Cave_crystalNode->attachObject(Cave_crystalEntity);
    Cave_floorNode->attachObject(Cave_floorEntity);
    Cave_grassNode->attachObject(Cave_grassEntity);
    Cave_rootNode->attachObject(Cave_rootEntity);
    Cave_stoneNode->attachObject(Cave_stoneEntity);
    Cave_wallNode->attachObject(Cave_wallEntity);



}

void TutorialApplication::selectPokemonMenu(void) {
    std::cout << "0" << std::endl;
}

void TutorialApplication::highlightCurrentButton(void)
{
    // Reset all buttons to the normal color
    for (auto& button : mButtons) {
        button->setCaption(button->getName());
    }

    // Highlight the current button
    Button* highlightedButton = mButtons[mCurrentButtonIndex];
    highlightedButton->setCaption("> " + highlightedButton->getName());
}

void TutorialApplication::transitionToMenu(void) {
    mIntroOverlay->hide();
    createMenu();
    mIntroActive = false;
}

void TutorialApplication::itemSelected(SelectMenu* sceneMenu)
{
    //mTrayMgr->itemSelected();
    if (sceneMenu->getName() == "Forest") {
        std::cout << "Select menu Forest" << std::endl;
        mSceneMgr->clearScene();
        //mTrayMgr->destroyAllWidgets();
        setupForestScene();
    }
    else if (sceneMenu->getName() == "Cave") {
        std::cout << "Select menu Cave" << std::endl;
        mSceneMgr->clearScene();
        //mTrayMgr->destroyAllWidgets();
        setupCaveScene();
    }
    else if (sceneMenu->getName() == "Menu") {
        std::cout << "Select Menu" << std::endl;
        //transitionToMenu();
        mSceneMgr->clearScene();
        //mTrayMgr->destroyAllWidgets();

        setupIntroScene();
    }
}

//-------------------------------------------------------------------------------------
bool TutorialApplication::frameRenderingQueued(const FrameEvent& evt) {
    if (mWindow->isClosed()) return false;
    mTrayMgr->frameRendered(evt);

    if (objectName == "SquirtleNode"  )  {
        if (mPressKeySet.count('j')) {
            SquirtleNode->translate(Vector3(1, 0, 0) * evt.timeSinceLastFrame);
            SquirtleNode->yaw(Degree(5));
        }

        else if (mPressKeySet.count('l')) {
            SquirtleNode->translate(Vector3(1, 0, 0) * evt.timeSinceLastFrame);
            SquirtleNode->yaw(Degree(-5));
        }
        else if (mPressKeySet.count('i')) {
            SquirtleNode->translate(Vector3(0, 1, 0) * evt.timeSinceLastFrame);
            Quaternion rotation = Quaternion(Degree(60), Vector3::UNIT_X);
            SquirtleNode->rotate(rotation);
            //SquirtleNode->yaw(Degree(-5));
        }

        else if (mPressKeySet.count('k')) {
            SquirtleNode->translate(Vector3(0, -1, 0) * evt.timeSinceLastFrame);
            Quaternion rotation = Quaternion(Degree(-60), Vector3::UNIT_Z);
            SquirtleNode->rotate(rotation);
            //SquirtleNode->yaw(Degree(-5));
        }

        else if (mPressKeySet.count('o')) {
            SquirtleAnimation->setEnabled(true);
            SquirtleAnimation->addTime(evt.timeSinceLastFrame);
        }
    }

    else if (objectName == "WartortleNode") {
        if (mPressKeySet.count('j')) {
            WartortleNode->translate(Vector3(1, 0, 0) * evt.timeSinceLastFrame);
            WartortleNode->yaw(Degree(5));
        }

        else if (mPressKeySet.count('l')) {
            WartortleNode->translate(Vector3(1, 0, 0) * evt.timeSinceLastFrame);
            WartortleNode->yaw(Degree(-5));
        }

        else if (mPressKeySet.count('i')) {
            WartortleNode->translate(Vector3(0, 1, 0) * evt.timeSinceLastFrame);
            Quaternion rotation = Quaternion(Degree(60), Vector3::UNIT_X);
            WartortleNode->rotate(rotation);
            //WartortleNode->yaw(Degree(-5));
        }

        else if (mPressKeySet.count('k')) {
            WartortleNode->translate(Vector3(0, -1, 0) * evt.timeSinceLastFrame);
            Quaternion rotation = Quaternion(Degree(-60), Vector3::UNIT_Z);
            WartortleNode->rotate(rotation);
            //WartortleNode->yaw(Degree(-5));
        }

        else if (mPressKeySet.count('o')) {
            WartortleAnimation->setEnabled(true);
            WartortleAnimation->addTime(evt.timeSinceLastFrame);
        }
    }

    else if (objectName == "BlastoiseNode") {
        if (mPressKeySet.count('j')) {
            BlastoiseNode->translate(Vector3(1, 0, 0) * evt.timeSinceLastFrame);
            BlastoiseNode->yaw(Degree(5));
        }

        else if (mPressKeySet.count('l')) {
            BlastoiseNode->translate(Vector3(1, 0, 0) * evt.timeSinceLastFrame);
            BlastoiseNode->yaw(Degree(-5));
        }
        else if (mPressKeySet.count('i')) {
            BlastoiseNode->translate(Vector3(0, 1, 0) * evt.timeSinceLastFrame);
            Quaternion rotation = Quaternion(Degree(60), Vector3::UNIT_X);
            BlastoiseNode->rotate(rotation);
            //BlastoiseNode->yaw(Degree(5));
        }

        else if (mPressKeySet.count('k')) {
            BlastoiseNode->translate(Vector3(0, -1, 0) * evt.timeSinceLastFrame);
            Quaternion rotation = Quaternion(Degree(-60), Vector3::UNIT_Z);
            BlastoiseNode->rotate(rotation);
            //BlastoiseNode->yaw(Degree(-5));
        }

        else if (mPressKeySet.count('o')) {
            BlastoiseAnimation->setEnabled(true);
            BlastoiseAnimation->addTime(evt.timeSinceLastFrame);
        }
    }

    return ApplicationContext::frameRenderingQueued(evt);
}

//-------------------------------------------------------------------------------------
bool TutorialApplication::keyPressed(const KeyboardEvent& evt)
{
    mPressKeySet.insert(evt.keysym.sym);
    if (evt.keysym.sym == SDLK_DOWN || evt.keysym.sym == SDLK_UP)
    {
        // Change the selected button
        mCurrentButtonIndex += (evt.keysym.sym == SDLK_DOWN) ? 1 : -1;
        std::cout << mCurrentButtonIndex << std::endl;
        if (mCurrentButtonIndex < 0) mCurrentButtonIndex = mButtons.size() - 1;
        else if (mCurrentButtonIndex >= mButtons.size()) mCurrentButtonIndex = 0;

        highlightCurrentButton();
    }
    else if (evt.keysym.sym == SDLK_RETURN)
    {
        // Select the current button
        buttonHit(mButtons[mCurrentButtonIndex]);
        highlightCurrentButton();
    }

    if (mIntroActive && evt.keysym.sym == SDLK_END) {
        transitionToMenu();
    }
    
    return BaseApplication::keyPressed(evt);
}

void TutorialApplication::destroyMenu(void) {
    mTrayMgr->destroyWidget("StartButton");
    mTrayMgr->destroyWidget("MenuButton");
    mTrayMgr->destroyWidget("OptionButton");
}

void TutorialApplication::buttonHit(OgreBites::Button* button)
{
    const std::string& buttonName = button->getName();
    if (buttonName == "CaveButton" )
    {
        setupSound(2, false);
        soundMgr->stopAllAudio();

        //if (Forest_root_base1Node) {
        //    Forest_root_baseNode->detachObject(Forest_root_base);
        //    Forest_root_base1Node->detachObject(Forest_root_base1);
        //    Forest_root_base2Node->detachObject(Forest_root_base2);
        //    Forest_root_base3Node->detachObject(Forest_root_base3);
        //    Forest_root_base4Node->detachObject(Forest_root_base4);
        //    Forest_root_base5Node->detachObject(Forest_root_base5);
        //    Forest_root_base6Node->detachObject(Forest_root_base6);
        //    Forest_root_loopANode->detachObject(Forest_root_loopA);
        //    Forest_root_loopBNode->detachObject(Forest_root_loopB);
        //    Forest_root_loopCNode->detachObject(Forest_root_loopC);
        //}
        // Handle Start button logic
        Ogre::LogManager::getSingletonPtr()->logMessage("Cave button clicked");
        setupCaveScene();
    }
    else if (buttonName == "ForestButton" )
    {
        setupSound(2, false);
        soundMgr->stopAllAudio();

        //if (Cave_crystalNode) {
        //    Cave_crystalNode->detachObject(Cave_crystalEntity);
        //    Cave_floorNode->detachObject(Cave_floorEntity);
        //    Cave_grassNode->detachObject(Cave_grassEntity);
        //    Cave_rootNode->detachObject(Cave_rootEntity);
        //    Cave_stoneNode->detachObject(Cave_stoneEntity);
        //    Cave_wallNode->detachObject(Cave_wallEntity);
        //}
        // Handle Map button logic - transition to another scene
        Ogre::LogManager::getSingletonPtr()->logMessage("Forest button clicked");
        setupForestScene();
    }

    else if (buttonName == "SquirtleButton" )
    {
        setupSound(2, false);

        //if (WartortleNode) {
        //    WartortleNode->detachObject(Wartortle);
        //}
        //if (BlastoiseNode) {
        //    BlastoiseNode->detachObject(Blastoise);
        //}
        // Handle Option button logic
        Ogre::LogManager::getSingletonPtr()->logMessage("Squirtle button clicked");
        createSquirtle();

        if (SquirtleNode) {
            objectName= SquirtleNode->getName();
        }
        Ogre::LogManager::getSingletonPtr()->logMessage("Object Name: "+objectName);
    }

    else if (buttonName == "WartortleButton" )
    {
        setupSound(2, false);

        // Handle Option button logic
        //if (SquirtleNode) {
        //    SquirtleNode->detachObject(Squirtle);
        //}
        //if (BlastoiseNode) {
        //    BlastoiseNode->detachObject(Blastoise);
        //}
        Ogre::LogManager::getSingletonPtr()->logMessage("Wartortle button clicked");
        if (!WartortleNode) {
            createWartortle();

            if (WartortleNode) {
                objectName = WartortleNode->getName();
            }
            Ogre::LogManager::getSingletonPtr()->logMessage("Object Name: " + objectName);
        }

    }

    else if (buttonName == "BlastoiseButton"  )
    {
        setupSound(2, false);
        // Handle Option button logic
        //Ogre::LogManager::getSingletonPtr()->logMessage("Blastoise button clicked");
        if (!BlastoiseNode) {
            /*if (SquirtleNode) {
                SquirtleNode->detachObject(Squirtle);
                std::cout << "Detach Squirtle" << std::endl;
            }
            if (Wartortle) {
                WartortleNode->detachObject(Wartortle);
                std::cout << "Detach Wartortle" << std::endl;
            }*/
            createBlastoise();
            if (BlastoiseNode) {
                objectName = BlastoiseNode->getName();
            }
            Ogre::LogManager::getSingletonPtr()->logMessage("Object Name: " + objectName);
        }
    }
}


//-------------------------------------------------------------------------------------
bool TutorialApplication::keyReleased(const KeyboardEvent& evt)
{
    mPressKeySet.erase(evt.keysym.sym);
    return BaseApplication::keyReleased(evt);
}


//-------------------------------------------------------------------------------------
bool TutorialApplication::mousePressed(const MouseButtonEvent& evt)
{
    mPressMouseSet.insert(evt.button);

    if (mIntroActive) {

        transitionToMenu();
    }

    return BaseApplication::mousePressed(evt);
}


//-------------------------------------------------------------------------------------
bool TutorialApplication::mouseReleased(const MouseButtonEvent& evt)
{
    mPressMouseSet.erase(evt.button);
    return BaseApplication::mouseReleased(evt);
}

//-------------------------------------------------------------------------------------
void TutorialApplication::setupSound(int audioIndex, bool loopSet)
{
    soundMgr = SoundManager::createManager();

    std::cout << soundMgr->listAvailableDevices();

    soundMgr->init();
    soundMgr->setAudioPath((char*)".\\");

    unsigned int id0;
    soundMgr->loadAudio("audio\\intro.wav", &id0, false);
    unsigned int id1;
    soundMgr->loadAudio("audio\\menu_stage.wav", &id1, false);
    unsigned int id2;
    soundMgr->loadAudio("audio\\menu_okay.wav", &id2, false);
    unsigned int id3;
    soundMgr->loadAudio("audio\\cave.wav", &id3, false);
    unsigned int id4;
    soundMgr->loadAudio("audio\\forest.wav", &id4, false);

    audioId.push_back(id0);
    audioId.push_back(id1);
    audioId.push_back(id2);
    audioId.push_back(id3);
    audioId.push_back(id4);
    // Just for testing
    std::cout << "setup sound" << std::endl;
    soundMgr->playAudio(audioId[audioIndex], loopSet);
}

//-------------------------------------------------------------------------------------
int main(int argc, char **argv)
{
    try
    {
    	TutorialApplication app;
        app.initApp();
		app.go();
        app.closeApp();
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error occurred during execution: " << e.what() << '\n';
        return 1;
    }

    return 0;
}
