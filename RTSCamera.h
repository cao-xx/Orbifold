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
#include <Ogre/OgreTimer.h>
#include <OIS/OISMouse.h>
#include <OIS/OISKeyboard.h>

namespace Orbifold {
  
  class BaseAnim {
  
  protected:
    double mMv;
    double mGm;
    
    Ogre::Timer* mxT;
    Ogre::Timer* myT;
    Ogre::Timer* mzT;
    
    Ogre::Vector3 mVelocity;
    
    
    
    
    // those 6 functions should really just be 2
    // they should represent slowdown and acceleration with
    // air resistance
    void xAcc(double vx0, unsigned long tx) {
      mVelocity.x = mMv*tanh(tx + atanh(vx0));      
    }
    
    void yAcc(double vy0, unsigned long ty) {
      mVelocity.y = mMv*tanh(ty + atanh(vy0));
    }
    
    void zAcc(double vz0, unsigned long tz) {
      mVelocity.z = mMv*tanh(tz - atanh(vz0));
    }
    
    void xSlow(double vx0, unsigned long tx) {
      mVelocity.x = vx0 / (1 + vx0 * mGm * tx);
    }
    
    void ySlow(double vy0, unsigned long ty) {
      mVelocity.y = vy0 / (1 + vy0 * mGm * ty);
    }
    
    void zSlow(double vz0, unsigned long tz) {
      mVelocity.z = vz0 / (1 + vz0 * mGm * tz);
    }    
  };
  
  
  class RTSCamera : BaseAnim {
  public:
    RTSCamera(const Ogre::String& name, Ogre::SceneManager* sm);
    virtual ~RTSCamera();
    
    Ogre::Viewport* initialise();
    
    void restore();
    void save();
    
    void update(unsigned long tslu);
    
    // Input Handling, not sure if its a good idea to place it here, but well...
    
    bool keyPressed(const OIS::KeyEvent &evt);
    bool keyReleased(const OIS::KeyEvent &evt);
    bool mouseMoved(const OIS::MouseEvent &evt);
    
    bool mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id);
    bool mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id);
  
  protected:
    Ogre::SceneManager* mSceneManager;
    Ogre::RaySceneQuery* mRaySceneQuery;
    
    Ogre::Vector3 mSavedDirection;
    Ogre::Vector3 mSavedPosition;
    Ogre::Quaternion mSavedOrientation;
    Ogre::Vector3 mSavedUp;
    Ogre::Vector3 mSavedRight;
    
    
    Ogre::Radian mRollVel;
    Ogre::Radian mPitchVel;
    Ogre::Radian mYawVel;
    
    bool rollLckd;
    bool pitchLckd;
    bool yawLckd;
    
    
  private:
    Ogre::Camera* mCamera;
  };

}

#endif