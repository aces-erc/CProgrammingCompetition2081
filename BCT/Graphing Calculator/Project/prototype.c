#include <windows.h>
#include <stdio.h>
#include <math.h>
double s;
int check(double x, double y){
double r = sin(x)
    ;s = fabs(y - r);
    if (s < (0.05)){
        return 1;
    }
    else {
        return 0;
    }
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASS wc = { 0 };
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszClassName = L"GraphWindowClass";

    if (!RegisterClass(&wc)) {
        MessageBoxW(NULL, L"Window Registration Failed!", L"Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    HWND hwnd = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        L"GraphWindowClass",
        L"Graph",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
        NULL, NULL, hInstance, NULL);

    if (hwnd == NULL) {
        MessageBoxW(NULL, L"Window Creation Failed!", L"Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        int row,col;
        double r=500,x,y ;
        double aspectRatio = (double)(ps.rcPaint.right - ps.rcPaint.left) / (ps.rcPaint.bottom - ps.rcPaint.top);

        for ( row = 0; row < r; row++) {
            y = ((r - (1 + row)) - (1 + r / 2)) / (55.38);
            for (col = 0; col < r * 5; col++) {
                x = (col - (1 + r / 2)) / (55.38);
                if (check(x, y) == 1) {
                    SetPixel(hdc, col, row, RGB(0, 0, 255));
                }
                else if ((x * y) == 0) {
                    SetPixel(hdc, col, row, RGB(0, 0, 255));
                }
                else {
                    SetPixel(hdc, col, row, RGB(255, 0, 0));
                }
            }
        }

        EndPaint(hwnd, &ps);
        break;
    }
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}


