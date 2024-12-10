#include <iostream>
#include "header.hpp"

using namespace std;

int main()
{
    // Create a cinema with 3 rows, 5 seats each, and prices 10, 20, and 30
    int rowPrices[] = {10, 20, 30};
    Cinema *cinema = new Cinema(3, 5, rowPrices);
    displaySeats(cinema);
    int n;
    while (cin >> n)
    {
        if (n == 1)
        {
            int row, seat;
            cin >> row >> seat;
            reserveSeat(cinema, row, seat);
        }
        else if (n == 2)
        {
            int row, seat;
            cin >> row >> seat;
            cancelSeat(cinema, row, seat);
        }
        else if (n == 3)
        {
            cout << "Total sales: " << getTotalSales(cinema) << endl;
        }
        displaySeats(cinema);
        if (n == 0)
            break;
    }
    return 0;
}