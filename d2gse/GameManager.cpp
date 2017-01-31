#include "GameManager.h"
#include "Ptrs.h"
#include "Structs.h"

GameManager::GameManager()
{
}

void GameManager::GameCreated(D2GAMEINFO* gameInfo)
{
    std::lock_guard<std::mutex> lock(gameLock);
    _gameInfos[gameInfo->GameId] = new ExtendedGameInfo(gameInfo);
}

void GameManager::GameClosed(D2GAMEINFO* gameInfo)
{
    std::lock_guard<std::mutex> lock(gameLock);
    _gameInfos.erase(gameInfo->GameId);
}

ExtendedGameInfo* GameManager::GetExtendedGameInfo(WORD gameId)
{
    std::lock_guard<std::mutex> lock(gameLock);

    auto itr = _gameInfos.find(gameId);
    return itr != _gameInfos.end() ? itr->second : nullptr;
}

GameManager::~GameManager()
{
    std::lock_guard<std::mutex> lock(gameLock);
    for (auto& itr : _gameInfos)
        delete itr.second;
    _gameInfos.clear();
}
