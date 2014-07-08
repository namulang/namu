#pragma once

#include "../Command/Command.hpp"

template
class NEArrayTemplate<Command*, true>;
typedef NEArrayTemplate<Command*, true> CommandSet;