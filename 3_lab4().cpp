// 3_lab4().cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "3_lab4().h"
#include <string>
#include <sstream>
#include "DirectGraph.h"
#include "UndirectGraph.h"
#include "DictionaryOnSequence.h"
#include <cmath>
#include <map>
#define _USE_MATH_DEFINES

#define MAX_LOADSTRING 100
#define ADD_VERTEX_BUTTON 101
#define ADD_EDGE_BUTTON 102
#define DRAW_BUTTON 103
#define VERTEX_ID_INPUT 104
#define FROM_INPUT 105
#define TO_INPUT 106
#define WEIGHT_INPUT 107

HINSTANCE hInst;
WCHAR szTitle[MAX_LOADSTRING];
WCHAR szWindowClass[MAX_LOADSTRING];
HWND hAddVertexButton, hAddEdgeButton, hDrawButton;
HWND hVertexIdInput, hFromInput, hToInput, hWeightInput;
DirectedGraph<int> graph;

ATOM MyRegisterClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MY3LAB4, szWindowClass, MAX_LOADSTRING);

    MyRegisterClass(hInstance);

    if (!InitInstance(hInstance, nCmdShow))
        return FALSE;

    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY3LAB4));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_MY3LAB4);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance;

    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, 800, 600, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
        return FALSE;

    // Create controls
    hAddVertexButton = CreateWindowEx(0, L"BUTTON", L"Add Vertex", WS_CHILD | WS_VISIBLE,
        20, 20, 100, 30, hWnd, (HMENU)ADD_VERTEX_BUTTON, hInstance, nullptr);
    hVertexIdInput = CreateWindowEx(0, L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER,
        130, 20, 100, 30, hWnd, nullptr, hInstance, nullptr);

    hAddEdgeButton = CreateWindowEx(0, L"BUTTON", L"Add Edge", WS_CHILD | WS_VISIBLE,
        20, 60, 100, 30, hWnd, (HMENU)ADD_EDGE_BUTTON, hInstance, nullptr);
    hFromInput = CreateWindowEx(0, L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER,
        130, 60, 50, 30, hWnd, nullptr, hInstance, nullptr);
    hToInput = CreateWindowEx(0, L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER,
        190, 60, 50, 30, hWnd, nullptr, hInstance, nullptr);
    hWeightInput = CreateWindowEx(0, L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER,
        250, 60, 50, 30, hWnd, nullptr, hInstance, nullptr);

    hDrawButton = CreateWindowEx(0, L"BUTTON", L"Draw Graph", WS_CHILD | WS_VISIBLE,
        20, 100, 100, 30, hWnd, (HMENU)DRAW_BUTTON, hInstance, nullptr);

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}

void AddVertex(HWND hWnd);
void AddEdge(HWND hWnd);
void DrawGraph(HWND hWnd, HDC hdc);

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        switch (wmId)
        {
        case ADD_VERTEX_BUTTON:
            AddVertex(hWnd);
            break;
        case ADD_EDGE_BUTTON:
            AddEdge(hWnd);
            break;
        case DRAW_BUTTON:
            InvalidateRect(hWnd, nullptr, TRUE);
            break;
        }
    }
    break;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        DrawGraph(hWnd, hdc);
        EndPaint(hWnd, &ps);
        break;
    }
    //break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

void AddVertex(HWND hWnd)
{
    wchar_t buffer[256];
    GetWindowText(hVertexIdInput, buffer, 256);
    int vertexId = _wtoi(buffer);
    graph.addVertex(vertexId);
    MessageBox(hWnd, L"Vertex added!", L"Info", MB_OK);
}

void AddEdge(HWND hWnd)
{
    wchar_t buffer[256];
    GetWindowText(hFromInput, buffer, 256);
    int from = _wtoi(buffer);
    GetWindowText(hToInput, buffer, 256);
    int to = _wtoi(buffer);
    GetWindowText(hWeightInput, buffer, 256);
    float weight = (float)_wtof(buffer);
    graph.addEdge(from, to, weight);
    MessageBox(hWnd, L"Edge added!", L"Info", MB_OK);
}

//void DrawGraph(HWND hWnd, HDC hdc)
//{
//    auto vertices = graph.GetVertices();
//    auto keys = vertices.GetKeys();
//
//    for (int i = 0; i < vertices.GetCount(); ++i) 
//    {
//        auto vertex = vertices.GetByIndex(i);
//
//    }
//}
void DrawArrow(HDC hdc, POINT from, POINT to)
{
    int dx = to.x - from.x;
    int dy = to.y - from.y;
    const int arrowSize = 6;
    double angle = atan2(dy, dx);

    POINT arrowPoint1, arrowPoint2;
    arrowPoint1.x = to.x - static_cast<int>(arrowSize * cos(angle - 3.141592653589793 / 6));
    arrowPoint1.y = to.y - static_cast<int>(arrowSize * sin(angle - 3.141592653589793 / 6));
    arrowPoint2.x = to.x - static_cast<int>(arrowSize * cos(angle + 3.141592653589793 / 6));
    arrowPoint2.y = to.y - static_cast<int>(arrowSize * sin(angle + 3.141592653589793 / 6));

    MoveToEx(hdc, to.x, to.y, NULL);
    LineTo(hdc, arrowPoint1.x, arrowPoint1.y);
    MoveToEx(hdc, to.x, to.y, NULL);
    LineTo(hdc, arrowPoint2.x, arrowPoint2.y);
}

void DrawGraph(HWND hWnd, HDC hdc)
{
    auto vertices = graph.GetVertices();
    auto keys = vertices.GetKeys();

    RECT rect;
    GetClientRect(hWnd, &rect);

    int width = rect.right - rect.left;
    int height = rect.bottom - rect.top;
    int centerX = width / 2;
    int centerY = height / 2;
    int radius;
    if (width < height) 
    {
        radius = width / 2 - 50;
    }
    else 
    {
        radius = height / 2 - 50;
    }
        
    std::map<int, POINT> positions;
    for (int i = 0; i < keys.GetLength(); ++i)
    {
        int key = keys.Get(i);
        double angle = 2 * 3.141592653589793 * i / keys.GetLength();
        int x = centerX + static_cast<int>(radius * cos(angle));
        int y = centerY + static_cast<int>(radius * sin(angle));
        positions[key] = { x, y };
    }

    // Draw vertices
    for (const auto& pair : positions)
    {
        int id = pair.first;
        POINT pos = pair.second;

        // Draw a circle for the vertex
        Ellipse(hdc, pos.x - 10, pos.y - 10, pos.x + 10, pos.y + 10);

        // Draw the vertex ID near the circle
        wchar_t buf[256];
        size_t bufsize = sizeof(buf) / sizeof(wchar_t);
        swprintf_s(buf, bufsize, L"%d", id);
        TextOut(hdc, pos.x - 5, pos.y - 5, buf, wcslen(buf));
    }

    // Draw edges
    for (int i = 0; i < keys.GetLength(); ++i)
    {
        int fromKey = keys.Get(i);
        Vertex<int>* fromVertex = vertices.Get(fromKey);
        auto edges = fromVertex->getEdges();
        for (int j = 0; j < edges.GetLength(); ++j)
        {
            Edge<int>* edge = edges.Get(j);
            int toKey = edge->getTo()->getId();

            // Get positions of from and to
            auto fromIter = positions.find(fromKey);
            auto toIter = positions.find(toKey);
            if (fromIter != positions.end() && toIter != positions.end())
            {
                POINT fromPos = fromIter->second;
                POINT toPos = toIter->second;

                // Draw line from fromPos to toPos
                MoveToEx(hdc, fromPos.x, fromPos.y, NULL);
                LineTo(hdc, toPos.x, toPos.y);

                // Draw arrowhead at the end of the edge
                DrawArrow(hdc, fromPos, toPos);
            }
        }
    }
}


// Helper function to draw arrowheads


//for (int j = 0; j < edges.GetLength(); ++j) 
        //{
        //    auto edge = edges.Get(j);
        //     /*Здесь логика рисования рёбер и вершин с использованием WinAPI
        //     Например:
        //     MoveToEx(hdc, startX, startY, nullptr);
        //     LineTo(hdc, endX, endY);*/
        //}