// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

#define BITS_IN_ONE_MEM (sizeof(TELEM) * 8)

TBitField::TBitField(int len)
{
  if (len < 0)
    throw "negative length";
  BitLen = len;
  MemLen = BitLen / BITS_IN_ONE_MEM + 1;
  pMem = new TELEM[MemLen];
  for (int i = 0; i < MemLen; i++)
	  pMem[i] = 0;
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = BitLen / BITS_IN_ONE_MEM + 1;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
		pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{
	delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
  return n / BITS_IN_ONE_MEM;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
  return 1 << (n % BITS_IN_ONE_MEM);
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if ((n < 0) || (n > BitLen))
		throw "negative bit";
	pMem[GetMemIndex(n)] |= GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if ((n < 0) || (n > BitLen))
		throw "negative bit";
	pMem[GetMemIndex(n)] &= ~(GetMemMask(n));
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if ((n < 0) || (n > BitLen))
		throw "negative bit";
	if ((pMem[GetMemIndex(n)] & GetMemMask(n)) == 0)
		return 0;
	else
		return 1;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	if (BitLen == bf.BitLen){
		for (int i = 0; i < MemLen; i++)
			pMem[i] = bf.pMem[i];
}
	else
	{
		delete[]pMem;
		BitLen = bf.BitLen;
		MemLen = BitLen/BITS_IN_ONE_MEM +1;
		pMem = new TELEM[MemLen];
		for (int i = 0; i < MemLen; i++)
			pMem[i] = bf.pMem[i];
}

  return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	if (BitLen != bf.BitLen)
		return 0;
	else
	{
		int flag = 1;
		for (int i = 0; (i < bf.MemLen) && (flag); i++)
			if (pMem[i] != bf.pMem[i])
				flag = 0;
		return flag;
	}
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	return !(*this == bf);
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	if (BitLen > bf.BitLen)
	{
		TBitField x(BitLen);
		for (int i = 0; i < bf.MemLen; i++)
			x.pMem[i] = pMem[i] | bf.pMem[i];
		for (int i = bf.MemLen; i < x.MemLen; i++)
			x.pMem[i] = pMem[i];
		return x;
	}
	else
	{
		TBitField x(bf.BitLen);
		for (int i = 0; i < MemLen; i++)
			x.pMem[i] = pMem[i] | bf.pMem[i];
		for (int i = MemLen; i < x.MemLen; i++)
			x.pMem[i] = bf.pMem[i];
		return x;
	}
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	if (BitLen > bf.BitLen)
	{
		TBitField x(BitLen);
		for (int i = 0; i < bf.MemLen; i++)
			x.pMem[i] = pMem[i] & bf.pMem[i];
		for (int i = bf.MemLen; i < x.MemLen; i++)
			x.pMem[i] = pMem[i];
		return x;
	}
	else
	{
		TBitField x(bf.BitLen);
		for (int i = 0; i < MemLen; i++)
			x.pMem[i] = pMem[i] & bf.pMem[i];
		for (int i = MemLen; i < x.MemLen; i++)
			x.pMem[i] = bf.pMem[i];
		return x;
	}
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField x(BitLen);
	for (int i = 0; i < MemLen - 1; i++)
		x.pMem[i] = ~pMem[i];
	for (int i = ((MemLen - 1)*BITS_IN_ONE_MEM); i < BitLen; i++)
		if (GetBit(i) == 0)
			x.SetBit(i);
		else
			x.ClrBit(i);
	return x;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	int len = 0;
	istr >> len;
	for (int i = 0; i < len; i++)
	{
		int flag = 0;
		istr >> flag;
		if (flag == 1)
			bf.SetBit(i);
	}

  return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	cout << "{";
	for (int i = 0; i < bf.BitLen; i++)
		ostr << bf.GetBit(i);
	ostr << "}\n";
  return ostr;
}
