#pragma once

struct Location
{
public:
	void Add(const Location& loc) {
		x += loc.x;
		y += loc.y;
	}
	bool operator==(const Location& rhs)const
	{
		return x == rhs.x && y == rhs.y; //sobrecarga de operadores. Redefinimos el operador == para nuestros propios objetos
	}
	int x;
	int y;
};