#define FONT_MAIN "Arial"

// these are colors used
#define COLOR_50	0xE0F2F1
#define COLOR_100	0xB2DFDB
#define COLOR_200	0x80CBC4
#define COLOR_300	0x4DB6AC
#define COLOR_400	0x26A69A
#define COLOR_500	0x009688
#define	COLOR_600	0x00897B
#define	COLOR_700	0x00796B
#define COLOR_800	0x00695C
#define COLOR_900	0x004D40
#define COLOR_A100	0xA7FFEB
#define COLOR_A200	0x64FFDA
#define COLOR_A400	0x1DE9B6
#define COLOR_A700	0x00BFA5


#define C4B(color) Color4B((color & 0xFF0000) >> 16, (color & 0x00FF00) >> 8, color & 0x0000FF, 255)
#define C4F(color) Color4F(((color & 0xFF0000) >> 16)/255.0f, ((color & 0x00FF00) >> 8)/255.0f, (color & 0x0000FF)/255.0f, 1.0f)
#define C3B(color) Color3B((color & 0xFF0000) >> 16, (color & 0x00FF00) >> 8, color & 0x0000FF)