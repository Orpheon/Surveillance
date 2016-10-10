#include <cmath>

#include "timer.h"

Timer::Timer(void (*eventfunc_)(Gamestate *state), double duration_) : timer(0), duration(duration_), active(true), eventfunc(eventfunc_)
{
    ;
}

Timer::~Timer()
{
    //dtor
}

void Timer::update(Gamestate *state, double dt)
{
    if (active)
    {
        timer += dt;
        if (timer >= duration)
        {
            eventfunc(state);
            active = false;
        }
    }
}

double Timer::getpercent()
{
    // Max and min are for rounding errors
    return std::fmax(std::fmin(timer/duration, 1.0), 0.0);
}

void Timer::interpolate(Timer *prev_timer, Timer *next_timer, double alpha)
{
    timer = prev_timer->timer + alpha*(next_timer->timer - prev_timer->timer);
}
