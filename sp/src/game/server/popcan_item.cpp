//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
//=============================================================================//

//===============
//===============
// Made by Merlin
//===============
//===============

#include "cbase.h"
#include "popcan_item.h"
#include "player.h"
#include "datamap.h" // Add this line
// Add this line
PRECACHE_REGISTER(item_popcan);

BEGIN_DATADESC(CPopCanItem)
DEFINE_THINKFUNC(ThrowEmptyCan), // Add this line
END_DATADESC()

CPopCanItem::CPopCanItem() : time(0), m_bThrown(false)
{
}





void CPopCanItem::Spawn()
{
    Precache();
    SetModel("models/props_junk/popcan01a.mdl");
    BaseClass::Spawn();
}


void CPopCanItem::Precache()
{
    PrecacheModel("models/props_junk/popcan01a.mdl");
   // PrecacheModel("models/items/empty_popcan.mdl");
    PrecacheScriptSound("HL2Player.Use");
  //  PrecacheScriptSound("PopCan.Throw");
}

bool CPopCanItem::MyTouch(CBasePlayer* pPlayer)
{
    // Add a debug message at the beginning of the function
    Msg("MyTouch(CBasePlayer* pPlayer) called!\n");
    if (!pPlayer)
        return false;

    // Play the pickup sound
    if (gpGlobals->curtime >= time)
    {
        time = gpGlobals->curtime + 2;
        EmitSound("HL2Player.Use");
    }

    // Schedule the can to be thrown away after 2 seconds
    SetThink(&CPopCanItem::ThrowEmptyCan);
    SetNextThink(gpGlobals->curtime + 2.0f);

    // Make the item non-solid to prevent further interactions
    AddSolidFlags(FSOLID_NOT_SOLID);

    // HACK: there is almost certainly a better way of doing this but 
    //it does get removed after the 2 secounds so it works for now
    AddEffects(EF_NODRAW);
    SetTouch(NULL);


    m_bThrown = true;
    return false; // Return false to prevent the item from being removed immediately
}


void CPopCanItem::ThrowEmptyCan()
{
    // Add a debug message at the beginning of the function
    Msg("ThrowEmptyCan() called!\n");
    CBasePlayer* pPlayer = UTIL_GetLocalPlayer();
    if (!pPlayer)
        return;

    // Calculate the spawn position and angles for the empty can
    Vector vecSpawn = pPlayer->EyePosition() + pPlayer->EyeDirection3D() * 2;
    QAngle angSpawn;
    VectorAngles(pPlayer->EyeDirection3D(), angSpawn);

    // Create an empty can physics prop
    CBaseEntity* pEmptyCan = CreateEntityByName("prop_physics");
    if (!pEmptyCan)
        return;

    pEmptyCan->SetModel("models/props_junk/popcan01a.mdl");
    pEmptyCan->SetAbsOrigin(vecSpawn);
    pEmptyCan->SetAbsAngles(angSpawn);
    pEmptyCan->Spawn();

    // Apply a force to simulate the player throwing away the can
    IPhysicsObject* pPhysicsObject = pEmptyCan->VPhysicsGetObject();
    if (pPhysicsObject)
    {
        Vector vecForce = pPlayer->EyeDirection3D() * 200; // Apply force in the player's view direction
        vecForce.z += 110; // Add some vertical force
        pPhysicsObject->ApplyForceCenter(vecForce);
    }

    // Play the throw sound
    EmitSound("HL2Player.Use");
   
    if (m_bThrown == true)
    {
        // Remove the original can item
        UTIL_Remove(this);
    }

    //this->MyTouch((CBasePlayer*)UTIL_GetLocalPlayer());
}

LINK_ENTITY_TO_CLASS(item_popcan, CPopCanItem);