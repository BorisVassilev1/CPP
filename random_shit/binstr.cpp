#include <iostream>
#include <string>
#include <Windows.h>
#include <winuser.h>

void toClipboard(const std::string &s){
    HWND hwnd = GetDesktopWindow();
	OpenClipboard(hwnd);
	EmptyClipboard();
	HGLOBAL hg=GlobalAlloc(GMEM_MOVEABLE,s.size()+1);
	if (!hg){
		CloseClipboard();
		return;
	}
	memcpy(GlobalLock(hg),s.c_str(),s.size()+1);
	GlobalUnlock(hg);
	SetClipboardData(CF_TEXT,hg);
	CloseClipboard();
	GlobalFree(hg);
}

int main() {
    std::string bin;
    //std::cin >> str;
    std::getline(std::cin, bin);

    std::string str = std::string((bin.size() + 1) / 9, ' ');

    for(int i = 0; i < str.size(); i ++) {
        char curr = 0;
        for(int j = 0; j < 8; j ++) {
            int x = bin[i * 9 + j] - '0';
            curr <<= 1;
            curr += x;
        }
        str[i] = curr;
    }
    std::cout << str;
    toClipboard(str);
}
/*

*/

