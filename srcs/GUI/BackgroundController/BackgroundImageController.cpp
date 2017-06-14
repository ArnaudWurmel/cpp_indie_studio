//
// Created by wurmel_a on 14/06/17.
//

#include <OgreRectangle2D.h>
#include "BackgroundImageController.hh"

Indie::BackgroundImageController::BackgroundImageController(RootViewController& delegate) {
    mBackgroundRect = std::unique_ptr<Ogre::Rectangle2D>(new Ogre::Rectangle2D(true));
    mBackgroundRect->setCorners(-1.0, 1.0, 1.0, -1.0);
    mBackgroundRect->setRenderQueueGroup(Ogre::RENDER_QUEUE_BACKGROUND);
    Ogre::AxisAlignedBox axisAlignedBox;
    axisAlignedBox.setInfinite();
    mBackgroundRect->setBoundingBox(axisAlignedBox);
    Ogre::SceneNode* node = delegate.getSceneManager()->getRootSceneNode()->createChildSceneNode("Background");
    node->attachObject(mBackgroundRect.get());
}

void    Indie::BackgroundImageController::hideBackground() {
    mBackgroundRect->setVisible(false);
}

void Indie::BackgroundImageController::showBackground() {
    mBackgroundRect->setVisible(true);
}

void    Indie::BackgroundImageController::setBackgroundMaterialName(std::string const& materialName) {
    mBackgroundRect->setMaterial(materialName);
}

Indie::BackgroundImageController::~BackgroundImageController() {}