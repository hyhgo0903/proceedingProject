#include "stdafx.h"
#include "collision.h"


void collision::yoonghoInit()
{
}

void collision::yoonghoUpdate()
{ // 아무도 잡히지 않았으면 풀음
	bool check = false;
	for (int i = 0; i < _em->getVEnemy().size(); ++i)
	{
		if (_pl->getEnumState() != GRAB) break;
		if (_em->getVEnemy()[i]->getState() == E_GRAB)
		{
			check = true;
			break;
		}
	}
	if (!check && _pl->getEnumState() == GRAB) _pl->setState(IDLE);
	
	// 잡거나 잡기스윙이 아니면 풀림
	if (_pl->getEnumState() != GRAB && _pl->getEnumState() != GRABSWING)
	{
		for (int i = 0; i < _em->getVEnemy().size(); ++i)
		{
			if (_em->getVEnemy()[i]->getState() == E_GRAB)
			{
				_em->getVEnemy()[i]->setState(E_WALK);
			}
		}
	}


	// ############ 쓰레기통 제외한 오브젝트라면 진로방해하는 기능 ######################
	//RECT temp1;	
	//RECT temp2 = _pl->getShadow();// 50은 나중에 플레이어 너비수정하면 변경할것
	//for (int i = 0; i < _sm->getVObject().size(); ++i)
	//{
	//	if (_sm->getVObject()[i]->getId() != 0) continue; // 의자랑 임의의 렉트만(장애물) 감지
	//	RECT temp3 = _sm->getVObject()[i]->getRect();
	//	int x = (temp3.left + temp3.right) / 2;
	//	int y = (temp3.bottom+ temp3.top)/2;
	//	temp3 = RectMakeCenter(x + 30, y + 90, 130, 100);
	//	if (IntersectRect(&temp1, &temp2, &temp3))
	//	{
	//		if (temp1.right - temp1.left > temp1.bottom - temp1.top)
	//		{//위아래로 부딪
	//			if (temp2.top < temp1.top)
	//			{ // 아래로 부딪
	//				_pl->getFlyY() -= temp1.bottom - temp1.top;
	//				_pl->getGroundY() -= temp1.bottom - temp1.top;
	//			}
	//			else
	//			{ // 위로부딪
	//				_pl->getFlyY() += temp1.bottom - temp1.top;
	//				_pl->getGroundY() += temp1.bottom - temp1.top;
	//			}
	//		}
	//		else // 좌우로 부딪
	//		{
	//			if (temp2.left < temp1.left)
	//			{ // 왼쪽으로
	//				_pl->getFlyX() -= temp1.right - temp1.left;
	//				_pl->getGroundX() -= temp1.right - temp1.left;
	//			}
	//			else
	//			{ // 위로부딪
	//				_pl->getFlyX() += temp1.right - temp1.left;
	//				_pl->getGroundX() += temp1.right - temp1.left;
	//			}
	//		}
	//	}
	//}
}

void collision::yoonghoRender()
{
}
