# A Linux Ogre/CEGUI/OIS/OgreOde build Script by Grey, with many thanks to keir from #scons on freenode.

# Setup our Build Environment, Smarter scripts might be able to change this at the command line,
env = Environment(
   CCFLAGS='-ggdb -pg -g3 -DEXT_HASH',
   LDFLAGS='-pg'
)

# Our External Libs
# Got some fugly stuff ( || true ) in there to supress unreadable crashes, it
# ends up using the nicer formatted error messages below 
env.ParseConfig('pkg-config --silence-errors --libs --cflags OGRE || true')
env.ParseConfig('pkg-config --silence-errors --libs --cflags OIS || true')
#env.ParseConfig('pkg-config --silence-errors --libs --cflags CEGUI-OGRE || true')
#env.ParseConfig('pkg-config --silence-errors --libs --cflags OgreOde_Core || true')

# Get out current config so we can verify we have everything we need.
# There is an autoadd method here, but then we'd have to specify full paths for 
# the libs and headers, which is lame.
config = Configure(env);

# Everyone needs OIS :)
if not config.CheckLibWithHeader('OIS', 'OISPrereqs.h', 'C++'):
 print 'OIS must be installed!'
 Exit(1)

# this should work to get Ogre included
if not config.CheckLibWithHeader( 'OgreMain', 'Ogre.h', 'C++' ):
 print "Ogre Must be installed!"
 Exit(1)

# # Any other component libraries you use can be added and tested in this manner
# if not config.CheckLibWithHeader( 'OgreOde_Core', 'OgreOde_Core.h', 'C++'):
#  print 'OgreOde must be installed!'
#  Exit(1);

# # Substitute with your GUI of choice
# if not config.CheckLibWithHeader('CEGUIBase', 'CEGUI.h', 'C++'):
#  print "You need CEGUI to compile this program"
#  Exit(1);

# if not config.CheckLibWithHeader('CEGUIOgreRenderer', 'OgreCEGUIRenderer.h', 'C++'):
#  print "You need OGRE-CEGUI to compile this program"
#  Exit(1);

# Validate the configuration and assign it to our env
env = config.Finish(); 

# Build our main program
env.Program(
   target = 'main',
   # Replace these with your source files of course
   source = [
       'main.cpp', 'game.cpp', 'input.cpp', 'game_state.cpp', 'play_state.cpp'])

