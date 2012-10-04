#ifndef WUBMANAGER_H
#define WUBMANAGER_H

#include <irrKlang.h>
#include <map>
#include <string>
#include <iostream>

#define SOUNDSCALE 128.0f

using namespace std;
using namespace irrklang;

class WubManager
{
    public:
        static WubManager* Instance();
        void freeSounds();
        irrklang::ISoundSource* requestSoundSource(string filepath);
        irrklang::ISoundEngine* getDJ(){ return dj; }

    private:
        ISoundEngine* dj;
        map<string, ISoundSource* > soundBank;

        WubManager();
        ~WubManager();
        WubManager(WubManager const&){};
        WubManager& operator=(WubManager const&);
        static WubManager* instance;
};

#endif // WUBMANAGER_H
