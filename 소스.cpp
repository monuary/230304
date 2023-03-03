//friend 선언은 정보은닉을 무너뜨리기 때문에 위험하다. 따라서 문법적 이해만 하고, 가급적 사용하지 않는 것이 좋다.
//연산자 오버로딩을 공부할 때쯤 이 문법이 다시 등장한다.
//friend 선언은 전역함수에도 접근 가능하다.

#include<iostream>
using namespace std;

class Point;

class PointOP
{
	int opcnt;	//계산 횟수
public:
	PointOP():opcnt(0){}

	Point PointAdd(const Point&, const Point&);	//Point 클래스 내부의 함수. 이름공간은 PointOP.
	Point PointSub(const Point&, const Point&);
	~PointOP() { cout << "Operation times: " << opcnt << endl; }	//마지막에 PointOP가 사라지면서 계산 횟수를 출력한다.
};

class Point
{
	int x;
	int y;
public:
	Point(const int&xpos,const int&ypos):x(xpos),y(ypos){}
	friend Point PointOP::PointAdd(const Point&, const Point&);
	friend Point PointOP::PointSub(const Point&, const Point&);
	friend void ShowPointPos(const Point&);	//아직 선언되지 않은 함수를 friend 선언과 동시에 선언할 수 있다.
};

Point PointOP::PointAdd(const Point& pnt1, const Point& pnt2) { opcnt++; return Point(pnt1.x + pnt2.x, pnt1.y + pnt2.y); }
Point PointOP::PointSub(const Point& pnt1, const Point& pnt2) { opcnt++; return Point(pnt1.x - pnt2.x, pnt1.y - pnt2.y); }

void ShowPointPos(const Point& pos) { cout << "x: " << pos.x << ", y: " << pos.y << endl; }

int main()
{
	Point pos1(1, 2);
	Point pos2(2, 4);
	PointOP op;

	ShowPointPos(op.PointAdd(pos1, pos2));
	ShowPointPos(op.PointSub(pos2, pos1));
	return 0;
}