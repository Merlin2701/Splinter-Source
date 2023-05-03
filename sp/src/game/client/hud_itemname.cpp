#include "cbase.h"
#include "hud.h"
#include "hud_macros.h"
#include "iclientmode.h"
#include "vgui/ILocalize.h"
#include "vgui/ISurface.h"
#include "vgui/IScheme.h"
#include "vgui_controls/Controls.h"
#include "hud_itemname.h"
#include "view.h"
#include "c_baseplayer.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

DECLARE_HUDELEMENT(CHudItemName);

CHudItemName::CHudItemName(const char* pElementName)
    : CHudElement(pElementName), BaseClass(NULL, "HudItemName")
{
    Panel* pParent = g_pClientMode->GetViewport();
    SetParent(pParent);

    // Initialize the font
    m_hFont = vgui::surface()->CreateFont();
    vgui::surface()->SetFontGlyphSet(m_hFont, "Arial", 14, 700, 0, 0, vgui::ISurface::FONTFLAG_ANTIALIAS);
}

void CHudItemName::Init()
{
    Reset();
}

void CHudItemName::Reset()
{
    SetItemName(NULL);
    SetPos(m_iXPos, m_iYPos);
}




void CHudItemName::OnThink()
{
    C_BasePlayer* pPlayer = C_BasePlayer::GetLocalPlayer();

    if (!pPlayer)
        return;

    Vector vecStart, vecEnd, vecForward;
    pPlayer->EyeVectors(&vecForward);
    vecStart = pPlayer->EyePosition();
    vecEnd = vecStart + vecForward * MAX_TRACE_LENGTH;

    trace_t tr;
    UTIL_TraceLine(vecStart, vecEnd, MASK_SOLID, pPlayer, COLLISION_GROUP_NONE, &tr);

    if (tr.DidHitNonWorldEntity() && tr.m_pEnt && tr.m_pEnt->GetClientClass())
    {
        const char* pszItemName = tr.m_pEnt->GetEntityName();

        wchar_t wszItemName[128];

        if (pszItemName)
        {
            g_pVGuiLocalize->ConvertANSIToUnicode(pszItemName, wszItemName, sizeof(wszItemName));
            SetItemName(wszItemName);
        }
        else
        {
            SetItemName(NULL);
        }
    }
    else
    {
        SetItemName(NULL);
    }
}

void CHudItemName::Paint()
{
    if (m_itemName[0] == 0)
        return;

    // Get the screen size
    int screenWidth, screenHeight;
    vgui::surface()->GetScreenSize(screenWidth, screenHeight);

    // Calculate the center of the screen
    int centerX = screenWidth / 2;
    int centerY = screenHeight / 2;

    // Calculate the position of the text (just below the crosshair)
    int xpos = centerX - 75; // Adjust the x offset value if needed
    int ypos = centerY + 25; // Adjust the y offset value if needed

    vgui::surface()->DrawSetTextFont(m_hFont);
    vgui::surface()->DrawSetTextColor(255, 255, 255, 255);
    vgui::surface()->DrawSetTextPos(xpos, ypos);
    vgui::surface()->DrawPrintText(m_itemName, wcslen(m_itemName));
}




