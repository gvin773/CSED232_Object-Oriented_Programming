#include "PieceArray.h"
#include "Pawn.h"

PieceArray::PieceArray(int maxLength)
{
	length = 0;
	this->maxLength = maxLength;
	arr = new Piece*[maxLength];
	for (int i = 0; i < maxLength; i++)
		arr[i] = NULL;
}

PieceArray::~PieceArray()
{
	for (int i = 0; i < length; i++) delete arr[i];
	delete[] arr;
}

int PieceArray::GetLength() const
{
	return length;
}

Piece* PieceArray::GetPieceAt(int index) const
{
	return arr[index];
}

void PieceArray::PushPiece(Piece* piece)
{
	arr[length] = piece;
	length++;
	if (typeid(*piece) == typeid(Pawn)) piece->Init(Player::PLAYER_LEFT, { 0,0 });
	//isPromoted�� �� ������ ���� ��Ͽ� �� ��µǰ� �Ϸ��� ����, ���忡 ������ �ٽ� �ʱ�ȭ ���ֹǷ� player, pos�� �ƹ� ���̳� ������� 
}

Piece* PieceArray::PopPieceAt(int index)
{
	Piece* ret = arr[index];
	for (int i = index; i < length-1; i++)
	{
		arr[i] = arr[i + 1];
	}
	arr[length-1] = NULL;
	length--;
	return ret;
}

std::ostream& operator<<(std::ostream& os, const PieceArray& pa)
{
	int len = pa.GetLength();
	for (int i = 0; i < len - 1; i++)
	{
		pa.GetPieceAt(i)->PrintLabel(os);
		os << ", ";
	}
	if(len != 0) pa.GetPieceAt(len - 1)->PrintLabel(os);
	return os;
}
