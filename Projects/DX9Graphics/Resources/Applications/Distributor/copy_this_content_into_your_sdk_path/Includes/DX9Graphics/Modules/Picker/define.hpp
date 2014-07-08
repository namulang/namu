#ifdef _DEBUG
#	ifdef DEVELOPER
#		define	_NAME									"Picker.dev.dbg"
#		define	_DEVELOPER								"kniz"
#		define	_REVISION								1
#		define	_COMMENT								"0번: 카메라 모듈 \n1번: 모델 모듈\n2번: 피킹결과"
#		define	_VERSION								"0.0.1a"
#		define	_DATE									"2013-09-23"
#		define	_DEPENDENCIES_COUNT						0
#		define	_KEY_COUNT								2
#	endif
#else
#	ifdef DEVELOPER
#		define	_NAME									"PerspectiveCamera.dev"
#		define	_DEVELOPER								"kniz"
#		define	_REVISION								1
#		define	_COMMENT								"0번: 바인딩할 DX9\n1번: 렌더링할 노드\n2번: pos x\n3번. pos y\n4번. pos z\n5번. right x\n6번. right y\n7번. right z\n8번. up x\n9번. up y\n10번. up z\n11번. look x\n12번. look y\n13번. look z\n14번. fov y\n15번. aspect\n16번. z near\n17번. z far\n18번. viewport x\n19번 viewport y\n20번 viewport width pixel\n21번 viewport height pixel\n22번. viewport z\n23번. viewport z far"
#		define	_VERSION								"0.0.1a"
#		define	_DATE									"2013-01-29"
#		define	_DEPENDENCIES_COUNT						0
#		define	_KEY_COUNT								14
#	else
#		define	_NAME									"PerspectiveCamera"
#		define	_DEVELOPER								"kniz"
#		define	_REVISION								1
#		define	_COMMENT								"0번: 바인딩할 DX9\n1번: 렌더링할 노드\n2번: pos x\n3번. pos y\n4번. pos z\n5번. right x\n6번. right y\n7번. right z\n8번. up x\n9번. up y\n10번. up z\n11번. look x\n12번. look y\n13번. look z\n14번. fov y\n15번. aspect\n16번. z near\n17번. z far\n18번. viewport x\n19번 viewport y\n20번 viewport width pixel\n21번 viewport height pixel\n22번. viewport z\n23번. viewport z far"
#		define	_VERSION								"0.0.1a"
#		define	_DATE									"2013-01-29"
#		define	_DEPENDENCIES_COUNT						0
#		define	_KEY_COUNT								14
#	endif
#endif