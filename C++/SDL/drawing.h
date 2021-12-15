#ifndef _DRAWING_H_
#define _DRAWING_H_

#define BLACK   0
#define WHITE   0xFFFFFF
#define RED     0xFF0000
#define GREEN   0x00FF00
#define BLUE    0x0000FF
#define YELLOW  0xFFFF00
#define CYAN    0x00FFFF
#define MAGENTA 0xFF00fF
#define GRAY    0x808080
#define SILVER  0xC0C0C0
#define DARK_RED    0x800000
#define DARK_GREEN  0x008000
#define DARK_BLUE   0x000080
#define TEAL    0x008080
#define GOLD    0x808000
#define PURPLE  0x008080

extern SDL_Surface *screen;

typedef struct {
    unsigned int index;
    unsigned int speed;
    unsigned int counter;
    SDL_Rect *tiles;
    unsigned int totalTiles;
} Animation;

void DrawTile(SDL_Surface *image, SDL_Rect *tile, unsigned int x, unsigned int y) {
    SDL_Rect destination = {x * 2, y * 2, tile->w * 2, tile->h * 2};
    SDL_BlitScaled(image, tile, screen, &destination);
}

Animation CreateAnimation(SDL_Rect *tiles, unsigned int totalTiles, unsigned int speed) {
    Animation a;
    a.index = 0;
    a.counter = 0;
    a.speed = speed;
    a.tiles = tiles;
    a.totalTiles = totalTiles;
    return a;
}

void DrawAnimation(SDL_Surface *image, Animation *a, int x, int y) {
    a->counter++;
    for (unsigned char i = 0; i<a->totalTiles; i++) {
        if (a->counter == a->speed * i) {
            if (i > 0) a->index++;
            a->counter = 0;
            if (a->index == a->totalTiles) a->index = 0;
            break;
        }
    }

    SDL_Rect tile = a->tiles[a->index];
    DrawTile(image, &tile, x, y);
}

void SetPixel(unsigned int x, unsigned int y, unsigned int color) {
    SDL_Rect test = {x * 2, y * 2, 2, 2};
    SDL_FillRect(screen, &test, color);
}

#endif // _DRAWING_H_
