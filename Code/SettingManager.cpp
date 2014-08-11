#include "StdAfx.h"
#include "SettingManager.h"


SettingManager::SettingManager(const core::stringw &settingsFile) : SettingsFile(settingsFile), NullDevice(0)
{
	NullDevice = createDevice(video::EDT_NULL);

	DriverOptions.insert(L"Software", video::EDT_SOFTWARE);
	DriverOptions.insert(L"OpenGL", video::EDT_OPENGL);
	DriverOptions.insert(L"Direct3D9", video::EDT_DIRECT3D9);

	ResolutionOptions.insert(L"640x480", core::dimension2du(640,480));
    ResolutionOptions.insert(L"800x600", core::dimension2du(800,600));
    ResolutionOptions.insert(L"1024x768", core::dimension2du(1024,768));

	VideoMap.insert(L"driver",L"OpenGL");
	VideoMap.insert(L"resolution", L"800x600");
    VideoMap.insert(L"fullscreen", L"0"); //0 ist false
}


SettingManager::~SettingManager(void)
{
	if (NullDevice)
    {
        NullDevice->closeDevice();
        NullDevice->drop();
    }
}

bool SettingManager::load()
{
	if(!NullDevice)
		return false;

	else
	{
		io::IXMLReader *xml = NullDevice->getFileSystem()->createXMLReader(SettingsFile);
		if(!xml)
			return false;
		else
		{
			const core::stringw settingTag(L"setting"); //<- Im XML nach dem Tag suchen
			core::stringw currentSection;
			const core::stringw videoTag(L"video");

			while(xml->read())
			{
				switch(xml->getNodeType())
				{
				case io::EXN_ELEMENT:
					{
						if(currentSection.empty() && videoTag.equals_ignore_case(xml->getNodeName()))
						{
							currentSection = videoTag;
						}
						else if(currentSection.equals_ignore_case(videoTag) && settingTag.equals_ignore_case(xml->getNodeName()))
						{
							//Schlüssel auslesen
							core::stringw key = xml->getAttributeValueSafe(L"name");
							if(!key.empty())
							{
								VideoMap[key] = xml->getAttributeValueSafe(L"value");
							}
						}

						//..
						//Weitere Sektionen einfügen
						//..
					}
					break;
				case io::EXN_ELEMENT_END:
					{
						currentSection = L"";
					}
					break;
				}
			}
			xml->drop();
			return true;
		}
	}
}

bool SettingManager::save()
{
	if(NullDevice)
	{
		io::IXMLWriter* xwriter = NullDevice->getFileSystem()->createXMLWriter(SettingsFile);
		if(xwriter)
		{
			//obligatorischen Header schreiben
			xwriter->writeXMLHeader();

			xwriter->writeElement(L"teapot");
			xwriter->writeLineBreak();

			xwriter->writeElement(L"video");
			xwriter->writeLineBreak();

			//Pointer zum ersten Knoten von video besorgen
			core::map<core::stringw, core::stringw>::Iterator i = VideoMap.getIterator();
			for(i; !i.atEnd(); i++)
			{
				//Elemente in video schreiben : <setting name="key" value="x">
				xwriter->writeElement(L"setting", true, L"name", i->getKey().c_str(), L"value", i->getValue().c_str());
				xwriter->writeLineBreak();
			}
			xwriter->writeLineBreak();
			//videoberreich schließen
			xwriter->writeClosingTag(L"video");
			xwriter->writeLineBreak();

			//..
			//Hier weitere Bereiche hinzufügen
			//..

			//teapot schließen
			xwriter->writeClosingTag(L"teapot");

			xwriter->drop();

			return true;

		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

void SettingManager::setVideoSetting(const core::stringw &name, const core::stringw &value)
{
	VideoMap[name] = value;
}

void SettingManager::setVideoSetting(const core::stringw &name, s32 value)
{
	VideoMap[name] = core::stringw(value);
}

const core::stringw SettingManager::getVideoSetting(const core::stringw &key)
{
	core::map<core::stringw, core::stringw>::Node* n = VideoMap.find(key);
    if (n)
        return n->getValue();
    else
        return L"";
}

const bool SettingManager::getVideoSettingAsBoolean(const core::stringw &key)
{
	 core::stringw s = getVideoSetting(key);
    if (s.empty())
        return false;
    return s.equals_ignore_case(L"1");
}

const s32 SettingManager::getVideoSettingAsInteger(const core::stringw &key)
{
	const core::stringc s = getVideoSetting(key);
    if (s.empty())
        return 0;

    return core::strtol10(s.c_str());
}
