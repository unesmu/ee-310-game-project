
//{{BLOCK(background)

//======================================================================
//
//	background, 256x192@8, 
//	+ palette 240 entries, not compressed
//	+ 49 tiles (t|f reduced) not compressed
//	+ regular map (flat), not compressed, 32x24 
//	Total size: 480 + 3136 + 1536 = 5152
//
//	Time-stamp: 2022-01-26, 23:38:01
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_BACKGROUND_H
#define GRIT_BACKGROUND_H

#define backgroundTilesLen 3136
extern const unsigned int backgroundTiles[784];

#define backgroundMapLen 1536
extern const unsigned short backgroundMap[768];

#define backgroundPalLen 480
extern const unsigned short backgroundPal[240];

#endif // GRIT_BACKGROUND_H

//}}BLOCK(background)
