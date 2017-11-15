//
// Created by MTesseracT on 20-10-2017.
//

#ifndef VULKANENGINE_GAMEBASE_HPP
#define VULKANENGINE_GAMEBASE_HPP

#include <stdexcept>
#include <iostream>
#include <Utility/Logger.hpp>
#include <Core/Renderers/SimpleRenderer.hpp>
#include "GameWorld.hpp"

class GameBase
{
private:
    SimpleRenderer  m_renderer;
    GameWorld       m_gameWorld;
    int             m_ticksPerSecond;
    double          m_timePerUpdate;

    void SetGameSpeed(int p_tps);
public:
    void RunGame();

    void InitializeRenderer();
    void InitializeInput();
    void InitializeGameTimer();
};


#endif //VULKANENGINE_GAMEBASE_HPP
