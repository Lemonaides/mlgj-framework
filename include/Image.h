#ifndef IMAGE_H_INCLUDED
#define IMAGE_H_INCLUDED

#include "Artist.h"

#include <sstream>

// Define DIRENT if you are on linux or MingGW and want
// a function to get a random PNG from a directory
#if DIRENT
#include <dirent.h>
#endif

using namespace std;
/*
 * Contains a reference to a GL texture, and has methods to manipulate
 * and display the texture at some coordinate.
 *
 * "frame" is defined as a section of a horizontal strip of the image
 * "track" is defined as a section of a vertical strip of the image
 *
 * So to animate across frames left and right, use frame related functions;
 * to animate across frames up and down, use track related functions.
 *
 * This lets you easily switch between animation sets as long as they
 * all progress horizontally OR vertically.
**/
class Image
{
    public:
        Image();
        Image(string tex);
        Image(string tex, int x, int y);
        Image(const Image& otherImage );

        int getNumFrames() { return bounds.w / framew; }
        int currentFrame() { return anim_frame / frameDelay + 1; }
        int currentTrack() { return anim_track / frameDelay + 1; }
        bool isFlipped() { return xflip; }

        Rect getBounds() { return bounds; }

        // Image can display its texture at a permanent (mutable) offset
        void setOffset(int x, int y){ bounds.x = x; bounds.y = y; }

        void getTint(float &r, float &g, float &b) { r = tint[0]; g = tint[1]; b = tint[2]; }
        // interprets a hex code as a color, assumes full alpha tint
        void setTint(string colorstring);
        // accepts RGBA floats
        void setTint(float r, float g, float b, float a);

        void display(int xOffset = 0, int yOffset = 0);
        // sets the size of the subdivision of the image for frames
        void setFrameSize(int w, int h);
        // divides the image into equally sized frames and tracks
        void partition(int wPieces, int hPieces);

        /// ANIM frame control
        void nextFrame();
        void prevFrame();
        void randomFrame() { anim_frame = 1 + rand()%(maxFrame()-1); }
        void nextTrack();

        /// SPRITE frame control
        void setFrame(int f);
        void setTrack(int t);

        void setFrameDelay(int d);
        void setXFlip(bool xf) { xflip = xf; }
        void setTexture(GLuint t) { texture = t; }
        void setTexture(string filepath){ texture = Artist::Instance()->requestTexture(filepath);
                                          bounds = Artist::Instance()->requestBounds(filepath); }
        GLuint getTexture() { return texture; }

        // for coloring pastel ponies using a grayscale texture
        void randomCoatColor();

    protected:
        GLuint texture;
        Rect bounds;
        float framew, frameh;
        float tint[4];
        unsigned int frameDelay;
        int anim_frame;
        int anim_track;
        bool xflip;

        int maxFrame();
        inline int maxTrack();
        inline void getFrame(int &framex, int &framey);

        // mixes up three ints
        void randomlyAssign(int r, int g, int b);

        // requires dirent.h library (linux / MinGW)
        #if DIRENT
        GLuint getRandomTexture(string directory);
        #endif

};

#endif // IMAGE_H_INCLUDED
