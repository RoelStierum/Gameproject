#############################################################################
#
# Project Makefile
#
# (c) Wouter van Ooijen (www.voti.nl) 2016
#
# This file is in the public domain.
# 
#############################################################################

# source files in this project (main.cpp is automatically assumed)
SOURCES := StateMachine.cpp InputManager.cpp AssetManager.cpp Game.cpp SplashState.cpp MainMenuState.cpp Character.cpp Levels/TestLevel.cpp

# header files in this project
HEADERS := State.hpp StateMachine.hpp InputManager.hpp AssetManager.hpp Game.hpp SplashState.hpp MainMenuState.hpp Character.hpp Levels/TestLevel.hpp

# other places to look for files for this project
SEARCH  := 

# set REATIVE to the next higher directory 
# and defer to the Makefile.due there
RELATIVE := $(RELATIVE)../
include $(RELATIVE)Makefile.native
