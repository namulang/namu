#pragma once

#include "../Command/Command.hpp"

template
class NETVector<Command*, true>;
typedef NETVector<Command*, true> CommandSet;