#include <iostream>
using namespace std;

class Point
{
public:
    Point(int ix = 0, int iy = 0) : x(ix), y(iy)
    {
        cout << "Point::Constructor" << endl;
    }
    ~Point()
    {
        cout << "Point::Destructor" << endl;
    }

    static void *operator new(size_t size)
    {
        Point *p;
        if (freeStore == nullptr)
        {
            cout << "chunk" << endl;
            size_t chunk = NUM_CHUNK * sizeof(Point);
            freeStore = p = static_cast<Point *>(::operator new(chunk));

            for (; p != &freeStore[NUM_CHUNK - 1]; p++)
            {
                p->next = p + 1;
            }
            p->next = nullptr;
        }
        p = freeStore;
        freeStore = freeStore->next;
        return p;
    }

    static void operator delete(void *p)
    {
        if (nullptr != p)
        {
            cout << "return to freelist" << endl;
            static_cast<Point *>(p)->next = freeStore;
            freeStore = static_cast<Point *>(p);
        }
    }

private:
    int x;
    int y;

    Point *next;
    static Point *freeStore;
    static const int NUM_CHUNK;
};

const int Point::NUM_CHUNK = 5;
Point *Point::freeStore = nullptr;

void test_Point()
{
    Point *p1 = new Point(12, 23);
    Point *p2 = new Point(2, 23);
    Point *p3 = new Point(12, 2);
    Point *p4 = new Point(122, 213);
    Point *p5 = new Point(12, 273);
    Point *p6 = new Point(1002, 2563);

    // 注意查看各个对象地址的间距，尤其注意p5和p6
    cout << p1 << endl;
    cout << p2 << endl;
    cout << p3 << endl;
    cout << p4 << endl;
    cout << p5 << endl;
    cout << p6 << endl;
}

int main(int argc, char *argv[])
{
    test_Point();

    return 0;
}