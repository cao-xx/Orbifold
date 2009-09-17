/*
 *  RTSCamera.h
 *  Prototyp
 *
 *  Created by Christian Pehle on 07.09.09.
 *  Copyright 2009 Orbifold. All rights reserved.
 *
 */


#ifndef RTSCamera_H
#define RTSCamera_H

#include <Ogre/OgreCamera.h>

namespace Orbifold {
  class RTSCamera {
  public:
    RTSCamera(const Ogre::String& name, Ogre::SceneManager* sm);
    virtual ~RTSCamera();
    
    Ogre::Viewport* initialize();
    
    void restore();
    void save();
    
    void update(unsigned long tslu);
    //void update();
    
    //Ogre::Camera* getCamera();
    
  protected:
    Ogre::SceneManager* mSceneManager;
    Ogre::RaySceneQuery* mRaySceneQuery;
    
    Ogre::Vector3 mSavedDirection;
    Ogre::Vector3 mSavedPosition;
    Ogre::Quaternion mSavedOrientation;
    Ogre::Vector3 mSavedUp;
    Ogre::Vector3 mSavedRight;
    
    Ogre::Vector3 mVelocity;
    Ogre::Radian mRollvel;
    
  
  private:
    Ogre::Camera* mCamera;
  };

}

#endif