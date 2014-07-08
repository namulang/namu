#include "ModuleEncyclo.hpp"

void ModuleEncyclo::ModuleList::_focusWhatWantToBrowse()
{
	if( ! want_to_browse) return;

	type_code scr_idx = want_to_browse->getScriptCode();
	if(scr_idx < 0 || scr_idx > items.getLengthLastIndex())	return ;

	choosed = scr_idx;
}