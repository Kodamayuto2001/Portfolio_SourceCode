//
///*�K�v�ȃw�b�_�[�t�@�C���̃C���N���[�h*/
//#include "DxLib.h"
//
///*�V���{����`�y�у}�N��*/
//#define WINDOW_WIDTH  640
//#define WINDOW_HEIGHT 480
//#define SHOGI_BOARD_HEIGHT 9
//#define SHOGI_BOARD_WIDTH 9
//
///*�����Ղ̂̏c���T�C�Y���������ق��ɍ��킹��*/
//int FuncCompare() {
//	if (WINDOW_WIDTH > WINDOW_HEIGHT) {
//		return (int)WINDOW_WIDTH;
//	}
//	else {
//		return (int)WINDOW_HEIGHT;
//	}
//}
//
///*�����ՂP�̃Z�������艽�s�N�Z�����v�Z����֐�(�]����v�Z)*/
//int CELL_LENGTH_CALCULATION(int length, int* surplus) {
//	int num1;/*cell�̈�ӂ̒���*/
//	num1 = length / 90;
//	num1 = num1 * 10;
//
//	/*�����Վl�ӂ̒����̂��܂�*/
//	/*��O���X���[����܂���:�������݃A�N�Z�X�ᔽ�Bsurplus �� nullptr �ł��� */
//	*surplus = length % 90;
//	*surplus = *surplus / 2;
//
//	return num1;
//}
//
//int Key[256]; // �L�[��������Ă���t���[�������i�[����
//int gpUpdateKey() {
//	char tmpKey[256]; // ���݂̃L�[�̓��͏�Ԃ��i�[����
//	GetHitKeyStateAll(tmpKey); // �S�ẴL�[�̓��͏�Ԃ𓾂�
//	for (int i = 0; i < 256; i++) {
//		if (tmpKey[i] != 0) { // i�Ԃ̃L�[�R�[�h�ɑΉ�����L�[��������Ă�����
//			Key[i]++;     // ���Z
//		}
//		else {              // ������Ă��Ȃ����
//			Key[i] = 0;   // 0�ɂ���
//		}
//	}
//	return 0;
//}
//
///*������9*9�ƍ��W�i�[�p�ϐ����֘A�t����*/
//class Koma
//{
//public:
//	void CELL_XY(int x, int y);/*�Z�b�g�p�֐�*/
//	void CellCalc();/*�Z�b�g�p�֐�*/
//	void DBox();/*�`��p�֐�*/
//private:
//	int x, y;//���W�i�[�p�ϐ�
//	int cell[SHOGI_BOARD_HEIGHT - 1][SHOGI_BOARD_WIDTH - 1];/*���W�i�[�p�z��*/
//	int cell_x_start;
//	int cell_y_start;
//	int cell_x_end;
//	int cell_y_end;
//};
///*DrawBox�悤�Ɍv�Z���ĕϐ���ۑ�*/
//void Koma::CellCalc() {
//	cell_x_start = 15 + 50 * x;
//	cell_y_start = 15 + 50 * y;
//	cell_x_end = 65 + 50 * x;
//	cell_y_end = 65 + 50 * y;
//}
///*���̏�����9*9�̒��̂��擾*/
//void Koma::CELL_XY(int x, int y) {
//	Koma::x = x;
//	Koma::y = y;
//}
//
//void Koma::DBox() {
//	DrawBox(cell_x_start, cell_y_start, cell_x_end, cell_y_end, GetColor(255, 255, 255), FALSE);
//}
//
///*���C���֐�*/
//int WINAPI WinMain(HINSTANCE hInstance,
//	HINSTANCE hPrevInstance,
//	LPSTR lpCmdLine,
//	int nCmdShow)
//{
//	ChangeWindowMode(TRUE);
//	DxLib_Init();
//	SetDrawScreen(DX_SCREEN_BACK);
//
//	/*�֐�FuncCompare�̖߂�l�������Ղ̏c���T�C�Y�̒萔�ɂ���*/
//	const int SYOGI_BOARD = FuncCompare();
//
//	/*������9*9��1�̃Z������߂�s�N�Z����*/ /*�A�N�Z�X�ᔽ*/
//	const int CELL_LENGTH = CELL_LENGTH_CALCULATION(SYOGI_BOARD, (int*)0);
//
//	/*�]������߂�*/
//	int SURPLUS;
//	CELL_LENGTH_CALCULATION(0, &SURPLUS);
//
//	/*�C���X�^���X������*/
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
#include<windowsx.h>/*�t�@�C�����J���p�w�b�_*/
#include"resource.h"

#define WINDOW_WIDTH  (unsigned const int)640
#define WINDOW_HEIGHT (unsigned const int)480
#define PI (double)3.141592654
// �ǂݍ��ރt�@�C���̑���
#define FILENUM 100
// �Q�[�W�̕�
#define GAUGEWIDTH 200
//�����{�[�h
#define SHOGI_BOARD_HEIGHT 9
#define SHOGI_BOARD_WIDTH 9
#define START_BUTTON 2
#define SHOGI_BOARD_SIZE 400

// �摜�n���h��
static int GrHandle[FILENUM];

// �ǂݍ���ł���摜�̔ԍ�
static int LoadingFile;

WNDPROC dxWndProc;

//���C���E�B���h�E�̃n���h��
HWND hMainWnd;

//�C���X�^���X�n���h�����i�[����O���[�o���ϐ�
HINSTANCE hInst;

//�摜�n���h���̏����l��-1(��MyOpen�ł̃G���[�l)
static int gHandle = -1;

static int x = 320, vec = 5;
static int Key[256]; // �L�[��������Ă���t���[�������i�[����
static unsigned int KomaMove_x = 130;
static unsigned int KomaMove_y = 50;
static double Turn = 0;
static unsigned int CursorMove_x = 130;
static unsigned int CursorMove_y = 50;
static unsigned int Enter_num = 0;
static unsigned int SelectNum = 0; // ���݂̑I��ԍ�
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

//�v���g�^�C�v�錾
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
	HU,/*��*/
	KYOU,/*����*/
	KEI,/*�j�n*/
	GIN,/*��*/
	KIN,/*��*/
	KAKU,/*�p*/
	HISYA,/*���*/
	TOKIN,/*�Ƌ�*/
	NARIKYO,/*����*/
	NARIKEI,/*���j*/
	NARIGIN,/*����*/
	RYUMA,/*���n*/
	RYUOU,/*����*/
	OUSYO,/*��*/
	KOMA_TYPE_MAX//�񋓒萔=14
};

// WinMain�֐�
int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{

	MessageBox(
		NULL,
		_T("�Q�[�����n�߂܂�"),
		_T("���"),
		NULL
	);

	//�C���X�^���X�n���h���̑��
	hInst = hInstance;

	SettingBeforeInit(true);

	// �c�w���C�u�����̏�����
	DxLib_Init();

	// �`���𗠉�ʂɂ���
	SettingAfterInit();

	// �ǂݍ��މ摜�̐������J��Ԃ�
	for (LoadingFile = 0; LoadingFile < FILENUM; LoadingFile++)
	{
		GrHandle[LoadingFile] = FuncLoad(LoadingFile);

		// �Q�O�ǂݍ��ݏI��閈�ɓǂݍ��ݒ���ʂ����X�V����
		if (LoadingFile % 2 == 0)
		{
			// ��ʂ̏�����
			ClearDrawScreen();

			// �ǂݍ��ݒ���ʂ�`��
			DrawLoadingScreen();

			// ����ʂ̓��e��\��ʂɔ��f
			ScreenFlip();

			// ���b�Z�[�W����
			if (ProcessMessage() != 0) break;
		}
	}
	EnterPutNum = 0;
	/*��̏�����*/
	Koma_Calc_init();
	while (ScreenFlip() == 0 &&
		ProcessMessage() == 0 &&
		ClearDrawScreen() == 0 &&
		gpUpdateKey() == 0)
	{
		FuncBackGroundAinmation();
		FuncMenu();
		tama();/*�V��*/
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
			///*Enter�������ꂽ�烍�[�h���ƕ`�悵���̂��AWINDOW��CREATE����*/
			///*�E�B���h�E�̓o�^*/
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
			///*�E�B���h�E�̐���*/
			//HWND hWnd_yuto;
			////HWND CreateWindow(
			////	LPCTSTR lpClassName, LPCTSTR lpWindowName,
			////	DWORD dwStyle,
			////	int x, int y, int nWidth, int nHeight,
			////	HWND hWndParent, HMENU hMenu,
			////	HANDLE hInstance, LPVOID lpParam
			////);
			//hWnd_yuto = CreateWindow(
			//	"����",
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
			///*�E�B���h�E��\������*/
			//ShowWindow(hWnd_yuto, nCmdShow);
			///*�\����������*/
			//UpdateWindow(hWnd_yuto);
			///*�t�H�[�J�X���w��*/
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
					_T("W,S,A,D,Q,E,Z,X�L�[���g���ċ�̓�����\�����܂�\n��O�I�ɂ͌j�n��A,D�L�[��p���ĕ\�����܂�\nW�E�E�E��\nS�E�E�E��\nA�E�E�E��\nD�E�E�E�E\nQ�E�E�E����\nE�E�E�E�E��\nZ�E�E�E����\nX�E�E�E�E��\nEnter�L�[�Ō���\n"),
					_T("��̓��������ɂ���"),
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
	// �c�w���C�u�����̌�n��
	DxLib_End();
	// �\�t�g�̏I��
	return 0;
}

//
//LRESULT  CALLBACK  wndproc_yuto(
//	HWND hWnd,
//	UINT msg,
//	WPARAM wParam,
//	LPARAM lParam) 
//{
//	//�n���ꂽ message ����A�C�x���g�̎�ނ���͂���
//	switch (msg) {
//		//----�I������----
//	case WM_DESTROY:
//		PostQuitMessage(0);
//		break;
//
//		//----�f�t�H���g�̏���----
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
	//�v�Z�t�F�[�Y
	if (Key[KEY_INPUT_W] == 1)
	{
		SelectNum = (SelectNum + 1) % START_BUTTON;
	}
	if (Key[KEY_INPUT_A] == 1)
	{
		/*�����Ȃ�*/
	}
	if (Key[KEY_INPUT_S] == 1)
	{
		SelectNum = (SelectNum + 1) % START_BUTTON;
	}
	if (Key[KEY_INPUT_D] == 1)
	{
		/*�����Ȃ�*/
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
	//�`��t�F�[�Y
	for (int i = 0; i < START_BUTTON; i++)
	{
		DrawString(START_MENU[i].x, START_MENU[i].y, START_MENU[i].MenuName, GetColor(50, 60, 100));
	}

}
//
//typedef struct {
//	int x, y;//���W�i�[�p�ϐ�
//	enum KOMA_TYPE KomaType[KOMA_TYPE_MAX];//��̃^�C�v
//	int KomaAngle;//�G�̋�A�����̋
//	int NarigomaAngle;//�G�̐����A�����̐���
//	enum KOMA_TYPE Motigoma[KOMA_TYPE_MAX];//������
//	int MotigomaAngle;//�G�̎�����H�����̎�����H
//	int n, m;//�����p��������W�i�[�p�ϐ�
//	int N, M;//�G�p��������W�i�[�p�ϐ�
//	char Motigoma_Select[KOMA_TYPE_MAX][100];//�ǂ̎����������̂������[�U�[�ɕ����点�邽�߂ɕ������i�[���āA�����̎��������o��
//	char Teki_Motigoma_Select[KOMA_TYPE_MAX][100];
//	int Nari_Select;//�O�̎��E�E�E�H�@�P�̎��E�E�E�H�@�r���I�_���a
//}Koma;/*�v�Z�p�̍\���̂̔z��*/
//
//Koma Koma_box[81] = {
//	/*�����l�̐ݒ�*/
//	{/*����*/},{/*�j�n*/},{/*�⏫*/},{/*����*/},{/*�ʏ�*/},{/*����*/},{/*�⏫*/},{/*�j�n*/},{/*����*/},
//	{/**/},{/*���*/},{/**/},{/**/},{/**/},{/**/},{/**/},{/*�p�s*/},{/**/},
//	{/*����*/},{/*����*/},{/*����*/},{/*����*/},{/*����*/},{/*����*/},{/*����*/},{/*����*/},{/*����*/},
//	{/**/},{/**/},{/**/},{/**/},{/**/},{/**/},{/**/},{/**/},{/**/},
//	{/**/},{/**/},{/**/},{/**/},{/**/},{/**/},{/**/},{/**/},{/**/},
//	{/**/},{/**/},{/**/},{/**/},{/**/},{/**/},{/**/},{/**/},{/**/},
//	{/*����*/},{/*����*/},{/*����*/},{/*����*/},{/*����*/},{/*����*/},{/*����*/},{/*����*/},{/*����*/},
//	{/**/},{/*�p�s*/},{/**/},{/**/},{/**/},{/**/},{/**/},{/*���*/},{/**/},
//	{/*����*/},{/*�j�n*/},{/*�⏫*/},{/*����*/},{/*����*/},{/*����*/},{/*�⏫*/},{/*�j�n*/},{/*����*/},
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
		/*����̋���Ƃ�Ƃ�����̋�������B�����ăJ�[�\���̃^�[���Ɠ����ق��̎�����{�[�h�ɕ`�悵�A������i���̃^�[���̂ق��j�ɕۑ�����*/
		/*���͈�O�ɂ����i�߂Ȃ�*/
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
							/*�����ړ���������ɋ����̂ł���΂����ɂ͈ړ��ł��Ȃ�*/
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
							/*�����ړ���������ɋ����̂ł���΂����ɂ͈ړ��ł��Ȃ�*/
							Koma_hInstance[_KomaType][_num].y = Koma_hInstance[_KomaType][_num].y - 50;
							CursorMove_y = CursorMove_y - 50;
						}
					}
				}
			}
		}
		break;
	case KEI:
		/*�j�n����񂵂��ړ��ł��Ȃ�����*/
		if (Koma_hInstance[_KomaType][_num].turn == 0)
		{
			if (Key[KEY_INPUT_A] == 1)
			{
				if (KEI_MOVE_NUM == 0)
				{
					KEI_MOVE_NUM ^= 1;
					/*�㍶�Ɉړ�����*/
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
					/*��E�Ɉړ�����*/
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
					/*�����Ɉړ�����*/
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
					/*���E�Ɉړ�����*/
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
		/*����ړ�����������������Ȃ�����*/
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
		/*�J�[�\���̈ړ�*/
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
	//	/*��̈ړ�*/
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
				/*��𓮂����֐��Ɉړ�*/
				FuncKomaMove(KomaType, num);
			}
		}
	}

	/*��u���邩*/

	if (Key[KEY_INPUT_RETURN] == 1) {
		/*Enter����������Enter���X�V*/
		Enter_num ^= 1;
		Enter_turn_num++;
	}

	DrawBox(0, 0, 640, 480, GetColor(255, 255, 255), TRUE);// ��ʑS�̂���]�̐F�œh��Ԃ�
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
		"%d�N %d�� %d��   -------�߂�Ƃ��́AESC�L�[�������Ă�������-------\n%d�� %d�� %d�b",
		stTime.wYear, stTime.wMonth, stTime.wDay,
		stTime.wHour, stTime.wMinute, stTime.wSecond
	);
	DrawString(0, 0, strTime, GetColor(0, 0, 0));
	if (Enter_turn_num % 4 == 1)
	{
		DrawString(0, 240, "���Ȃ��̔Ԃł�", GetColor(0, 0, 0));
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
		DrawString(0, 240, "�I���������\n�u���Ă�������", GetColor(0, 0, 0));
		Turn = 0;
	}
	if (Enter_turn_num % 4 == 3)
	{
		DrawString(0, 240, "����̔Ԃł�", GetColor(0, 0, 0));
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
		DrawString(0, 240, "�I���������\n�u���Ă�������", GetColor(0, 0, 0));
		Turn = PI;
	}
	/*�J�[�\��,���`��*/
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
			wsprintf(ten[i][j], "�E");
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
	wsprintf(strTime, "%d�N %d�� %d��\n%d�� %d�� %d�b",
		stTime.wYear, stTime.wMonth, stTime.wDay,
		stTime.wHour, stTime.wMinute, stTime.wSecond
	);
	DrawString(0, 0, strTime, GetColor(255, 255, 255));
}

// �ǂݍ��݉�ʕ`��֐�
void DrawLoadingScreen(void)
{
	// �u�ǂݍ��ݒ��v�̕\��
	DrawString(0, 0, "Now Loading ...", GetColor(255, 255, 255));

	// �Q�[�W�̑S�̂��D�F�ŕ`��
	DrawBox(0, 32, GAUGEWIDTH, 56, GetColor(128, 128, 128), TRUE);

	// �����_�œǂݍ��ݏI����Ă��镪�𔒐F�ŕ`��
	DrawBox(0, 32, LoadingFile * GAUGEWIDTH / FILENUM, 56, GetColor(255, 255, 255), TRUE);
}

int gpUpdateKey()
{
	char tmpKey[256]; // ���݂̃L�[�̓��͏�Ԃ��i�[����
	GetHitKeyStateAll(tmpKey); // �S�ẴL�[�̓��͏�Ԃ𓾂�
	for (int i = 0; i < 256; i++) {
		if (tmpKey[i] != 0) { // i�Ԃ̃L�[�R�[�h�ɑΉ�����L�[��������Ă�����
			Key[i]++;     // ���Z
		}
		else {              // ������Ă��Ȃ����
			Key[i] = 0;   // 0�ɂ���
		}
	}
	return 0;
}

int SettingBeforeInit(bool wndMode) {
	ChangeWindowMode(wndMode);
	if (wndMode)
	{
		//���j���[ID�̓ǂݍ���
		LoadMenuResource(IDR_MENU1);
	}
	return 0;
}

int SettingAfterInit() {
	//���`��ݒ�
	SetDrawScreen(DX_SCREEN_BACK);
	hMainWnd = GetMainWindowHandle();
	dxWndProc = (WNDPROC)GetWindowLong(hMainWnd, GWL_WNDPROC);
	SetWindowLong(hMainWnd, GWL_WNDPROC, (LONG)MyProc);
	return 0;
}

int FuncLoad(int n) {
	//�z��ɉ摜�̖��O��������
	TCHAR array[FILENUM - 1][50];
	switch (n)
	{
	case 0:/*��*/
		return LoadGraph("�摜/Shogi_pawn[1].jpg");
		break;
	case 1:/*��*/
		return LoadGraph("�摜/Shogi_lance[1].jpg");
		break;
	case 2:/*�j*/
		return LoadGraph("�摜/Shogi_knight[1].jpg");
		break;
	case 3:/*��*/
		return LoadGraph("�摜/Shogi_silver[1].jpg");
		break;
	case 4:/*��*/
		return LoadGraph("�摜/Shogi_gold[1].jpg");
		break;
	case 5:/*�p*/
		return LoadGraph("�摜/Shogi_bishop[1].jpg");
		break;
	case 6:/*���*/
		return LoadGraph("�摜/Shogi_rook[1].jpg");
		break;
	case 7:/*�Ƌ�*/
		return LoadGraph("Shogi_pawn_p[1].jpg");
		break;
	case 8:/*����*/
		return LoadGraph("�摜/Shogi_lance_p[1].jpg");
		break;
	case 9:/*���j*/
		return LoadGraph("�摜/Shogi_knight_p[1].jpg");
		break;
	case 10:/*����*/
		return LoadGraph("Shogi_silver_p[1].jpg");
		break;
	case 11:/*���n*/
		return LoadGraph("�摜/Shogi_bishop_p[1].jpg");
		break;
	case 12:/*����*/
		return LoadGraph("�摜/Shogi_rook_p[1].jpg");
		break;
	case 13:/*��*/
		return LoadGraph("�摜/Shogi_king[1].jpg");
		break;
	case 14:
		return LoadGraph("�摜/IMG20190730191029.jpg");
		break;
	case 15:
		return LoadGraph("�摜/IMG20190730191029.jpg");
		break;
	case 16:
		return LoadGraph("�摜/IMG20190730191029.jpg");
		break;
	case 17:
		return LoadGraph("�摜/IMG20190730191029.jpg");
		break;
	case 18:
		return LoadGraph("�摜/IMG20190730191029.jpg");
		break;
	case 19:
		return LoadGraph("�摜/IMG20190730191029.jpg");
		break;
	case 20:
		return LoadGraph("�摜/maxresdefault-1[1].jpg");
		break;
	case 21:
		/*�^�C�g��*/
		return SetMainWindowText("����");
		break;
	case 22:
		/*�A�C�R��*/
		return SetWindowIconID(104);
		break;
	case 23:
		return LoadGraph("�摜/risu-illust8[1].png");
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
			//�u�t�@�C���ǂݍ��݁v���j���[���I�����ꂽ�ꍇ
		case ID_FILE:
			MyOpen(hWnd);
			break;
		case ID_SETTEI:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, MyDlgProc);
			break;
		case ID_SYOUGI:
			/*�������X�^�[�g������*/
			/*�m�F�p���b�Z�[�W*/
			if (MessageBox(
				NULL,
				"�������X�^�[�g���܂�",
				"�m�F���Ă��������I",
				MB_OKCANCEL
			) == IDOK)
			{
				/*�ʂ̃E�B���h�E�����*/
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

	//�t�@�C�����J���ׂ̐ݒ�p�\����
	OPENFILENAME ofn;
	//�����Ɏw��t�@�C���̐�΃p�X����������
	char szFile[MAX_PATH];
	//memset�֐��ŕϐ��E�z��̒��g��S��NULL�A\0��
	memset(&ofn, NULL, sizeof(OPENFILENAME));
	memset(szFile, '\0', sizeof(szFile));

	//�������g�̃T�C�Y
	ofn.lStructSize = sizeof(OPENFILENAME);
	//�e�E�B���h�E�̃n���h��
	ofn.hwndOwner = hWnd;
	//�\��������t�@�C���̃t�B���^�����O
	ofn.lpstrFilter = "PNG Files {*.png}\0*.png\0"
		"JPEG Files {*.jpg}\0*.jpg\0"
		"BITMAP Files {*.bmp}\0*.bmp\0\0";
	//�p�X��������z��
	ofn.lpstrFile = szFile;
	//�p�X�̍ő啶����
	ofn.nMaxFile = MAX_PATH;
	//�t�@�C�����Ŋg���q���w�肳��Ȃ������ꍇ�ɒǉ����镶����
	ofn.lpstrDefExt = ".png";
	//�E�B���h�E�̖��O
	ofn.lpstrTitle = "�摜�t�@�C���̑I��";

	//�t�@�C���I�[�v���Ɏ��s������return
	if (GetOpenFileName(&ofn) == 0) return -1;

	//�t�@�C���ǂݍ���
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