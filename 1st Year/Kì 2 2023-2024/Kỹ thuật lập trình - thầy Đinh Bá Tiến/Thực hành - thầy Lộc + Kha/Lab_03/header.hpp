#include <iostream>
using namespace std;

struct Seat
{
    bool isReserved;
    Seat()
    {
        isReserved = false;
    }
};

struct Row
{
    int rowSize;
    int price;
    Seat *seats;
    Row() {}
    Row(int rowSize, int price)
    {
        this->rowSize = rowSize;
        this->price = price;
        seats = new Seat[rowSize];
        for (int i = 0; i < rowSize; i++)
        {
            seats[i] = Seat();
        }
    }
    int getSales()
    {
        int total = 0;
        for (int i = 0; i < rowSize; i++)
        {
            if (seats[i].isReserved)
            {
                total += price;
            }
        }
        return total;
    }
};
struct Cinema
{
    int numRows;
    Row *rows;
    Cinema(int numRows, int rowSizes, int *rowPrice)
    {
        this->numRows = numRows;
        rows = new Row[numRows];
        for (int i = 0; i < numRows; i++)
        {
            rows[i] = Row(rowSizes, rowPrice[i]);
        }
    }
};

void displaySeats(Cinema *cinema);

int getTotalSales(Cinema *cinema);

void reserveSeat(Cinema *cinema, int row, int seat);

void cancelSeat(Cinema *cinema, int row, int seat);

int getSeatPrice(Cinema *cinema, int row, int seat);