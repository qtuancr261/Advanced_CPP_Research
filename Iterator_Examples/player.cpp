#include "player.h"

Player::Player(std::string defaultName, int defaultLevel)
    : name{defaultName},
      level{defaultLevel}
{
    basicHitPoints = static_cast<int>(level * 100 + 0.2 * basicHitPoints);
    // Player Default constructor
}

bool Player::operator()(std::string checkName)
{
    QString qstr{QString::fromStdString(checkName)};
    QRegExp regex{QString(R"(\w{4,30})")};
    return regex.exactMatch(qstr);
}
