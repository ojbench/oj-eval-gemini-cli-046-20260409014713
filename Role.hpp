#ifndef ROLE_HPP
#define ROLE_HPP
#include <string>
#include <iostream>

namespace final {
    
    class Fighter;
    class Protector;
    class Caster;

    class Base {
        friend class Fighter;
        friend class Protector;
        friend class Caster;
    private:
        std::string name;
        int health, attack;
        bool alive, defensive;
        inline static int aliveNumber = 0;
    public:
        static int getAliveNumber() {
            return aliveNumber;
        }

        Base(const std::string& name, int health, int attack) 
            : name(name), health(health), attack(attack), alive(true), defensive(false) {
            aliveNumber++;
        }

        virtual ~Base() {
            if (alive) {
                aliveNumber--;
            }
        }

        virtual void launch_attack(Base* target) = 0;
        virtual void defend(bool flag) = 0;

        bool isAlive() {
            return alive;
        }

        bool isDefensive() {
            return defensive;
        }
    };

    class Fighter : public Base {
    public:
        Fighter(const std::string& name, const int health, const int attack) : Base(name, health, attack) {}

        void launch_attack(Base* target) override;

        void defend(bool flag) override {
            if (flag) {
                defensive = 1;
                health += 3;
                attack += 2;
            } else {
                defensive = 0;
            }
        }
    };

    class Protector : public Base {
    public:
        Protector(const std::string& name, const int health, const int attack) : Base(name, health, attack) {}

        void launch_attack(Base* target) override;

        void defend(bool flag) override {
            if (flag) {
                defensive = 1;
                health += 7;
                attack += 1;
            } else {
                defensive = 0;
            }
        }
    };

    class Caster : public Base {
    public:
        Caster(const std::string& name, const int health, const int attack) : Base(name, health, attack) {}

        void launch_attack(Base* target) override;

        void defend(bool flag) override {
            if (flag) {
                defensive = 1;
                health += 5;
            } else {
                defensive = 0;
            }
        }
    };

    inline void Fighter::launch_attack(Base *target) {
        int multiplier = 1;
        if (dynamic_cast<Caster*>(target)) multiplier = 2;

        if (target->defensive) {
            int damage_to_target = this->attack * multiplier - target->attack;
            if (damage_to_target < 0) damage_to_target = 0;
            target->health -= damage_to_target;

            int damage_to_attacker = target->attack;
            this->health -= damage_to_attacker;
        } else {
            int damage_to_target = this->attack * multiplier;
            target->health -= damage_to_target;
        }

        bool target_dead = false;
        if (target->health <= 0 && target->alive) {
            target->alive = false;
            Base::aliveNumber--;
            target_dead = true;
        }

        bool attacker_dead = false;
        if (this->health <= 0 && this->alive) {
            this->alive = false;
            Base::aliveNumber--;
            attacker_dead = true;
        }

        if (target_dead) {
            std::string role = "";
            if (dynamic_cast<Fighter*>(target)) role = "Fighter";
            else if (dynamic_cast<Protector*>(target)) role = "Protector";
            else if (dynamic_cast<Caster*>(target)) role = "Caster";
            std::cout << role << " " << target->name << " is killed\n";
        }
        if (attacker_dead) {
            std::cout << "Fighter " << this->name << " is killed\n";
        }
    }

    inline void Protector::launch_attack(Base *target) {
        int multiplier = 1;
        if (dynamic_cast<Fighter*>(target)) multiplier = 2;

        if (target->defensive) {
            int damage_to_target = this->attack * multiplier - target->attack;
            if (damage_to_target < 0) damage_to_target = 0;
            target->health -= damage_to_target;

            int damage_to_attacker = target->attack;
            this->health -= damage_to_attacker;
        } else {
            int damage_to_target = this->attack * multiplier;
            target->health -= damage_to_target;
        }

        bool target_dead = false;
        if (target->health <= 0 && target->alive) {
            target->alive = false;
            Base::aliveNumber--;
            target_dead = true;
        }

        bool attacker_dead = false;
        if (this->health <= 0 && this->alive) {
            this->alive = false;
            Base::aliveNumber--;
            attacker_dead = true;
        }

        if (target_dead) {
            std::string role = "";
            if (dynamic_cast<Fighter*>(target)) role = "Fighter";
            else if (dynamic_cast<Protector*>(target)) role = "Protector";
            else if (dynamic_cast<Caster*>(target)) role = "Caster";
            std::cout << role << " " << target->name << " is killed\n";
        }
        if (attacker_dead) {
            std::cout << "Protector " << this->name << " is killed\n";
        }
    }

    inline void Caster::launch_attack(Base *target) {
        int multiplier = 1;
        if (dynamic_cast<Protector*>(target)) multiplier = 2;

        if (target->defensive) {
            int damage_to_target = this->attack * multiplier - target->attack;
            if (damage_to_target < 0) damage_to_target = 0;
            target->health -= damage_to_target;

            // Caster takes no reflection damage
        } else {
            int damage_to_target = this->attack * multiplier;
            target->health -= damage_to_target;
        }

        bool target_dead = false;
        if (target->health <= 0 && target->alive) {
            target->alive = false;
            Base::aliveNumber--;
            target_dead = true;
        }

        bool attacker_dead = false;
        if (this->health <= 0 && this->alive) {
            this->alive = false;
            Base::aliveNumber--;
            attacker_dead = true;
        }

        if (target_dead) {
            std::string role = "";
            if (dynamic_cast<Fighter*>(target)) role = "Fighter";
            else if (dynamic_cast<Protector*>(target)) role = "Protector";
            else if (dynamic_cast<Caster*>(target)) role = "Caster";
            std::cout << role << " " << target->name << " is killed\n";
        }
        if (attacker_dead) {
            std::cout << "Caster " << this->name << " is killed\n";
        }
    }
}
#endif //ROLE_HPP