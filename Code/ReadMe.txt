========================================================================
    CONSOLE APPLICATION : Irrlicht1 Project Overview
========================================================================

This file contains a summary of what you will find in each of the files that
make up your Irrlicht1 application.

EventReceiver.cpp
    This is the Event Receiver for testing-purposes only. Each GameState has its on Event
    Receiver. Definitions and declarations of the functions are both in the headerfile.

EventReceiver.h

GameState.cpp
    This is the parent-class of all further GameStates. It includes some standard virtual
    functions for events like on enter function, on leave function, on render function and
    of course an event receiver for all kinds off inputs (derived from Irrlicht)

GameState.h

GameStateManager.cpp
    This is the Game State Manager. It stores all GameStates in a array and manages them
    with methods to change the active GameState, find the active GameState, flushing ended
    GameStates and initalizing new ones. Furthermore it is able to generate a engine-device.

GameStateManager.h

Intro.cpp
    This GameState provides the Intro on the startup of the game. Derrived from GameState.

Intro.h

Irrlicht1.cpp
    This is the main application source file.

Irrlicht1.sdf

Irrlicht1.sln

Irrlicht1.suo

Irrlicht1.vcxproj
    This is the main project file for VC++ projects generated using an Application Wizard.
    It contains information about the version of Visual C++ that generated the file, and
    information about the platforms, configurations, and project features selected with the
    Application Wizard.

Irrlicht1.vcxproj.filters
    This is the filters file for VC++ projects generated using an Application Wizard. 
    It contains information about the association between the files in your project 
    and the filters. This association is used in the IDE to show grouping of files with
    similar extensions under a specific node (for e.g. ".cpp" files are associated with the
    "Source Files" filter).

Irrlicht1.vcxproj.user

Main.cpp

Main.h

ResManager.cpp
    This source file manages all resources needed in this project for easy access an a source
    friendly programming.

ResManager.h

StartMenu.cpp
    This GameState provides the mainmenu of the game. Here shall be implemented the functions
    for loading a game, options, credits and of course starting the game.

StartMenu.h

swap.cpp
    This sourcefile is ust for code snippets that are not used in the project at the moment
    but are maybe usefull in the future.

targetver.h
    Defines the highest avaiable Windows-Version.

/////////////////////////////////////////////////////////////////////////////
Other standard files:

StdAfx.h, StdAfx.cpp
    These files are used to build a precompiled header (PCH) file
    named Irrlicht1.pch and a precompiled types file named StdAfx.obj.

/////////////////////////////////////////////////////////////////////////////
Other notes:

AppWizard uses "TODO:" comments to indicate parts of the source code you
should add to or customize.

/////////////////////////////////////////////////////////////////////////////
