#pragma once
#include <citro2d.h>
#define RGBA(r,g,b,a) (uint32_t)(r | (g << (uint32_t)8) | (b << (uint32_t)16) | (a << (uint32_t)24))
#define HexColor(hex) RGBA(((hex>>16) & 0xFF),((hex>>8)&0xFF),((hex&0xFF)),0xFF)


#define THEME_BG                HexColor(0xC87941)
#define THEME_TEXT              HexColor(0x290001)
#define THEME_BORDER1           HexColor(0x290001)
#define THEME_BORDER2           HexColor(0x290001)

#define THEME_BUTTON_BG         HexColor(0x393031)
#define THEME_BUTTON_TEXT       HexColor(0xA0A0A0)
#define THEME_BUTTON_BORDER1    HexColor(0x492021)
#define THEME_BUTTON_BORDER2    HexColor(0x290001)       

#define THEME_PANEL_BG         THEME_BG
#define THEME_PANEL_TEXT       THEME_TEXT
#define THEME_PANEL_BORDER1    THEME_BORDER2
#define THEME_PANEL_BORDER2    HexColor(0x492021)

#define THEME_LIST_ENTRY_BG         THEME_BG
#define THEME_LIST_ENTRY_HIGHLIGHT  THEME_TEXT
#define THEME_LIST_ENTRY_TEXT       THEME_TEXT
#define THEME_LIST_ENTRY_HIGHLIGHT_TEXT  THEME_BG
#define THEME_LIST_ENTRY_BORDER     THEME_BORDER2


#define THEME_CHECKBOX_FILL     HexColor(0x492021)
#define THEME_CHECKBOX_BORDER   THEME_BORDER1

#define TEXT_SCALE              0.67f
#define BUTTON_PADDING          10
#define BUTTON_PADDING_TOP      5
#define BUTTON_PADDING_LEFT     10
#define BUTTON_PADDING_BOTTOM   5
#define BUTTON_PADDING_RIGHT    10
#define BUTTON_BORDER           3
#define BUTTON_MARGIN           5
#define PANEL_MARGIN            8
#define PANEL_BORDER            2
#define FAT_PANEL_BORDER        8
#define PANEL_PADDING_DEFAULT   4
#define PANEL_PADDING_TOP       8
#define PANEL_PADDING_LEFT      PANEL_PADDING_DEFAULT
#define PANEL_PADDING_RIGHT     PANEL_PADDING_DEFAULT
#define PANEL_PADDING_BOTTOM    PANEL_PADDING_DEFAULT
#define LIST_ENTRY_BORDER       1
#define LIST_ENTRY_PADDING_LEFT 10
#define CHECKBOX_BORDER         2
#define CHECKBOX_PADDING        2
#define CHECKBOX_TEXT           THEME_TEXT