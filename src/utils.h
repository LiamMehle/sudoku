#pragma once

#ifdef __GNUC__ // works on clang and gcc
	#define prefetch(x) __builtin_prefetch(x)
#else
	#define prefetch(x)
#endif

/*
 * @brief vrne offset za Board
 * vrne razmak naslova elementa podanega z koordinati v 'Board' podatkovnem tipu.
 * validnost parametrov ni preverjena
 * @param x koordinata v x osi
 * @param y koordinata v y osi
 * @return offset izračunan iz x in y osi (ter podatki podatkovnega tipa 'board')
 */

// returns offset into board
// // supress warnings
//static
//short at(int x, int y) {
//	return x + y*9;
//}

#define at(x,y) (x + y*9)

/**
 * @brief vrne offset za frame buffer
 * vrne razmak naslova elementa podanega z koordinati v 'FrameBuffer' podatkovnem tipu.
 * validnost parametrov ni preverjena
 * @param x koordinata v x osi
 * @param y koordinata v y osi
 * @return offset izračunan iz x in y osi (ter podatki podatkovnega tipa 'FrameBuffer')
 */


//static
//short fb_at(const short x, const short y) {
//	return (y+1)*21+(x+1)*2;
//}

#define fb_at(x,y) ((y+1)*21+(x+1)*2)

/**
 * @brief napiše lokacijo v izvorni kodi.
 * Macro, ki se razširi v printf funkcijo, ki napiše število vrstice v izvorni kodi.
 */

#define log_line    printf("%d\n", __LINE__); fflush(stdout)
