#pragma once

#include "../common/dep.hpp"

namespace wrd {
	struct point {
		wcnt row;
		wcnt col;

        void rel() {
            row = col = 0;
        }
	};

	struct area {
		point start;
		point end;

        void rel() {
            start.rel();
            end.rel();
        }
	};
}
