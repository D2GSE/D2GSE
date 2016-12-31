#pragma once

#include <string>
#include <vector>

struct Game;
struct Unit;

class CommandHandler
{
    typedef bool (*HandlerCallback)(Game* game, Unit* player, std::vector<char const*> const& arguments);

    struct Handler
    {
        std::string Command;
        HandlerCallback Callback;
    };

    static std::vector<Handler> CommandTable;

    static bool HandleHello(Game* game, Unit* player, std::vector<char const*> const& arguments);

public:
    static void HandleCommand(Game* game, Unit* player, std::string const& message);
};

// from TrinityCore
class Tokenizer : public std::vector<char const*>
{
public:

public:
    Tokenizer(const std::string &src, char const sep, unsigned int vectorReserve = 0, bool keepEmptyStrings = true)
        : std::vector<char const*>(vectorReserve)
    {
        m_str = new char[src.length() + 1];
        memcpy(m_str, src.c_str(), src.length() + 1);

        char* posold = m_str;
        char* posnew = m_str;

        for (;;)
        {
            if (*posnew == sep)
            {
                if (keepEmptyStrings || posold != posnew)
                    push_back(posold);

                posold = posnew + 1;
                *posnew = '\0';
            }
            else if (*posnew == '\0')
            {
                // Hack like, but the old code accepted these kind of broken strings,
                // so changing it would break other things
                if (posold != posnew)
                    push_back(posold);

                break;
            }

            ++posnew;
        }
    }

    ~Tokenizer() { delete[] m_str; }

private:
    char* m_str;
};
