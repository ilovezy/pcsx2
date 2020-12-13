/*  PCSX2 - PS2 Emulator for PCs
 *  Copyright (C) 2002-2020  PCSX2 Dev Team
 *
 *  PCSX2 is free software: you can redistribute it and/or modify it under the terms
 *  of the GNU Lesser General Public License as published by the Free Software Found-
 *  ation, either version 3 of the License, or (at your option) any later version.
 *
 *  PCSX2 is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 *  without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 *  PURPOSE.  See the GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along with PCSX2.
 *  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "PAD.h"

#ifdef SDL_BUILD
#include <SDL.h>
#endif

class Device
{
public:
	Device()
		: m_deadzone(1500)
		, m_no_error(false)
	{
	}

	virtual ~Device()
	{
	}

	Device(const Device&);            // copy constructor
	Device& operator=(const Device&); // assignment

	/*
     * Update state of every attached devices
     */
	virtual void UpdateDeviceState() = 0;

	/*
     * Causes devices to rumble
     * Rumble will differ according to type which is either 0(small motor) or 1(big motor)
     */
	virtual void Rumble(unsigned type, unsigned pad) {}
	/*
     * Safely dispatch to the Rumble method above
     */
	static void DoRumble(unsigned type, unsigned pad);

	/*
     * Used for GUI checkbox to give feedback to the user
     */
	virtual bool TestForce(float strength = 0.6) { return false; }

	virtual const char* GetName() = 0;

	virtual int GetInput(gamePadValues input) = 0;

	int GetDeadzone()
	{
		return m_deadzone;
	}

	virtual size_t GetUniqueIdentifier() = 0;

	static size_t index_to_uid(int index);
	static int uid_to_index(int pad);

	bool IsProperlyInitialized()
	{
		return m_no_error;
	}

protected:
	int m_deadzone;
	bool m_no_error;
};

extern std::vector<std::unique_ptr<Device>> s_vgamePad;

/*
 * Find every interesting device and create right structure for them(depends on backend)
 */
extern void EnumerateDevices();
