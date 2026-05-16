//
// Created by Caleb on 5/9/2026.
//

#include "Resources.h"

dl::Music* Resources::MainTheme;
dl::Music* Resources::ClearSound;
dl::Music* Resources::PlaceSound;

void Resources::loadResources() {

    MainTheme = new dl::Music(0);
    ClearSound = new dl::Music(1);
    PlaceSound = new dl::Music(2);


    MainTheme->loadFromFile("romfs:/Adventure.opus");
    ClearSound->loadFromFile("romfs:/ClearLine.opus");
    PlaceSound->loadFromFile("romfs:/Tick.opus");
}

void Resources::freeResources() {
    delete MainTheme;
    delete ClearSound;
    delete PlaceSound;
}
