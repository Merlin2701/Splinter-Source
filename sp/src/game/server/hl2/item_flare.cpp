//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
// $NoKeywords: $
//
//=============================================================================//
/*

===== item_flare.cpp ========================================================

  handling for the flare object
*/
 
#include "cbase.h"
#include "player.h"
#include "basecombatweapon.h"
#include "gamerules.h"
#include "items.h"

class CItemFlare : public CItem
{
public:
	DECLARE_CLASS(CItemFlare, CItem);

	static int nCount;


	void Spawn(void)
	{
		Precache();
		SetModel("models/props_junk/flare.mdl");
		BaseClass::Spawn();
	}
	void Precache(void)
	{
		PrecacheModel("models/props_junk/flare.mdl");
	}
    bool MyTouch(CBasePlayer* pPlayer)
    {

        // Play a sound effect
        EmitSound("Weapon_FlareGun.Burn");

        DevMsg("MyTouch() called!\n");
        // Increment the count of flares touched by players
        static int nCount = 0;
        nCount++;



        // Wait for 2 seconds before throwing the item forward
        SetThink(&CItemFlare::ThrowForward);
        SetNextThink(gpGlobals->curtime + 2.0f);

        return true;
    }

    void ThrowForward()
    {
        // Play a sound effect
        EmitSound("Weapon_FlareGun.Burn");

        Vector vForward;
        AngleVectors(GetLocalAngles(), &vForward);
        Vector velocity = vForward * 800.0f;

        CBasePlayer* pPlayer = UTIL_GetLocalPlayer();

        Vector startPos = pPlayer->WorldSpaceCenter();

        CItemFlare* pItem = (CItemFlare*)CBaseEntity::Create("item_flare", startPos, pPlayer->EyeAngles(), pPlayer);
        pItem->SetAbsVelocity(velocity);
    }


	static int GetCount() { return nCount; }


};

LINK_ENTITY_TO_CLASS(item_flare, CItemFlare);