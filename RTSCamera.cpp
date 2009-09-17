/*
 *  RTSCamera.cpp
 *  Prototyp
 *
 *  Created by Christian Pehle on 07.09.09.
 *  Copyright 2009 Orbifold. All rights reserved.
 *
 */

#include <Ogre/OgreSceneManager.h>
#include "RTSCamera.h"

class RTSCamera;

namespace Orbifold {
  
  RTSCamera::RTSCamera(const Ogre::String& name,  Ogre::SceneManager* sm) {
    mSceneManager = sm;
    mCamera = sm->createCamera(name);
  }
  
  RTSCamera::~RTSCamera() {}
  
  void RTSCamera::save() {
    if (mCamera) {
    mSavedDirection = mCamera->getRealDirection();
    mSavedOrientation = mCamera->getRealOrientation();
    mSavedPosition = mCamera->getRealPosition();
    }
  }

  void RTSCamera::restore() {
    if(mCamera) {
      mCamera->setPosition(mSavedPosition);
      mCamera->setDirection(mSavedDirection);
      mCamera->setOrientation(mSavedOrientation);
    }
  }
  
  void RTSCamera::update(unsigned long tslu) {
      // Movement should be adapted / restricted
      mCamera->moveRelative(tslu*this->velocity);
      mCamera->roll(tslu*this->spin);
      
      // Basic collision detection
      static Ogre::Ray updateRay;
      updateRay.setOrigin(mCamera->getPosition());
      updateRay.setDirection(-Ogre::Vector3::UNIT_Y);
      mRaySceneQuery->setRay(updateRay);
      Ogre::RaySceneQueryResult& qryResult = mRaySceneQuery->execute();
      Ogre::RaySceneQueryResult::iterator i = qryResult.begin();
      if (i != qryResult.end() && i->worldFragment) {
        Ogre::Vector3 campos = mCamera->getPosition();
        Ogre::Vector3 inter = i->worldFragment->singleIntersection;  
        if (campos.y < inter.y + 10) {
          mCamera->setPosition(mCamera->getPosition().x,
                           inter.y +10,
                           mCamera->getPosition().z);
        } else {
          mCamera->setPosition(campos);
        }
        
      }
  }
  
  Ogre::Camera* RTSCamera::getCamera() {
    return mCamera;
  }
}