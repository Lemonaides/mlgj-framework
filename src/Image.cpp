#include "Image.h"

Image::Image()
{
    texture = TEXTURE_LOAD_ERROR;
    bounds.x = 0; bounds.y = 0; bounds.w = 0; bounds.h = 0;
    frameDelay = 4;
    anim_frame = 1;
    anim_track = 1;
    xflip = false;
    setTint(1.0,1.0,1.0,1.0);
}

Image::Image(string tex)
{
    texture = Artist::Instance()->requestTexture(tex);
    bounds = Artist::Instance()->requestBounds(tex);
    framew = bounds.w;
    frameh = bounds.h;
    bounds.x = 0;
    bounds.y = 0;
    frameDelay = 4;
    anim_frame = 1;
    anim_track = 1;
    xflip = false;
    setTint(1.0, 1.0, 1.0, 1.0);
}

Image::Image(string tex, int x, int y)
{
    texture = Artist::Instance()->requestTexture(tex);
    bounds = Artist::Instance()->requestBounds(tex);
    framew = bounds.w;
    frameh = bounds.h;
    bounds.x = x;
    bounds.y = y;
    anim_frame = 1;
    anim_track = 1;
    frameDelay = 4;
    xflip = false;
    setTint(1.0, 1.0, 1.0, 1.0);
}

Image::Image(const Image& otherImage)
{
    this->texture = otherImage.texture;
    this->bounds = otherImage.bounds;
    this->framew = otherImage.framew;
    this->frameh = otherImage.frameh;
    this->frameDelay = otherImage.frameDelay;
    this->anim_frame = otherImage.anim_frame;
    this->anim_track = otherImage.anim_track;
    this->xflip = otherImage.xflip;
    for(int i = 0; i<4; i++)
        this->tint[i] = otherImage.tint[i];
}

void Image::setTint(string colorstring)
{
    unsigned int color;
    std::stringstream ss;
    ss << std::hex << colorstring;
    ss >> color;

    unsigned char r, g, b;
    b = color & 0xFF;
    g = (color >> 8) & 0xFF;
    r = (color >> 16) & 0xFF;

    tint[0] = r/255.0f;
    tint[1] = g/255.0f;
    tint[2] = b/255.0f;
    tint[3] = 1.0;
}

void Image::setTint(float r, float g, float b, float a)
{
    tint[0] = r;
    tint[1] = g;
    tint[2] = b;
    tint[3] = a;
}

void Image::randomCoatColor()
{
    int r, g, b;

    r = rand() % 31 + 224 - 32;

    g = r + rand() % (256-r - 16);

    b = g + rand() % (256-g);

    int average = (r + g + b)/3;
    if(average < 221)
    {
        r += (221 - average);
        g += (221 - average);
        b += (221 - average);
    }

    randomlyAssign(r,g,b);
}

void Image::setFrameDelay(int d)
{
    if(d <= 0)
        return;

    anim_frame = anim_frame * d / frameDelay;
    frameDelay = d;

    //cout << "frameDelay is now " << frameDelay << "\n";

    if(anim_frame >= maxFrame() )
        anim_frame = 1;
}

/// max anim frame
int Image::maxFrame()
{
    return (bounds.w / framew * frameDelay);
}

/// max anim track
int Image::maxTrack()
{
    return ( bounds.h / frameh * frameDelay);
}

/// next anim frame
void Image::nextFrame()
{
    anim_frame++;

    if(anim_frame >= maxFrame() )
        anim_frame = 1;
}

/// prev anim frame
void Image::prevFrame()
{
    anim_frame--;

    if(anim_frame<1)
        anim_frame = maxFrame() - 1;
}

/// next anim track
void Image::nextTrack()
{
    anim_track++;

    if(anim_track >= maxTrack() )
        anim_track = 1;
}

void Image::partition(int wPieces, int hPieces)
{
    if( wPieces <= 0 || hPieces <= 0 || wPieces > bounds.w || hPieces > bounds.h)
    {
        cout << "invalid image partion\n";
        return;
    }
    framew = bounds.w / wPieces;
    frameh = bounds.h / hPieces;

    // cout << "framew : " << framew << "  frameh : " << frameh << "\n";

    // cout << "partitioned : " << maxFrame()/frameDelay << " , " << maxTrack()/frameDelay << endl;
}

void Image::setFrameSize(int w, int h)
{
    framew = abs(w);
    if(!framew)
        framew = bounds.w;

    frameh = abs(h);
    if(!frameh)
        frameh = bounds.h;
}

void Image::getFrame(int &framex, int &framey)
{
    int myframe = anim_frame/frameDelay + 1;

    if(myframe <= 0)
        myframe = 1;

    int mytrack = anim_track/frameDelay + 1;

    if(mytrack <= 0)
        mytrack = 1;

    int w = framew * myframe;
    int h = frameh * mytrack;

    while(w > bounds.w)
    {
        w -= bounds.w;
    }

    while(h > bounds.h)
    {
        h -= bounds.h;
    }

    //h = bounds.h - h;

    // start at the begining of the frame box not the end
    framex = w - framew;
    framey = h - frameh;

    if(xflip)
        framex = bounds.w - framex - framew;

    //cout << "fx = " << framex / framew << " , fy = " << framey / frameh<< endl;
}

void Image::setFrame(int f)
{
    if(f<=0)
        f = 1;

    anim_frame = (f-1)*frameDelay;

    if(anim_frame >= maxFrame())
       anim_frame = 1;
}

void Image::setTrack(int t)
{
   anim_track = (t-1)*frameDelay;
    if(anim_track >= maxTrack())
       anim_track = 1;
}

// displays a texture on a quad
void Image::display(int xOffset, int yOffset)
{
    glMatrixMode(GL_TEXTURE);
    glLoadIdentity();
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,  GL_MODULATE);

    glColor4fv(tint);

    // for horizontal mirroring
    int xsign = 1;
    if(xflip)
        xsign = -1;

    // display the quads upside down (for using quadrant 4 cartesian coords)
    // (flip your camera over too)
    glScalef(xsign/((float)bounds.w), -1/((float)bounds.h), 1);

    glBindTexture( GL_TEXTURE_2D, texture );

    int framex, framey;
    getFrame(framex, framey);

    glBegin( GL_QUADS );

        // Top-left vertex
        glTexCoord2f( framex, framey );
        glVertex2i( xOffset + bounds.x, yOffset + bounds.y);

        // Bottom-left vertex
        glTexCoord2f( framex + framew, framey );
        glVertex2i( xOffset + bounds.x + framew, yOffset + bounds.y);

        // Bottom-right vertex
        glTexCoord2f(framex + framew, frameh + framey );
        glVertex2i( xOffset + bounds.x + framew, yOffset + bounds.y + frameh);

        // Top-right vertex
        glTexCoord2f( framex, frameh + framey);
        glVertex2i( xOffset + bounds.x , yOffset + bounds.y + frameh);

    glEnd();
}

void Image::randomlyAssign(int r, int g, int b)
{
    int primary = r;
    int secondary = g;
    int tertiary = b;

    int rnd = rand()%3;

    if(rnd == 0)
    {
        if(rand()%2)
        {
            b = secondary;
            g = tertiary;
        }

    }
    else if(rnd == 1)
    {
        g = primary;
        if(rand()%2)
        {
            r = secondary;
            b = tertiary;
        }
        else
        {
            b = secondary;
            r = tertiary;
        }
    }
    if(rnd == 2)
    {
        b = primary;
        if (rand()%2)
        {
            r = secondary;
            g = tertiary;
        }
        else
        {
            g = secondary;
            r = tertiary;
        }
    }

    cout << "new tint: " << r << " " << g << " " << b << "\n";

    tint[0] = r/255.0;
    tint[1] = g/255.0;
    tint[2] = b/255.0;
    tint[3] = 1.0;
}

#if DIRENT
GLuint Image::getRandomTexture(string directory)
{
    vector<string> filenames;

    DIR *pdir;
    struct dirent *pent;

    // open directory
    pdir=opendir(directory.c_str());
    if (!pdir)
    {
        cout << "failed to open " << directory << "!\n";
        return TEXTURE_LOAD_ERROR;
    }

    // get the contents of the directory
    while ((pent=readdir(pdir)))
    {
        filenames.push_back(directory + '/' + string(pent->d_name));
    }

    // get rid of the files that aren't marked .png
    for(unsigned int i = 0; i < filenames.size(); i++)
    {
        unsigned int lastMatchPos = filenames[i].rfind(".png");
        if(lastMatchPos == string::npos)
        {
            filenames.erase(filenames.begin() + i);
            i--;
        }
        // it doesn't cound unless .png is at the very end of the string
        else if(lastMatchPos != filenames[i].size() - 4)
        {
            filenames.erase(filenames.begin() + i);
            i--;
        }
    }

    // randomly choose one until a valid png is found
    while(!filenames.empty())
    {
        int rnd = rand()%filenames.size();
        GLuint tex = Artist::Instance()->requestTexture(filenames[rnd]);
        if(tex != TEXTURE_LOAD_ERROR)
            return tex;
        else
            filenames.erase(filenames.begin() + rnd);
    }

    return TEXTURE_LOAD_ERROR;
}
#endif
