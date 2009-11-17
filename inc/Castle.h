#define BLACK	1
#define WHITE	-1

class Piece {
public:
	Piece();
	~Piece();
	void operator =();
	Set<Square> Moves(Board * board);	// Return squares for valid moves
private:
	string type;
	int color;
	int direction;
	void Init();
	void Copy();
	void Clear();
};
