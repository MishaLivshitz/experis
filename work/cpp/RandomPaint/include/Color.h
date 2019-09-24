#ifndef COLOR_H
#define COLOR_H

typedef struct Color {
typedef unsigned char Uchar;

public:
    Color(Uchar r=0, Uchar g = 0, Uchar b = 0);

public:

    Uchar R;
    Uchar G;
    Uchar B;

}Color;

#endif