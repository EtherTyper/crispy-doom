// Emacs style mode select   -*- C++ -*- 
//-----------------------------------------------------------------------------
//
// $Id: info.c,v 1.44 1998/05/12 12:46:36 phares Exp $
//
//  BOOM, a modified and improved DOOM engine
//  Copyright (C) 1999 by
//  id Software, Chi Hoang, Lee Killough, Jim Flynn, Rand Phares, Ty Halderman
//
//  This program is free software; you can redistribute it and/or
//  modify it under the terms of the GNU General Public License
//  as published by the Free Software Foundation; either version 2
//  of the License, or (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 
//  02111-1307, USA.
//
// DESCRIPTION:
//  Thing frame/state LUT,
//  generated by multigen utilitiy.
//  This one is the original DOOM version, preserved.
//  BOOM changes include commenting and addition of predefined lumps
//  for providing things that aren't in the IWAD without sending a
//  separate must-use wad file around with the EXE.
//
//-----------------------------------------------------------------------------

#include "doomtype.h"

// [crispy] the next two will get filled up in r_data:R_InitColormaps(),
// and are thus not "const":
// this will become the identity matrix (cr_none[i] = i)
static byte cr_none[256];
// this will become the ~50% darker matrix (cr_dark[i] = colormaps[16*256+i])
static byte cr_dark[256];

// [crispy] from boom202s/INFO.C:9268-9470

static const byte cr_gray[]=
    {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,
     80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,
     96,97,98,99,100,101,102,103,104,105,106,107,110,110,110,110,
     80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,
     96,97,98,110,100,101,102,103,104,105,106,107,108,109,110,111,
     80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,
     96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,
     80,82,84,86,88,90,92,94,96,98,100,102,104,106,108,110,
     88,89,90,91,92,93,94,95,96,97,98,110,100,101,102,103,
     104,105,106,107,108,109,110,111,152,153,154,155,156,157,158,159,
     88,89,90,91,92,93,94,95,168,169,170,171,172,173,174,175,
     80,82,84,86,88,90,92,94,96,98,100,102,104,106,108,110,
     80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,
     80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,
     224,225,226,227,228,229,230,231,96,98,100,102,104,106,108,110,
     104,105,106,107,108,109,110,111,248,249,250,251,252,253,254,255};

static const byte cr_green[]=
    {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,
     112,112,113,113,114,114,115,115,116,116,117,117,118,118,119,119,
     120,120,121,121,122,122,123,123,124,124,125,125,127,127,127,127,
     112,112,113,113,114,114,115,115,116,116,117,117,118,118,119,119,
     120,120,121,127,122,122,123,123,124,124,125,125,126,126,127,127,
     112,112,113,113,114,114,115,115,116,116,117,117,118,118,119,119,
     120,120,121,121,122,122,123,123,124,124,125,125,127,109,127,127,
     112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127,
     112,112,113,113,114,114,115,115,116,116,117,117,118,118,119,119,
     120,120,121,121,122,122,123,123,152,153,154,155,156,157,158,159,
     112,113,114,115,116,117,118,119,168,169,170,171,172,173,174,175,
     112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127,
     112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127,
     112,112,113,113,114,114,115,115,116,116,117,117,118,118,119,119,
     224,225,226,227,228,229,230,231,120,121,122,123,124,125,126,127,
     124,124,125,125,126,126,127,127,248,249,250,251,252,253,254,255};

static const byte cr_gold[]=
    {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,
     160,160,160,160,161,161,161,161,162,162,162,162,163,163,163,163,
     164,164,164,164,165,165,165,165,166,166,166,166,167,167,167,167,
     160,160,160,160,161,161,161,161,162,162,162,162,163,163,163,163,
     164,164,164,167,165,165,165,165,166,166,166,166,167,167,167,167,
     160,160,160,160,161,161,161,161,162,162,162,162,163,163,163,163,
     164,164,164,164,165,165,165,165,166,166,166,166,167,109,167,167,
     160,160,161,161,162,162,163,163,164,164,165,165,166,166,167,167,
     160,160,160,160,161,161,161,161,162,162,162,162,163,163,163,163,
     164,164,164,164,165,165,165,165,160,161,162,163,164,165,166,167,
     160,161,162,163,164,165,166,167,168,169,170,171,172,173,174,175,
     160,160,161,161,162,162,163,163,164,164,165,165,166,166,167,167,
     160,160,161,161,162,162,163,163,164,164,165,165,166,166,167,167,
     160,160,160,160,161,161,161,161,162,162,162,162,163,163,163,163,
     224,225,226,227,228,229,230,231,164,164,165,165,166,166,167,167,
     166,166,166,166,167,167,167,167,248,249,250,251,252,253,254,255};

static const byte cr_red[]=
    {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,
     176,176,177,177,178,178,179,179,180,180,181,181,182,182,183,183,
     184,184,185,185,186,186,187,187,188,188,189,189,191,191,191,191,
     176,176,177,177,178,178,179,179,180,180,181,181,182,182,183,183,
     184,184,185,191,186,186,187,187,188,188,189,189,190,190,191,191,
     176,176,177,177,178,178,179,179,180,180,181,181,182,182,183,183,
     184,184,185,185,186,186,187,187,188,188,189,189,191,109,191,191,
     176,177,178,179,180,181,182,183,184,185,186,187,188,189,190,191,
     176,176,177,177,178,178,179,179,180,180,181,181,182,182,183,183,
     184,184,185,185,186,186,187,187,176,178,180,182,184,186,188,190,
     176,177,178,179,180,181,182,183,168,169,170,171,172,173,174,175,
     176,177,178,179,180,181,182,183,184,185,186,187,188,189,190,191,
     176,177,178,179,180,181,182,183,184,185,186,187,188,189,190,191,
     176,176,177,177,178,178,179,179,180,180,181,181,182,182,183,183,
     224,225,226,227,228,229,230,231,184,185,186,187,188,189,190,191,
     188,188,189,189,190,190,191,191,248,249,250,251,252,253,254,255};

static const byte cr_blue2[]=
    {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,
     192,192,193,193,194,194,195,195,196,196,197,197,198,198,199,199,
     200,200,201,201,202,202,203,203,204,204,205,205,207,207,207,207,
     192,192,193,193,194,194,195,195,196,196,197,197,198,198,199,199,
     200,200,201,207,202,202,203,203,204,204,205,205,207,207,207,207,
     192,192,193,193,194,194,195,195,196,196,197,197,198,198,199,199,
     200,200,201,201,202,202,203,203,204,204,205,205,206,109,207,207,
     200,200,201,201,202,202,203,203,204,204,205,205,206,206,207,207,
     192,192,193,193,194,194,195,195,196,196,197,197,198,198,199,199,
     200,200,201,201,202,202,203,203,200,200,201,201,202,202,203,203,
     200,200,201,201,202,202,203,203,168,169,170,171,172,173,174,175,
     200,200,201,201,202,202,203,203,204,204,205,205,206,206,207,207,
     192,193,194,195,196,197,198,199,200,201,202,203,204,205,206,207,
     192,192,193,193,194,194,195,195,196,196,197,197,198,198,199,199,
     224,225,226,227,228,229,230,231,200,201,202,203,204,205,206,207,
     240,241,242,243,244,245,246,247,248,249,250,251,252,253,254,255};

const byte *cr[] =
{
    (byte *) &cr_none,
    (byte *) &cr_dark,
    (byte *) &cr_gray,
    (byte *) &cr_green,
    (byte *) &cr_gold,
    (byte *) &cr_red,
    (byte *) &cr_blue2
};

char **crstr = 0;