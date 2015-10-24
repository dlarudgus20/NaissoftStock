
struct Stock
{
	int price;
	int company;
	
	Stock *next;
	Stock *prev;
};

extern Stock *head, *now, tmp;

void InitStock();

Stock *InsertStock(Stock *Target,Stock *aStock);

bool DeleteStock(Stock *Target);

void AppendStock(Stock);

Stock *FindStock(int);

void UnInitStock();
