#include <iostream>
#include <windows.h>
#include <conio.h>
#include <string>
#define COLUMNS 120  // maksymalna liczba kolumn
#define ROWS 30     // maksymalna liczba wierszy`

using namespace std;
void triangle(int h, int w, char znak, int x, int y); // podstawowa funkcja rysujaca trojkat
void clear(); //czyszczenie ekranu 
void gotoxy(int column, int line); // ustawienie wspolrzednych kursora

int main()
{
	int strzalka, h, w;
	char znak;
	string info = "Wprowadz znak i rozmiar trojkata wysokosc i szerokosc (wieksze od 1)\n.";
	cout << info;
	while (true) {
		cin >> znak >> h >> w;
		if (h > 1 && w > 1) {
			break;
		}
		else {
			cout << info;
		}
	}
	triangle(h, w, znak, 0, 0);
	int x = 0;
	int y = 0;
	while (true) {
		unsigned char z = _getch();
		if (z == 27) break; //ESC - wyjscie z programu

		if (z == 224) {
			z = _getch(); 
			switch (z)
			{
			case 72: //strzałka w górę
				triangle(h, w, znak, x, (y > 0) ? --y : y);
				break;
			case 80: //strzałka w dół
				triangle(h, w, znak, x, (y < ROWS) ? ++y : y);
				break;
			case 75: //strzałka w lewo
				triangle(h, w, znak, (x > 0) ? --x : x, y);
				break;
			case 77: //strzałka w prawo
				triangle(h, w, znak, (x < COLUMNS) ? ++x : x, y);
				break;
			}
		}
		else if (z == 43) { // Powiekszanie za pomoca plusa '+'
			if ((h + y) < ROWS) {
				++h;
			}
			else {
				if (y > 0) {
					--y;
					h++;
				}
			}
			if ((w + x) < COLUMNS) {
				++w;
			}
			else {
				if (x > 0) {
					--x;
					w++;
				}
			}
			triangle(h, w, znak, x, y);
		}
		else if (z == 45) {  // Zmniejszanie za pomoca minusa '-'
			triangle(h > 2 ? --h : h, w > 2 ? --w : w, znak, x, y);
		}

	}
	return 0;
}
void triangle(int h, int w, char znak, int x, int y) {
	clear();
	gotoxy(x, y);
	for (int i = 1; i <= h; i++) {
		if (i == 1) { cout << znak; continue; }
		double a = (double)w / h * i;
		a = (a == 0) ? 1 : a;
		for (int j = 1; j <= a; j++) {
			gotoxy(x + j - 1, y + i - 1);
			cout << znak;
		}
	}
}
void clear() {
	COORD topLeft = { 0, 0 };
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO screen;
	DWORD written;

	GetConsoleScreenBufferInfo(console, &screen);
	FillConsoleOutputCharacterA(
		console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written
	);
	FillConsoleOutputAttribute(
		console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
		screen.dwSize.X * screen.dwSize.Y, topLeft, &written
	);
	SetConsoleCursorPosition(console, topLeft);
}
void gotoxy(int column, int line)
{
	COORD c;
	c.X = column;
	c.Y = line;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}