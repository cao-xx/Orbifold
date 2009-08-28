/*
 *  OggStream.h
 *  Prototyp
 *
 *  Created by Christian Pehle on 28.08.09.
 *  Copyright 2009 Universität Heidelberg. All rights reserved.
 *
 */


#ifndef OggStream_H
#define OggStream_H 

#include <string>
#include <iostream>
using namespace std;

#include <al/al.h>
#include <ogg/ogg.h>
#include <vorbis/codec.h>
#include <vorbis/vorbisenc.h>
#include <vorbis/vorbisfile.h>

#define BUFFFER_SIZE (4096 * 8)

class OggStream {
	
public:

	void open(string path);
	void release();
	void display();
	bool playback();
	bool playing();
	bool update();
	
protected:
	
	bool stream(ALuint buffer);
	void empty();
	void check();
	string errorString(int code);
	
private:
	
	FILE* oggFile;
	OggVorbis_File oggStream;
	vorbis_info* vorbisInfo;
	vorbis_comment* vorbisComment;
	
	ALuint buffers[2];
	ALuint source;
	ALuint format;
	
};
#endif