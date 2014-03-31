#ifndef __CZ2KBOARD_H__
#define __CZ2KBOARD_H__

#include <map>

class CBlitter;
class CSDLSprite;

#define CZ2K_BOARD_SIZE 4

class CZ2kBoard
{
public:
	CZ2kBoard();
	~CZ2kBoard() {;}
	
	void Draw(std::map<int, CSDLSprite*> &Sprites_);
	
	bool MoveRight();
	bool MoveLeft();
	bool MoveUp();
	bool MoveDown();

	inline int GetAt(int col, int row) {return Data_[row * CZ2K_BOARD_SIZE + col];}
	inline void SetAt(int col, int row, int val) {Data_[row * CZ2K_BOARD_SIZE + col] = val;}
	
private:
	int Data_[CZ2K_BOARD_SIZE * CZ2K_BOARD_SIZE] = {0};

	bool AddRandom();
	int CountEmpty();
};

#endif
