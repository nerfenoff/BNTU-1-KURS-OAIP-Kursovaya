// Kurs.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <conio.h>
#include <thread>
#include "plane.h"
#include "windows.h"

using namespace std;

/// <summary>
/// Calculate P for bomber and fighters in loop
/// </summary>
/// <param name="bomber"></param>
/// <param name="fighters"></param>
/// <param name="size">- array size of fighters</param>
void calculatePForAll(Plane& bomber, Plane* fighters, int& size);
/// <summary>
/// Fires bomber shots at fighters
/// </summary>
/// <param name="bomber"></param>
/// <param name="fighters"></param>
/// <param name="size">- array size of fighters</param>
void bomberShoot(Plane& bomber, Plane* fighters, int size);
/// <summary>
/// Fires fighters shots at bomber
/// </summary>
/// <param name="bomber"></param>
/// <param name="fighters"></param>
/// <param name="size">- array size of fighters</param>
void fightersShoot(Plane& bomber, Plane* fighters, int size);
/// <summary>
/// Checks if all the fighters have been shot down
/// </summary>
/// <param name="fighters"></param>
/// <param name="size"></param>
/// <returns>Returns true if all fighters are shot down. Returns false if at least 1 fighter is alive</returns>
bool isAllfightersShotDown(Plane* fighters, int size);

static bool isEnd = false;

int main()
{
	Plane bomber;
	Plane fighter1;
	Plane fighter2;

	Plane fighters[] = { fighter1, fighter2 };
	int arraySize = (sizeof(fighters) / sizeof(*fighters));

	thread thr(calculatePForAll, ref(bomber), fighters, ref(arraySize));
	thr.detach();

	while (!isEnd)
	{
		cout << "Bomber status: " << ((bomber.isShotDown) ? "Shot Down" : "Allive") << endl;
		for (int i = 0; i < arraySize; ++i)
		{
			cout << "Fighter" << i + 1 << " status: " << ((fighters[i].isShotDown) ? "Shot Down" : "Allive") << endl;
		}
		cout << endl << endl;

		cout << "Press key to action:" << endl;
		cout << "any - Shoot int figters" << endl;
		cout << "1 - Escape" << endl;
		if ((char)_getch() != '1')
		{
			system("cls");
			bomberShoot(bomber, fighters, arraySize);
			cout << endl;
			fightersShoot(bomber, fighters, arraySize);
			cout << endl << endl;

			if (isAllfightersShotDown(fighters, arraySize) || bomber.isShotDown)
			{
				cout << (bomber.isShotDown ? "Bomber" : "All fighters") << " was shotdown!" << endl;
				isEnd = true;
			}
		}
		else 
		{
			isEnd = true;
		}
	}


	isEnd = true;
	
	return 0;
}

void bomberShoot(Plane& bomber, Plane* fighters, int size)
{
	for (int i = 0; i < size; ++i)
	{
		if (fighters[i].isShotDown) continue;
		float p = bomber.GetP();
		cout << "Bomber shoots fighter" << i + 1 << " whith p = " << p << endl;
		fighters[i].getShooot(p);
	}
}

void fightersShoot(Plane& bomber, Plane* fighters, int size)
{
	for (int i = 0; i < size; ++i)
	{
		if (fighters[i].isShotDown) continue;
		float p = fighters[i].GetP();
		cout << "fighter" << i + 1 << " shoots bomber whith p = " << p << endl;
		bomber.getShooot(p);
	}
}

bool isAllfightersShotDown(Plane* fighters, int size)
{
	for (int i = 0; i < size; ++i)
	{
		if (!fighters[i].isShotDown) return false;
	}
	return true;
}

void calculatePForAll(Plane &bomber, Plane* fighters, int &size) {
	while (!isEnd) {
		if (!bomber.isShotDown) bomber.CalculateP();

		for (int i = 0; i < size; ++i)
		{
			if (!fighters[i].isShotDown) fighters[i].CalculateP();
		}
	}
}