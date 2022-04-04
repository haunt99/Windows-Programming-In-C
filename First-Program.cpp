#include<windows.h>

LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE HInstance, HINSTANCE HPrevInstance, PSTR szCmdLine, int iCmdShow)
{
	//hInstance: HĐH sử dụng giá trị này để xác định tập tin thực thi exe khi nó xử lý trong RAM
	//hPrevInstance: Đc sử dụng trong Windows 16 bit nhưng bây giờ thì luôn luôn bằng 0
	//szCmdLine: Chứa các đối số Command Line dưới dạng chuỗi unicode
	//iCmdShow: Là 1 flag, thể hiện cho cửa sổ phóng to, thu nhỏ hay bình thường
	
	//MessageBox(NULL, TEXT("Hello World 2018"), TEXT("Notify!!!"), NULL);

	// WNDCLASSW: Là Contructor cho khởi tạo Windows 
	// CreateWindowW(ClassName, WindowsName, style, x, y, width, height, NULL, NULL, NULL, NULL);

	// B 1: Đăng ký 1 Windows Class
	WNDCLASSW wc = { 0 };
	wc.hbrBackground = (HBRUSH) COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hInstance = HInstance;
	wc.lpszClassName = L"MyWindowsClass";
	wc.lpfnWndProc = WindowProcedure;

	if (!RegisterClassW(&wc))
		return -1;

	// B 2: Tạo Windows
	CreateWindowW(L"MyWindowsClass", L"Windows Applications", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 500, 500,
		NULL, NULL, NULL, NULL);

	// B 3: Vòng lặp message
	MSG msg = {0};

	// GetMessage() là hàm lấy thông tin từ message queue. Khi tương tác với system, các tương tác được máy
	// hiểu là các message trong Windows và lưu vào hàng đợi trong system. Vòng lặp sẽ lấy các message ra
	// thực hiện với 2 hàm dưới: 
	// + TranslateMessage: Biên dịch các message để cho máy hiểu các tương tác của bạn là tương tác gì, ở đâu.
	// + DispatchMessage: Hàm này sẽ xác định message này được gửi đến cửa sổ nào và xác định rồi thực thi nó.
	while (GetMessage(&msg, NULL, NULL, NULL))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}

// B 4: Tạo thủ tục window
LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) 
{
	switch (msg) {
		// DestroyWindow() Hàm sẽ gửi câu lệnh WM_DESTROY đến message queue.
		// Khi WM_DESTROY được thực hiện, nó sẽ xóa các “con” của cửa sổ này trước 
		// khi thực hiện các thao tác kế tiếp.
		case WM_DESTROY:
			//PostQuitMessage(0) – Gửi lệnh WM_QUIT đến hệ thống.
			PostQuitMessage(0);
			break;
		case WM_CLOSE:
			DestroyWindow(hWnd);
		default:
			return DefWindowProcW(hWnd, msg, wp, lp);
	}
}


