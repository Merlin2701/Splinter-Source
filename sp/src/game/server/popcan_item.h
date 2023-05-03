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


#ifndef POPCAN_ITEM_H
#define POPCAN_ITEM_H

#include "cbase.h"
#include "items.h"

class CPopCanItem : public CItem
{
public:
    DECLARE_CLASS(CPopCanItem, CItem);
    DECLARE_DATADESC(); // Add this line

    CPopCanItem();

    void Spawn() override;
    void Precache() override;
    bool MyTouch(CBasePlayer* pPlayer) override;


private:
    void ThrowEmptyCan();
    float time;
    bool m_bThrown;
};

#endif // POPCAN_ITEM_H
