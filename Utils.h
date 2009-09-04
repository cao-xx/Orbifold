/*
 *  Utils.h
 *  Prototyp
 *
 *  Created by Christian Pehle on 04.09.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */


#ifndef Utils_H
#define Utils_H


#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE
#include <CoreFoundation/CoreFoundation.h>

/*
 * This function will return the appropriate working directory depending
 * on the platform. For Windows, a blank string will suffice. For OS X,
 * however, we need to do a little extra work.
 */

std::string macBundlePath()
{
	char path[1024];
	CFBundleRef mainBundle = CFBundleGetMainBundle();
	assert(mainBundle);
	CFURLRef mainBundleURL = CFBundleCopyBundleURL(mainBundle);
	assert(mainBundleURL);
	CFStringRef cfStringRef = CFURLCopyFileSystemPath(mainBundleURL, kCFURLPOSIXPathStyle);
	assert(cfStringRef);
	CFStringGetCString(cfStringRef, path, 1024, kCFStringEncodingASCII);
	CFRelease(mainBundleURL);
	CFRelease(cfStringRef);
	return std::string(path);
}
#endif



#endif