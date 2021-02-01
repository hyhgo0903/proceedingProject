#include "stdafx.h"
#include "stageManager.h"

stageManager::stageManager()
{
}

stageManager::~stageManager()
{
}

HRESULT stageManager::init()
{
	_stage = STAGE1;
	_battlePhase = false;
	_menuInPt = false;
	return S_OK;
}

void stageManager::release()
{
}

void stageManager::update()
{
	_cameraPtMouse.x = _ptMouse.x + CAMX;
	_cameraPtMouse.y = _ptMouse.y + CAMY;
	_pickingPt = picking(_cameraPtMouse.x, _cameraPtMouse.y);
	uiRect();
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		homeBt();
	}

	if (KEYMANAGER->isOnceKeyDown(VK_F1))
	{
		_stage = STAGE1;
		setStage(_stage);
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F2))
	{
		_stage = STAGE2;
		setStage(_stage);
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F3))
	{
		_stage = STAGE3;
		setStage(_stage);
	}
	if (KEYMANAGER->isStayKeyDown(VK_RETURN))
	{ // 지금은 엔터키로해놨지만 나중에 배치페이즈 끝내는 버튼(게임시작)을 누른 경우로 바꿀거임
		_battlePhase = true;
		_um->setActive();
	}
}

void stageManager::render()
{
	//아이소타일
	for (int i = 0; i < TILEX * TILEY; ++i)
	{ 
		if (_isoTile[i].centerX < CAMX - 32 || _isoTile[i].centerX > CAMX + WINSIZEX + 32 ||
			_isoTile[i].centerY < CAMY - 16 || _isoTile[i].centerY > CAMY + WINSIZEY + 16) continue;

		IMAGEMANAGER->findImage("mapTiles")->frameRender(getMemDC(), _isoTile[i].drawX, _isoTile[i].drawY, _isoTile[i].fX, _isoTile[i].fY);
	}
}

void stageManager::objectRender()
{
	//오브젝트만! 그려준다
	for (int i = 0; i < TILEX * TILEY; ++i)
	{
		if (_isoTile[i].centerX < CAMX - 32 || _isoTile[i].centerX > CAMX + WINSIZEX + 32 ||
			_isoTile[i].centerY < CAMY - 16 || _isoTile[i].centerY > CAMY + WINSIZEY + 16) continue;

		else if (_isoTile[i].name == TREE1)
		{
			IMAGEMANAGER->findImage("tree")->render(getMemDC(), _isoTile[i].drawX - 32, _isoTile[i].drawY - 90);
		}
		else if (_isoTile[i].name == TREE2)
		{
			IMAGEMANAGER->findImage("tree2")->render(getMemDC(), _isoTile[i].drawX - 10, _isoTile[i].drawY - 90);
		}
		else if (_isoTile[i].name == TREE3)
		{
			IMAGEMANAGER->findImage("tree3")->render(getMemDC(), _isoTile[i].drawX - 12, _isoTile[i].drawY - 118);
		}
		else if (_isoTile[i].name == TREE4)
		{
			IMAGEMANAGER->findImage("tree4")->render(getMemDC(), _isoTile[i].drawX - 15, _isoTile[i].drawY - 105);
		}
		else if (_isoTile[i].name == TREE5)
		{
			IMAGEMANAGER->findImage("tree5")->render(getMemDC(), _isoTile[i].drawX - 3, _isoTile[i].drawY - 58);
		}
	}
}

void stageManager::uiRender()
{
	IMAGEMANAGER->findImage("ui_clear")->render(getMemDC(), CAMX + WINSIZEX - 128, CAMY);
	IMAGEMANAGER->findImage("ui_start")->render(getMemDC(), CAMX + WINSIZEX - 64, CAMY);
	IMAGEMANAGER->findImage("ui_home")->render(getMemDC(), CAMX, CAMY + 500);
	IMAGEMANAGER->findImage("ui_retry")->render(getMemDC(), CAMX, CAMY + 532);

	//유닛 선택 메뉴
	IMAGEMANAGER->findImage("ui_menu")->render(getMemDC(), CAMX + WINSIZEX - 930, CAMY + WINSIZEY - 132);
	IMAGEMANAGER->findImage("icon_zergling")->render(getMemDC(), CAMX + 280, CAMY + WINSIZEY - 95);
	IMAGEMANAGER->findImage("icon_marine")->render(getMemDC(), CAMX + 360, CAMY + WINSIZEY - 95);
	IMAGEMANAGER->findImage("icon_civilian")->render(getMemDC(), CAMX + 440, CAMY + WINSIZEY - 95);
	IMAGEMANAGER->findImage("icon_templar")->render(getMemDC(), CAMX + 520, CAMY + WINSIZEY - 95);
	IMAGEMANAGER->findImage("icon_bishop")->render(getMemDC(), CAMX + 600, CAMY + WINSIZEY - 95);
	IMAGEMANAGER->findImage("icon_ghost")->render(getMemDC(), CAMX + 680, CAMY + WINSIZEY - 95);
}

void stageManager::uiRect()
{
	_homeBt = RectMake(CAMX, CAMY + 500, 64, 32);
}

void stageManager::homeBt()
{
	if (PtInRect(&_homeBt, _cameraPtMouse))
	{
		_menuInPt = true;
		if (_menuInPt) SCENEMANAGER->changeScene("타이틀씬");
	}
	else _menuInPt = false;
}

inline POINT stageManager::picking(long x, long y)
{ // 이게 피킹
	int xx; int yy;
	if (2 * y < (x - 960))	return { -1,0 }; // y=1/2x보다 위에있는지 (맵밖 벗어남)
	if (2 * y < -(x - 960))	return { -1,0 }; // y=-1/2x보다 위에있는지 (맵밖 벗어남)
	//-1이면 예외처리됨(키매니저 L버튼 참고)

	// 왜 y=1/2x가 아니라 2y=x로 썼냐면 나눗셈연산이 느리기때문에 이렇게 쓴거임.
	// 320은 TILEWIDTH * TILEX / 2 (=맵전체 가로크기의 절반값)와 같은데 부하를 줄이기 위해 계산하고 넣은것임

	 // 64는 타일 높이(TILEHEIGHT)에 양변 2곱한값이며 이만큼씩 이격된(밑으로간) 직선이라 보면 됨
	xx = (2 * y + (x - 960)) / 64; // y절편을 이용한 방식으로 바꾸었음
	// xx = ((y + 1/2*(x - 960)) / 32
	// (x좌표) = ((y + 1/2 *(x - 맵x절반)) / 타일높이
	//           ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
	//           ㄴ>이 부분이 y절편(h)
	if (xx > 29) return { -1,0 }; // 맵밖 벗어난거면 예외처리

	yy = (2 * y - (x - 960)) / 64; // 기울기만 음수고 나머진 상동
	// yy = ((y - 1/2*(x - 960)) / 32
	// (y좌표) = ((y - 1/2 *(x - 맵x절반)) / 타일높이
	//           ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
	//           ㄴ>이 부분이 y절편(h)
	if (yy > 29) return { -1,0 };

	return { xx , yy };
}

void stageManager::setStage(STAGE stage)
{ // 적 유닛 생성도 요기서하기로 함
	HANDLE file;
	DWORD read;

	switch (stage)
	{
	case STAGE1:
		file = CreateFile("stage1.map", GENERIC_READ, NULL, NULL,
			OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		ReadFile(file, _isoTile, sizeof(isoTile) * TILEX*TILEY, &read, NULL);
		CloseHandle(file);

		_gold = _isoTile[0].gold;
		for (int i = 0; i < TILEX * TILEY; ++i)
		{
			if (_isoTile[i].name == ZERGLING)
			{ // 에너미 생성은 여기서하고 오브젝트는 우리가 그려주면됨(유닛보다 나중에 그려줄거임. 가리도록)
				_um->createZergling(ENEMY, _isoTile[i].centerX, _isoTile[i].centerY);
			}
			if (_isoTile[i].name == MARINE)
			{ // 에너미 생성은 여기서하고 오브젝트는 우리가 그려주면됨(유닛보다 나중에 그려줄거임. 가리도록)
				_um->createMarine(ENEMY, _isoTile[i].centerX, _isoTile[i].centerY);
			}
			if (_isoTile[i].name == CIVILIAN)
			{ // 에너미 생성은 여기서하고 오브젝트는 우리가 그려주면됨(유닛보다 나중에 그려줄거임. 가리도록)
				_um->createCivilian(ENEMY, _isoTile[i].centerX, _isoTile[i].centerY);
			}
			if (_isoTile[i].name == TEMPLAR)
			{ // 에너미 생성은 여기서하고 오브젝트는 우리가 그려주면됨(유닛보다 나중에 그려줄거임. 가리도록)
				_um->createTemplar(ENEMY, _isoTile[i].centerX, _isoTile[i].centerY);
			}
			if (_isoTile[i].name == BISHOP)
			{ // 에너미 생성은 여기서하고 오브젝트는 우리가 그려주면됨(유닛보다 나중에 그려줄거임. 가리도록)
				_um->createBishop(ENEMY, _isoTile[i].centerX, _isoTile[i].centerY);
			}
			//if (_isoTile[i].name == DIABLO)
			//{ // 에너미 생성은 여기서하고 오브젝트는 우리가 그려주면됨(유닛보다 나중에 그려줄거임. 가리도록)
			//	_um->createDiablo(ENEMY, _isoTile[i].centerX, _isoTile[i].centerY);
			//}
			//if (_isoTile[i].name == SKELETON)
			//{ // 에너미 생성은 여기서하고 오브젝트는 우리가 그려주면됨(유닛보다 나중에 그려줄거임. 가리도록)
			//	_um->createSkeleton(ENEMY, _isoTile[i].centerX, _isoTile[i].centerY);
			//}
			if (_isoTile[i].name == GHOST)
			{ // 에너미 생성은 여기서하고 오브젝트는 우리가 그려주면됨(유닛보다 나중에 그려줄거임. 가리도록)
				_um->createGhost(ENEMY, _isoTile[i].centerX, _isoTile[i].centerY);
			}
		}

		break;
	case STAGE2:
		file = CreateFile("stage2.map", GENERIC_READ, NULL, NULL,
			OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		ReadFile(file, _isoTile, sizeof(isoTile) * TILEX*TILEY, &read, NULL);
		CloseHandle(file);

		_gold = _isoTile[0].gold;
		for (int i = 0; i < TILEX * TILEY; ++i)
		{
			if (_isoTile[i].name == ZERGLING)
			{ // 에너미 생성은 여기서하고 오브젝트는 우리가 그려주면됨(유닛보다 나중에 그려줄거임. 가리도록)
				_um->createZergling(ENEMY, _isoTile[i].centerX, _isoTile[i].centerY);
			}
			if (_isoTile[i].name == MARINE)
			{ // 에너미 생성은 여기서하고 오브젝트는 우리가 그려주면됨(유닛보다 나중에 그려줄거임. 가리도록)
				_um->createMarine(ENEMY, _isoTile[i].centerX, _isoTile[i].centerY);
			}
			if (_isoTile[i].name == CIVILIAN)
			{ // 에너미 생성은 여기서하고 오브젝트는 우리가 그려주면됨(유닛보다 나중에 그려줄거임. 가리도록)
				_um->createCivilian(ENEMY, _isoTile[i].centerX, _isoTile[i].centerY);
			}
			if (_isoTile[i].name == TEMPLAR)
			{ // 에너미 생성은 여기서하고 오브젝트는 우리가 그려주면됨(유닛보다 나중에 그려줄거임. 가리도록)
				_um->createTemplar(ENEMY, _isoTile[i].centerX, _isoTile[i].centerY);
			}
			if (_isoTile[i].name == BISHOP)
			{ // 에너미 생성은 여기서하고 오브젝트는 우리가 그려주면됨(유닛보다 나중에 그려줄거임. 가리도록)
				_um->createBishop(ENEMY, _isoTile[i].centerX, _isoTile[i].centerY);
			}
			//if (_isoTile[i].name == DIABLO)
			//{ // 에너미 생성은 여기서하고 오브젝트는 우리가 그려주면됨(유닛보다 나중에 그려줄거임. 가리도록)
			//	_um->createDiablo(ENEMY, _isoTile[i].centerX, _isoTile[i].centerY);
			//}
			//if (_isoTile[i].name == SKELETON)
			//{ // 에너미 생성은 여기서하고 오브젝트는 우리가 그려주면됨(유닛보다 나중에 그려줄거임. 가리도록)
			//	_um->createSkeleton(ENEMY, _isoTile[i].centerX, _isoTile[i].centerY);
			//}
			if (_isoTile[i].name == GHOST)
			{ // 에너미 생성은 여기서하고 오브젝트는 우리가 그려주면됨(유닛보다 나중에 그려줄거임. 가리도록)
				_um->createGhost(ENEMY, _isoTile[i].centerX, _isoTile[i].centerY);
			}
		}

		break;
	case STAGE3:
		file = CreateFile("stage3.map", GENERIC_READ, NULL, NULL,
			OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		ReadFile(file, _isoTile, sizeof(isoTile) * TILEX*TILEY, &read, NULL);
		CloseHandle(file);

		_gold = _isoTile[0].gold;
		for (int i = 0; i < TILEX * TILEY; ++i)
		{
			if (_isoTile[i].name == ZERGLING)
			{ // 에너미 생성은 여기서하고 오브젝트는 우리가 그려주면됨(유닛보다 나중에 그려줄거임. 가리도록)
				_um->createZergling(ENEMY, _isoTile[i].centerX, _isoTile[i].centerY);
			}
			if (_isoTile[i].name == MARINE)
			{ // 에너미 생성은 여기서하고 오브젝트는 우리가 그려주면됨(유닛보다 나중에 그려줄거임. 가리도록)
				_um->createMarine(ENEMY, _isoTile[i].centerX, _isoTile[i].centerY);
			}
			if (_isoTile[i].name == CIVILIAN)
			{ // 에너미 생성은 여기서하고 오브젝트는 우리가 그려주면됨(유닛보다 나중에 그려줄거임. 가리도록)
				_um->createCivilian(ENEMY, _isoTile[i].centerX, _isoTile[i].centerY);
			}
			if (_isoTile[i].name == TEMPLAR)
			{ // 에너미 생성은 여기서하고 오브젝트는 우리가 그려주면됨(유닛보다 나중에 그려줄거임. 가리도록)
				_um->createTemplar(ENEMY, _isoTile[i].centerX, _isoTile[i].centerY);
			}
			if (_isoTile[i].name == BISHOP)
			{ // 에너미 생성은 여기서하고 오브젝트는 우리가 그려주면됨(유닛보다 나중에 그려줄거임. 가리도록)
				_um->createBishop(ENEMY, _isoTile[i].centerX, _isoTile[i].centerY);
			}
			//if (_isoTile[i].name == DIABLO)
			//{ // 에너미 생성은 여기서하고 오브젝트는 우리가 그려주면됨(유닛보다 나중에 그려줄거임. 가리도록)
			//	_um->createDiablo(ENEMY, _isoTile[i].centerX, _isoTile[i].centerY);
			//}
			//if (_isoTile[i].name == SKELETON)
			//{ // 에너미 생성은 여기서하고 오브젝트는 우리가 그려주면됨(유닛보다 나중에 그려줄거임. 가리도록)
			//	_um->createSkeleton(ENEMY, _isoTile[i].centerX, _isoTile[i].centerY);
			//}
			if (_isoTile[i].name == GHOST)
			{ // 에너미 생성은 여기서하고 오브젝트는 우리가 그려주면됨(유닛보다 나중에 그려줄거임. 가리도록)
				_um->createGhost(ENEMY, _isoTile[i].centerX, _isoTile[i].centerY);
			}
		}
		break;
	}
}
