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
    std::string str;
    //std::cin >> str;
    std::getline(std::cin, str);

    std::string bin = std::string(str.size() * 9, ' ');
    for(int i = 0; i < str.size(); i ++) {
        char curr = str[i];
        for(int j = 7; j >=0 ; j --) {
            bin[i*9+j] = curr%2 + '0';
            curr >>= 1;
        }
    }
    std::cout << bin;
    toClipboard(bin);
}
/*
01101101 01100001 01101001 01101011 01100001 00100000 01110100 01101001
*/
