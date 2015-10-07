
struct Stock
{
	int price;
	int company;
	
	Stock *next;
	Stock *prev;
};


void InitStock();

Stock *InsertStock(Stock *Target,Stock *aStock);

bool DeleteStock(Stock *Target);

void AppendStock(Stock);

Stock *FindStock(int);

void UnInitStock();
