#include "stdafx.h"
#include "Win32Project1.h"
#include <windows.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include "resource.h"

#include "log.h"

void log_init(const char* log_path, const char* program, LogLevel level);

#if _MSC_VER
#define snprintf _snprintf_s
#endif

const char GameName[] = "QQ��Ϸ - ��������ɫ��";
HDC hScrnDC;
POINT position;
#define nothing                 0x704C30     //����������ֵ
//#define blank                   16777215  //�հ״�����ֵ
#define BLOCK_PIXEL_ROW         31          //ÿ���������������ص���
#define BLOCK_PIXEL_COLUMN      35          //ÿ����������������ص���
#define NUM_POINTS_PER_BLOCK    9           //ÿ����ȡ���ٸ��㣬��Ϊ��֤�������Ƿ���ͬ��֤��
#define NUM_ROW                 11          //
#define NUM_COLUMN              19
#define GAP_LEFT                10
#define GAP_TOP                 179
COLORREF g_map[NUM_POINTS_PER_BLOCK][NUM_ROW][NUM_COLUMN] = { 0 };
RECT g_rect;

int g_do_ok_num = 0;

HWND try_to_get_instanceid_by_name(const char *name) {
    HWND hwnd = NULL;
    hwnd = FindWindow(NULL, name);
    if (hwnd != NULL)
    {
        MessageBox(NULL, TEXT("�ҵ�����!"), TEXT("message"), MB_OK | MB_ICONWARNING);
    }
    else
    {
        MessageBox(NULL, TEXT("û���ҵ�����!"), TEXT("message"), MB_OK | MB_ICONWARNING);
    }

    return hwnd;
}

BOOL is_same(int i, int j, int s, int t)
{
    if (i == s && j == t || i >= NUM_ROW || s >= NUM_ROW || j >= NUM_COLUMN || t >= NUM_COLUMN)
        return FALSE;

    int m = 0;
    for (m = 0; m < NUM_POINTS_PER_BLOCK; m++) {
        if (g_map[m][i][j] != g_map[m][s][t])
            return FALSE;
    }
    return TRUE;
}
BOOL is_same(int i, int j, COLORREF val)
{
    if (i >= NUM_ROW || j >= NUM_COLUMN)
        return FALSE;

    int m = 0;
    for (m = 0; m < NUM_POINTS_PER_BLOCK; m++) {
        if (g_map[m][i][j] != val) {
            return FALSE;
        }
    }
    ilog("i:%d j:%d color:0x%x\n", i, j, g_map[m][i][j]);
    return TRUE;
}
void draw_rect(int i, int j)
{
    int k;
    char out_txt[512] = { 0 };
    COLORREF color = RGB(255, 0, 0);  //����Ϊ��ɫ
    int point_left = g_rect.left + j * BLOCK_PIXEL_ROW;
    int point_top = g_rect.top + i * BLOCK_PIXEL_COLUMN;
    snprintf(out_txt, 512, "draw_rect rect=(left=%ld, top=%ld)\n", point_left, point_top);

    MessageBox(NULL, TEXT(out_txt), TEXT("message"), MB_OK);
    SetCursorPos(10*i, 10*j);//����ж�������ͬ������Ƶ���һ�����
    //MessageBox(NULL, TEXT(Err.LastDllError), TEXT("message"), MB_OK);
}
COLORREF get_colorref_by_block_index(int i, int j, int k)
{
    COLORREF color = 0;

    color = GetPixel(hScrnDC, g_rect.left + j * BLOCK_PIXEL_ROW + BLOCK_PIXEL_ROW / 4 * (k % 3 + 1), g_rect.top + i * BLOCK_PIXEL_COLUMN + BLOCK_PIXEL_COLUMN / 4 * (k / 3 + 1));
    return color;
}

BOOL gen_map(COLORREF map[][NUM_ROW][NUM_COLUMN])
{
    int i, j, k;
    COLORREF color = 0;
    hScrnDC = GetDC(NULL);
    for (i = 0; i < NUM_ROW; i++) { //�����õ�����ֵ
        for (j = 0; j < NUM_COLUMN; j++) {
            for (k = 0; k < NUM_POINTS_PER_BLOCK; k++) {
                color = get_colorref_by_block_index(i, j, k);

//                ilog("i:%d j:%d color:0x%x\n", i, j, color);
                //MessageBox(NULL, TEXT(out_txt), TEXT("message"), MB_OK);
                if (CLR_INVALID == color) {
                    break;
                }
                g_map[k][i][j] = color;
            }
            //draw_rect(i, j);
        }
    }
    return TRUE;
}

#if 0
BOOL gen_map(COLORREF map[][NUM_ROW][NUM_COLUMN], int i, int j)
{
    int k;
    COLORREF val = 0;
    for (k = 0; k < NUM_POINTS_PER_BLOCK; k++) {
        val = GetPixel(hScrnDC, rect.left + j * BLOCK_PIXEL_ROW + BLOCK_PIXEL_ROW / 4 * (k % 3 + 1), rect.top + i * BLOCK_PIXEL_COLUMN + BLOCK_PIXEL_COLUMN / 4 * (k / 3 + 1));
        if (g_map[k][i][j] != val)
    }
        map[k][i][j] =;

    return TRUE;
}
#endif

BOOL is_get_rid_off(int i, int j)
{
    int k;
    COLORREF val = 0;
    for (k = 0; k < NUM_POINTS_PER_BLOCK; k++) {
        val = get_colorref_by_block_index(i, j, k);
        if (g_map[k][i][j] != val)
            return TRUE;
    }
    return FALSE;
}
BOOL do_it(int i, int j, int s, int t)
{
    ilog("i:%d j:%d s:%d t:%d\n", i, j, s, t);
    if (is_same(i, j, s, t)) {
        GetCursorPos(&position);
        SetCursorPos(g_rect.left + t * BLOCK_PIXEL_ROW + 15, g_rect.top + s * BLOCK_PIXEL_COLUMN + 12);//�Ƶ��ڶ������
        mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
        mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
        Sleep(rand() % 1 + 1);
        SetCursorPos(g_rect.left + j * BLOCK_PIXEL_ROW + 15, g_rect.top + i * BLOCK_PIXEL_COLUMN + 12);//����ж�������ͬ������Ƶ���һ�����
        mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
        mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
        Sleep(rand() % 1 + 1);
        SetCursorPos(g_rect.left + t * BLOCK_PIXEL_ROW + 15, g_rect.top + s * BLOCK_PIXEL_COLUMN + 12);//�Ƶ��ڶ������
        mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
        mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
//        SetCursorPos(position.x, position.y);//��귵�ص�Զ��        
//        SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 200, 100, SWP_SHOWWINDOW);
    }

//    Sleep(10);
    if (is_get_rid_off(i, j)) {
        g_do_ok_num ++;
        return TRUE;
    } else 
        return FALSE;
}

BOOL just_do_it()
{
    int i, j, s, t, f = 0;

    for (f; f < 2; f++) { //Ϊ�˱�֤û��ʣ�࣬����ѭ��
        for (i = 0; i < NUM_ROW; i++) {
            for (j = 0; j < NUM_COLUMN; j++) {
                if (is_same(i, j, nothing)) {
                    continue;
                } else {
                    for (s = 0; s < NUM_ROW; s++) {
                        for (t = 0; t < NUM_COLUMN; t++) {
                            if (is_same(i, j, nothing))
                                continue;
                            if (do_it(i, j, s, t))
                                continue;
                        }
                    }
                }
            }
        }
        gen_map(g_map);
    }
    return TRUE;
}

BOOL CALLBACK DlgMain(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        case WM_INITDIALOG:
        {
            log_init(".", "main", LOG_INFO);
            return 0;
        }
        case WM_CLOSE:
        {
            ReleaseDC(hwnd, hScrnDC);
            EndDialog(hwnd, 0);
            return 0;
        }
        case WM_COMMAND:
        {
            switch (LOWORD(wParam))
            {
                case IDOK:
                {
#if 1
                    HWND dest_hwnd = try_to_get_instanceid_by_name(GameName);
                    if (NULL == dest_hwnd) {
                        return FALSE;
                    }

                    BOOL ret;
                    char out_txt[512] = {0};
                    RECT rect;
                    ret = GetWindowRect(dest_hwnd, &rect);
                    g_rect.left = rect.left + GAP_LEFT;
                    g_rect.top = rect.top + GAP_TOP;
                    if (!ret) {
                        MessageBox(NULL, TEXT("get window position error"), TEXT("message"), MB_OK | MB_ICONWARNING);
                        return FALSE;
                    } else {
                        snprintf(out_txt, 512, "GetWindowRect hwnd = %p -> rect=(left=%ld, top=%ld, right=%ld, bottom=%ld)\n", dest_hwnd, rect.left, rect.top, rect.right, rect.bottom);
//                        MessageBox(NULL, TEXT(out_txt), TEXT("message"), MB_OK | MB_ICONWARNING);
                    }
#endif

                    gen_map(g_map);
                    srand(time(NULL));
                    just_do_it();

                }//case IDOK
            }
        }
    }
    return FALSE;
}