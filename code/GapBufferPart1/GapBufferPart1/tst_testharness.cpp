#include <QtTest>

#include "GapBuffer.h"
using namespace std;


class TestHarness : public QObject
{
    Q_OBJECT

public:
    TestHarness();
    ~TestHarness();

private slots:
    void insert_at_test_basic();
    void insert_move_cursor_at_basic();
    void move_cursor_jump();
    void insert_move_mixed();
    void reserve_test_basic();

};

TestHarness::TestHarness() { /* No global data used needed */}

TestHarness::~TestHarness() { /* No global data used needed */}

void TestHarness::insert_at_test_basic() {
    GapBuffer buf;
    for (char ch = 'a'; ch < 'g'; ch++) {
        buf.insert_at_cursor(ch);
    }

    for (char ch = 'a'; ch < 'g'; ch++) {
        QVERIFY(ch == buf.at(ch - 'a'));
    }

}

void TestHarness::insert_move_cursor_at_basic() {
    GapBuffer buf;
    for (char ch = 'a'; ch < 'g'; ch++) {
        buf.insert_at_cursor(ch);
    }

    for (char ch = 'f'; ch >= 'a'; ch--) {
        buf.move_cursor(-1);
        QVERIFY(ch == buf.get_at_cursor());
    }

}

void TestHarness::move_cursor_jump() {
    GapBuffer buf;
    for (char ch = 'a'; ch <= 'g'; ch++) {
        buf.insert_at_cursor(ch);
    }
    buf.move_cursor(-1);
    for (char ch = 'g'; ch >= 'c'; ch -= 3) {
        QVERIFY(buf.get_at_cursor() == ch);
        buf.move_cursor(-3);
    }
}

void TestHarness::reserve_test_basic() {
    GapBuffer buf;
    vector<char> vec;
    for (char ch = 'a'; ch <= 'o'; ++ch) {
        buf.insert_at_cursor(ch);
        vec.push_back(ch);
        QVERIFY(buf.size() == vec.size());
    }
    buf.move_cursor(-14);
    for (size_t i = 0; i < 14; i++) {
        QVERIFY(buf.at(i) == vec[i]);
        buf.move_cursor(1);
    }
}

void TestHarness::insert_move_mixed() {
    GapBuffer buf;
    for (char ch = 'a'; ch <= 'g'; ch++) {
        buf.insert_at_cursor(ch);
    }
    for (char ch = 'g'; ch > 'a'; ch--) {
        buf.insert_at_cursor(ch);
        buf.move_cursor(-1);
    }
    buf.move_cursor(-1);
}

// We'll add more test cases as we move to later parts.

// insert your own test cases here
// if you want, you can also write couts in the test cases
// to simulate actually using the program

QTEST_APPLESS_MAIN(TestHarness)

#include "tst_testharness.moc"
