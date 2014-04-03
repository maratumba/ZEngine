#include "cz2kboard.h"
#include "csdlsprite.h"
#include <string.h>
#include <iostream>
#include <random>

CZ2kBoard::CZ2kBoard()
{
	memset(Data_, 0, sizeof(int) * CZ2K_BOARD_SIZE * CZ2K_BOARD_SIZE);
	
	AddRandom();
}

void CZ2kBoard::Draw(std::map<int, CSDLSprite*> &Sprites_)
{
	for(int i = 0; i < CZ2K_BOARD_SIZE * CZ2K_BOARD_SIZE; i++)
	{
		int row = i / CZ2K_BOARD_SIZE;
		int col = i % CZ2K_BOARD_SIZE;
		int val = Data_[i];
		
		auto it = Sprites_.find(val);
		CSDLSprite *s = (*it).second;
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

	Data_[i] = 2;
	
	return true;
}

bool CZ2kBoard::MoveRight()
{
	bool needadd = false;
	
	//summ up
	for(int row = 0; row < CZ2K_BOARD_SIZE; ++row)
	{
		for(int col = CZ2K_BOARD_SIZE-1; col > 0; --col)
		{
			if(GetAt(col, row) > 0)
			{
				int i = col-1;
				while((i > 0) && (GetAt(i, row) == 0))
					--i;
				
				if(GetAt(col, row) == GetAt(i, row))
				{
					int val = GetAt(col, row);
					SetAt(col, row, val*2);
					SetAt(i, row, 0);
					
					needadd = true;
				}
			}
		}
	}
	
	//push
	for(int row = 0; row < CZ2K_BOARD_SIZE; ++row)
	{
		for(int col = CZ2K_BOARD_SIZE-1; col > 0; --col)
		{
			if(GetAt(col, row) == 0)
			{
				int i = col-1;
				while((i > 0) && (GetAt(i, row) == 0))
					--i;
				
				if(GetAt(i, row) != 0)
				{
					int val = GetAt(i, row);
					SetAt(col, row, val);
					SetAt(i, row, 0);
					
					needadd = true;
				}
			}
		}
	}
	
	bool rvl = true;
	if(needadd)
		rvl = AddRandom();
	
	return rvl;
}

bool CZ2kBoard::MoveLeft()
{
	bool needadd = false;
	
	//summ up
	for(int row = 0; row < CZ2K_BOARD_SIZE; ++row)
	{
		for(int col = 0; col < CZ2K_BOARD_SIZE-1; ++col)
		{
			if(GetAt(col, row) > 0)
			{
				int i = col + 1;
				while((i < CZ2K_BOARD_SIZE-1) && (GetAt(i, row) == 0))
					++i;
				
				if(GetAt(col, row) == GetAt(i, row))
				{
					int val = GetAt(col, row);
					SetAt(col, row, val*2);
					SetAt(i, row, 0);
					
					needadd = true;
				}
			}
		}
	}

	//push
	for(int row = 0; row < CZ2K_BOARD_SIZE; ++row)
	{
		for(int col = 0; col < CZ2K_BOARD_SIZE-1; ++col)
		{
			if(GetAt(col, row) == 0)
			{
				int i = col+1;
				while((i < CZ2K_BOARD_SIZE-1) && (GetAt(i, row) == 0))
					++i;
				
				if(GetAt(i, row) != 0)
				{
					int val = GetAt(i, row);
					SetAt(col, row, val);
					SetAt(i, row, 0);
					
					needadd = true;
				}
			}
		}
	}

	bool rvl = true;
	if(needadd)
		rvl = AddRandom();
	
	return rvl;
}

bool CZ2kBoard::MoveUp()
{
	bool needadd = false;
	
	//summ up
	for(int col = 0; col < CZ2K_BOARD_SIZE; ++col)
	{
		for(int row = 0; row < CZ2K_BOARD_SIZE-1; ++row)
		{
			if(GetAt(col, row) > 0)
			{
				int i = row + 1;
				while((i < CZ2K_BOARD_SIZE-1) && (GetAt(col, i) == 0))
					++i;
				
				if(GetAt(col, row) == GetAt(col, i))
				{
					int val = GetAt(col, row);
					SetAt(col, row, val*2);
					SetAt(col, i, 0);
					
					needadd = true;
				}
			}
		}
	}

	//push
	for(int col = 0; col < CZ2K_BOARD_SIZE; ++col)
	{
		for(int row = 0; row < CZ2K_BOARD_SIZE-1; ++row)
		{
			if(GetAt(col, row) == 0)
			{
				int i = row+1;
				while((i < CZ2K_BOARD_SIZE-1) && (GetAt(col, i) == 0))
					++i;
				
				if(GetAt(col, i) != 0)
				{
					int val = GetAt(col, i);
					SetAt(col, row, val);
					SetAt(col, i, 0);
					
					needadd = true;
				}
			}
		}
	}

	bool rvl = true;
	if(needadd)
		rvl = AddRandom();
	
	return rvl;
}

bool CZ2kBoard::MoveDown()
{
	bool needadd = false;
	
	//summ up
	for(int col = 0; col < CZ2K_BOARD_SIZE; ++col)
	{
		for(int row = CZ2K_BOARD_SIZE-1; row > 0; --row)
		{
			if(GetAt(col, row) > 0)
			{
				int i = row-1;
				while((i > 0) && (GetAt(col, i) == 0))
					--i;
				
				if(GetAt(col, row) == GetAt(col, i))
				{
					int val = GetAt(col, row);
					SetAt(col, row, val*2);
					SetAt(col, i, 0);
					
					needadd = true;
				}
			}
		}
	}

		//push
	for(int col = 0; col < CZ2K_BOARD_SIZE; ++col)
	{
		for(int row = CZ2K_BOARD_SIZE-1; row > 0; --row)
		{
			if(GetAt(col, row) == 0)
			{
				int i = row-1;
				while((i > 0) && (GetAt(col, i) == 0))
					--i;
				
				if(GetAt(col, i) != 0)
				{
					int val = GetAt(col, i);
					SetAt(col, row, val);
					SetAt(col, i, 0);
					
					needadd = true;
				}
			}
		}
	}
	
	bool rvl = true;
	if(needadd)
		rvl = AddRandom();
	
	return rvl;
}
