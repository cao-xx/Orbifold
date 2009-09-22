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
  
  /*class BaseAnim {
  
  protected:
    double mMv;
    double mGm;
    
    Ogre::Timer* mxT;
    Ogre::Timer* myT;
    Ogre::Timer* mzT;
    
    Ogre::Vector3 mVelocity;
    
    // those 6 functions should really just be 2
    // they represent slowdown and acceleration with
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
  }; */
  
  
  class RTSCamera : public OIS::KeyListener, public OIS::MouseListener {
  public:
    RTSCamera(const Ogre::String& name, Ogre::SceneManager* sm);
    virtual ~RTSCamera();
    
    void initialise();
    
    void restore();
    void save();
    
    void update(unsigned long tslu);
    
    inline Ogre::Camera* getCamera() {
      return this->mCamera;
    }
    
    // Input Handling, not sure if its a good idea to place it here, but well...
    
    bool keyPressed(const OIS::KeyEvent &evt) {
      switch (evt.key) {
        case OIS::KC_D:
          mVelocity.x += 0.1;
          break;
        case OIS::KC_A:
          mVelocity.x -= 0.1;
          break;
        case OIS::KC_S:
          mVelocity.z -= 0.1;
          break;
        case OIS::KC_W:
          mVelocity.z += 0.1;
          break;  
        case OIS::KC_Q:
          mVelocity.y += 0.1;
          break;
        case OIS::KC_E:
          mVelocity.y -= 0.1;
          break;
        default:
          break;
      }
      return true;
    }
    
    bool keyReleased(const OIS::KeyEvent &evt) {
      switch (evt.key) {
        case OIS::KC_D:
          mVelocity.x -= 0.1;
          break;
        case OIS::KC_A:
          mVelocity.x += 0.1;
        break;
        case OIS::KC_W:
          mVelocity.z -= 0.1;
          break;
        case OIS::KC_S:
          mVelocity.z += 0.1;
          break;
        case OIS::KC_Q:
          mVelocity.y -= 0.1;
          break;
        case OIS::KC_E:
          mVelocity.y += 0.1;
          break;
        default:
          break;
      }
      
      
      return true;
    }
    
    
    bool mouseMoved(const OIS::MouseEvent &evt) {return true;}
    bool mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id) {return true;}
    bool mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id) {return true;}
  
  protected:
    Ogre::SceneManager* mSceneManager;
    Ogre::RaySceneQuery* mRaySceneQuery;
    
    Ogre::Vector3 mSavedDirection;
    Ogre::Vector3 mSavedPosition;
    Ogre::Quaternion mSavedOrientation;
    Ogre::Vector3 mSavedUp;
    Ogre::Vector3 mSavedRight;
    
    Ogre::Vector3 mVelocity;
    
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