#include "header.hpp"

void displaySeats(Cinema *cinema)
{
    for (int i = 0; i < cinema->numRows; i++)
    {
        for (int j = 0; j < cinema->rows[i].rowSize; j++)
        {
            if (cinema->rows[i].seats[j].isReserved)
            {
                cout << "*";
            }
            else
            {
                cout << "#";
            }
        }
        cout << "\n";
    }
}

void reserveSeat(Cinema *cinema, int row, int seat)
{
    cinema->rows[row].seats[seat].isReserved = true;
}

int getTotalSales(Cinema *cinema)
{
    int total = 0;
    for (int i = 0; i < cinema->numRows; i++)
    {
        total += cinema->rows[i].getSales();
    }
    return total;
}

void cancelSeat(Cinema *cinema, int row, int seat)
{
    cinema->rows[row].seats[seat].isReserved = false;
}

int getSeatPrice(Cinema *cinema, int row, int seat)
{
    return cinema->rows[row].price;
}
