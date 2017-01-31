#pragma once

#include <unordered_map>
#include <Windows.h>
#include <mutex>

struct D2GAMEINFO;

class ExtendedGameInfo
{
    D2GAMEINFO* _gameInfo;
public:
    ExtendedGameInfo(D2GAMEINFO* gameInfo) : _gameInfo(gameInfo) {}

    D2GAMEINFO const* GetGameInfo() { return _gameInfo; }
};

class GameManager
{
    std::mutex gameLock;
    typedef std::unordered_map<WORD /*gameId*/, ExtendedGameInfo*> ExtendedGameInfoMap;
    ExtendedGameInfoMap _gameInfos;

    GameManager();

public:
    static GameManager& instance()
    {
        static GameManager instance;
        return instance;
    }

    void GameCreated(D2GAMEINFO* gameInfo);
    void GameClosed(D2GAMEINFO* gameInfo);

    ExtendedGameInfo* GetExtendedGameInfo(WORD gameId);

    ~GameManager();
};

#define sGameManager (GameManager::instance())

