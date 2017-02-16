#ifndef CHARACTER_H
#define CHARACTER_H

#include <memory>
#include <string>

#include "ingameelements/movingentity.h"
#include "datastructures.h"
#include "ingameelements/player.h"
#include "animation.h"
#include "ingameelements/weapon.h"
#include "global_constants.h"

class Character : public MovingEntity
{
    public:
        virtual void init(uint64_t id_, Gamestate *state, EntityPtr owner_);
        virtual ~Character() override;
        virtual void setinput(Gamestate *state, InputContainer heldkeys_, double mouse_x_, double mouse_y_);
        virtual void beginstep(Gamestate *state, double frametime) override;
        virtual void midstep(Gamestate *state, double frametime) override;
        virtual void endstep(Gamestate *state, double frametime) override;
        virtual void render(Renderer *renderer, Gamestate *state) override;
        bool isrootobject() override {return false;}
        virtual void interpolate(Entity *prev_entity, Entity *next_entity, double alpha) override;
        virtual void serialize(Gamestate *state, WriteBuffer *buffer, bool fullupdate) override;
        virtual void deserialize(Gamestate *state, ReadBuffer *buffer, bool fullupdate) override;
        virtual void destroy(Gamestate *state) override;

        virtual bool onground(Gamestate *state);
        virtual Rect getcollisionrect(Gamestate *state) = 0;
        virtual Rect getstandingcollisionrect(Gamestate *state) = 0;
        virtual bool cangetinput(Gamestate *state) {return not stunanim.active();}
        virtual bool canuseweapons(Gamestate *state) {return cangetinput(state);}
        virtual bool canuseabilities(Gamestate *state) {return cangetinput(state);}
        virtual void damage(Gamestate *state, double amount);
        virtual void die(Gamestate *state);
        virtual void interrupt(Gamestate *state) = 0;
        virtual void stun(Gamestate *state);
        Weapon *getweapon(Gamestate *state);
        virtual void useability1(Gamestate *state) = 0;
        virtual void useability2(Gamestate *state) = 0;
        virtual void useultimate(Gamestate *state) = 0;
        virtual void drawhud(Renderer *renderer, Gamestate *state);
        virtual double hudheight() {return 7.0/8.0;}
        virtual bool weaponvisible(Gamestate *state) {return true;}
        virtual double maxhspeed(Gamestate *state) {return crouchanim.active() ? 60.0 : 153.0;}

        virtual double runpower() = 0;
        virtual Health maxhp() = 0;
        virtual Heroclass heroclass() = 0;
        virtual std::string herofolder() = 0;
        virtual EntityPtr constructweapon(Gamestate *state) = 0;
        virtual double passiveultcharge() = 0;


        EntityPtr owner;
        EntityPtr weapon;

        Health hp;

        bool xblocked;
        bool yblocked;
        double friction;
        double acceleration;

        Team team;

        bool isflipped;
        LoopAnimation runanim;
        LoopAnimation crouchanim;
        Animation stunanim;
        Timer ongroundsmooth;

        InputContainer heldkeys;
        double mouse_x;
        double mouse_y;
        constexpr static int LEFT = -1;
        constexpr static int RIGHT = 1;
};

#endif // CHARACTER_H
