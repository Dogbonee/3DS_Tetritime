//
// Created by Caleb on 5/9/2026.
//

#ifndef RESOURCES_H
#define RESOURCES_H
#include <Dualie/Audio/Music.hpp>

namespace Resources {
    extern dl::Music* MainTheme;
    extern dl::Music* ClearSound;
    extern dl::Music* PlaceSound;

    void loadResources();
    void freeResources();
}



#endif //RESOURCES_H
