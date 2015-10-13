#ifndef __CZ2KBOARD_H__
#define __CZ2KBOARD_H__

#include <map>
#include <list>

class CBlitter;
class CSDLSprite;
class CAnimatorScale;

#define CZ2K_BOARD_SIZE 4

class CZ2kBoard
{
public:
	CZ2kBoard(CBlitter *blitter);
	~CZ2kBoard();
	
	void Draw();
	void Tick(int usec);
	
	bool MoveRight();
	bool MoveLeft();
	bool MoveUp();
	bool MoveDown();

	inline int GetAt(int col, int row) {return GetAt(row * GetSize() + col);}
	inline void SetAt(int col, int row, int val) {SetAt(row * GetSize() + col, val);}
	
	inline const int GetSize() {return (const int)CZ2K_BOARD_SIZE;}

private:
	struct tNewTile
	{
		int pos = 0;
		int val = 2;
	};

	inline int GetAt(int pos) {return Data_[pos];}
	inline void SetAt(int pos, int val) {Data_[pos] = val;}

	void DrawTile(int col, int row, int val);
	/**
	 * Adds one new number 2 tile to the board at a random place
	 */
	bool AddRandom();
	int CountEmpty();

	int Data_[CZ2K_BOARD_SIZE * CZ2K_BOARD_SIZE] = {0};
	std::list<tNewTile> NewTiles_;
	CAnimatorScale *Scaler_ = nullptr;
	std::map<int, CSDLSprite*> Sprites_;
};

#endif
