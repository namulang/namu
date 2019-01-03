#pragma once

#include "../wrd-commons.hpp"

namespace wrd
{
    union Id
    {
		Id(wint64 it = WRD_INDEX_ERROR) : num(it) {}
		Id(widx itscls, widx itsidx) : cls(itscls), idx(itsidx) {}
        widx cls; //    클래스의 종류
        widx idx; //    해당 클래스 인스턴스 벡터의 몇번째인가.type과 index를 조합하면 어디서든 객체에 접근할 수 있다.
        wint64 num;
    };
}
