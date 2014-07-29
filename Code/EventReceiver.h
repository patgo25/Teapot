#pragma once
#include <irrlicht.h>
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class EventReceiver : public IEventReceiver
{
private:
    bool KeyIsDown[KEY_KEY_CODES_COUNT];
	IrrlichtDevice *internalDevice;

public:

	/*enum
	{
	GUI_ID_QUIT_BUTTON = 101,
	GUI_ID_OPTIONS_BUTTON,
	GUI_ID_SAVE_BUTTON,
	};
*/

	EventReceiver(IrrlichtDevice *device) : internalDevice(device)
    {
		//bindet das Device an diese Instanz
        //Wichtig, da sonst nicht auf die Benutzereingabe reagiert werden kann!
		device->setEventReceiver(this);
		for (u32 i=0; i<KEY_KEY_CODES_COUNT; ++i)
			KeyIsDown[i] = false;
    }

    // This is the one method that we have to implement
    virtual bool OnEvent(const SEvent& event)
    {
        // Remember whether each key is down or up
        if (event.EventType == irr::EET_KEY_INPUT_EVENT)
            KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;


		if(event.EventType == EET_GUI_EVENT)
		{
			s32 id = event.GUIEvent.Caller->getID();
			IGUIEnvironment *env = internalDevice->getGUIEnvironment();

			switch(event.GUIEvent.EventType)
			{
	
			case EGET_BUTTON_CLICKED:
				switch(id)
				{
				case 101:
					internalDevice->closeDevice();
					return true;
				case 102:
					{
						
					}
					return true;
				case 103:
					{

					}
					return true;

				default:
					return false;
				}
				break;
			
			}
		}
		return false;
	}
  

    // This is used to check whether a key is being held down
    virtual bool IsKeyDown(EKEY_CODE keyCode) const
    {
        return KeyIsDown[keyCode];
    }


	virtual IrrlichtDevice* ReturnDevice()
	{
		return internalDevice;
	}

	

};

