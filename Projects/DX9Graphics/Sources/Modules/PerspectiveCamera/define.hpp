#ifdef _DEBUG
#	ifdef DEVELOPER
#		define	_NAME									"PerspectiveCamera"
#		define	_DEVELOPER								"kniz"
#		define	_REVISION								1
#		define	_COMMENT								"0번:TransX \n1번:TransY \n2번:TransZ \n3번:RotateX \n4번:RotateY \n5번:RotateZ \n6번:ScaleX \n7번: ScaleY \n8번:ScaleZ \n9번:ColorRed \n10번. ColorGreen \n11번. ColorBlue \n12번. ColorAlpha \n13번: SourceBlending \n14번: DestBlending \n15번: DX9 \n16번: 촬영대상 \n17번:UpX \n18번: UpY\n19번:UpZ \n20번:뷰포트를 자동으로 처리(전체화면 모드) \n21번:뷰포트사용자정의(X) \n22번:뷰포트사용자정의(Y) \n23번:뷰포트사용자정의(Width) \n24번:뷰포트사용자정의(Height) \n25번:뷰포트사용자정의(MinimumZ) \n26번:뷰포트사용자정의(MaximumZ) \n27번:ShaderPrograms \n28번: Projection행렬을 자동으로 생성함 \n29번:Projection행렬 사용자 정의(FOVY) \n30번: Projection행렬 사용자 정의(Aspect) \n31번:Projection행렬 사용자 정의(MinimumZ) \n32번: Projection행렬 사용자 정의(MaximumZ)"
#		define	_VERSION								"0.0.1a"
#		define	_DATE									"2013-08-10"
#		define	_DEPENDENCIES_COUNT						0
#		define	_KEY_COUNT								14
#	endif
#else
#	ifdef DEVELOPER
#		define	_NAME									"PerspectiveCamera"
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