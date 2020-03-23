#define Cell_length 50
#define PI (double)3.141592654
enum KOMATYPE { HU, KYOU, KEI, GIN, KIN, KAKU, HISYA, TOKIN, NARIKYOU, NARIKEI, NARIGIN, RYUMA, RYUOU, OU, KOMATYPE_MAX };
class Koma
{
private:
protected:
	typedef struct {
		unsigned int x;
		unsigned int y;
		double rota;
		double turn;
		unsigned int grhandle;
		unsigned int a;
	}KomaDraw;
	unsigned int mKeyNum_Koma = 0;
public:
	KomaDraw KomaDraw_Instance[KOMATYPE_MAX][20];
	void FuncKomaINIT();
	void ONE_Move_Q();
	void ONE_Move_W();
	void ONE_Move_E();
	void ONE_Move_A();
	void ONE_Move_S();
	void ONE_Move_D();
	void ONE_Move_Z();
	void ONE_Move_X();
	void FuncKomaTurn();
	void FuncKomaZahyoData();
};
class Cursor : public Koma
{
private:

public:

};
class Data : public Koma
{
private:
	typedef struct {
		unsigned int x;
		unsigned int y;
		double rota;
		double turn;
		unsigned int grhandle;
		unsigned int a;
		unsigned int* KomaZahyoData;
		unsigned int* NumTeData;
		unsigned int* MotigomaTurn_0Data;
		unsigned int* MotigomaTurn_PIData;
		unsigned int* OuteNumData;
	}KomaData;
public:
	KomaData KomaData_Instance[KOMATYPE_MAX][20];
};
class MotiKoma : public Koma
{
private:
	KomaDraw MotiKoma_Instance[KOMATYPE_MAX][20];

public:
};
void Koma::ONE_Move_W() {}
void Koma::ONE_Move_S() {}
void Koma::ONE_Move_A() {}
void Koma::ONE_Move_D() {}
void Koma::ONE_Move_Q() {}
void Koma::ONE_Move_E() {}
void Koma::ONE_Move_Z() {}
void Koma::ONE_Move_X() {}
Koma KomaClass_Instance[KOMATYPE_MAX][20];
Cursor CursorClass_Instance;
Data DataClass_Instance[KOMATYPE_MAX][20];