#pragma once

namespace Patches
{
	void ApplyRequired();
	void ApplyOnFirstTick();
	void ApplyAfterTagsLoaded();
	void PreferencesUpdated();

	void Tick();
}