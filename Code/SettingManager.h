#pragma once
#include <irrlicht.h>

using namespace irr;

class SettingManager
{
private:
	core::stringw SettingsFile;
	IrrlichtDevice* NullDevice;

public:
	core::map<core::stringw, s32> DriverOptions;					//Verfügbare Treiberoptionen
	core::map<core::stringw, core::dimension2du> ResolutionOptions;	//Verfügbare Auflösungen
	core::map<core::stringw, s32> SoundOptionen;					//Toneinstellungen
	core::map<core::stringw, s32> CrosshairOptions;					//Verfügbare Fadenkreuze
	core::map<core::stringw, s32> KeyOptions;						//Tastenbelegung
	core::map<core::stringw, s32> gameOptions;						//Spieleoptionen
	core::map<core::stringw, core::stringw> VideoMap;				//aktive Einstellungen
		
	SettingManager(const core::stringw &settingsFile);

	~SettingManager(void);

	bool load(); //Einstellungen laden

	bool save(); //Einstellungen speichern	

	void setVideoSetting(const core::stringw &name, const core::stringw &value);
	void setVideoSetting(const core::stringw &name, s32 value);

	const core::stringw getVideoSetting(const core::stringw &key);
	const bool getVideoSettingAsBoolean(const core::stringw &key);
	const s32 getVideoSettingAsInteger(const core::stringw &key);
};

