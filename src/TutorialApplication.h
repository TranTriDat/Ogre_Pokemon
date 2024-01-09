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

#ifndef __TutorialApplication_h_
#define __TutorialApplication_h_

#include "BaseApplication.h"

#include "SoundManager.h"

using namespace Ogre;
using namespace OgreBites;

class TutorialApplication : public BaseApplication
{
public:
    TutorialApplication();
    virtual ~TutorialApplication();

protected:
    virtual bool frameRenderingQueued(const FrameEvent& evt);
    virtual bool keyPressed(const KeyboardEvent& evt);
    virtual bool keyReleased(const KeyboardEvent& evt);
    virtual bool mousePressed(const MouseButtonEvent& evt);
    virtual bool mouseReleased(const MouseButtonEvent& evt);

	virtual void createScene(void) override;
    virtual void createMenu(void);
    virtual void transitionToMenu(void);
    SelectMenu* sceneMenu;
    virtual void itemSelected(SelectMenu* sceneMenu); 

    // GUI scene management
    virtual void setupIntroScene(void);
    virtual void destroyMenu(void);
    virtual void setupCaveScene(void);
    virtual void setupForestScene(void);


    // Event handlers
   /* virtual bool handleKeyPress(const KeyboardEvent& evt);
    virtual void onSelectionMenuClicked(Button* button);*/

    virtual void highlightCurrentButton(void);

    virtual void buttonHit(Button* button) override;


    StringVector listOfOptions;
    // Cave Scene
    Entity* Cave_crystalEntity;
    SceneNode* Cave_crystalNode;
    Entity* Cave_floorEntity;
    SceneNode* Cave_floorNode;
    Entity* Cave_grassEntity;
    SceneNode* Cave_grassNode;
    Entity* Cave_rootEntity;
    SceneNode* Cave_rootNode;
    Entity* Cave_stoneEntity;
    SceneNode* Cave_stoneNode;
    Entity* Cave_wallEntity;
    SceneNode* Cave_wallNode;


    Overlay* mIntroOverlay;
    bool mIntroActive;
    bool mSelectStage;
    bool mCaveScene;
    bool mForestScene;


    //Forest Scene
    Entity* Forest_root_base;
    SceneNode* Forest_root_baseNode;
    Entity* Forest_root_base1;
    SceneNode* Forest_root_base1Node;
    Entity* Forest_root_base2;
    SceneNode* Forest_root_base2Node;
    Entity* Forest_root_base3;
    SceneNode* Forest_root_base3Node;
    Entity* Forest_root_base4;
    SceneNode* Forest_root_base4Node;
    Entity* Forest_root_base5;
    SceneNode* Forest_root_base5Node;
    Entity* Forest_root_base6;
    SceneNode* Forest_root_base6Node;
    Entity* Forest_root_loopA;
    SceneNode* Forest_root_loopANode;
    Entity* Forest_root_loopB;
    SceneNode* Forest_root_loopBNode;
    Entity* Forest_root_loopC;
    SceneNode* Forest_root_loopCNode;

    // Squirtle
    Entity* Squirtle;
    SceneNode* SquirtleNode;
    AnimationState* SquirtleAnimation;
    virtual void createSquirtle(void);

    // Wartortle
    Entity* Wartortle;
    SceneNode* WartortleNode;
    AnimationState* WartortleAnimation;
    virtual void createWartortle(void);

    // Blastoise
    Entity* Blastoise;
    SceneNode* BlastoiseNode;
    Entity* Blastoise_CannonA;
    SceneNode* Blastoise_CannonANode;
    Entity* Blastoise_CannonB;
    SceneNode* Blastoise_CannonBNode;
    AnimationState* BlastoiseAnimation;
    virtual void createBlastoise(void);

    virtual void selectPokemonMenu(void);

    String objectName;

    std::set<Keycode> mPressKeySet;
    std::set<unsigned char> mPressMouseSet;
    std::vector<Button*> mButtons;
    OgreBites::Button* mCurrentButton;
    int mCurrentButtonIndex;

    TextBox* mSelectionIndicator;
    Ogre::ColourValue mNormalColour;    // Normal text colour
    Ogre::ColourValue mHighlightColour; // Highlighted text colour
    OverlayContainer* mSelector;

    Button* caveButton; 
    Button* forestButton;
    Button* squirtleButton;
    Button* wartortleButton;
    Button* blastoiseButton;

    // Sound
    SoundManager* soundMgr;

    ALCdevice* device;
    ALCcontext* context;
    ALuint introBuffer, menuBuffer, caveBuffer, forestBuffer, squirtleBuffer, wartortleBuffer, blastoiseBuffer;
    ALuint source;

    std::vector<unsigned int> audioId ;

    //virtual void playIntroMusic(void);
    //virtual void playMenuMusic(void);
    //virtual void playSquirtleMusic(void);
    //virtual void playWartortleMusic(void);
    //virtual void playBlastoiseMusic(void);

    virtual void setupSound(int audioIndex, bool loopSet);

};

#endif // __TutorialApplication_h_
