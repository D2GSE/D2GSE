#pragma once

#include <unordered_map>
#include <Windows.h>
#include <mutex>

class GameInfo
{

};

class GameManager
{
    std::mutex gameLock;
    typedef std::unordered_map<WORD /*gameId*/, GameInfo*> GameInfoMap;
    GameInfoMap _gameInfos;

    GameManager();

public:
    static GameManager& instance()
    {
        static GameManager instance;
        return instance;
    }

    void GameCreated(WORD gameId);
    void GameClosed(WORD gameId);

    GameInfo* GetGameInfo(WORD gameId);

    ~GameManager();
};

#define sGameManager (GameManager::instance())

