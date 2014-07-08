#pragma once

#include "../CommandSet/CommandSet.hpp"

class Commander : public CommandSet
{
public:		
	NEString command(const NEString& command_name) {
		for(int n=0; n < getLength() ; n++) {
			Command& itr = getElement(n);

			if(itr.name == command_name)
				return itr.execute();
		}

		return command_name + "이란 명령어는 없다구요.\n오타? 아님 착각?";
	}
};