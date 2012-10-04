#include "WubManager.h"

using namespace std;

WubManager* WubManager::instance = NULL;

WubManager* WubManager::Instance()
{
    return instance ? instance : (instance = new WubManager());
}

WubManager::WubManager()
{
    // start the sound engine with default parameters
    dj = irrklang::createIrrKlangDevice();

    if (!dj)
        cout << "[WubManager] ERROR: Could not startup the sound engine\n";
    else
        cout << "[WubManager] DJ Pon-3 is ready to rock!\n";
}

WubManager::~WubManager()
{
    if(dj)
        dj->drop();
}

irrklang::ISoundSource* WubManager::requestSoundSource(string filepath)
{
    cout << "Requesting Sound Source for \"" << filepath << "\" ... ";
    irrklang::ISoundSource* source = NULL;

    map<string, irrklang::ISoundSource* > ::iterator it = soundBank.find(filepath);
    // key is already present in map return it
    if( it != soundBank.end() )
    {
        cout << "SoundSource already loaded.\n";
        return (*it).second;
    }
    source = dj->addSoundSourceFromFile(filepath.c_str());
    if(source)
    {
        soundBank.insert(pair<string, irrklang::ISoundSource*>(filepath, source));
        source->setDefaultMinDistance(2.0f);
        cout << "successfully loaded.\n";
    }
    return source;
}

void WubManager::freeSounds()
{
    soundBank.clear();
    dj->removeAllSoundSources();
}
