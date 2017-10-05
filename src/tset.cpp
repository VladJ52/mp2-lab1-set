// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : BitField(mp)
{
	MaxPower = mp;
}

// конструктор копирования
TSet::TSet(const TSet &s) : BitField(s.MaxPower)
{
	MaxPower = s.MaxPower;
	BitField = s.BitField;
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField(bf.GetLength())
{
	MaxPower = bf.GetLength();
	BitField = bf;
}

TSet::operator TBitField()
{
  return BitField;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
  return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
	if (BitField.GetBit(Elem) == 1)
		return 1;
	else
    return 0;
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
	BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
	BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
	MaxPower = s.MaxPower;
	BitField = s.BitField;
  return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
	return (BitField == s.BitField);
}

int TSet::operator!=(const TSet &s) const // сравнение
{
	return !(*this == s.BitField);
}

TSet TSet::operator+(const TSet &s) // объединение
{
	TSet x(MaxPower);
	x.BitField = BitField | s.BitField;
	x.MaxPower = x.BitField.GetLength();
  return x;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
	TSet x =*this;
	x.BitField.SetBit(Elem);
  return x;

}

TSet TSet::operator-(const int Elem) // разность с элементом
{
	TSet x = *this;
	x.BitField.ClrBit(Elem);
	return x;

}

TSet TSet::operator*(const TSet &s) // пересечение
{
	TSet x(MaxPower);
	x.BitField = BitField & s.BitField;
	x.MaxPower = x.BitField.GetLength();
	return x;

}

TSet TSet::operator~(void) // дополнение
{
	TSet x = *this;
	x.BitField = ~BitField;
	return x;

}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
	istr >> s.MaxPower;
	istr >> s.BitField;
  return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
	ostr << s.BitField;
  return ostr;
}
