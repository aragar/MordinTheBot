#include "Filter.h"

const double Filter::EXP = 0.000001;

Filter::Filter(GameEncoder* encoder)
: encoder(encoder)
{}