#include "cz2kboard.h"
#include "csdlsprite.h"
#include "canimatorscale.h"
#include <string.h>
#include <iostream>
#include <random>

CZ2kBoard::CZ2kBoard(CBlitter *blitter)
{
	std::string f;
	CSDLSprite *s;

	//this sprite is used for the pop animation
	f = "./data/2.bmp";
	s = new CSDLSprite(-1, dynamic_cast<CSDLBlitter*>(blitter));
	s->LoadImage(f);
	s->SetAnchorPos(CDrawable::AnchorPos::CENTER);
	Sprites_.insert(std::pair<int, CSDLSprite*>(-1, s));

	f = "./data/0.bmp";
	s = new CSDLSprite(0, dynamic_cast<CSDLBlitter*>(blitter));
	s->LoadImage(f);
	Sprites_.insert(std::pair<int, CSDLSprite*>(0, s));

	f = "./data/2.bmp";
	s = new CSDLSprite(2, dynamic_cast<CSDLBlitter*>(blitter));
	s->LoadImage(f);
	Sprites_.insert(std::pair<int, CSDLSprite*>(2, s));

	f = "./data/4.bmp";
	s = new CSDLSprite(4, dynamic_cast<CSDLBlitter*>(blitter));
	s->LoadImage(f);
	Sprites_.insert(std::pair<int, CSDLSprite*>(4, s));

	f = "./data/8.bmp";
	s = new CSDLSprite(8, dynamic_cast<CSDLBlitter*>(blitter));
	s->LoadImage(f);
	Sprites_.insert(std::pair<int, CSDLSprite*>(8, s));

	f = "./data/16.bmp";
	s = new CSDLSprite(16, dynamic_cast<CSDLBlitter*>(blitter));
	s->LoadImage(f);
	Sprites_.insert(std::pair<int, CSDLSprite*>(16, s));
	
	f = "./data/32.bmp";
	s = new CSDLSprite(32, dynamic_cast<CSDLBlitter*>(blitter));
	s->LoadImage(f);
	Sprites_.insert(std::pair<int, CSDLSprite*>(32, s));
	
	f = "./data/64.bmp";
	s = new CSDLSprite(64, dynamic_cast<CSDLBlitter*>(blitter));
	s->LoadImage(f);
	Sprites_.insert(std::pair<int, CSDLSprite*>(64, s));
	
	f = "./data/128.bmp";
	s = new CSDLSprite(128, dynamic_cast<CSDLBlitter*>(blitter));
	s->LoadImage(f);
	Sprites_.insert(std::pair<int, CSDLSprite*>(128, s));
	
	f = "./data/256.bmp";
	s = new CSDLSprite(256, dynamic_cast<CSDLBlitter*>(blitter));
	s->LoadImage(f);
	Sprites_.insert(std::pair<int, CSDLSprite*>(256, s));
	
	f = "./data/512.bmp";
	s = new CSDLSprite(512, dynamic_cast<CSDLBlitter*>(blitter));
	s->LoadImage(f);
	Sprites_.insert(std::pair<int, CSDLSprite*>(512, s));
	
	f = "./data/1024.bmp";
	s = new CSDLSprite(1024, dynamic_cast<CSDLBlitter*>(blitter));
	s->LoadImage(f);
	Sprites_.insert(std::pair<int, CSDLSprite*>(1024, s));
	
	f = "./data/2048.bmp";
	s = new CSDLSprite(2048, dynamic_cast<CSDLBlitter*>(blitter));
	s->LoadImage(f);
	Sprites_.insert(std::pair<int, CSDLSprite*>(2048, s));

	AddRandom();
}

CZ2kBoard::~CZ2kBoard()
{
	for(auto i: Sprites_)
		delete i.second;
}

void CZ2kBoard::Draw()
{
	for(int i = 0; i < GetSize()*GetSize(); i++)
	{
		int row = i / GetSize();
		int col = i % GetSize();
		int val = GetAt(i);

		DrawTile(col, row, val);
	}
	
	auto itn = NewTiles_.begin();
	while(itn != NewTiles_.end())
	{
		auto &i = *itn;

		int row = i.pos / GetSize();
		int col = i.pos % GetSize();

		std::cout << "new tile " << i.val << " at " << col << " " << row << std::endl;
		
		auto it = Sprites_.find(-1); //-1 is the pop sprite
		CSDLSprite *s = (*it).second;
		s->SetPos(col * 128, row * 128);

		if(Scaler_)
			delete Scaler_;

		Scaler_ = new CAnimatorScale(s, {0.7, 0.8, 0.9, 1, 1.15, 1.3, 1.15, 1});
		Scaler_->StartAnimation();

		SetAt(i.pos, i.val);
		itn = NewTiles_.erase(itn);
	}
	
	if(Scaler_)
		Scaler_->GetDrawable()->Draw();
}

void CZ2kBoard::DrawTile(int col, int row, int val)
{
		auto it = Sprites_.find(val);
		CSDLSprite *s = (*it).second;
		if(s)
			s->DrawAt(col * 128, row * 128);
		else
			std::cout << "sprite for " << val << " not found" << std::endl;
}

void CZ2kBoard::Tick(int usec __attribute__((__unused__)))
{
	if(Scaler_ && !Scaler_->isRunning())
	{
		delete Scaler_;
		Scaler_ = nullptr;
	}

	if(Scaler_)
		Scaler_->Tick(usec);
}

int CZ2kBoard::CountEmpty()
{
	int count = 0;
	for(int i = 0; i < GetSize()*GetSize(); ++i)
	{
		if(GetAt(i) == 0)
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
	while((z < rnd) && (i < GetSize()*GetSize()))
	{
		if(GetAt(i) == 0)
			z++;
		i++;
	}
	while(GetAt(i) != 0)
		i++;

	assert(i < GetSize()*GetSize());
	assert(GetAt(i) == 0);

	//SetAt(i, 2);
	tNewTile t;
	t.pos = i;
	NewTiles_.push_back(t);
	return true;
}

bool CZ2kBoard::MoveRight()
{
	bool needadd = false;
	
	//summ up
	for(int row = 0; row < GetSize(); ++row)
	{
		for(int col = GetSize()-1; col > 0; --col)
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
	for(int row = 0; row < GetSize(); ++row)
	{
		for(int col = GetSize()-1; col > 0; --col)
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
	for(int row = 0; row < GetSize(); ++row)
	{
		for(int col = 0; col < GetSize()-1; ++col)
		{
			if(GetAt(col, row) > 0)
			{
				int i = col + 1;
				while((i < GetSize()-1) && (GetAt(i, row) == 0))
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
	for(int row = 0; row < GetSize(); ++row)
	{
		for(int col = 0; col < GetSize()-1; ++col)
		{
			if(GetAt(col, row) == 0)
			{
				int i = col+1;
				while((i < GetSize()-1) && (GetAt(i, row) == 0))
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
	for(int col = 0; col < GetSize(); ++col)
	{
		for(int row = 0; row < GetSize()-1; ++row)
		{
			if(GetAt(col, row) > 0)
			{
				int i = row + 1;
				while((i < GetSize()-1) && (GetAt(col, i) == 0))
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
	for(int col = 0; col < GetSize(); ++col)
	{
		for(int row = 0; row < GetSize()-1; ++row)
		{
			if(GetAt(col, row) == 0)
			{
				int i = row+1;
				while((i < GetSize()-1) && (GetAt(col, i) == 0))
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
	for(int col = 0; col < GetSize(); ++col)
	{
		for(int row = GetSize()-1; row > 0; --row)
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
	for(int col = 0; col < GetSize(); ++col)
	{
		for(int row = GetSize()-1; row > 0; --row)
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
