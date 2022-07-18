
@{{BLOCK(ball)

@=======================================================================
@
@	ball, 8x8@4, 
@	Transparent color : 00,FF,00
@	+ palette 16 entries, not compressed
@	+ 1 tiles not compressed
@	Total size: 32 + 32 = 64
@
@	Time-stamp: 2022-01-26, 23:38:01
@	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
@	( http://www.coranac.com/projects/#grit )
@
@=======================================================================

	.section .rodata
	.align	2
	.global ballTiles		@ 32 unsigned chars
ballTiles:
	.word 0x00333300,0x03111130,0x31122113,0x31222213,0x31222213,0x31122113,0x03111130,0x00333300

	.section .rodata
	.align	2
	.global ballPal		@ 32 unsigned chars
ballPal:
	.hword 0x0000,0x6C00,0x6DC0,0x2000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000

@}}BLOCK(ball)
