#include "cz2kboard.h"
#include "csdlsprite.h"
#include <string.h>
#include <iostream>
#include <random>

CZ2kBoard::CZ2kBoard()
{
	memset(Data_, 0, sizeof(int) * CZ2K_BOARD_SIZE * CZ2K_BOARD_SIZE);
}

void CZ2kBoard::Draw(std::map<int, CSDLSprite*> &Sprites_)
{
	for(int i = 0; i < CZ2K_BOARD_SIZE * CZ2K_BOARD_SIZE; i++)
	{
		int row = i / CZ2K_BOARD_SIZE;
		int col = i % CZ2K_BOARD_SIZE;
		int val = Data_[i];
		
		CSDLSprite *s = Sprites_.at(val);
		if(s)
		{
			s->SetPos(col * 128, row * 96);
			s->Draw();
		}
		else
			std::cout << "sprite for " << val << " not found" << std::endl;
	}
}

int CZ2kBoard::CountEmpty()
{
	int count = 0;
	for(int i : Data_)
	{
		if(i == 0)
			count++;
	}
	return count;
}

bool CZ2kBoard::AddRandom()
{
	int cnt = CountEmpty();
	if(cnt == 0)
		return false;
	
	std::random_device rd;
	int64_t rnd = (rd() - rd.min()) % cnt;
	
	//std::cout << "random: " << rnd << ", " << cnt << ", " << rd.min() << ", " << rd.max() << std::endl;
	
	int i = 0;
	int z = 0;
	while((z < rnd) && (i < CZ2K_BOARD_SIZE*CZ2K_BOARD_SIZE))
	{
		if(Data_[i] == 0)
			z++;
		i++;
	}
	while(Data_[i] != 0)
		i++;

	assert(i < CZ2K_BOARD_SIZE*CZ2K_BOARD_SIZE);
	assert(Data_[i] == 0);

	Data_[i] = 1;
	
	return true;
}

bool CZ2kBoard::MoveRight()
{
	int cnt = CountEmpty();
	if(cnt == 0)
		return false;
	
	AddRandom();
	
	return true;
}

bool CZ2kBoard::MoveLeft()
{
	int cnt = CountEmpty();
	if(cnt == 0)
		return false;

	AddRandom();

	return true;
}

bool CZ2kBoard::MoveUp()
{
	int cnt = CountEmpty();
	if(cnt == 0)
		return false;

	AddRandom();

	return true;
}

bool CZ2kBoard::MoveDown()
{
	int cnt = CountEmpty();
	if(cnt == 0)
		return false;

	AddRandom();

	return true;
}
