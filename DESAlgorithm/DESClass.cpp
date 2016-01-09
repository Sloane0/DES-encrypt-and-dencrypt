#include "stdafx.h"
#include "DESClass.h"
#include <fstream>

using namespace std;

int DESClass::PC_1[56] = {
	56,48,40,32,24,16,8,
	0,57,49,41,33,25,17,
	9,1,58,50,42,34,26,
	18,10,2,59,51,43,35,
	62,54,46,38,30,22,14,
	6,61,53,45,37,29,21,
	13,5,60,52,44,36,28,
	20,12,4,27,19,11,3
};

int DESClass::PC_2[48] = {
	13,16,10,23,0,4,2,27,
	14,5,20,9,22,18,11,3,
	25,7,15,6,26,19,12,1,
	40,51,30,36,46,54,29,39,
	50,44,32,46,43,48,38,55,
	33,52,45,41,49,35,28,31
};

int DESClass::IP_Table[64] = {
	57,49,41,33,25,17,9,1,
	59,51,43,35,27,19,11,3,
	61,53,45,37,29,21,13,5,
	63,55,47,39,31,23,15,7,
	56,48,40,32,24,16,8,0,
	58,50,42,34,26,18,10,2,
	60,52,44,36,28,20,12,4,
	62,54,46,38,30,22,14,6
};
int DESClass::E_Tabel[48] = {
	31, 0, 1, 2, 3, 4,
	3, 4, 5, 6, 7, 8,
	7, 8,9,10,11,12,
	11,12,13,14,15,16,
	15,16,17,18,19,20,
	19,20,21,22,23,24,
	23,24,25,26,27,28,
	27,28,29,30,31, 0
};
int DESClass::P_Table[32] = {
	15,6,19,20,28,11,27,16,
	0,14,22,25,4,17,30,9,
	1,7,23,13,31,26,2,8,
	18,12,29,5,21,10,3,24
};
int DESClass::IP_1_Table[64] = {
	39,7,47,15,55,23,63,31,
	38,6,46,14,54,22,62,30,
	37,5,45,13,53,21,61,29,
	36,4,44,12,52,20,60,28,
	35,3,43,11,51,19,59,27,
	34,2,42,10,50,18,58,26,
	33,1,41,9,49,17,57,25,
	32,0,40,8,48,16,56,24
};
int DESClass::S_Box[8][4][16] = {
	{ //S1
		{ 14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7 },
		{ 0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8 },
		{ 4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0 },
		{ 15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13 }
	},
	{ //S2
		{ 15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10 },
		{ 3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5 },
		{ 0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15 },
		{ 13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9 }
	},

	{ //S3
		{ 10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8 },
		{ 13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1 },
		{ 13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7 },
		{ 1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12 }
	},

	{ //S4
		{ 7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15 },
		{ 13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9 },
		{ 10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4 },
		{ 3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14 }
	},

	{ //S5
		{ 2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9 },
		{ 14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6 },
		{ 4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14 },
		{ 11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3 }
	},

	{ //S6
		{ 12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11 },
		{ 10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8 },
		{ 9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6 },
		{ 4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13 }
	},

	{ //S7
		{ 4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1 },
		{ 13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6 },
		{ 1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2 },
		{ 6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12 }
	},

	{ //S8
		{ 13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7 },
		{ 1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2 },
		{ 7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8 },
		{ 2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11 }
	}
};
int DESClass::Move_Times[16] = {
	1,1,2,2,2,2,2,2,
	1,2,2,2,2,2,2,1
};

DESClass::DESClass()
{

}


DESClass::~DESClass()
{
}

void DESClass::DES_MakeSubKeys(ElemType key[64], ElemType subKeys[16][48])
{
	ElemType temp[56];

	DES_PC1_Transform(key, temp);//PC1置换
	for (int i = 0; i < 16; i++) {
		DES_ROL(temp, Move_Times[i]);
		DES_PC2_Transform(temp, subKeys[i]);
	}
}

void DESClass::DES_PC1_Transform(ElemType key[64], ElemType tempbts[56])
{
	for (int i = 0; i < 56; i++) {
		tempbts[i] = key[PC_1[i]];
	}
}

void DESClass::DES_PC2_Transform(ElemType key[56], ElemType tempbts[48])
{
	for (int i = 0; i < 48; i++) {
		tempbts[i] = key[PC_2[i]];
	}
}

void DESClass::DES_ROL(ElemType data[56], int time)
{
	ElemType temp[56];

	/*左边28位向左移动time位，右边28位向左移动time位，然后将移动后的数据合并在一起
	*/
	//保存将要循环移动到右边的位  
	memcpy(temp, data, time);
	memcpy(temp + time, data + 28, time);

	//前28位移动  
	memcpy(data, data + time, 28 - time);
	memcpy(data + 28 - time, temp, time);

	//后28位移动  
	memcpy(data + 28, data + 28 + time, 28 - time);
	memcpy(data + 56 - time, temp + time, time);
}

void DESClass::ByteToBit(ElemType ch, ElemType bit[8])
{
	const ElemType stone = 0x01;

	for (int i = 0; i < 8; i++) {
		bit[i] = (ch >> (7 - i)) & stone;
	}
}

void DESClass::BitToByte(ElemType bit[8], ElemType *ch)
{
	*ch = 0;
	const char stone = 0x01;

	for (int i = 0; i < 8; i++) {
		*ch |= bit[i] << (7 - i);
	}
}

void DESClass::Char8ToBit64(ElemType ch[8], ElemType bit[64])
{
	for (int i = 0; i < 8; i++) {
		ByteToBit(ch[i], bit + 8 * i);
	}
}

void DESClass::Bit64ToChar8(ElemType bit[64], ElemType ch[8])
{
	for (int i = 0; i < 8; i++) {
		BitToByte(bit + 8 * i, ch + i);
	}
}

void DESClass::DES_IP_Transform(ElemType data[64])
{
	ElemType temp[64];

	for (int i = 0; i < 64; i++) {
		temp[i] = data[IP_Table[i]];
	}
	memcpy(data, temp, 64);
}

void DESClass::DES_IP_1_Transform(ElemType data[64])
{
	ElemType temp[64];

	for (int i = 0; i < 64; i++) {
		temp[i] = data[IP_1_Table[i]];
	}
	memcpy(data, temp, 64);
}

void DESClass::DES_E_Transform(ElemType data[48])
{
	ElemType temp[48];

	for (int i = 0; i < 48; i++) {
		temp[i] = data[E_Tabel[i]];
	}
	memcpy(data, temp, 48);
}

void DESClass::DES_P_Transform(ElemType data[32])
{
	ElemType temp[32];

	for (int i = 0; i < 32; i++) {
		temp[i] = data[P_Table[i]];
	}
	memcpy(data, temp, 32);
}

void DESClass::DES_SBOX(ElemType data[48])
{
	int cur1, cur2;
	for (int i = 0; i < 8; i++) {
		cur1 = i * 6;		//将原来数据的6位变为4位，得到的结果是8*4 = 32位的
		cur2 = i * 4;

		//计算在S盒中的行与列  
		int row = (data[cur1] << 1) + data[cur1 + 5]; //每6位中的第一位和第六位组成行号
		int col = (data[cur1 + 1] << 3) + (data[cur1 + 2] << 2) //每6位中的第2、3、4、5位组成列号
			+ (data[cur1 + 3] << 1) + data[cur1 + 4];
		int output = S_Box[i][row][col];

		//化为2进制  
		data[cur2] = (output & 0X08) >> 3;
		data[cur2 + 1] = (output & 0X04) >> 2;
		data[cur2 + 2] = (output & 0X02) >> 1;
		data[cur2 + 3] = output & 0x01;
	}
}

//左右两部分异或，结果保存在R数组中
void DESClass::DES_XOR(ElemType R[48], ElemType L[48], int count)
{
	for (int i = 0; i < count; i++) {
		R[i] ^= L[i];
	}
}

void DESClass::DES_Swap(ElemType left[32], ElemType right[32])
{
	ElemType temp[32];

	memcpy(temp, left, 32);
	memcpy(left, right, 32);
	memcpy(right, temp, 32);
}

//加密单个分组
void DESClass::DES_EncryptBlock(ElemType plainBlock[8], ElemType subKeys[16][48], ElemType cipherBlock[8])
{
	ElemType plainBits[64];
	ElemType copyRight[48];

	Char8ToBit64(plainBlock, plainBits);
	//初始置换（IP置换）  
	DES_IP_Transform(plainBits);

	//16轮迭代  
	for (int i = 0; i < 16; i++) {
		memcpy(copyRight, plainBits + 32, 32);
		//将右半部分进行扩展置换，从32位扩展到48位  
		DES_E_Transform(copyRight);
		//将右半部分与子密钥进行异或操作  
		DES_XOR(copyRight, subKeys[i], 48);
		//异或结果进入S盒，输出32位结果  
		DES_SBOX(copyRight);
		//P置换  
		DES_P_Transform(copyRight);
		//将明文左半部分与右半部分进行异或  
		DES_XOR(plainBits, copyRight, 32);
		if (i != 15) {
			//最终完成左右部的交换  
			DES_Swap(plainBits, plainBits + 32);
		}
	}
	//逆初始置换（IP^1置换）  
	DES_IP_1_Transform(plainBits);
	Bit64ToChar8(plainBits, cipherBlock);
}

void DESClass::DES_DecryptBlock(ElemType cipherBlock[8], ElemType subKeys[16][48], ElemType plainBlock[8])
{
	ElemType cipherBits[64];
	ElemType copyRight[48];

	Char8ToBit64(cipherBlock, cipherBits);
	//初始置换（IP置换）  
	DES_IP_Transform(cipherBits);

	//16轮迭代  
	for (int i = 15; i >= 0; i--) {
		memcpy(copyRight, cipherBits + 32, 32);
		//将右半部分进行扩展置换，从32位扩展到48位  
		DES_E_Transform(copyRight);
		//将右半部分与子密钥进行异或操作  
		DES_XOR(copyRight, subKeys[i], 48);
		//异或结果进入S盒，输出32位结果  
		DES_SBOX(copyRight);
		//P置换  
		DES_P_Transform(copyRight);
		//将明文左半部分与右半部分进行异或  
		DES_XOR(cipherBits, copyRight, 32);
		if (i != 0) {
			//最终完成左右部的交换  
			DES_Swap(cipherBits, cipherBits + 32);
		}
	}
	//逆初始置换（IP^1置换）  
	DES_IP_1_Transform(cipherBits);
	Bit64ToChar8(cipherBits, plainBlock);
}

void DESClass::DES_Encrypt(CString plainFile, char *keyStr, CString cipherFile)
{
	int count;
	ElemType plainBlock[8], cipherBlock[8], keyBlock[8];
	ElemType bKey[64];
	ElemType subKeys[16][48];

	ifstream plain(plainFile, ios::binary | ios::in);
	ofstream cipher(cipherFile, ios::binary | ios::out);

	//设置密钥  
	memcpy(keyBlock, keyStr, 8);
	//将密钥转换为二进制流  
	Char8ToBit64(keyBlock, bKey);
	//生成子密钥  
	DES_MakeSubKeys(bKey, subKeys);

	while (!plain.eof()) {
		memset(plainBlock, 0, sizeof(plainBlock));
		memset(cipherBlock, 0, sizeof(cipherBlock));
		plain.read((char *)plainBlock, sizeof(plainBlock));
		
		if (plainBlock[7] != '\0') {
			DES_EncryptBlock(plainBlock, subKeys, cipherBlock);
			cipher.write((char *)cipherBlock, sizeof(cipherBlock));
		}
	}
	count = strlen((char *)plainBlock);
	if (count) {
		//最后一个字符保存包括最后一个字符在内的所填充的字符数量  
		plainBlock[7] = 8 - count;
		DES_EncryptBlock(plainBlock, subKeys, cipherBlock);
		cipher.write((char *)cipherBlock,sizeof(cipherBlock));
	}
	plain.close();
	cipher.close();
}

void DESClass::DES_Decrypt(CString cipherFile, char *keyStr, CString plainFile)
{
	//FILE *plain, *cipher;
	int count, times = 0;
	long fileLen;
	ElemType plainBlock[8], cipherBlock[8], keyBlock[8];
	ElemType bKey[64];
	ElemType subKeys[16][48];

	ifstream cipher(cipherFile, ios::binary | ios::in);
	ofstream plain(plainFile, ios::binary | ios::out);

	//设置密钥  
	memcpy(keyBlock, keyStr, 8);
	//将密钥转换为二进制流  
	Char8ToBit64(keyBlock, bKey);
	//生成子密钥  
	DES_MakeSubKeys(bKey, subKeys);

	cipher.seekg(0, ios::end);
	fileLen = cipher.tellg();
	cipher.seekg(0, ios::beg);
	while (1) {
		memset(cipherBlock, 0, sizeof(cipherBlock));
		memset(plainBlock, 0, sizeof(plainBlock));
		cipher.read((char *)cipherBlock, sizeof(cipherBlock));
		DES_DecryptBlock(cipherBlock, subKeys, plainBlock);
		times += 8;
		if (times < fileLen) {
			plain.write((char *)plainBlock, sizeof(plainBlock));
		}
		else {
			break;
		}
	}
	if (plainBlock[7] < 8) {
		plainBlock[7] = '\0';
	}
	plain.write((char *)plainBlock, strlen((char *)plainBlock));

	plain.close();
	cipher.close();
}
