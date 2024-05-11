#include "Modifier.h"

void MultiBall::apply()
{
    std::cout << "Applying MultiBall modifier" << std::endl;
}

ModifierType MultiBall::getType() const
{
    return ModifierType::MultiBall;
}
