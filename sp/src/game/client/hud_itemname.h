#ifndef HUD_ITEMNAME_H
#define HUD_ITEMNAME_H

#include "hudelement.h"
#include "vgui_controls/Panel.h"

class CHudItemName : public CHudElement, public vgui::Panel
{
    DECLARE_CLASS_SIMPLE(CHudItemName, vgui::Panel);

public:
    CHudItemName(const char* pElementName);
    CPanelAnimationVarAliasType(int, m_iXPos, "xpos", "200", "proportional_int");
    CPanelAnimationVarAliasType(int, m_iYPos, "ypos", "200", "proportional_int");



    void Init() override;
    void Reset() override;
    void OnThink() override;
    void Paint() override;

    void SetItemName(const wchar_t* wszItemName)
    {
        wcsncpy(m_itemName, wszItemName ? wszItemName : L"", sizeof(m_itemName) / sizeof(wchar_t));
    }

private:
    wchar_t m_itemName[128];
    vgui::HFont m_hFont;
};

#endif // HUD_ITEMNAME_H
