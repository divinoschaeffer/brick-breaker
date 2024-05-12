#include <iostream>
#include <memory>

// Enum pour représenter les différents types de modifications
enum class ModifierType {
    None,
    MultiBall,
    BonusSpeedBall,
    BonusPaddle,
    MalusPaddle
};

// Classe abstraite représentant une modification
class Modifier {
public:
    virtual ~Modifier() {}
    virtual void apply() = 0;
    virtual ModifierType getType() const = 0;
};

class MultiBall : public Modifier {
public:
    void apply() override;

    ModifierType getType() const override;
};

class BonusSpeedBall: public Modifier{
    public:
        void apply() override;

        ModifierType getType() const override;
};

class BonusPaddle: public Modifier{
public:
    void apply() override;

    ModifierType getType() const override;
};

class MalusPaddle: public Modifier{
public:
    void apply() override;

    ModifierType getType() const override;
};