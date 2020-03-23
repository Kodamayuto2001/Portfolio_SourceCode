//
///*必要なヘッダーファイルのインクルード*/
//#include "DxLib.h"
//
///*シンボル定義及びマクロ*/
//#define WINDOW_WIDTH  640
//#define WINDOW_HEIGHT 480
//#define SHOGI_BOARD_HEIGHT 9
//#define SHOGI_BOARD_WIDTH 9
//
///*将棋盤のの縦横サイズを小さいほうに合わせる*/
//int FuncCompare() {
//	if (WINDOW_WIDTH > WINDOW_HEIGHT) {
//		return (int)WINDOW_WIDTH;
//	}
//	else {
//		return (int)WINDOW_HEIGHT;
//	}
//}
//
///*将棋盤１つのセルあたり何ピクセルか計算する関数(余りも計算)*/
//int CELL_LENGTH_CALCULATION(int length, int* surplus) {
//	int num1;/*cellの一辺の長さ*/
//	num1 = length / 90;
//	num1 = num1 * 10;
//
//	/*将棋盤四辺の長さのあまり*/
//	/*例外がスローされました:書き込みアクセス違反。surplus が nullptr でした */
//	*surplus = length % 90;
//	*surplus = *surplus / 2;
//
//	return num1;
//}
//
//int Key[256]; // キーが押されているフレーム数を格納する
//int gpUpdateKey() {
//	char tmpKey[256]; // 現在のキーの入力状態を格納する
//	GetHitKeyStateAll(tmpKey); // 全てのキーの入力状態を得る
//	for (int i = 0; i < 256; i++) {
//		if (tmpKey[i] != 0) { // i番のキーコードに対応するキーが押されていたら
//			Key[i]++;     // 加算
//		}
//		else {              // 押されていなければ
//			Key[i] = 0;   // 0にする
//		}
//	}
//	return 0;
//}
//
///*将棋盤9*9と座標格納用変数を関連付ける*/
//class Koma
//{
//public:
//	void CELL_XY(int x, int y);/*セット用関数*/
//	void CellCalc();/*セット用関数*/
//	void DBox();/*描画用関数*/
//private:
//	int x, y;//座標格納用変数
//	int cell[SHOGI_BOARD_HEIGHT - 1][SHOGI_BOARD_WIDTH - 1];/*座標格納用配列*/
//	int cell_x_start;
//	int cell_y_start;
//	int cell_x_end;
//	int cell_y_end;
//};
///*DrawBoxように計算して変数を保存*/
//void Koma::CellCalc() {
//	cell_x_start = 15 + 50 * x;
//	cell_y_start = 15 + 50 * y;
//	cell_x_end = 65 + 50 * x;
//	cell_y_end = 65 + 50 * y;
//}
///*今の将棋盤9*9の中のを取得*/
//void Koma::CELL_XY(int x, int y) {
//	Koma::x = x;
//	Koma::y = y;
//}
//
//void Koma::DBox() {
//	DrawBox(cell_x_start, cell_y_start, cell_x_end, cell_y_end, GetColor(255, 255, 255), FALSE);
//}
//
///*メイン関数*/
//int WINAPI WinMain(HINSTANCE hInstance,
//	HINSTANCE hPrevInstance,
//	LPSTR lpCmdLine,
//	int nCmdShow)
//{
//	ChangeWindowMode(TRUE);
//	DxLib_Init();
//	SetDrawScreen(DX_SCREEN_BACK);
//
//	/*関数FuncCompareの戻り値を将棋盤の縦横サイズの定数にする*/
//	const int SYOGI_BOARD = FuncCompare();
//
//	/*将棋盤9*9の1つのセルが占めるピクセル数*/ /*アクセス違反*/
//	const int CELL_LENGTH = CELL_LENGTH_CALCULATION(SYOGI_BOARD, (int*)0);
//
//	/*余りを求める*/
//	int SURPLUS;
//	CELL_LENGTH_CALCULATION(0, &SURPLUS);
//
//	/*インスタンス化する*/
//	Koma koma;
//	int x = 0, y = 0;
//	while (ScreenFlip() == 0 &&
//		ProcessMessage() == 0 &&
//		ClearDrawScreen() == 0 &&
//		gpUpdateKey() == 0)
//	{
//		koma.CELL_XY(x, y);
//		koma.CellCalc();
//		koma.DBox();
//	}
//	return 0;
//}
//
//
//

#include "DxLib.h"
#include<windowsx.h>/*ファイルを開く用ヘッダ*/
#include"resource.h"

#define WINDOW_WIDTH  (unsigned const int)640
#define WINDOW_HEIGHT (unsigned const int)480
#define PI (double)3.141592654
// 読み込むファイルの総数
#define FILENUM 100
// ゲージの幅
#define GAUGEWIDTH 200
//将棋ボード
#define SHOGI_BOARD_HEIGHT 9
#define SHOGI_BOARD_WIDTH 9
#define START_BUTTON 2
#define SHOGI_BOARD_SIZE 400

// 画像ハンドル
static int GrHandle[FILENUM];

// 読み込んでいる画像の番号
static int LoadingFile;

WNDPROC dxWndProc;

//メインウィンドウのハンドル
HWND hMainWnd;

//インスタンスハンドルを格納するグローバル変数
HINSTANCE hInst;

//画像ハンドルの初期値は-1(＝MyOpenでのエラー値)
static int gHandle = -1;

static int x = 320, vec = 5;
static int Key[256]; // キーが押されているフレーム数を格納する
static unsigned int KomaMove_x = 130;
static unsigned int KomaMove_y = 50;
static double Turn = 0;
static unsigned int CursorMove_x = 130;
static unsigned int CursorMove_y = 50;
static unsigned int Enter_num = 0;
static unsigned int SelectNum = 0; // 現在の選択番号
static unsigned int EnterPutNum = 0;
static unsigned int Enter_turn_num = 0;
static unsigned int NUM_W = 0;
static unsigned int NUM_S = 0;
static unsigned int NUM_A = 0;
static unsigned int NUM_D = 0;
static unsigned int NUM_Q = 0;
static unsigned int NUM_E = 0;
static unsigned int NUM_Z = 0;
static unsigned int NUM_X = 0;
static unsigned int KEI_MOVE_NUM = 0;
static unsigned int GIN_MOVE_NUM = 0;
static unsigned int KIN_MOVE_NUM = 0;
static unsigned int messageINT = 0;
//static TCHAR ten[SHOGI_BOARD_HEIGHT][SHOGI_BOARD_WIDTH][1];
//HINSTANCE hInstance_yuto;
//LPCTSTR syougi_main_window;
SYSTEMTIME stTime;
static TCHAR strTime[128];

//プロトタイプ宣言
void DrawLoadingScreen(void);
int gpUpdateKey();
int FuncLoad(int);
int SettingBeforeInit(bool);
int SettingAfterInit();
LRESULT CALLBACK MyProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);
BOOL CALLBACK MyDlgProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp);
int MyOpen(HWND);
void tama();
void FuncMenu();
void FuncBackGroundAinmation();
void FuncDrawKoma();
int gpUpdateKey();
void FuncSTART();
void Koma_Calc_init();
void FuncKomaMove(unsigned int, unsigned int);
//LRESULT  CALLBACK  wndproc_yuto(HWND, UINT, WPARAM, LPARAM);

typedef struct {
	int x, y;
	char MenuName[200];
}start;


enum KOMA_TYPE {
	HU,/*歩*/
	KYOU,/*香車*/
	KEI,/*桂馬*/
	GIN,/*銀*/
	KIN,/*金*/
	KAKU,/*角*/
	HISYA,/*飛車*/
	TOKIN,/*と金*/
	NARIKYO,/*成香*/
	NARIKEI,/*成桂*/
	NARIGIN,/*成銀*/
	RYUMA,/*龍馬*/
	RYUOU,/*竜王*/
	OUSYO,/*王*/
	KOMA_TYPE_MAX//列挙定数=14
};

// WinMain関数
int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{

	MessageBox(
		NULL,
		_T("ゲームを始めます"),
		_T("情報"),
		NULL
	);

	//インスタンスハンドルの代入
	hInst = hInstance;

	SettingBeforeInit(true);

	// ＤＸライブラリの初期化
	DxLib_Init();

	// 描画先を裏画面にする
	SettingAfterInit();

	// 読み込む画像の数だけ繰り返し
	for (LoadingFile = 0; LoadingFile < FILENUM; LoadingFile++)
	{
		GrHandle[LoadingFile] = FuncLoad(LoadingFile);

		// ２０個読み込み終わる毎に読み込み中画面を一回更新する
		if (LoadingFile % 2 == 0)
		{
			// 画面の初期化
			ClearDrawScreen();

			// 読み込み中画面を描画
			DrawLoadingScreen();

			// 裏画面の内容を表画面に反映
			ScreenFlip();

			// メッセージ処理
			if (ProcessMessage() != 0) break;
		}
	}
	EnterPutNum = 0;
	/*駒の初期化*/
	Koma_Calc_init();
	while (ScreenFlip() == 0 &&
		ProcessMessage() == 0 &&
		ClearDrawScreen() == 0 &&
		gpUpdateKey() == 0)
	{
		FuncBackGroundAinmation();
		FuncMenu();
		tama();/*遊び*/
		if (EnterPutNum == 0)
		{
			FuncSTART();
		}
		if (Key[KEY_INPUT_RETURN])
		{
			EnterPutNum = 1;
		}
		if (SelectNum == 0 && EnterPutNum == 1) {
			FuncDrawKoma();
			///*Enterが押されたらロード中と描画したのち、WINDOWをCREATEする*/
			///*ウィンドウの登録*/
			//WNDCLASS wndclass_yuto;
			////typedef struct _WNDCLASS {
			////	UINT    style;
			////	WNDPROC lpfnWndProc;
			////	int     cbClsExtra;
			////	int     cbWndExtra;
			////	HANDLE  hInstance;
			////	HICON   hIcon;
			////	HCURSOR hCursor;
			////	HBRUSH  hbrBackground;
			////	LPCTSTR lpszMenuName;
			////	LPCTSTR lpszClassName;
			////} WNDCLASS;
			//wndclass_yuto = {
			//	CS_HREDRAW | CS_VREDRAW,
			//	wndproc_yuto,
			//	0,
			//	0,
			//	hInstance_yuto,
			//	(HICON)IDI_ICON2,
			//	NULL,
			//	(HBRUSH)GetStockObject(WHITE_BRUSH),
			//	NULL,
			//	syougi_main_window
			//};
			//if (RegisterClass(&wndclass_yuto) == 0) {
			//	return FALSE;
			//}
			//
			///*ウィンドウの生成*/
			//HWND hWnd_yuto;
			////HWND CreateWindow(
			////	LPCTSTR lpClassName, LPCTSTR lpWindowName,
			////	DWORD dwStyle,
			////	int x, int y, int nWidth, int nHeight,
			////	HWND hWndParent, HMENU hMenu,
			////	HANDLE hInstance, LPVOID lpParam
			////);
			//hWnd_yuto = CreateWindow(
			//	"将棋",
			//	syougi_main_window,
			//	WS_OVERLAPPEDWINDOW,
			//	CW_USEDEFAULT,
			//	CW_USEDEFAULT,
			//	CW_USEDEFAULT,
			//	CW_USEDEFAULT,
			//	NULL,
			//	NULL,
			//	hInstance_yuto,
			//	NULL
			//);
			//if (!hWnd_yuto)
			//{
			//	return FALSE;
			//}
			///*ウィンドウを表示する*/
			//ShowWindow(hWnd_yuto, nCmdShow);
			///*表示を初期化*/
			//UpdateWindow(hWnd_yuto);
			///*フォーカスを指定*/
			//SetFocus(hWnd_yuto);
			//MSG         msg;
			//while (GetMessage(&msg,NULL,0,0))
			//{
			//	TranslateMessage(&msg);
			//	DispatchMessage(&msg);
			//}
			//return msg.wParam;
			if (messageINT == 1)
			{
				MessageBox(
					NULL,
					_T("W,S,A,D,Q,E,Z,Xキーを使って駒の動きを表現します\n例外的には桂馬はA,Dキーを用いて表現します\nW・・・上\nS・・・下\nA・・・左\nD・・・右\nQ・・・左上\nE・・・右上\nZ・・・左下\nX・・・右下\nEnterキーで決定\n"),
					_T("駒の動かし方について"),
					NULL
				);
			}
			messageINT++;
		}
		else
		{
			EnterPutNum = 0;
		}
		if (SelectNum == 1 && Key[KEY_INPUT_RETURN])
		{
			EnterPutNum = 0;
			DxLib_End();
		}
	}
	EnterPutNum = 0;
	// ＤＸライブラリの後始末
	DxLib_End();
	// ソフトの終了
	return 0;
}

//
//LRESULT  CALLBACK  wndproc_yuto(
//	HWND hWnd,
//	UINT msg,
//	WPARAM wParam,
//	LPARAM lParam) 
//{
//	//渡された message から、イベントの種類を解析する
//	switch (msg) {
//		//----終了処理----
//	case WM_DESTROY:
//		PostQuitMessage(0);
//		break;
//
//		//----デフォルトの処理----
//	default:
//		return DefWindowProc(hWnd, msg, wParam, lParam);
//	}
//
//	return 0L;
//}
//

void FuncSTART() {
	start START_MENU[2] = {
		{100,100,"game_start"},
		{100,200,"game_end"},
	};
	//計算フェーズ
	if (Key[KEY_INPUT_W] == 1)
	{
		SelectNum = (SelectNum + 1) % START_BUTTON;
	}
	if (Key[KEY_INPUT_A] == 1)
	{
		/*処理なし*/
	}
	if (Key[KEY_INPUT_S] == 1)
	{
		SelectNum = (SelectNum + 1) % START_BUTTON;
	}
	if (Key[KEY_INPUT_D] == 1)
	{
		/*処理なし*/
	}
	for (int i = 0; i < START_BUTTON; i++)
	{
		if (SelectNum == i) {
			START_MENU[i].x = 80;
		}
		else
		{
			START_MENU[i].x = 100;
		}
	}
	//描画フェーズ
	for (int i = 0; i < START_BUTTON; i++)
	{
		DrawString(START_MENU[i].x, START_MENU[i].y, START_MENU[i].MenuName, GetColor(50, 60, 100));
	}

}
//
//typedef struct {
//	int x, y;//座標格納用変数
//	enum KOMA_TYPE KomaType[KOMA_TYPE_MAX];//駒のタイプ
//	int KomaAngle;//敵の駒か、味方の駒か
//	int NarigomaAngle;//敵の成り駒か、味方の成り駒か
//	enum KOMA_TYPE Motigoma[KOMA_TYPE_MAX];//持ち駒
//	int MotigomaAngle;//敵の持ち駒？味方の持ち駒？
//	int n, m;//味方用持ち駒座標格納用変数
//	int N, M;//敵用持ち駒座標格納用変数
//	char Motigoma_Select[KOMA_TYPE_MAX][100];//どの持ち駒が何個あるのかをユーザーに分からせるために文字を格納して、条件の時文字を出力
//	char Teki_Motigoma_Select[KOMA_TYPE_MAX][100];
//	int Nari_Select;//０の時・・・？　１の時・・・？　排他的論理和
//}Koma;/*計算用の構造体の配列*/
//
//Koma Koma_box[81] = {
//	/*初期値の設定*/
//	{/*香車*/},{/*桂馬*/},{/*銀将*/},{/*金将*/},{/*玉将*/},{/*金将*/},{/*銀将*/},{/*桂馬*/},{/*香車*/},
//	{/**/},{/*飛車*/},{/**/},{/**/},{/**/},{/**/},{/**/},{/*角行*/},{/**/},
//	{/*歩兵*/},{/*歩兵*/},{/*歩兵*/},{/*歩兵*/},{/*歩兵*/},{/*歩兵*/},{/*歩兵*/},{/*歩兵*/},{/*歩兵*/},
//	{/**/},{/**/},{/**/},{/**/},{/**/},{/**/},{/**/},{/**/},{/**/},
//	{/**/},{/**/},{/**/},{/**/},{/**/},{/**/},{/**/},{/**/},{/**/},
//	{/**/},{/**/},{/**/},{/**/},{/**/},{/**/},{/**/},{/**/},{/**/},
//	{/*歩兵*/},{/*歩兵*/},{/*歩兵*/},{/*歩兵*/},{/*歩兵*/},{/*歩兵*/},{/*歩兵*/},{/*歩兵*/},{/*歩兵*/},
//	{/**/},{/*角行*/},{/**/},{/**/},{/**/},{/**/},{/**/},{/*飛車*/},{/**/},
//	{/*香車*/},{/*桂馬*/},{/*銀将*/},{/*金将*/},{/*王将*/},{/*金将*/},{/*銀将*/},{/*桂馬*/},{/*香車*/},
//};
//

typedef struct {
	unsigned int x;
	unsigned int y;
	double rota;
	double turn;
	int grhandle;
	int a;
}Koma;

Koma Koma_hInstance[KOMA_TYPE_MAX][20];

void Koma_Calc_init() {
	Koma_hInstance[HU][0] = {
		130,
		150,
		0.2,
		PI,
		GrHandle[0],
		TRUE
	};
	Koma_hInstance[HU][1] = {
		180,
		150,
		0.2,
		PI,
		GrHandle[0],
		TRUE
	};
	Koma_hInstance[HU][2] = {
		230,
		150,
		0.2,
		PI,
		GrHandle[0],
		TRUE
	};
	Koma_hInstance[HU][3] = {
		280,
		150,
		0.2,
		PI,
		GrHandle[0],
		TRUE
	};
	Koma_hInstance[HU][4] = {
		330,
		150,
		0.2,
		PI,
		GrHandle[0],
		TRUE
	};
	Koma_hInstance[HU][5] = {
		380,
		150,
		0.2,
		PI,
		GrHandle[0],
		TRUE
	};
	Koma_hInstance[HU][6] = {
		430,
		150,
		0.2,
		PI,
		GrHandle[0],
		TRUE
	};
	Koma_hInstance[HU][7] = {
		480,
		150,
		0.2,
		PI,
		GrHandle[0],
		TRUE
	};
	Koma_hInstance[HU][8] = {
		530,
		150,
		0.2,
		PI,
		GrHandle[0],
		TRUE
	};
	Koma_hInstance[HU][10] = {
		130,
		350,
		0.2,
		0,
		GrHandle[0],
		TRUE
	};
	Koma_hInstance[HU][11] = {
		180,
		350,
		0.2,
		0,
		GrHandle[0],
		TRUE
	};
	Koma_hInstance[HU][12] = {
		230,
		350,
		0.2,
		0,
		GrHandle[0],
		TRUE
	};
	Koma_hInstance[HU][13] = {
		280,
		350,
		0.2,
		0,
		GrHandle[0],
		TRUE
	};
	Koma_hInstance[HU][14] = {
		330,
		350,
		0.2,
		0,
		GrHandle[0],
		TRUE
	};
	Koma_hInstance[HU][15] = {
		380,
		350,
		0.2,
		0,
		GrHandle[0],
		TRUE
	};
	Koma_hInstance[HU][16] = {
		430,
		350,
		0.2,
		0,
		GrHandle[0],
		TRUE
	};
	Koma_hInstance[HU][17] = {
		480,
		350,
		0.2,
		0,
		GrHandle[0],
		TRUE
	};
	Koma_hInstance[HU][18] = {
		530,
		350,
		0.2,
		0,
		GrHandle[0],
		TRUE
	};
	Koma_hInstance[KYOU][0] = {
		130,
		50,
		0.2,
		PI,
		GrHandle[1],
		TRUE
	};
	Koma_hInstance[KYOU][1] = {
		530,
		50,
		0.2,
		PI,
		GrHandle[1],
		TRUE
	};
	Koma_hInstance[KYOU][2] = {
		130,
		450,
		0.2,
		0,
		GrHandle[1],
		TRUE
	};
	Koma_hInstance[KYOU][3] = {
		530,
		450,
		0.2,
		0,
		GrHandle[1],
		TRUE
	};
	Koma_hInstance[KEI][0] = {
		180,
		50,
		0.2,
		PI,
		GrHandle[2],
		TRUE
	};
	Koma_hInstance[KEI][1] = {
		480,
		50,
		0.2,
		PI,
		GrHandle[2],
		TRUE
	};
	Koma_hInstance[KEI][2] = {
		180,
		450,
		0.2,
		0,
		GrHandle[2],
		TRUE
	};
	Koma_hInstance[KEI][3] = {
		480,
		450,
		0.2,
		0,
		GrHandle[2],
		TRUE
	};
	Koma_hInstance[GIN][0] = {
		230,
		50,
		0.2,
		PI,
		GrHandle[3],
		TRUE
	};
	Koma_hInstance[GIN][1] = {
		430,
		50,
		0.2,
		PI,
		GrHandle[3],
		TRUE
	};
	Koma_hInstance[GIN][2] = {
		230,
		450,
		0.2,
		0,
		GrHandle[3],
		TRUE
	};
	Koma_hInstance[GIN][3] = {
		430,
		450,
		0.2,
		0,
		GrHandle[3],
		TRUE
	};
	Koma_hInstance[KIN][0] = {
		280,
		50,
		0.2,
		PI,
		GrHandle[4],
		TRUE
	};
	Koma_hInstance[KIN][1] = {
		380,
		50,
		0.2,
		PI,
		GrHandle[4],
		TRUE
	};
	Koma_hInstance[KIN][2] = {
		280,
		450,
		0.2,
		0,
		GrHandle[4],
		TRUE
	};
	Koma_hInstance[KIN][3] = {
		380,
		450,
		0.2,
		0,
		GrHandle[4],
		TRUE
	};
	Koma_hInstance[KAKU][0] = {
		480,
		100,
		0.2,
		PI,
		GrHandle[5],
		TRUE
	};
	Koma_hInstance[KAKU][1] = {
		180,
		400,
		0.2,
		0,
		GrHandle[5],
		TRUE
	};
	Koma_hInstance[HISYA][0] = {
		180,
		100,
		0.2,
		PI,
		GrHandle[6],
		TRUE
	};
	Koma_hInstance[HISYA][1] = {
		480,
		400,
		0.2,
		0,
		GrHandle[6],
		TRUE
	};
	Koma_hInstance[OUSYO][0] = {
		330,
		50,
		0.2,
		PI,
		GrHandle[13],
		TRUE
	};
	Koma_hInstance[OUSYO][1] = {
		330,
		450,
		0.2,
		0,
		GrHandle[13],
		TRUE
	};
}

void FuncKomaMove(unsigned int _KomaType, unsigned int _num) {
	switch (_KomaType)
	{
	case HU:
		/*相手の駒をとるとき相手の駒を消す。そしてカーソルのターンと同じほうの持ち駒ボードに描画し、持ち駒（今のターンのほう）に保存する*/
		/*歩は一つ前にしか進めない*/
		if (Koma_hInstance[_KomaType][_num].turn == 0)
		{
			if (Key[KEY_INPUT_W] == 1)
			{
				if (NUM_W == 0)
				{
					Koma_hInstance[_KomaType][_num].y = Koma_hInstance[_KomaType][_num].y - 50;
					CursorMove_y = CursorMove_y - 50;
					for (unsigned int i = KYOU; i < KOMA_TYPE_MAX; i++)
					{
						for (unsigned int j = 0; j < 19; j++)
						{
							if ((Koma_hInstance[i][j].x == Koma_hInstance[_KomaType][_num].x)
								&& (Koma_hInstance[i][j].y == Koma_hInstance[_KomaType][_num].y))
							{
								Koma_hInstance[_KomaType][_num].y = Koma_hInstance[_KomaType][_num].y + 50;
								CursorMove_y = CursorMove_y + 50;
							}
						}
					}
					NUM_W ^= 1;
				}
			}
		}
		if (Koma_hInstance[_KomaType][_num].turn == PI)
		{
			if (Key[KEY_INPUT_S] == 1)
			{
				if (NUM_S == 0)
				{
					Koma_hInstance[_KomaType][_num].y = Koma_hInstance[_KomaType][_num].y + 50;
					CursorMove_y = CursorMove_y + 50;
					for (unsigned int i = KYOU; i < KOMA_TYPE_MAX; i++)
					{
						for (unsigned int j = 0; j < 19; j++)
						{
							if ((Koma_hInstance[i][j].x == Koma_hInstance[_KomaType][_num].x)
								&& (Koma_hInstance[i][j].y == Koma_hInstance[_KomaType][_num].y))
							{
								Koma_hInstance[_KomaType][_num].y = Koma_hInstance[_KomaType][_num].y - 50;
								CursorMove_y = CursorMove_y - 50;
							}
						}
					}
					NUM_S ^= 1;
				}
			}
		}
		break;
	case KYOU:
		if (Koma_hInstance[_KomaType][_num].turn == 0)
		{
			if (Key[KEY_INPUT_W] == 1)
			{
				
				Koma_hInstance[_KomaType][_num].y = Koma_hInstance[_KomaType][_num].y - 50;
				CursorMove_y = CursorMove_y - 50;
				for (unsigned int keikaraoumade = KEI; keikaraoumade < KOMA_TYPE_MAX; keikaraoumade++)
				{
					for (unsigned int j = 0; j < 19; j++)
					{
						if (
							(Koma_hInstance[HU][j].x == Koma_hInstance[_KomaType][_num].x
							&& Koma_hInstance[HU][j].y == Koma_hInstance[_KomaType][_num].y)
							||
							(Koma_hInstance[keikaraoumade][j].x == Koma_hInstance[_KomaType][_num].x
							&& Koma_hInstance[keikaraoumade][j].y == Koma_hInstance[_KomaType][_num].y)
							)
						{
							/*香を移動させた先に駒があるのであればそこには移動できない*/
							Koma_hInstance[_KomaType][_num].y = Koma_hInstance[_KomaType][_num].y + 50;
							CursorMove_y = CursorMove_y + 50;
						}
					}
				}
			}
		}
		if (Koma_hInstance[_KomaType][_num].turn == PI)
		{
			if (Key[KEY_INPUT_S] == 1)
			{
				Koma_hInstance[_KomaType][_num].y = Koma_hInstance[_KomaType][_num].y + 50;
				CursorMove_y = CursorMove_y + 50;
				for (unsigned int keikaraoumade = KEI; keikaraoumade < KOMA_TYPE_MAX; keikaraoumade++)
				{
					for (unsigned int j = 0; j < 19; j++)
					{
						if (
							(Koma_hInstance[HU][j].x == Koma_hInstance[_KomaType][_num].x
								&& Koma_hInstance[HU][j].y == Koma_hInstance[_KomaType][_num].y)
							||
							(Koma_hInstance[keikaraoumade][j].x == Koma_hInstance[_KomaType][_num].x
								&& Koma_hInstance[keikaraoumade][j].y == Koma_hInstance[_KomaType][_num].y)
							)
						{
							/*香を移動させた先に駒があるのであればそこには移動できない*/
							Koma_hInstance[_KomaType][_num].y = Koma_hInstance[_KomaType][_num].y - 50;
							CursorMove_y = CursorMove_y - 50;
						}
					}
				}
			}
		}
		break;
	case KEI:
		/*桂馬も一回しか移動できなくする*/
		if (Koma_hInstance[_KomaType][_num].turn == 0)
		{
			if (Key[KEY_INPUT_A] == 1)
			{
				if (KEI_MOVE_NUM == 0)
				{
					KEI_MOVE_NUM ^= 1;
					/*上左に移動する*/
					Koma_hInstance[_KomaType][_num].x = Koma_hInstance[_KomaType][_num].x - 50;
					Koma_hInstance[_KomaType][_num].y = Koma_hInstance[_KomaType][_num].y - 100;
					CursorMove_x = CursorMove_x - 50;
					CursorMove_y = CursorMove_y - 100;
					for (unsigned int i = GIN; i < KOMA_TYPE_MAX; i++)
					{
						for (unsigned int j = 0; j < 19; j++)
						{
							if (
								(Koma_hInstance[HU][j].x == Koma_hInstance[_KomaType][_num].x
									&& Koma_hInstance[HU][j].y == Koma_hInstance[_KomaType][_num].y)
								||
								(Koma_hInstance[KYOU][j].x == Koma_hInstance[_KomaType][_num].x
									&& Koma_hInstance[KYOU][j].y == Koma_hInstance[_KomaType][_num].y)
								||
								(Koma_hInstance[i][j].x == Koma_hInstance[_KomaType][_num].x
									&& Koma_hInstance[i][j].y == Koma_hInstance[_KomaType][_num].y)
								)
							{
								Koma_hInstance[_KomaType][_num].x = Koma_hInstance[_KomaType][_num].x + 50;
								Koma_hInstance[_KomaType][_num].y = Koma_hInstance[_KomaType][_num].y + 100;
								CursorMove_x = CursorMove_x + 50;
								CursorMove_y = CursorMove_y + 100;
							}
						}
					}
				}
			}
			if (Key[KEY_INPUT_D] == 1)
			{
				if (KEI_MOVE_NUM == 0)
				{
					KEI_MOVE_NUM ^= 1;
					/*上右に移動する*/
					Koma_hInstance[_KomaType][_num].x = Koma_hInstance[_KomaType][_num].x + 50;
					Koma_hInstance[_KomaType][_num].y = Koma_hInstance[_KomaType][_num].y - 100;
					CursorMove_x = CursorMove_x + 50;
					CursorMove_y = CursorMove_y - 100;
					for (unsigned int i = GIN; i < KOMA_TYPE_MAX; i++)
					{
						for (unsigned int j = 0; j < 19; j++)
						{
							if (
								(Koma_hInstance[HU][j].x == Koma_hInstance[_KomaType][_num].x
									&& Koma_hInstance[HU][j].y == Koma_hInstance[_KomaType][_num].y)
								||
								(Koma_hInstance[KYOU][j].x == Koma_hInstance[_KomaType][_num].x
									&& Koma_hInstance[KYOU][j].y == Koma_hInstance[_KomaType][_num].y)
								||
								(Koma_hInstance[i][j].x == Koma_hInstance[_KomaType][_num].x
									&& Koma_hInstance[i][j].y == Koma_hInstance[_KomaType][_num].y)
								)
							{
								Koma_hInstance[_KomaType][_num].x = Koma_hInstance[_KomaType][_num].x - 50;
								Koma_hInstance[_KomaType][_num].y = Koma_hInstance[_KomaType][_num].y + 100;
								CursorMove_x = CursorMove_x - 50;
								CursorMove_y = CursorMove_y + 100;
							}
						}
					}
				}
			}
		}
		if (Koma_hInstance[_KomaType][_num].turn == PI)
		{
			if (Key[KEY_INPUT_A] == 1)
			{
				if (KEI_MOVE_NUM == 0)
				{
					KEI_MOVE_NUM ^= 1;
					/*下左に移動する*/
					Koma_hInstance[_KomaType][_num].x = Koma_hInstance[_KomaType][_num].x - 50;
					Koma_hInstance[_KomaType][_num].y = Koma_hInstance[_KomaType][_num].y + 100;
					CursorMove_x = CursorMove_x - 50;
					CursorMove_y = CursorMove_y + 100;
					for (unsigned int i = GIN; i < KOMA_TYPE_MAX; i++)
					{
						for (unsigned int j = 0; j < 19; j++)
						{
							if (
								(Koma_hInstance[HU][j].x == Koma_hInstance[_KomaType][_num].x
									&& Koma_hInstance[HU][j].y == Koma_hInstance[_KomaType][_num].y)
								||
								(Koma_hInstance[KYOU][j].x == Koma_hInstance[_KomaType][_num].x
									&& Koma_hInstance[KYOU][j].y == Koma_hInstance[_KomaType][_num].y)
								||
								(Koma_hInstance[i][j].x == Koma_hInstance[_KomaType][_num].x
									&& Koma_hInstance[i][j].y == Koma_hInstance[_KomaType][_num].y)
								)
							{
								Koma_hInstance[_KomaType][_num].x = Koma_hInstance[_KomaType][_num].x + 50;
								Koma_hInstance[_KomaType][_num].y = Koma_hInstance[_KomaType][_num].y - 100;
								CursorMove_x = CursorMove_x + 50;
								CursorMove_y = CursorMove_y - 100;
							}
						}
					}
				}
			}
			if (Key[KEY_INPUT_D] == 1)
			{
				if (KEI_MOVE_NUM == 0)
				{
					KEI_MOVE_NUM ^= 1;
					/*下右に移動する*/
					Koma_hInstance[_KomaType][_num].x = Koma_hInstance[_KomaType][_num].x + 50;
					Koma_hInstance[_KomaType][_num].y = Koma_hInstance[_KomaType][_num].y + 100;
					CursorMove_x = CursorMove_x + 50;
					CursorMove_y = CursorMove_y + 100;
					for (unsigned int i = GIN; i < KOMA_TYPE_MAX; i++)
					{
						for (unsigned int j = 0; j < 19; j++)
						{
							if (
								(Koma_hInstance[HU][j].x == Koma_hInstance[_KomaType][_num].x
									&& Koma_hInstance[HU][j].y == Koma_hInstance[_KomaType][_num].y)
								||
								(Koma_hInstance[KYOU][j].x == Koma_hInstance[_KomaType][_num].x
									&& Koma_hInstance[KYOU][j].y == Koma_hInstance[_KomaType][_num].y)
								||
								(Koma_hInstance[i][j].x == Koma_hInstance[_KomaType][_num].x
									&& Koma_hInstance[i][j].y == Koma_hInstance[_KomaType][_num].y)
								)
							{
								Koma_hInstance[_KomaType][_num].x = Koma_hInstance[_KomaType][_num].x - 50;
								Koma_hInstance[_KomaType][_num].y = Koma_hInstance[_KomaType][_num].y - 100;
								CursorMove_x = CursorMove_x - 50;
								CursorMove_y = CursorMove_y - 100;
							}
						}
					}
				}
			}
		}
		break;
	case GIN:
		/*駒が一回移動したらもう動かせなくする*/
		if (Koma_hInstance[_KomaType][_num].turn == 0)
		{
			if (Key[KEY_INPUT_W] == 1)
			{
				if (NUM_W == 0)
				{
					Koma_hInstance[_KomaType][_num].y = Koma_hInstance[_KomaType][_num].y - 50;
					CursorMove_y = CursorMove_y - 50;
					for (unsigned int i = KIN; i < KOMA_TYPE_MAX; i++)
					{
						for (unsigned int j = 0; j < 19; j++)
						{
							if (
								(Koma_hInstance[i][j].x == Koma_hInstance[_KomaType][_num].x
									&& Koma_hInstance[i][j].y == Koma_hInstance[_KomaType][_num].y)
								||
								(Koma_hInstance[HU][j].x == Koma_hInstance[_KomaType][_num].x
									&& Koma_hInstance[HU][j].y == Koma_hInstance[_KomaType][_num].y)
								||
								(Koma_hInstance[KYOU][j].x == Koma_hInstance[_KomaType][_num].x
									&& Koma_hInstance[KYOU][j].y == Koma_hInstance[_KomaType][_num].y)
								||
								(Koma_hInstance[KEI][j].x == Koma_hInstance[_KomaType][_num].x
									&& Koma_hInstance[KEI][j].y == Koma_hInstance[_KomaType][_num].y)
								)
							{
								Koma_hInstance[_KomaType][_num].y = Koma_hInstance[_KomaType][_num].y + 50;
								CursorMove_y = CursorMove_y + 50;
							}
						}
					}
					NUM_W ^= 1;
					GIN_MOVE_NUM ^= 1;
				}
			}
			if (Key[KEY_INPUT_Q] == 1)
			{
				if (NUM_Q == 0)
				{
					Koma_hInstance[_KomaType][_num].x = Koma_hInstance[_KomaType][_num].x - 50;
					Koma_hInstance[_KomaType][_num].y = Koma_hInstance[_KomaType][_num].y - 50;
					CursorMove_x = CursorMove_x - 50;
					CursorMove_y = CursorMove_y - 50;
					for (unsigned int i = KIN; i < KOMA_TYPE_MAX; i++)
					{
						for (unsigned int j = 0; j < 19; j++)
						{
							if (
								(Koma_hInstance[i][j].x == Koma_hInstance[_KomaType][_num].x
									&& Koma_hInstance[i][j].y == Koma_hInstance[_KomaType][_num].y)
								||
								(Koma_hInstance[HU][j].x == Koma_hInstance[_KomaType][_num].x
									&& Koma_hInstance[HU][j].y == Koma_hInstance[_KomaType][_num].y)
								||
								(Koma_hInstance[KYOU][j].x == Koma_hInstance[_KomaType][_num].x
									&& Koma_hInstance[KYOU][j].y == Koma_hInstance[_KomaType][_num].y)
								||
								(Koma_hInstance[KEI][j].x == Koma_hInstance[_KomaType][_num].x
									&& Koma_hInstance[KEI][j].y == Koma_hInstance[_KomaType][_num].y)
								)
							{
								Koma_hInstance[_KomaType][_num].x = Koma_hInstance[_KomaType][_num].x + 50;
								Koma_hInstance[_KomaType][_num].y = Koma_hInstance[_KomaType][_num].y + 50;
								CursorMove_x = CursorMove_x + 50;
								CursorMove_y = CursorMove_y + 50;
							}
						}
					}
					if ((Koma_hInstance[_KomaType][_num].x < 130) || (Koma_hInstance[_KomaType][_num].y < 50))
					{
						Koma_hInstance[_KomaType][_num].x = Koma_hInstance[_KomaType][_num].x + 50;
						Koma_hInstance[_KomaType][_num].y = Koma_hInstance[_KomaType][_num].y + 50;
						CursorMove_x = CursorMove_x + 50;
						CursorMove_y = CursorMove_y + 50;
					}
					NUM_Q ^= 1;
					GIN_MOVE_NUM ^= 1;
				}
			}
			if (Key[KEY_INPUT_E] == 1)
			{
				if (NUM_E == 0)
				{
					Koma_hInstance[_KomaType][_num].x = Koma_hInstance[_KomaType][_num].x + 50;
					Koma_hInstance[_KomaType][_num].y = Koma_hInstance[_KomaType][_num].y - 50;
					CursorMove_x = CursorMove_x + 50;
					CursorMove_y = CursorMove_y - 50;
					for (unsigned int i = KIN; i < KOMA_TYPE_MAX; i++)
					{
						for (unsigned int j = 0; j < 19; j++)
						{
							if (
								(Koma_hInstance[i][j].x == Koma_hInstance[_KomaType][_num].x
									&& Koma_hInstance[i][j].y == Koma_hInstance[_KomaType][_num].y)
								||
								(Koma_hInstance[HU][j].x == Koma_hInstance[_KomaType][_num].x
									&& Koma_hInstance[HU][j].y == Koma_hInstance[_KomaType][_num].y)
								||
								(Koma_hInstance[KYOU][j].x == Koma_hInstance[_KomaType][_num].x
									&& Koma_hInstance[KYOU][j].y == Koma_hInstance[_KomaType][_num].y)
								||
								(Koma_hInstance[KEI][j].x == Koma_hInstance[_KomaType][_num].x
									&& Koma_hInstance[KEI][j].y == Koma_hInstance[_KomaType][_num].y)
								)
							{
								Koma_hInstance[_KomaType][_num].x = Koma_hInstance[_KomaType][_num].x - 50;
								Koma_hInstance[_KomaType][_num].y = Koma_hInstance[_KomaType][_num].y + 50;
								CursorMove_x = CursorMove_x - 50;
								CursorMove_y = CursorMove_y + 50;
							}
						}
					}
					if ((Koma_hInstance[_KomaType][_num].x > 530) || (Koma_hInstance[_KomaType][_num].y < 50))
					{
						Koma_hInstance[_KomaType][_num].x = Koma_hInstance[_KomaType][_num].x - 50;
						Koma_hInstance[_KomaType][_num].y = Koma_hInstance[_KomaType][_num].y + 50;
						CursorMove_x = CursorMove_x - 50;
						CursorMove_y = CursorMove_y + 50;
					}
					NUM_E ^= 1;
					GIN_MOVE_NUM ^= 1;
				}
			}
			if (Key[KEY_INPUT_Z] == 1)
			{
				if (NUM_Z == 0)
				{
					Koma_hInstance[_KomaType][_num].x = Koma_hInstance[_KomaType][_num].x - 50;
					Koma_hInstance[_KomaType][_num].y = Koma_hInstance[_KomaType][_num].y + 50;
					CursorMove_x = CursorMove_x - 50;
					CursorMove_y = CursorMove_y + 50;
					for (unsigned int i = KIN; i < KOMA_TYPE_MAX; i++)
					{
						for (unsigned int j = 0; j < 19; j++)
						{
							if (
								(Koma_hInstance[i][j].x == Koma_hInstance[_KomaType][_num].x
									&& Koma_hInstance[i][j].y == Koma_hInstance[_KomaType][_num].y)
								||
								(Koma_hInstance[HU][j].x == Koma_hInstance[_KomaType][_num].x
									&& Koma_hInstance[HU][j].y == Koma_hInstance[_KomaType][_num].y)
								||
								(Koma_hInstance[KYOU][j].x == Koma_hInstance[_KomaType][_num].x
									&& Koma_hInstance[KYOU][j].y == Koma_hInstance[_KomaType][_num].y)
								||
								(Koma_hInstance[KEI][j].x == Koma_hInstance[_KomaType][_num].x
									&& Koma_hInstance[KEI][j].y == Koma_hInstance[_KomaType][_num].y)
								)
							{
								Koma_hInstance[_KomaType][_num].x = Koma_hInstance[_KomaType][_num].x + 50;
								Koma_hInstance[_KomaType][_num].y = Koma_hInstance[_KomaType][_num].y - 50;
								CursorMove_x = CursorMove_x + 50;
								CursorMove_y = CursorMove_y - 50;
							}
						}
					}
					if ((Koma_hInstance[_KomaType][_num].x < 130) || (Koma_hInstance[_KomaType][_num].y < 50))
					{
						Koma_hInstance[_KomaType][_num].x = Koma_hInstance[_KomaType][_num].x + 50;
						Koma_hInstance[_KomaType][_num].y = Koma_hInstance[_KomaType][_num].y - 50;
						CursorMove_x = CursorMove_x + 50;
						CursorMove_y = CursorMove_y - 50;
					}
					NUM_Z ^= 1;
					GIN_MOVE_NUM ^= 1;
				}
			}
			if (Key[KEY_INPUT_X] == 1)
			{
				if (NUM_X == 0)
				{
					Koma_hInstance[_KomaType][_num].x = Koma_hInstance[_KomaType][_num].x + 50;
					Koma_hInstance[_KomaType][_num].y = Koma_hInstance[_KomaType][_num].y + 50;
					CursorMove_x = CursorMove_x + 50;
					CursorMove_y = CursorMove_y + 50;
					for (unsigned int i = KIN; i < KOMA_TYPE_MAX; i++)
					{
						for (unsigned int j = 0; j < 19; j++)
						{
							if (
								(Koma_hInstance[i][j].x == Koma_hInstance[_KomaType][_num].x
									&& Koma_hInstance[i][j].y == Koma_hInstance[_KomaType][_num].y)
								||
								(Koma_hInstance[HU][j].x == Koma_hInstance[_KomaType][_num].x
									&& Koma_hInstance[HU][j].y == Koma_hInstance[_KomaType][_num].y)
								||
								(Koma_hInstance[KYOU][j].x == Koma_hInstance[_KomaType][_num].x
									&& Koma_hInstance[KYOU][j].y == Koma_hInstance[_KomaType][_num].y)
								||
								(Koma_hInstance[KEI][j].x == Koma_hInstance[_KomaType][_num].x
									&& Koma_hInstance[KEI][j].y == Koma_hInstance[_KomaType][_num].y)
								)
							{
								Koma_hInstance[_KomaType][_num].x = Koma_hInstance[_KomaType][_num].x - 50;
								Koma_hInstance[_KomaType][_num].y = Koma_hInstance[_KomaType][_num].y - 50;
								CursorMove_x = CursorMove_x - 50;
								CursorMove_y = CursorMove_y - 50;
							}
						}
					}
					if ((Koma_hInstance[_KomaType][_num].x < 130) || (Koma_hInstance[_KomaType][_num].y < 50))
					{
						Koma_hInstance[_KomaType][_num].x = Koma_hInstance[_KomaType][_num].x - 50;
						Koma_hInstance[_KomaType][_num].y = Koma_hInstance[_KomaType][_num].y - 50;
						CursorMove_x = CursorMove_x - 50;
						CursorMove_y = CursorMove_y - 50;
					}
					NUM_X ^= 1;
					GIN_MOVE_NUM ^= 1;
				}
			}
		}
		if (Koma_hInstance[_KomaType][_num].turn == PI)
		{
			if (Key[KEY_INPUT_S] == 1)
			{
				if (NUM_S == 0)
				{
					Koma_hInstance[_KomaType][_num].y = Koma_hInstance[_KomaType][_num].y + 50;
					CursorMove_y = CursorMove_y + 50;
					for (unsigned int i = KIN; i < KOMA_TYPE_MAX; i++)
					{
						for (unsigned int j = 0; j < 19; j++)
						{
							if (
								(Koma_hInstance[i][j].x == Koma_hInstance[_KomaType][_num].x
									&& Koma_hInstance[i][j].y == Koma_hInstance[_KomaType][_num].y)
								||
								(Koma_hInstance[HU][j].x == Koma_hInstance[_KomaType][_num].x
									&& Koma_hInstance[HU][j].y == Koma_hInstance[_KomaType][_num].y)
								||
								(Koma_hInstance[KYOU][j].x == Koma_hInstance[_KomaType][_num].x
									&& Koma_hInstance[KYOU][j].y == Koma_hInstance[_KomaType][_num].y)
								||
								(Koma_hInstance[KEI][j].x == Koma_hInstance[_KomaType][_num].x
									&& Koma_hInstance[KEI][j].y == Koma_hInstance[_KomaType][_num].y)
								)
							{
								Koma_hInstance[_KomaType][_num].y = Koma_hInstance[_KomaType][_num].y - 50;
								CursorMove_y = CursorMove_y - 50;
							}
						}
					}
					NUM_S ^= 1;
					GIN_MOVE_NUM ^= 1;
				}
			}
			if (Key[KEY_INPUT_X] == 1)
			{
				if (NUM_X == 0)
				{
					Koma_hInstance[_KomaType][_num].x = Koma_hInstance[_KomaType][_num].x + 50;
					Koma_hInstance[_KomaType][_num].y = Koma_hInstance[_KomaType][_num].y + 50;
					CursorMove_x = CursorMove_x + 50;
					CursorMove_y = CursorMove_y + 50;
					for (unsigned int i = KIN; i < KOMA_TYPE_MAX; i++)
					{
						for (unsigned int j = 0; j < 19; j++)
						{
							if (
								(Koma_hInstance[i][j].x == Koma_hInstance[_KomaType][_num].x
									&& Koma_hInstance[i][j].y == Koma_hInstance[_KomaType][_num].y)
								||
								(Koma_hInstance[HU][j].x == Koma_hInstance[_KomaType][_num].x
									&& Koma_hInstance[HU][j].y == Koma_hInstance[_KomaType][_num].y)
								||
								(Koma_hInstance[KYOU][j].x == Koma_hInstance[_KomaType][_num].x
									&& Koma_hInstance[KYOU][j].y == Koma_hInstance[_KomaType][_num].y)
								||
								(Koma_hInstance[KEI][j].x == Koma_hInstance[_KomaType][_num].x
									&& Koma_hInstance[KEI][j].y == Koma_hInstance[_KomaType][_num].y)
								)
							{
								Koma_hInstance[_KomaType][_num].x = Koma_hInstance[_KomaType][_num].x - 50;
								Koma_hInstance[_KomaType][_num].y = Koma_hInstance[_KomaType][_num].y - 50;
								CursorMove_x = CursorMove_x - 50;
								CursorMove_y = CursorMove_y - 50;
							}
						}
					}
					if ((Koma_hInstance[_KomaType][_num].x < 130) || (Koma_hInstance[_KomaType][_num].y < 50))
					{
						Koma_hInstance[_KomaType][_num].x = Koma_hInstance[_KomaType][_num].x - 50;
						Koma_hInstance[_KomaType][_num].y = Koma_hInstance[_KomaType][_num].y - 50;
						CursorMove_x = CursorMove_x - 50;
						CursorMove_y = CursorMove_y - 50;
					}
					NUM_X ^= 1;
					GIN_MOVE_NUM ^= 1;
				}
			}
			if (Key[KEY_INPUT_Z] == 1)
			{
				if (NUM_Z == 0)
				{
					Koma_hInstance[_KomaType][_num].x = Koma_hInstance[_KomaType][_num].x - 50;
					Koma_hInstance[_KomaType][_num].y = Koma_hInstance[_KomaType][_num].y + 50;
					CursorMove_x = CursorMove_x - 50;
					CursorMove_y = CursorMove_y + 50;
					for (unsigned int i = KIN; i < KOMA_TYPE_MAX; i++)
					{
						for (unsigned int j = 0; j < 19; j++)
						{
							if (
								(Koma_hInstance[i][j].x == Koma_hInstance[_KomaType][_num].x
									&& Koma_hInstance[i][j].y == Koma_hInstance[_KomaType][_num].y)
								||
								(Koma_hInstance[HU][j].x == Koma_hInstance[_KomaType][_num].x
									&& Koma_hInstance[HU][j].y == Koma_hInstance[_KomaType][_num].y)
								||
								(Koma_hInstance[KYOU][j].x == Koma_hInstance[_KomaType][_num].x
									&& Koma_hInstance[KYOU][j].y == Koma_hInstance[_KomaType][_num].y)
								||
								(Koma_hInstance[KEI][j].x == Koma_hInstance[_KomaType][_num].x
									&& Koma_hInstance[KEI][j].y == Koma_hInstance[_KomaType][_num].y)
								)
							{
								Koma_hInstance[_KomaType][_num].x = Koma_hInstance[_KomaType][_num].x + 50;
								Koma_hInstance[_KomaType][_num].y = Koma_hInstance[_KomaType][_num].y - 50;
								CursorMove_x = CursorMove_x + 50;
								CursorMove_y = CursorMove_y - 50;
							}
						}
					}
					if ((Koma_hInstance[_KomaType][_num].x < 130) || (Koma_hInstance[_KomaType][_num].y < 50))
					{
						Koma_hInstance[_KomaType][_num].x = Koma_hInstance[_KomaType][_num].x + 50;
						Koma_hInstance[_KomaType][_num].y = Koma_hInstance[_KomaType][_num].y - 50;
						CursorMove_x = CursorMove_x + 50;
						CursorMove_y = CursorMove_y - 50;
					}
					NUM_Z ^= 1;
					GIN_MOVE_NUM ^= 1;
				}
			}
			if (Key[KEY_INPUT_E] == 1)
			{
				if (NUM_E == 0)
				{
					Koma_hInstance[_KomaType][_num].x = Koma_hInstance[_KomaType][_num].x + 50;
					Koma_hInstance[_KomaType][_num].y = Koma_hInstance[_KomaType][_num].y - 50;
					CursorMove_x = CursorMove_x + 50;
					CursorMove_y = CursorMove_y - 50;
					for (unsigned int i = KIN; i < KOMA_TYPE_MAX; i++)
					{
						for (unsigned int j = 0; j < 19; j++)
						{
							if (
								(Koma_hInstance[i][j].x == Koma_hInstance[_KomaType][_num].x
									&& Koma_hInstance[i][j].y == Koma_hInstance[_KomaType][_num].y)
								||
								(Koma_hInstance[HU][j].x == Koma_hInstance[_KomaType][_num].x
									&& Koma_hInstance[HU][j].y == Koma_hInstance[_KomaType][_num].y)
								||
								(Koma_hInstance[KYOU][j].x == Koma_hInstance[_KomaType][_num].x
									&& Koma_hInstance[KYOU][j].y == Koma_hInstance[_KomaType][_num].y)
								||
								(Koma_hInstance[KEI][j].x == Koma_hInstance[_KomaType][_num].x
									&& Koma_hInstance[KEI][j].y == Koma_hInstance[_KomaType][_num].y)
								)
							{
								Koma_hInstance[_KomaType][_num].x = Koma_hInstance[_KomaType][_num].x - 50;
								Koma_hInstance[_KomaType][_num].y = Koma_hInstance[_KomaType][_num].y + 50;
								CursorMove_x = CursorMove_x - 50;
								CursorMove_y = CursorMove_y + 50;
							}
						}
					}
					if ((Koma_hInstance[_KomaType][_num].x > 530) || (Koma_hInstance[_KomaType][_num].y < 50))
					{
						Koma_hInstance[_KomaType][_num].x = Koma_hInstance[_KomaType][_num].x - 50;
						Koma_hInstance[_KomaType][_num].y = Koma_hInstance[_KomaType][_num].y + 50;
						CursorMove_x = CursorMove_x - 50;
						CursorMove_y = CursorMove_y + 50;
					}
					NUM_E ^= 1;
					GIN_MOVE_NUM ^= 1;
				}
			}
			if (Key[KEY_INPUT_Q] == 1)
			{
				if (NUM_Q == 0)
				{
					Koma_hInstance[_KomaType][_num].x = Koma_hInstance[_KomaType][_num].x - 50;
					Koma_hInstance[_KomaType][_num].y = Koma_hInstance[_KomaType][_num].y - 50;
					CursorMove_x = CursorMove_x - 50;
					CursorMove_y = CursorMove_y - 50;
					for (unsigned int i = KIN; i < KOMA_TYPE_MAX; i++)
					{
						for (unsigned int j = 0; j < 19; j++)
						{
							if (
								(Koma_hInstance[i][j].x == Koma_hInstance[_KomaType][_num].x
									&& Koma_hInstance[i][j].y == Koma_hInstance[_KomaType][_num].y)
								||
								(Koma_hInstance[HU][j].x == Koma_hInstance[_KomaType][_num].x
									&& Koma_hInstance[HU][j].y == Koma_hInstance[_KomaType][_num].y)
								||
								(Koma_hInstance[KYOU][j].x == Koma_hInstance[_KomaType][_num].x
									&& Koma_hInstance[KYOU][j].y == Koma_hInstance[_KomaType][_num].y)
								||
								(Koma_hInstance[KEI][j].x == Koma_hInstance[_KomaType][_num].x
									&& Koma_hInstance[KEI][j].y == Koma_hInstance[_KomaType][_num].y)
								)
							{
								Koma_hInstance[_KomaType][_num].x = Koma_hInstance[_KomaType][_num].x + 50;
								Koma_hInstance[_KomaType][_num].y = Koma_hInstance[_KomaType][_num].y + 50;
								CursorMove_x = CursorMove_x + 50;
								CursorMove_y = CursorMove_y + 50;
							}
						}
					}
					if ((Koma_hInstance[_KomaType][_num].x < 130) || (Koma_hInstance[_KomaType][_num].y < 50))
					{
						Koma_hInstance[_KomaType][_num].x = Koma_hInstance[_KomaType][_num].x + 50;
						Koma_hInstance[_KomaType][_num].y = Koma_hInstance[_KomaType][_num].y + 50;
						CursorMove_x = CursorMove_x + 50;
						CursorMove_y = CursorMove_y + 50;
					}
					NUM_Q ^= 1;
					GIN_MOVE_NUM ^= 1;
				}
			}
		}
		break;
	case KIN:
		if (Koma_hInstance[_KomaType][_num].turn == 0)
		{
			if (Key[KEY_INPUT_W] == 1)
			{
				if (KIN_MOVE_NUM == 0)
				{
					KIN_MOVE_NUM ^= 1;
					Koma_hInstance[_KomaType][_num].y = Koma_hInstance[_KomaType][_num].y - 50;
					CursorMove_y = CursorMove_y - 50;
					for (unsigned int i = KAKU; i < KOMA_TYPE_MAX; i++)
					{
						for (unsigned int j = 0; j < 19; j++)
						{
							if (
								(Koma_hInstance[i][j].x == Koma_hInstance[_KomaType][_num].x
								&& Koma_hInstance[i][j].y == Koma_hInstance[_KomaType][_num].y)
								||
								(Koma_hInstance[HU][j].x == Koma_hInstance[_KomaType][_num].x
									&& Koma_hInstance[HU][j].y == Koma_hInstance[_KomaType][_num].y)
								||
								(Koma_hInstance[KYOU][j].x == Koma_hInstance[_KomaType][_num].x
									&& Koma_hInstance[KYOU][j].y == Koma_hInstance[_KomaType][_num].y)
								||
								(Koma_hInstance[KEI][j].x == Koma_hInstance[_KomaType][_num].x
									&& Koma_hInstance[KEI][j].y == Koma_hInstance[_KomaType][_num].y)
								||
								(Koma_hInstance[GIN][j].x == Koma_hInstance[_KomaType][_num].x
									&& Koma_hInstance[GIN][j].y == Koma_hInstance[_KomaType][_num].y)
								)
							{
								Koma_hInstance[_KomaType][_num].y = Koma_hInstance[_KomaType][_num].y + 50;
								CursorMove_y = CursorMove_y + 50;
							}
						}
					}
				}
			}
			if (Key[KEY_INPUT_Q] == 1)
			{
				if (KIN_MOVE_NUM == 0)
				{
					KIN_MOVE_NUM ^= 1;
					Koma_hInstance[_KomaType][_num].x = Koma_hInstance[_KomaType][_num].x - 50;
					Koma_hInstance[_KomaType][_num].y = Koma_hInstance[_KomaType][_num].y - 50;
					CursorMove_x = CursorMove_x - 50;
					CursorMove_y = CursorMove_y - 50;

				}
			}
			if (Key[KEY_INPUT_E] == 1)
			{
				if (KIN_MOVE_NUM == 0)
				{
					KIN_MOVE_NUM ^= 1;
					Koma_hInstance[_KomaType][_num].x = Koma_hInstance[_KomaType][_num].x + 50;
					Koma_hInstance[_KomaType][_num].y = Koma_hInstance[_KomaType][_num].y - 50;
					CursorMove_x = CursorMove_x + 50;
					CursorMove_y = CursorMove_y - 50;
				}
			}
			if (Key[KEY_INPUT_A] == 1)
			{
				if (KIN_MOVE_NUM == 0)
				{
					KIN_MOVE_NUM ^= 1;
					Koma_hInstance[_KomaType][_num].x = Koma_hInstance[_KomaType][_num].x - 50;
					CursorMove_x = CursorMove_x - 50;
				}
			}
			if (Key[KEY_INPUT_D] == 1)
			{
				if (KIN_MOVE_NUM == 0)
				{
					KIN_MOVE_NUM ^= 1;
					Koma_hInstance[_KomaType][_num].x = Koma_hInstance[_KomaType][_num].x + 50;
					CursorMove_x = CursorMove_x + 50;
				}
			}
			if (Key[KEY_INPUT_S] == 1)
			{
				if (KIN_MOVE_NUM == 0)
				{
					KIN_MOVE_NUM ^= 1;
					Koma_hInstance[_KomaType][_num].y = Koma_hInstance[_KomaType][_num].y + 50;
					CursorMove_y = CursorMove_y + 50;
				}
			}
		}
		if (Koma_hInstance[_KomaType][_num].turn == PI)
		{

		}
		break;
	case KAKU:
		break;
	case HISYA:
		break;
	case TOKIN:
		break;
	case NARIKYO:
		break;
	case NARIKEI:
		break;
	case NARIGIN:
		break;
	case RYUMA:
		break;
	case RYUOU:
		break;
	case OUSYO:
		break;
	default:
		break;
	}
	//
	//if (Key[KEY_INPUT_A] == 1)
	//{
	//	Koma_hInstance[_KomaType][_num].x = Koma_hInstance[_KomaType][_num].x - 50;
	//	CursorMove_x = CursorMove_x - 50;
	//}
	//if (Key[KEY_INPUT_D] == 1)
	//{
	//	Koma_hInstance[_KomaType][_num].x = Koma_hInstance[_KomaType][_num].x + 50;
	//	CursorMove_x = CursorMove_x + 50;
	//}
}

void FuncDrawKoma() {
	unsigned int cursor_grhandle = GrHandle[23];
	if (Enter_num == 1) {
		/*カーソルの移動*/
		if (Key[KEY_INPUT_W] == 1) {
			CursorMove_y = CursorMove_y - 50;
		}
		if (Key[KEY_INPUT_S] == 1) {
			CursorMove_y = CursorMove_y + 50;
		}
		if (Key[KEY_INPUT_A] == 1) {
			CursorMove_x = CursorMove_x - 50;
		}
		if (Key[KEY_INPUT_D] == 1) {
			CursorMove_x = CursorMove_x + 50;
		}
		if (Key[KEY_INPUT_Z] == 1)
		{
			CursorMove_y = CursorMove_y + 50;
			CursorMove_x = CursorMove_x - 50;
		}
		if (Key[KEY_INPUT_X] == 1)
		{
			CursorMove_y = CursorMove_y + 50;
			CursorMove_x = CursorMove_x + 50;
		}
		if (Key[KEY_INPUT_Q] == 1)
		{
			CursorMove_y = CursorMove_y - 50;
			CursorMove_x = CursorMove_x - 50;
		}
		if (Key[KEY_INPUT_E] == 1)
		{
			CursorMove_y = CursorMove_y - 50;
			CursorMove_x = CursorMove_x + 50;
		}
	}
	//
	//if (Enter_num == 0) {
	//	/*駒の移動*/
	//	if (Key[KEY_INPUT_W] == 1) {
	//		KomaMove_y = KomaMove_y - 50;
	//	}
	//	if (Key[KEY_INPUT_S] == 1) {
	//		KomaMove_y = KomaMove_y + 50;
	//	}
	//	if (Key[KEY_INPUT_A] == 1) {
	//		KomaMove_x = KomaMove_x - 50;
	//	}
	//	if (Key[KEY_INPUT_D] == 1) {
	//		KomaMove_x = KomaMove_x + 50;
	//	}
	//}
	if (CursorMove_x >= 530)
	{
		CursorMove_x = 530;
	}
	//if (KomaMove_x >= 530)
	//{
	//	KomaMove_x = 530;
	//}
	if (CursorMove_x <= 130)
	{
		CursorMove_x = 130;
	}
	//if (KomaMove_x <= 130)
	//{
	//	KomaMove_x = 130;
	//}
	if (CursorMove_y <= 50)
	{
		CursorMove_y = 50;
	}
	//if (KomaMove_y <= 50)
	//{
	//	KomaMove_y = 50;
	//}
	if (CursorMove_y >= 450)
	{
		CursorMove_y = 450;
	}
	//if (KomaMove_y >= 450)
	//{
	//	KomaMove_y = 450;
	//}

	for (unsigned int KomaType = 0; KomaType < KOMA_TYPE_MAX; KomaType++)
	{
		for (unsigned int num = 0; num < 20; num++)
		{
			if (Koma_hInstance[KomaType][num].x == CursorMove_x
				&& Koma_hInstance[KomaType][num].y == CursorMove_y
				&& Koma_hInstance[KomaType][num].turn == Turn
				&& (Enter_turn_num % 4 == 2 || Enter_turn_num % 4 == 0))
			{
				cursor_grhandle = Koma_hInstance[KomaType][num].grhandle;
				/*駒を動かす関数に移動*/
				FuncKomaMove(KomaType, num);
			}
		}
	}

	/*駒が置けるか*/

	if (Key[KEY_INPUT_RETURN] == 1) {
		/*Enterを押したらEnterを更新*/
		Enter_num ^= 1;
		Enter_turn_num++;
	}

	DrawBox(0, 0, 640, 480, GetColor(255, 255, 255), TRUE);// 画面全体を希望の色で塗りつぶす
	//DrawBox(120, 40, 520, 440, GetColor(0, 255, 255),TRUE);
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			DrawBox(120 + 50 * i, 40 + 50 * j, 140 + 50 * i, 60 + 50 * j, GetColor(0, 0, 0), TRUE);
		}
	}
	GetLocalTime(&stTime);
	wsprintf(strTime,
		"%d年 %d月 %d日   -------戻るときは、ESCキーを押してください-------\n%d時 %d分 %d秒",
		stTime.wYear, stTime.wMonth, stTime.wDay,
		stTime.wHour, stTime.wMinute, stTime.wSecond
	);
	DrawString(0, 0, strTime, GetColor(0, 0, 0));
	if (Enter_turn_num % 4 == 1)
	{
		DrawString(0, 240, "あなたの番です", GetColor(0, 0, 0));
		Turn = 0;
		NUM_W = 0;
		NUM_S = 0;
		NUM_A = 0;
		NUM_D = 0;
		NUM_Q = 0;
		NUM_E = 0;
		NUM_Z = 0;
		NUM_X = 0;
		KEI_MOVE_NUM = 0;
		GIN_MOVE_NUM = 0;
		KIN_MOVE_NUM = 0;
	}
	if (Enter_turn_num % 4 == 2)
	{
		DrawString(0, 240, "選択した駒を\n置いてください", GetColor(0, 0, 0));
		Turn = 0;
	}
	if (Enter_turn_num % 4 == 3)
	{
		DrawString(0, 240, "相手の番です", GetColor(0, 0, 0));
		Turn = PI;
		NUM_W = 0;
		NUM_S = 0;
		NUM_A = 0;
		NUM_D = 0;
		NUM_Q = 0;
		NUM_E = 0;
		NUM_Z = 0;
		NUM_X = 0;
		KEI_MOVE_NUM = 0;
		GIN_MOVE_NUM = 0;
		KIN_MOVE_NUM = 0;
	}
	if (Enter_turn_num % 4 == 0)
	{
		DrawString(0, 240, "選択した駒を\n置いてください", GetColor(0, 0, 0));
		Turn = PI;
	}
	/*カーソル,駒を描画*/
	for (unsigned int KomaType = 0; KomaType < KOMA_TYPE_MAX; KomaType++)
	{
		for (unsigned int num = 0; num < 20; num++)
		{
			DrawRotaGraph(Koma_hInstance[KomaType][num].x, Koma_hInstance[KomaType][num].y,
				Koma_hInstance[KomaType][num].rota, Koma_hInstance[KomaType][num].turn,
				Koma_hInstance[KomaType][num].grhandle, Koma_hInstance[KomaType][num].a);
		}
	}
	DrawRotaGraph(CursorMove_x, CursorMove_y, 0.05, Turn, cursor_grhandle, TRUE);
	//DrawRotaGraph(KomaMove_x, KomaMove_y, 0.2, Turn, GrHandle[0], TRUE);
	if (Key[KEY_INPUT_ESCAPE] == 1)
	{
		EnterPutNum = 0;
	}
	/*for (unsigned int i = 0; i < SHOGI_BOARD_HEIGHT; i++)
	{
		for (unsigned int j = 0; j < SHOGI_BOARD_WIDTH; j++)
		{
			wsprintf(ten[i][j], "・");
			DrawString(300 + 20 * j, 400 + 20 * i, ten[i][j], GetColor(0, 0, 0));
		}
	}*/
}

void FuncBackGroundAinmation() {
	DrawRotaGraph(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 0.25, PI, GrHandle[19], TRUE);
}

void tama() {
	int FPS = 60;
	int startTime = GetNowCount();
	if (x + vec > 640) {
		x = 640;
		vec *= -1;
	}
	if (x + vec < 0) {
		x = 0;
		vec *= -1;
	}
	x += vec;

	DrawCircle(x, 440, 5, 0xffffff, TRUE);
	int endTime = GetNowCount();
	WaitTimer((1000 / FPS) - (endTime - startTime));
}
void FuncMenu() {
	GetLocalTime(&stTime);
	wsprintf(strTime, "%d年 %d月 %d日\n%d時 %d分 %d秒",
		stTime.wYear, stTime.wMonth, stTime.wDay,
		stTime.wHour, stTime.wMinute, stTime.wSecond
	);
	DrawString(0, 0, strTime, GetColor(255, 255, 255));
}

// 読み込み画面描画関数
void DrawLoadingScreen(void)
{
	// 「読み込み中」の表示
	DrawString(0, 0, "Now Loading ...", GetColor(255, 255, 255));

	// ゲージの全体を灰色で描画
	DrawBox(0, 32, GAUGEWIDTH, 56, GetColor(128, 128, 128), TRUE);

	// 現時点で読み込み終わっている分を白色で描画
	DrawBox(0, 32, LoadingFile * GAUGEWIDTH / FILENUM, 56, GetColor(255, 255, 255), TRUE);
}

int gpUpdateKey()
{
	char tmpKey[256]; // 現在のキーの入力状態を格納する
	GetHitKeyStateAll(tmpKey); // 全てのキーの入力状態を得る
	for (int i = 0; i < 256; i++) {
		if (tmpKey[i] != 0) { // i番のキーコードに対応するキーが押されていたら
			Key[i]++;     // 加算
		}
		else {              // 押されていなければ
			Key[i] = 0;   // 0にする
		}
	}
	return 0;
}

int SettingBeforeInit(bool wndMode) {
	ChangeWindowMode(wndMode);
	if (wndMode)
	{
		//メニューIDの読み込み
		LoadMenuResource(IDR_MENU1);
	}
	return 0;
}

int SettingAfterInit() {
	//裏描画設定
	SetDrawScreen(DX_SCREEN_BACK);
	hMainWnd = GetMainWindowHandle();
	dxWndProc = (WNDPROC)GetWindowLong(hMainWnd, GWL_WNDPROC);
	SetWindowLong(hMainWnd, GWL_WNDPROC, (LONG)MyProc);
	return 0;
}

int FuncLoad(int n) {
	//配列に画像の名前を代入する
	TCHAR array[FILENUM - 1][50];
	switch (n)
	{
	case 0:/*歩*/
		return LoadGraph("画像/Shogi_pawn[1].jpg");
		break;
	case 1:/*香*/
		return LoadGraph("画像/Shogi_lance[1].jpg");
		break;
	case 2:/*桂*/
		return LoadGraph("画像/Shogi_knight[1].jpg");
		break;
	case 3:/*銀*/
		return LoadGraph("画像/Shogi_silver[1].jpg");
		break;
	case 4:/*金*/
		return LoadGraph("画像/Shogi_gold[1].jpg");
		break;
	case 5:/*角*/
		return LoadGraph("画像/Shogi_bishop[1].jpg");
		break;
	case 6:/*飛車*/
		return LoadGraph("画像/Shogi_rook[1].jpg");
		break;
	case 7:/*と金*/
		return LoadGraph("Shogi_pawn_p[1].jpg");
		break;
	case 8:/*成香*/
		return LoadGraph("画像/Shogi_lance_p[1].jpg");
		break;
	case 9:/*成桂*/
		return LoadGraph("画像/Shogi_knight_p[1].jpg");
		break;
	case 10:/*成銀*/
		return LoadGraph("Shogi_silver_p[1].jpg");
		break;
	case 11:/*龍馬*/
		return LoadGraph("画像/Shogi_bishop_p[1].jpg");
		break;
	case 12:/*竜王*/
		return LoadGraph("画像/Shogi_rook_p[1].jpg");
		break;
	case 13:/*王*/
		return LoadGraph("画像/Shogi_king[1].jpg");
		break;
	case 14:
		return LoadGraph("画像/IMG20190730191029.jpg");
		break;
	case 15:
		return LoadGraph("画像/IMG20190730191029.jpg");
		break;
	case 16:
		return LoadGraph("画像/IMG20190730191029.jpg");
		break;
	case 17:
		return LoadGraph("画像/IMG20190730191029.jpg");
		break;
	case 18:
		return LoadGraph("画像/IMG20190730191029.jpg");
		break;
	case 19:
		return LoadGraph("画像/IMG20190730191029.jpg");
		break;
	case 20:
		return LoadGraph("画像/maxresdefault-1[1].jpg");
		break;
	case 21:
		/*タイトル*/
		return SetMainWindowText("将棋");
		break;
	case 22:
		/*アイコン*/
		return SetWindowIconID(104);
		break;
	case 23:
		return LoadGraph("画像/risu-illust8[1].png");
	default:

		break;
	}
}

LRESULT CALLBACK MyProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {
	//HDC hdc;
	//PAINTSTRUCT ps;
	//RECT rctSize;
	switch (msg) {
	case WM_COMMAND:
		switch (LOWORD(wp)) {
			//「ファイル読み込み」メニューが選択された場合
		case ID_FILE:
			MyOpen(hWnd);
			break;
		case ID_SETTEI:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, MyDlgProc);
			break;
		case ID_SYOUGI:
			/*将棋をスタートさせる*/
			/*確認用メッセージ*/
			if (MessageBox(
				NULL,
				"将棋をスタートします",
				"確認してください！",
				MB_OKCANCEL
			) == IDOK)
			{
				/*別のウィンドウを作る*/
			}
			else {
				return FALSE;
			}
		case IDM_END:
			SendMessage(hWnd, WM_CLOSE, NULL, NULL);
			break;
			//case WM_TIMER:
			//	GetLocalTime(&stTime);
			//	InvalidateRect(hWnd, NULL, TRUE);
			//	return 0;
			//case WM_PAINT:
			//	hdc = BeginPaint(hWnd, &ps);
			//	GetClientRect(hWnd, &rctSize);
			//	DrawText(hdc, strTime, -1, &rctSize, DT_LEFT);
			//	EndPaint(hWnd, &ps);
		}
		break;
	}
	return CallWindowProc(dxWndProc, hWnd, msg, wp, lp);
}

int MyOpen(HWND hWnd) {

	//ファイルを開く為の設定用構造体
	OPENFILENAME ofn;
	//ここに指定ファイルの絶対パスが代入される
	char szFile[MAX_PATH];
	//memset関数で変数・配列の中身を全てNULL、\0に
	memset(&ofn, NULL, sizeof(OPENFILENAME));
	memset(szFile, '\0', sizeof(szFile));

	//自分自身のサイズ
	ofn.lStructSize = sizeof(OPENFILENAME);
	//親ウィンドウのハンドル
	ofn.hwndOwner = hWnd;
	//表示させるファイルのフィルタリング
	ofn.lpstrFilter = "PNG Files {*.png}\0*.png\0"
		"JPEG Files {*.jpg}\0*.jpg\0"
		"BITMAP Files {*.bmp}\0*.bmp\0\0";
	//パスを代入する配列
	ofn.lpstrFile = szFile;
	//パスの最大文字数
	ofn.nMaxFile = MAX_PATH;
	//ファイル名で拡張子が指定されなかった場合に追加する文字列
	ofn.lpstrDefExt = ".png";
	//ウィンドウの名前
	ofn.lpstrTitle = "画像ファイルの選択";

	//ファイルオープンに失敗したらreturn
	if (GetOpenFileName(&ofn) == 0) return -1;

	//ファイル読み込み
	gHandle = LoadGraph(szFile);
	return 0;
}

BOOL CALLBACK MyDlgProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp) {
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(1);
		break;
	case IDOK:
		return DefWindowProc(hDlg, msg, wp, lp);
	default:
		return DefWindowProc(hDlg, msg, wp, lp);
	}
	return FALSE;
}