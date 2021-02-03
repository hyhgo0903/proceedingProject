#include "stdafx.h"
#include "mapTool.h"

//얘는 마우스랑 오브젝트의 샘플렉트의 충돌 + 어떤 메뉴가 열려있는지 검사해서 결과값을 주는거에요
void mapTool::ptInObj()
{
	if (PtInRect(&_tree1, _cameraPtMouse) && _menuNum == TWO)	_objName = TREE1;
	else if (PtInRect(&_tree2, _cameraPtMouse) && _menuNum == TWO)	_objName = TREE2;
	else if (PtInRect(&_tree3, _cameraPtMouse) && _menuNum == TWO)	_objName = TREE3;
	else if (PtInRect(&_tree4, _cameraPtMouse) && _menuNum == TWO)	_objName = TREE4;
	else if (PtInRect(&_tree5, _cameraPtMouse) && _menuNum == TWO)	_objName = TREE5;
	else if (PtInRect(&_playerFlagRc, _cameraPtMouse) && _menuNum == TWO)	_objName = PLAYERFLAG;
	else if (PtInRect(&_enemyFlagRc, _cameraPtMouse) && _menuNum == TWO)	_objName = ENEMYFLAG;
	else if (PtInRect(&_icZergling, _cameraPtMouse) && _menuNum == THREE)	_objName = ZERGLING;
	else if (PtInRect(&_icMarine, _cameraPtMouse) && _menuNum == THREE)		_objName = MARINE;
	else if (PtInRect(&_icCivilian, _cameraPtMouse) && _menuNum == THREE)	_objName = CIVILIAN;
	else if (PtInRect(&_icTemplar, _cameraPtMouse) && _menuNum == THREE)	_objName = TEMPLAR;
	else if (PtInRect(&_icBishop, _cameraPtMouse) && _menuNum == THREE)		_objName = BISHOP;
	else if (PtInRect(&_icDiablo, _cameraPtMouse) && _menuNum == THREE)		_objName = DIABLO;
	else if (PtInRect(&_icSkeleton, _cameraPtMouse) && _menuNum == THREE)	_objName = SKELETON;
	else if (PtInRect(&_icGhost, _cameraPtMouse) && _menuNum == THREE)		_objName = GHOST;
}

//얘는 선택된 오브젝트가 어떤건지 판단해서 선택한 타일에 그 오브젝트 값을 부여해주는겁니다
void mapTool::createObj()
{
	//여기서 이제 담아둔 오브젝트 이름을 부여해서 타일위에 나무뜨게할꺼임
	if (!_menuInPt)
	{
		if (_objDelOn)
		{
			if (_isoTile[_pickingPt.y * TILEX + _pickingPt.x].name == PLAYERFLAG) _playerTile = -1;
			if (_isoTile[_pickingPt.y * TILEX + _pickingPt.x].name == ENEMYFLAG) _enemyTile = -1;
			_isoTile[_pickingPt.y * TILEX + _pickingPt.x].name = NONE;
			InvalidateRect(_hWnd, NULL, false);
		}
		else if (_objName == TREE1 && !_objDelOn)
		{
			_isoTile[_pickingPt.y * TILEX + _pickingPt.x].name = TREE1;
			_isoTile[_pickingPt.y * TILEX + _pickingPt.x].MUM = UNMOVE;
			InvalidateRect(_hWnd, NULL, false);
		}
		else if (_objName == TREE2 && !_objDelOn)
		{
			_isoTile[_pickingPt.y * TILEX + _pickingPt.x].name = TREE2;
			_isoTile[_pickingPt.y * TILEX + _pickingPt.x].MUM = UNMOVE;
			InvalidateRect(_hWnd, NULL, false);
		}
		else if (_objName == TREE3 && !_objDelOn)
		{
			_isoTile[_pickingPt.y * TILEX + _pickingPt.x].name = TREE3;
			_isoTile[_pickingPt.y * TILEX + _pickingPt.x].MUM = UNMOVE;
			InvalidateRect(_hWnd, NULL, false);
		}
		else if (_objName == TREE4 && !_objDelOn)
		{
			_isoTile[_pickingPt.y * TILEX + _pickingPt.x].name = TREE4;
			_isoTile[_pickingPt.y * TILEX + _pickingPt.x].MUM = UNMOVE;
			InvalidateRect(_hWnd, NULL, false);
		}
		else if (_objName == TREE5 && !_objDelOn)
		{
			_isoTile[_pickingPt.y * TILEX + _pickingPt.x].name = TREE5;
			_isoTile[_pickingPt.y * TILEX + _pickingPt.x].MUM = UNMOVE;
			InvalidateRect(_hWnd, NULL, false);
		}
		else if (_objName == PLAYERFLAG && !_objDelOn)
		{
			_isoTile[_playerTile].name = NONE;
			_isoTile[_pickingPt.y * TILEX + _pickingPt.x].name = PLAYERFLAG;
			_playerTile = _pickingPt.y * TILEX + _pickingPt.x;
			InvalidateRect(_hWnd, NULL, false);
		}
		else if (_objName == ENEMYFLAG && !_objDelOn)
		{
			_isoTile[_enemyTile].name = NONE;
			_isoTile[_pickingPt.y * TILEX + _pickingPt.x].name = ENEMYFLAG;
			_enemyTile = _pickingPt.y * TILEX + _pickingPt.x;
			InvalidateRect(_hWnd, NULL, false);
		}
		else if (_objName == ZERGLING && !_objDelOn && _isoTile[_pickingPt.y * TILEX + _pickingPt.x].MUM != UNMOVE)
		{
			_isoTile[_pickingPt.y * TILEX + _pickingPt.x].name = ZERGLING;
			InvalidateRect(_hWnd, NULL, false);
		}
		else if (_objName == MARINE && !_objDelOn && _isoTile[_pickingPt.y * TILEX + _pickingPt.x].MUM != UNMOVE)
		{
			_isoTile[_pickingPt.y * TILEX + _pickingPt.x].name = MARINE;
			InvalidateRect(_hWnd, NULL, false);
		}
		else if (_objName == CIVILIAN && !_objDelOn && _isoTile[_pickingPt.y * TILEX + _pickingPt.x].MUM != UNMOVE)
		{
			_isoTile[_pickingPt.y * TILEX + _pickingPt.x].name = CIVILIAN;
			InvalidateRect(_hWnd, NULL, false);
		}
		else if (_objName == TEMPLAR && !_objDelOn && _isoTile[_pickingPt.y * TILEX + _pickingPt.x].MUM != UNMOVE)
		{
			_isoTile[_pickingPt.y * TILEX + _pickingPt.x].name = TEMPLAR;
			InvalidateRect(_hWnd, NULL, false);
		}
		else if (_objName == BISHOP && !_objDelOn && _isoTile[_pickingPt.y * TILEX + _pickingPt.x].MUM != UNMOVE)
		{
			_isoTile[_pickingPt.y * TILEX + _pickingPt.x].name = BISHOP;
			InvalidateRect(_hWnd, NULL, false);
		}
		//이미지가없음 아직
		//else if (_objName == DIABLO && !_objDelOn)
		//{
		//	_isoTile[_pickingPt.y * TILEX + _pickingPt.x].name = DIABLO;
		//	InvalidateRect(_hWnd, NULL, false);
		//}
		//else if (_objName == SKELETON && !_objDelOn)
		//{
		//	_isoTile[_pickingPt.y * TILEX + _pickingPt.x].name = SKELETON;
		//	InvalidateRect(_hWnd, NULL, false);
		//}
		else if (_objName == GHOST && !_objDelOn && _isoTile[_pickingPt.y * TILEX + _pickingPt.x].MUM != UNMOVE)
		{
			_isoTile[_pickingPt.y * TILEX + _pickingPt.x].name = GHOST;
			InvalidateRect(_hWnd, NULL, false);
		}
	}
}