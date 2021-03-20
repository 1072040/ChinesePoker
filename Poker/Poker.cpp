#include "pch.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
using namespace std;

int mycard[13][2];
int Original = 0, Transform = 1;

int SoloCard[13][2];
int DoubleCard[12][2];
int TripleCard[12][2];
int QuadraCard[12][2];
int TotalSoloCard = 0;
int TotalDoubleCard = 0;
int TotalTripleCard = 0;
int TotalQuadraCard = 0;


int FrontCard[3][2] = { 0 };//頭墩
int MidCard[5][2] = { 0 };//中墩
int BackCard[5][2] = { 0 };//尾墩

int MaxCard = 52;
int MinCard = 1;

bool HasRepeat = false;



//亂數發牌
void Licensing() {
	int i = 0, j;
	while (i < 13) {

		int RandNum = rand() % ((MaxCard + 1) - MinCard) + MinCard;//隨機生成一個1~52的數
		bool FindSameNum = 0;

		for (j = 0; j < i; j++) {
			//若有重複就重新取一個亂數
			if (RandNum == mycard[j][Original])
			{
				FindSameNum = 1;
				break;
			}
		}
		//若無重複才記下
		if (FindSameNum == 0) {

			mycard[i][Original] = RandNum;
			mycard[i][Transform] = mycard[i][Original] % 13;
			if (mycard[i][Transform] == 0)
				mycard[i][Transform] = 13;

			++i;//切換到下一個數
		}
	}

}

void SortCard() {

	int i, j;
	int TempCard[1][3];
	//照數字排列順序
	for (i = 12; i >= 0; i--) {
		for (j = 0; j < i; j++) {
			if (mycard[j][Transform] > mycard[j + 1][Transform]) {
				TempCard[0][Original] = mycard[j][Original];
				TempCard[0][Transform] = mycard[j][Transform];

				mycard[j][Original] = mycard[j + 1][Original];
				mycard[j][Transform] = mycard[j + 1][Transform];

				mycard[j + 1][Original] = TempCard[0][Original];
				mycard[j + 1][Transform] = TempCard[0][Transform];
			}
		}
	}

	

}

void PickSoloCard() {
	int i = 0;
	while (i < 13) {
		if (i == 0) {
			if (mycard[i][Transform] != mycard[i + 1][Transform]){//比對第一第二個是否相同
				SoloCard[TotalSoloCard][Original] = mycard[i][Original];
				SoloCard[TotalSoloCard][Transform] = mycard[i][Transform];
				TotalSoloCard++;
			}
			i++;
		}
		else {//比對跟前後是否相同
			if (mycard[i][Transform] != mycard[i + 1][Transform] && mycard[i][Transform] != mycard[i - 1][Transform]) {
				SoloCard[TotalSoloCard][Original] = mycard[i][Original];
				SoloCard[TotalSoloCard][Transform] = mycard[i][Transform];
				TotalSoloCard++;
			}
			i++;
		}
	}
	cout << "單張卡牌 : "<<TotalSoloCard << endl;
	for (i = 0; i < 13; i++)
		cout << setw(2) << SoloCard[i][Transform] << " ";
	cout << endl;
}

void PickQuadraCard() {
	for (int i = 0; i < 10 ; i++) {
		if (mycard[i][Transform] == mycard[i + 3][Transform]) {
			for (int j = 0; j < 4; j++) {
				QuadraCard[TotalQuadraCard + j][Original] = mycard[i + j][Original];
				QuadraCard[TotalQuadraCard + j][Transform] = mycard[i + j][Transform];

				mycard[i + j][Transform] = 99;//紀錄過後改成99
				
				
			}
			TotalQuadraCard += 4;
		}
	}
	cout << "四連卡牌 : " << TotalQuadraCard << endl;
	for (int i = 0; i < 12; i++)
		cout << setw(2) << QuadraCard[i][Transform] << " ";
	cout << endl;
}

void PickTripleCard() {
	for (int i = 0; i < 11; i++) {
		if (mycard[i][Transform] == mycard[i + 2][Transform]) {
			if (mycard[i][Transform] != 99) {
				for (int j = 0; j < 3; j++) {
					TripleCard[TotalTripleCard + j][Original] = mycard[i + j][Original];
					TripleCard[TotalTripleCard + j][Transform] = mycard[i + j][Transform];

					mycard[i + j][Transform] = 99;//紀錄過後改成99
				}
				TotalTripleCard += 3;
			}
		}
	}
	cout << "三連卡牌 : " << TotalTripleCard << endl;
	for (int i = 0; i < 12; i++)
		cout << setw(2) << TripleCard[i][Transform] << " ";
	cout << endl;
}

void PickDoubleCard() {
	for (int i = 0; i < 12; i++) {
		if (mycard[i][Transform] == mycard[i + 1][Transform]) {
			if (mycard[i][Transform] != 99) {
				for (int j = 0; j < 2; j++) {
					DoubleCard[TotalDoubleCard + j][Original] = mycard[i + j][Original];
					DoubleCard[TotalDoubleCard + j][Transform] = mycard[i + j][Transform];
					mycard[i + j][Transform] = 99;//紀錄過後改成99
				}
				TotalDoubleCard += 2;
			}
		}
	}
	cout << "對子卡牌 : " << TotalDoubleCard << endl;
	for (int i = 0; i < 12; i++)
		cout << setw(2) << DoubleCard[i][Transform] << " ";
	cout << endl;
}

void ArrangeCard() {
	int TakeSolo = 0, TakeDouble = 0 , TakeTriple = 0 , TakeQuadra = 0;

	//鐵支
	while (TotalQuadraCard > 0) {//當四張連續的卡>0
		for (int i = 0; i < 4; i++) {//先放入後墩
			BackCard[i][Original] = QuadraCard[TakeQuadra][Original];
			BackCard[i][Transform] = QuadraCard[TakeQuadra][Transform];
			TakeQuadra++;
			TotalQuadraCard--;
		}
		for (int i = 0; i < 4; i++) {//再放入中墩
			MidCard[i][Original] = QuadraCard[TakeQuadra][Original];
			MidCard[i][Transform] = QuadraCard[TakeQuadra][Transform];
			TakeQuadra++;
			TotalQuadraCard--;
		}
	}
	////////////////////////////////////////////////////////////////////////////
	//三條
	while (TotalTripleCard > 0) {//當三張連續的卡>0
		if (BackCard[0][Original] == 0) {//尾墩為空就放入
			for (int i = 0; i < 3; i++) {
				BackCard[i][Original] = TripleCard[TakeTriple][Original];
				BackCard[i][Transform] = TripleCard[TakeTriple][Transform];
				TakeTriple++;
				TotalTripleCard--;
			}
		}
		if (MidCard[0][Original] == 0) {//中墩為空就放入
			for (int i = 0; i < 3; i++) {
				MidCard[i][Original] = TripleCard[TakeTriple][Original];
				MidCard[i][Transform] = TripleCard[TakeTriple][Transform];
				TakeTriple++;
				TotalTripleCard--;
			}
		}
		if (FrontCard[0][Original] == 0) {//前墩為空就放入
			for (int i = 0; i < 3; i++) {
				FrontCard[i][Original] = TripleCard[TakeTriple][Original];
				FrontCard[i][Transform] = TripleCard[TakeTriple][Transform];
				TakeTriple++;
				TotalTripleCard--;
			}
		}
	}
	/////////////////////////////////////////////////////////////////////////////////////////
	//對子
	while (TotalDoubleCard > 0) {
		//後敦 0&2&3位置空就放對子進去
		if (BackCard[0][Original] == 0) {
			for (int i = 0; i < 2; i++) {
				BackCard[0 + i][Original] = DoubleCard[TakeDouble][Original];
				BackCard[0 + i][Transform] = DoubleCard[TakeDouble][Transform];
				TakeDouble++;
				TotalDoubleCard--;
			}
		}
		if (BackCard[2][Original] == 0) {
			for (int i = 0; i < 2; i++) {
				BackCard[2 + i][Original] = DoubleCard[TakeDouble][Original];
				BackCard[2 + i][Transform] = DoubleCard[TakeDouble][Transform];
				TakeDouble++;
				TotalDoubleCard--;
			}
		}
		if (BackCard[3][Original] == 0) {//有三條的情況
			for (int i = 0; i < 2; i++) {
				BackCard[3 + i][Original] = DoubleCard[TakeDouble][Original];
				BackCard[3 + i][Transform] = DoubleCard[TakeDouble][Transform];
				TakeDouble++;
				TotalDoubleCard--;
			}
		}
		//中墩 0&3空放
		if (MidCard[0][Original] == 0) {
			for (int i = 0; i < 2; i++) {
				MidCard[0 + i][Original] = DoubleCard[TakeDouble][Original];
				MidCard[0 + i][Transform] = DoubleCard[TakeDouble][Transform];
				TakeDouble++;
				TotalDoubleCard--;
			}
		}
		if (MidCard[2][Original] == 0) {
			for (int i = 0; i < 2; i++) {
				MidCard[2 + i][Original] = DoubleCard[TakeDouble][Original];
				MidCard[2 + i][Transform] = DoubleCard[TakeDouble][Transform];
				TakeDouble++;
				TotalDoubleCard--;
			}
		}
		if (MidCard[3][Original] == 0) {//有三條的情況
			for (int i = 0; i < 2; i++) {
				MidCard[3 + i][Original] = DoubleCard[TakeDouble][Original];
				MidCard[3 + i][Transform] = DoubleCard[TakeDouble][Transform];
				TakeDouble++;
				TotalDoubleCard--;
			}
		}
		//前墩 0空放
		if (FrontCard[0][Original] == 0) {
			for (int i = 0; i < 2; i++) {
				FrontCard[0 + i][Original] = DoubleCard[TakeDouble][Original];
				FrontCard[0 + i][Transform] = DoubleCard[TakeDouble][Transform];
				TakeDouble++;
				TotalDoubleCard--;
			}
		}
	}
	/////////////////////////////////////////////////////////////////////////////////////
	//單張
	while (TotalSoloCard >0)
	{
		//有空位就塞入
		for (int i = 0; i < 5; i++) {//後墩
			if (BackCard[i][Original] == 0) {
				BackCard[i][Original] = SoloCard[TakeSolo][Original];
				BackCard[i][Transform] = SoloCard[TakeSolo][Transform];
				TakeSolo++;
				TotalSoloCard--;
			}
		}
		for (int i = 0; i < 5; i++) {//中墩
			if (MidCard[i][Original] == 0) {
				MidCard[i][Original] = SoloCard[TakeSolo][Original];
				MidCard[i][Transform] = SoloCard[TakeSolo][Transform];
				TakeSolo++;
				TotalSoloCard--;
			}
		}
		for (int i = 0; i < 3; i++) {//前墩
			if (FrontCard[i][Original] == 0) {
				FrontCard[i][Original] = SoloCard[TakeSolo][Original];
				FrontCard[i][Transform] = SoloCard[TakeSolo][Transform];
				TakeSolo++;
				TotalSoloCard--;
			}
		}
	}
}
void MergeCard() {
	int num = 0;
	for (int i = 0; i < 3; i++) {
		mycard[num][Original] = FrontCard[i][Original];
		mycard[num][Transform] = FrontCard[i][Transform];
		num++;
	}
	for (int i = 0; i < 5; i++) {
		mycard[num][Original] = MidCard[i][Original];
		mycard[num][Transform] = MidCard[i][Transform];
		num++;
	}
	for (int i = 0; i < 5; i++) {
		mycard[num][Original] = BackCard[i][Original];
		mycard[num][Transform] = BackCard[i][Transform];
		num++;
	}
}

void ShowCard() {
	int i;
	cout << "原始牌號 : ";
	for (i = 0; i < 13; i++)
		cout << setw(2) << mycard[i][Original] << " ";
	cout << endl << "轉換牌號 : ";
	for (i = 0; i < 13; i++)
		cout << setw(2) << mycard[i][Transform] << " ";
	cout << endl;
}
void ShowFMB() {
	int i;
	cout << "前 : ";
	for (i = 0; i < 3; i++)
		cout << setw(2) << FrontCard[i][Transform] << " ";
	cout << endl << "中 : ";
	for (i = 0; i < 5; i++)
		cout << setw(2) << MidCard[i][Transform] << " ";
	cout << endl << "後 : ";
	for (i = 0; i < 5; i++)
		cout << setw(2) << BackCard[i][Transform] << " ";
	cout << endl;
}

int main()
{
	srand(time(NULL)); //亂數種子

	Licensing();//發牌
	ShowCard();
	cout << "-------------------------------------------------" << endl;
	SortCard();//照順序排列
	ShowCard();
	cout << "-------------------------------------------------" << endl;
	PickSoloCard();//取單張
	PickQuadraCard();//取四張相同的
	PickTripleCard();//取三張相同的
	PickDoubleCard();//取兩張相同的
	cout << "-------------------------------------------------" << endl;
	ArrangeCard();//整理排
	ShowFMB();//顯示前中後敦的排
	cout << "-------------------------------------------------" << endl;
	MergeCard();//合併前中後敦到mycard
	ShowCard();
	cout << endl;
	return 0;
}                                  