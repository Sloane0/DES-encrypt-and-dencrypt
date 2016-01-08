#pragma once

typedef unsigned char ElemType;

class DESClass
{
public:
	DESClass();
	virtual ~DESClass();
	void DES_Encrypt(CString plainFile, char *keyStr, CString cipherFile);
	void DES_Decrypt(CString cipherFile, char *keyStr, CString plainFile);

protected:
	void DES_MakeSubKeys(ElemType key[64], ElemType subKeys[16][48]);
	void DES_PC1_Transform(ElemType key[64], ElemType tempbts[56]);
	void DES_PC2_Transform(ElemType key[56], ElemType tempbts[48]);
	void DES_ROL(ElemType data[56], int time);
	void ByteToBit(ElemType ch, ElemType bit[8]);
	void BitToByte(ElemType bit[8], ElemType *ch);
	void Char8ToBit64(ElemType ch[8], ElemType bit[64]);
	void Bit64ToChar8(ElemType bit[64], ElemType ch[8]);
	void DES_IP_Transform(ElemType data[64]);
	void DES_IP_1_Transform(ElemType data[64]);
	void DES_E_Transform(ElemType data[48]);
	void DES_P_Transform(ElemType data[32]);
	void DES_SBOX(ElemType data[48]);
	void DES_XOR(ElemType R[48], ElemType L[48], int count);
	void DES_Swap(ElemType left[32], ElemType right[32]);
	void DES_EncryptBlock(ElemType plainBlock[8], ElemType subKeys[16][48], ElemType cipherBlock[8]);
	void DES_DecryptBlock(ElemType cipherBlock[8], ElemType subKeys[16][48], ElemType plainBlock[8]);

private:
	static int PC_1[56];
	static int PC_2[48];
	static int IP_Table[64];
	static int E_Tabel[48];
	static int P_Table[32];
	static int IP_1_Table[64];
	static int S_Box[8][4][16];
	static int Move_Times[16];
};

