#include "GameManager.h"
#include "Ptrs.h"
#include "Structs.h"

GameManager::GameManager()
{
}


void GameManager::GameCreated(WORD gameId)
{
    if (!gameId)
        return;

    DWORD hash = D2Game_GameHashFromGameId(gameId);
    if (!hash)
        return;

    Game* game = D2Game_AcquireGameFromHash(hash);
    if (!game)
        return;

    D2Game_LeaveCriticalSection(game);

    std::lock_guard<std::mutex> lock(gameLock);
    if (_gameInfos.find(gameId) != _gameInfos.end())
        return;

    _gameInfos[gameId] = new GameInfo();
}

void GameManager::GameClosed(WORD gameId)
{
    std::lock_guard<std::mutex> lock(gameLock);
    _gameInfos.erase(gameId);
}

GameInfo* GameManager::GetGameInfo(WORD gameId)
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
