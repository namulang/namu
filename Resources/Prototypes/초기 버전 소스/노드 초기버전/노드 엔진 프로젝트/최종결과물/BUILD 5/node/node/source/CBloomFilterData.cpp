#include "CBloomFilterData.hpp"
//	생성자
CBloomFilterData::CBloomFilterData() : _bloom_level(DEFAULT_CBLOOMFILTER_BLOOM_LEVEL)
{}
//	소멸자
CBloomFilterData::~CBloomFilterData()
{}
//	블룸의 정도를 가져온다
float	CBloomFilterData::getBloomLevel()
{
	return _bloom_level;
}
//	얼마나 블룸을 할것인지 값을 넣는다.
void	CBloomFilterData::setBloomLevel(float bloom_level)
{
	//	예외상황처리:
	if (bloom_level < DEFAULT_CBLOOMFILTER_BLOOM_MIN_LEVEL)
		bloom_level = DEFAULT_CBLOOMFILTER_BLOOM_MIN_LEVEL;

	_bloom_level = bloom_level;
}
	

