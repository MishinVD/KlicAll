#undef UNICODE
#include <windows.h>
#include <string>
#include <vector>
#include <wingdi.h>
#include <winuser.h>
#include <cmath>

struct Points
{
	double x;
	double y;
	Points(double x1, double y1): x(x1), y(y1) {}
};

using namespace std;

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL InitApplication(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow);

LPCSTR szClassName = "WinAPI";
LPCSTR szTitle =     "ѳ�������";

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow)
{
  MSG msg;
  /*���� �������� hPrevInstance � Win32 ������ ����� NULL���������� ��������� ��� �������� */
  if (!hPrevInstance) 
  {  /* �������������� ���������� -  �������������� ������ ������ ���� � ������������ ��� */
    if (!InitApplication(hInstance)) 
      return (FALSE);
  }
   /* ��������� �������� ����� ���������� -     ������� ������� ���� ���������� */
  if (!InitInstance(hInstance, nCmdShow)) 
    return (FALSE);  
  
  /* ���� ��������� ��������� */
  while (GetMessage(&msg, NULL, 0, 0)) 
  {   	TranslateMessage(&msg);
    		DispatchMessage(&msg);
  }
  return (msg.wParam);
}

BOOL InitApplication(HINSTANCE hInstance)
{
  WNDCLASS  wc;
  // ��������� ��������� ������ ���� WNDCLASS
  wc.style         = CS_HREDRAW | CS_VREDRAW;
  wc.lpfnWndProc   = (WNDPROC)WndProc;
  wc.cbClsExtra    = 0;
  wc.cbWndExtra    = 0;
  wc.hInstance     = hInstance;
  wc.hIcon         = LoadIcon(NULL, IDI_ASTERISK);
  wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
  wc.hbrBackground = (HBRUSH)COLOR_3DSHADOW;
  wc.lpszMenuName  = NULL;
  wc.lpszClassName = szClassName;
  // ������������ ����� ����
  return RegisterClass(&wc);
} 
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
  HWND hWnd;
  hWnd = CreateWindow(
    szClassName,         // ��������� �� ������ ������������������� ����� ������
    szTitle,             // ��������� �� ��������� ����
    WS_OVERLAPPEDWINDOW, // ����� ����
    10,       // �������������� ���������� ����
    10,       // ������������ ���������� ����
    1200,       // ������ ����
    600,       // ������ ����
    NULL,                // ���������� ������������� ����
    NULL,                // ���������� ���� ����
    hInstance,           // ���������� ���������� ����������
    NULL);               // ��������� �� �������������� ������ ����

  if (!hWnd)    return (FALSE); 
  ShowWindow(hWnd, nCmdShow);
  UpdateWindow(hWnd);
  return (TRUE);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	static int sx, sy;
	static double time=0, time1, time2;
	HDC hdc, hdc1;
	static char out[10], outx[100], outy[100];
	vector<Points> point;
	vector<Points>::iterator it;
 switch(message)
  {
  case WM_SIZE:
	  sx=LOWORD(lParam);
	  sy=HIWORD(lParam);  
	  break;
  case WM_CREATE:
	  SetTimer (hwnd, 1, 100, NULL);
	  break;
  case WM_TIMER:
	  time+=3;
	  InvalidateRect(hwnd, NULL, true);
	  break;
  case WM_PAINT:
	  hdc = BeginPaint(hwnd, &ps);
	  for (double t=0; t<sx; t+=12*sx/1200)
		  point.push_back(Points(t, sy/2-(sy/2-60)*sin(t/75)));
	  for (it=point.begin(); it!=(--point.end()); it++)
	  {
		  MoveToEx(hdc, it->x, it->y, NULL);
		  LineTo(hdc, (it+1)->x, (it+1)->y);
	  }
	  time1=(int)time%sx;
	  time2=(int)time%1200;
	  Ellipse(hdc, time1-40, sy/2-(sy/2-60)*sin(time1/75)-40, time1+40, sy/2-(sy/2-60)*sin(time1/75)+40);
	  MoveToEx(hdc, time1, sy/2-(sy/2-60)*sin(time1/75), NULL);
	  LineTo(hdc, time1-40*sin(time1/5), sy/2-(sy/2-60)*sin(time1/75)+40*cos(time1/5));
	  EndPaint(hwnd, &ps);
	  break;
  case WM_DESTROY:
	  PostQuitMessage(0);
	  break;
    default:
      return DefWindowProc(hwnd, message, wParam, lParam);
  }
 return  0;
}
