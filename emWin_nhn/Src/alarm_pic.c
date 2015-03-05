/*********************************************************************
*                SEGGER Microcontroller GmbH & Co. KG                *
*        Solutions for real time microcontroller applications        *
*                           www.segger.com                           *
**********************************************************************
*                                                                    *
* C-file generated by                                                *
*                                                                    *
*        Bitmap converter for emWin V5.16.                           *
*        Compiled Jun  4 2012, 15:48:30                              *
*        (C) 1998 - 2010 Segger Microcontroller GmbH & Co. KG        *
*                                                                    *
**********************************************************************
*                                                                    *
* Source file: 11                                                    *
* Dimensions:  41 * 36                                               *
* NumColors:   15bpp: 32768                                          *
*                                                                    *
**********************************************************************
*/

#include <stdlib.h>

#include "GUI.h"

#ifndef GUI_CONST_STORAGE
  #define GUI_CONST_STORAGE const
#endif


static GUI_CONST_STORAGE unsigned short acalarm_pic[] = {
  0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x6FBD, 0x1F5C, 0x537C, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 
        0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF,
  0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x77DE, 0x177D, 0x03BF, 0x079E, 0x5FBD, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 
        0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF,
  0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x337D, 0x039F, 0x039F, 0x039F, 0x0F7D, 0x77DE, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 
        0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF,
  0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x67BD, 0x037E, 0x039F, 0x039F, 0x039F, 0x039F, 0x377C, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 
        0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF,
  0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x237D, 0x039F, 0x039E, 0x079E, 0x039E, 0x039F, 0x037E, 0x67BD, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 
        0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF,
  0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x5B9D, 0x037E, 0x039E, 0x0F9E, 0x23BF, 0x179E, 0x039E, 0x039F, 0x237D, 0x7FFE, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 
        0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF,
  0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FDE, 0x175D, 0x037E, 0x077E, 0x1F9E, 0x1F9E, 0x239E, 0x0F9E, 0x037E, 0x037E, 0x539D, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 
        0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF,
  0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x4B7C, 0x037E, 0x037E, 0x139E, 0x239E, 0x1F9E, 0x1F9E, 0x1F9E, 0x037E, 0x037E, 0x135D, 0x7BDE, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 
        0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF,
  0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x77DE, 0x0F5D, 0x037E, 0x077E, 0x1F9E, 0x1F9E, 0x1F9E, 0x1F9E, 0x1F9E, 0x137E, 0x037E, 0x037E, 0x3F7C, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 
        0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF,
  0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x3B7C, 0x035E, 0x037E, 0x177E, 0x1F9E, 0x1B9E, 0x1B9F, 0x1B9F, 0x1F9E, 0x1F9E, 0x077E, 0x037E, 0x075D, 0x6FBD, 0x7FFF, 0x7FFF, 0x7FFF, 
        0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF,
  0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x6BBD, 0x075D, 0x035E, 0x0B7E, 0x1F7E, 0x1B9E, 0x1B7D, 0x231A, 0x1F1A, 0x1B9E, 0x1F9E, 0x177E, 0x035E, 0x035E, 0x2B5C, 0x7FFF, 0x7FFF, 0x7FFF, 
        0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF,
  0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x2B5C, 0x035E, 0x035D, 0x177E, 0x1B7E, 0x177E, 0x2A74, 0x45EF, 0x41EF, 0x22D7, 0x1B9F, 0x1F7E, 0x0B5E, 0x035E, 0x033D, 0x5F9D, 0x7FFF, 0x7FFF, 
        0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF,
  0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x5F9D, 0x033D, 0x035D, 0x0B5D, 0x1B7E, 0x1B9E, 0x173B, 0x39EF, 0x4610, 0x45EF, 0x2E31, 0x177E, 0x1B7E, 0x177E, 0x035D, 0x035D, 0x1B3C, 0x7FDE, 0x7FFF, 
        0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF,
  0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FDE, 0x1F3C, 0x035D, 0x035D, 0x177E, 0x1B7E, 0x1B7E, 0x173B, 0x35EF, 0x41EF, 0x41EF, 0x2A32, 0x177E, 0x1B7E, 0x1B7E, 0x0B5D, 0x033D, 0x033D, 0x4B7C, 0x7FFF, 
        0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF,
  0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x4F7C, 0x033D, 0x033D, 0x0B5D, 0x1B7D, 0x175D, 0x177E, 0x173C, 0x31EF, 0x3DEE, 0x3DCE, 0x2633, 0x177E, 0x175D, 0x1B5D, 0x175D, 0x033D, 0x033D, 0x0B3C, 0x73BD, 
        0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF,
  0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x77DE, 0x133C, 0x033D, 0x033D, 0x175D, 0x175D, 0x175D, 0x175E, 0x135D, 0x29F0, 0x3DCD, 0x3DAD, 0x1E54, 0x137E, 0x175D, 0x175D, 0x1B5D, 0x0F5D, 0x033D, 0x033D, 0x375C, 
        0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF,
  0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x3F5C, 0x031D, 0x033D, 0x0F3D, 0x175D, 0x175D, 0x175D, 0x175D, 0x135E, 0x2611, 0x39AC, 0x358C, 0x1A75, 0x137E, 0x175D, 0x175D, 0x175D, 0x175D, 0x033D, 0x033D, 0x031C, 
        0x679D, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF,
  0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x6FBD, 0x071C, 0x031D, 0x033D, 0x175D, 0x175D, 0x175D, 0x175D, 0x175D, 0x135E, 0x1E12, 0x358B, 0x316B, 0x16B7, 0x137E, 0x175D, 0x175D, 0x175D, 0x175D, 0x0F3D, 0x031C, 0x031D, 
        0x233B, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF,
  0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x2F3B, 0x031C, 0x031C, 0x0F3D, 0x173D, 0x133D, 0x133D, 0x133D, 0x133D, 0x135E, 0x1A33, 0x314A, 0x2D6B, 0x12D8, 0x135E, 0x133D, 0x133D, 0x133D, 0x133D, 0x173D, 0x071C, 0x031C, 
        0x031C, 0x577C, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF,
  0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x639C, 0x02FC, 0x031C, 0x071C, 0x133D, 0x133D, 0x133D, 0x133D, 0x133D, 0x133D, 0x135E, 0x1675, 0x2D29, 0x256B, 0x12FA, 0x135D, 0x133D, 0x133D, 0x133D, 0x133D, 0x133D, 0x0F3D, 0x031C, 
        0x031C, 0x131B, 0x7BDE, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF,
  0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFE, 0x1F1B, 0x02FC, 0x031C, 0x0F1C, 0x133D, 0x133D, 0x133D, 0x133D, 0x133D, 0x133D, 0x135E, 0x1297, 0x2908, 0x216B, 0x0EFB, 0x133D, 0x133D, 0x133D, 0x133D, 0x133D, 0x133D, 0x133D, 0x071C, 
        0x031C, 0x02FC, 0x435C, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF,
  0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x537C, 0x02FC, 0x02FC, 0x071C, 0x131C, 0x131C, 0x131C, 0x131C, 0x131C, 0x131C, 0x131C, 0x0F3D, 0x12B8, 0x2508, 0x1D6C, 0x0F1C, 0x133D, 0x131C, 0x131C, 0x131C, 0x131C, 0x131C, 0x131C, 0x0F1C, 
        0x02FC, 0x02FC, 0x0AFB, 0x6FBD, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF,
  0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x77DE, 0x12FB, 0x02FC, 0x02FC, 0x0F1C, 0x0F1C, 0x0F1C, 0x0F1C, 0x0F1C, 0x0F1C, 0x0F1C, 0x0F1C, 0x0F3D, 0x0ED9, 0x2107, 0x198D, 0x0F3D, 0x0F1C, 0x0F1C, 0x0F1C, 0x0F1C, 0x0F1C, 0x0F1C, 0x0F1C, 0x131C, 
        0x0B1C, 0x02FC, 0x02FC, 0x2F1B, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF,
  0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x3F3B, 0x02DB, 0x02FC, 0x06FC, 0x0F1C, 0x0F1C, 0x0F1C, 0x0F1C, 0x0F1C, 0x0F1C, 0x0F1C, 0x0F1C, 0x0F1D, 0x0EDA, 0x1CE7, 0x158E, 0x0F3D, 0x0F1C, 0x0F1C, 0x0F1C, 0x0F1C, 0x0F1C, 0x0F1C, 0x0F1C, 0x0F1C, 
        0x0F1C, 0x02FC, 0x02FC, 0x02DB, 0x5F7C, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF,
  0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x6FBD, 0x06DB, 0x02DB, 0x02FB, 0x0EFC, 0x0EFC, 0x0EFC, 0x0EFC, 0x0EFC, 0x0EFC, 0x0EFC, 0x0EFC, 0x0EFC, 0x0F1C, 0x0AFB, 0x1508, 0x11D0, 0x0F3D, 0x0EFC, 0x0EFC, 0x0EFC, 0x0EFC, 0x0EFC, 0x0EFC, 0x0EFC, 0x0EFC, 
        0x0F1C, 0x0AFC, 0x02DB, 0x02DC, 0x1AFB, 0x7FDE, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF,
  0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x2F1B, 0x02DB, 0x02DB, 0x06FB, 0x0EFC, 0x0EFC, 0x0EFC, 0x0EFC, 0x0EFC, 0x0EFC, 0x0EFC, 0x0EFC, 0x0EFC, 0x0EFC, 0x0EFC, 0x0AB9, 0x0ADA, 0x0EFC, 0x0EFC, 0x0EFC, 0x0EFC, 0x0EFC, 0x0EFC, 0x0EFC, 0x0EFC, 0x0EFC, 
        0x0EFC, 0x0EFC, 0x02FB, 0x02DB, 0x02DB, 0x4B5B, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF,
  0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x5F7C, 0x02DB, 0x02DB, 0x02DB, 0x0AFB, 0x0AFB, 0x0AFB, 0x0AFB, 0x0AFB, 0x0AFB, 0x0AFB, 0x0AFB, 0x0AFB, 0x0AFB, 0x0AFB, 0x0B1C, 0x0B3E, 0x0B3E, 0x0AFC, 0x0AFB, 0x0AFB, 0x0AFB, 0x0AFB, 0x0AFB, 0x0AFB, 0x0AFB, 0x0AFB, 
        0x0AFB, 0x0EFB, 0x0AFB, 0x02DB, 0x02DB, 0x0EDA, 0x73BD, 0x7FFF, 0x7FFF, 0x7FFF,
  0x7FFF, 0x7FFF, 0x7FFF, 0x7BDE, 0x1AFA, 0x02DB, 0x02DB, 0x06DB, 0x0AFB, 0x0AFB, 0x0AFB, 0x0AFB, 0x0AFB, 0x0AFB, 0x0AFB, 0x0AFB, 0x0AFB, 0x0AFB, 0x0AFC, 0x0A98, 0x118E, 0x0DD1, 0x0ADA, 0x0AFC, 0x0AFB, 0x0AFB, 0x0AFB, 0x0AFB, 0x0AFB, 0x0AFB, 0x0AFB, 
        0x0AFB, 0x0AFB, 0x0AFB, 0x06DB, 0x02DB, 0x02BB, 0x371B, 0x7FFF, 0x7FFF, 0x7FFF,
  0x7FFF, 0x7FFF, 0x7FFF, 0x473B, 0x02BB, 0x02BB, 0x02DB, 0x0ADB, 0x0ADB, 0x0ADB, 0x0ADB, 0x0ADB, 0x0ADB, 0x0ADB, 0x0ADB, 0x0ADB, 0x0ADB, 0x0AFC, 0x0ABA, 0x0CC7, 0x0800, 0x0C00, 0x0D6D, 0x0AFC, 0x0ADB, 0x0ADB, 0x0ADB, 0x0ADB, 0x0ADB, 0x0ADB, 0x0ADB, 
        0x0ADB, 0x0ADB, 0x0ADB, 0x0ADB, 0x02DB, 0x02BB, 0x06BA, 0x639C, 0x7FFF, 0x7FFF,
  0x7FFF, 0x7FFF, 0x6FBD, 0x0ABA, 0x02BB, 0x02BB, 0x06DB, 0x0ADB, 0x0ADB, 0x0ADB, 0x0ADB, 0x0ADB, 0x0ADB, 0x0ADB, 0x0ADB, 0x0ADB, 0x0ADB, 0x0AFC, 0x0A56, 0x0821, 0x0000, 0x0000, 0x0CC7, 0x0ADB, 0x0ADB, 0x0ADB, 0x0ADB, 0x0ADB, 0x0ADB, 0x0ADB, 0x0ADB, 
        0x0ADB, 0x0ADB, 0x0ADB, 0x0ADB, 0x06DB, 0x02BB, 0x02BB, 0x22FA, 0x7FFE, 0x7FFF,
  0x7FFF, 0x7FFF, 0x331A, 0x02BB, 0x02BB, 0x02BB, 0x0ADB, 0x06DB, 0x0ADB, 0x0ADB, 0x0ADB, 0x0ADB, 0x0ADB, 0x0ADB, 0x0ADB, 0x0ADB, 0x0ADB, 0x0ADB, 0x06BA, 0x08E9, 0x0800, 0x0800, 0x098F, 0x06FC, 0x0ADB, 0x0ADB, 0x0ADB, 0x0ADB, 0x0ADB, 0x0ADB, 0x0ADB, 
        0x0ADB, 0x0ADB, 0x0ADB, 0x0ADB, 0x06DB, 0x02BB, 0x02BB, 0x02BA, 0x4F5B, 0x7FFF,
  0x7FFF, 0x5F7C, 0x02BA, 0x02BA, 0x02BA, 0x06BB, 0x06DB, 0x06BB, 0x06BB, 0x06BB, 0x06BB, 0x06BB, 0x06BB, 0x06BB, 0x06BB, 0x06BB, 0x06BB, 0x06BB, 0x06DB, 0x0699, 0x09F2, 0x0A14, 0x06DB, 0x06DB, 0x06BB, 0x06BB, 0x06BB, 0x06BB, 0x06BB, 0x06BB, 0x06BB, 
        0x06BB, 0x06BB, 0x06BB, 0x06DB, 0x0ADB, 0x02BB, 0x02BA, 0x02BA, 0x12BA, 0x77BE,
  0x7FFE, 0x26FA, 0x029A, 0x02BA, 0x02BA, 0x02BA, 0x06BB, 0x06BB, 0x06BB, 0x06BB, 0x06BB, 0x06BB, 0x06BB, 0x06BB, 0x06BB, 0x06BB, 0x06BB, 0x06BB, 0x06BA, 0x06DB, 0x06FC, 0x06DC, 0x06BB, 0x06BA, 0x06BB, 0x06BB, 0x06BB, 0x06BB, 0x06BB, 0x06BB, 0x06BB, 
        0x06BB, 0x06BB, 0x06BB, 0x06BB, 0x06BA, 0x02BA, 0x02BA, 0x02BA, 0x029A, 0x473B,
  0x635B, 0x06BA, 0x029A, 0x029A, 0x029A, 0x029A, 0x029A, 0x029A, 0x029A, 0x029A, 0x029A, 0x029A, 0x029A, 0x029A, 0x029A, 0x029A, 0x029A, 0x029A, 0x029A, 0x029A, 0x029A, 0x029A, 0x029A, 0x029A, 0x029A, 0x029A, 0x029A, 0x029A, 0x029A, 0x029A, 0x029A, 
        0x029A, 0x029A, 0x029A, 0x029A, 0x029A, 0x029A, 0x029A, 0x029A, 0x029A, 0x22FA,
  0x573B, 0x029A, 0x029A, 0x029A, 0x029A, 0x029A, 0x029A, 0x029A, 0x029A, 0x029A, 0x029A, 0x029A, 0x029A, 0x029A, 0x029A, 0x029A, 0x029A, 0x029A, 0x029A, 0x029A, 0x029A, 0x029A, 0x029A, 0x029A, 0x029A, 0x029A, 0x029A, 0x029A, 0x029A, 0x029A, 0x029A, 
        0x029A, 0x029A, 0x029A, 0x029A, 0x029A, 0x029A, 0x029A, 0x029A, 0x027A, 0x26FA,
  0x7FFE, 0x4F5B, 0x2AFA, 0x22DA, 0x1EDA, 0x1EDA, 0x1EDA, 0x1EDA, 0x1EDA, 0x1EDA, 0x1EDA, 0x1EDA, 0x1EDA, 0x1EDA, 0x1EDA, 0x1EDA, 0x1EDA, 0x1EDA, 0x1EDA, 0x1EDA, 0x1EDA, 0x1EDA, 0x1EDA, 0x1EDA, 0x1EDA, 0x1EDA, 0x1EDA, 0x1EDA, 0x1EDA, 0x1EDA, 0x1EDA, 
        0x1EDA, 0x1EDA, 0x1EDA, 0x1EDA, 0x1EDA, 0x1EDA, 0x22DA, 0x26DA, 0x371B, 0x6FBD
};

GUI_CONST_STORAGE GUI_BITMAP bmalarm_pic = {
  41, /* XSize */
  36, /* YSize */
  82, /* BytesPerLine */
  16, /* BitsPerPixel */
  (unsigned char *)acalarm_pic,  /* Pointer to picture data */
  NULL,  /* Pointer to palette */
  GUI_DRAW_BMP555
};

/* *** End of file *** */