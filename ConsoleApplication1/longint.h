class LongInt 
{
	protected:
		static const int N = 1000;
		int number[N] = {};
		int n = 1;
		int base = 10;
		static LongInt* (*multiply) (LongInt, LongInt);
	public:
		LongInt() = default;
		LongInt(int n0, int base0, int seed);

		int getN();
		int getBase();
		int getDigit(int i);
		void setN(int n0);
		void setBase(int base0);
		void setDigit(int i, int x);
		static void setMultiply(LongInt* (*multiply0) (LongInt, LongInt));

		LongInt& operator= (LongInt &a);
		LongInt* operator+ (LongInt a);
		LongInt* operator* (LongInt a);

		LongInt* basicMultiply(LongInt a);
		LongInt* multiplyByDigit(int k);
		LongInt* multiplyByBasePow(int k);


		LongInt* getFirst(int k);
		LongInt* getWithoutFirst(int k);

		void output();
		void checkLastDigit();

		static const int notABigNumber = 5;
};

