#pragma once

#include "../Command/Command.hpp"

template
class NETArray<Command*, true>;
typedef NETArray<Command*, true> CommandSet;