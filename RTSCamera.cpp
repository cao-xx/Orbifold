/*
 *  RTSCamera.cpp
 *  Prototyp
 *
 *  Created by Christian Pehle on 07.09.09.
 *  Copyright 2009 Orbifold. All rights reserved.
 *
 */

#include <Ogre/OgreSceneManager.h>
#include <Ogre/OgreRenderSystem.h>
#include "RTSCamera.h"
#include "Game.h"

class RTSCamera;

namespace Orbifold {
  RTSCamera::RTSCamera(const Ogre::String& name,  Ogre::SceneManager* sm) {
    mSceneManager = sm;
    mCamera = sm->createCamera(name);
  }
  
  RTSCamera::~RTSCamera() {}
  
  Ogre::Viewport* RTSCamera::initialise() {
    Ogre::Camera* cam = mCamera;
    
    if (Ogre::Root::getSingletonPtr()->getRenderSystem()->getCapabilities()->hasCapability(Ogre::RSC_INFINITE_FAR_PLANE)) {
      cam->setFarClipDistance(0);
    }
    
    cam->setPosition(707,2500,528);
    cam->setOrientation(Ogre::Quaternion(-0.3486, 0.0122, 0.9365, 0.0329));
    mRaySceneQuery = mSceneManager->createRayQuery(Ogre::Ray(cam->getPosition(), -Ogre::Vector3::UNIT_Y));
    static Ogre::Ray updateRay;
    updateRay.setOrigin(cam->getPosition());
    updateRay.setDirection(-Ogre::Vector3::UNIT_Y);
    mRaySceneQuery->setRay(updateRay);
    Ogre::RaySceneQueryResult& qryResult = mRaySceneQuery->execute();
    Ogre::RaySceneQueryResult::iterator i = qryResult.begin();
    if (i != qryResult.end() && i->worldFragment) {
      Ogre::Vector3 campos = cam->getPosition();
      Ogre::Vector3 inter = i->worldFragment->singleIntersection;  
      
      cam->setPosition(cam->getPosition().x,
                       inter.y +10,
                       cam->getPosition().z);
    }
  }
  
  
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
    mCamera->moveRelative(tslu*this->mVelocity);
    mCamera->roll(tslu*this->mRollVel);
    
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
}