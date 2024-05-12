#include "Modifier.h"

void MultiBall::apply()
{
    std::cout << "Applying MultiBall modifier" << std::endl;
}

ModifierType MultiBall::getType() const
{
    return ModifierType::MultiBall;
}

void BonusSpeedBall::apply()
{
    std::cout << "Applying BonusSpeedBall modifier" << std::endl;
}

ModifierType BonusSpeedBall::getType() const
{
    return ModifierType::BonusSpeedBall;
}

void BonusPaddle::apply()
{
    std::cout << "Applying BonusPaddle modifier" << std::endl;
}

ModifierType BonusPaddle::getType() const
{
    return ModifierType::BonusPaddle;
}

void MalusPaddle::apply()
{
    std::cout << "Applying MalusPaddle modifier" << std::endl;
}

ModifierType MalusPaddle::getType() const
{
    return ModifierType::MalusPaddle;
}
