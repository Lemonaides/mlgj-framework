#ifndef ARTIST_H_INCLUDED
#define ARTIST_H_INCLUDED

#include <GL/gl.h>
#include <GL/glu.h>

#include <iostream>
#include <png.h>
#include <cstdio>
#include <cstdlib>

#include <string>
#include <vector>
#include <map>

#include "helper.h"

#define TEXTURE_LOAD_ERROR 0
#define DEFAULT_WINDOW_WIDTH 1280
#define DEFAULT_WINDOW_HEIGHT 720

using namespace std;

struct Rect
{
    int x, y, w, h;
};

class Artist
{
    public:
        static Artist* Instance();
        GLuint requestTexture(string filepath);
        Rect requestBounds(string filepath);

        void freeTextures();
        int windowWidth(){ return window_width; }
        int windowHeight(){ return window_height; }
        void setWindowWidth(int width);
        void setWindowHeight(int height);

    private:
        Artist();
        Artist(Artist const&){};
        Artist& operator=(Artist const&);
        ~Artist();
        static Artist* instance;

        map<string, pair<GLuint, Rect> > textureBank;
        GLuint loadTexture(const string filename, int &width, int &height);
        int window_width, window_height;


};

#endif // ARTIST_H_INCLUDED
