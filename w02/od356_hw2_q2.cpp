#include <iostream>
using namespace std;

int main()
{
  char hasClubCardInput;

  bool hasClubCard;

  float firstItemPrice,
        secondItemPrice,
        taxRate,
        basePrice,
        priceAfterDiscounts,
        totalPrice;

  cout<<"Enter price of first item: ";
  cin>>firstItemPrice;

  cout<<"Enter price of second item: ";
  cin>>secondItemPrice;

  cout<<"Does customer have a club card? (Y/N): ";
  cin>>hasClubCardInput;

  cout<<"Enter tax rate, e.g. 5.5 for 5.5\% tax: ";
  cin>>taxRate;

  switch (hasClubCardInput) {
    case 'Y':
    case 'y':
      hasClubCard = true;
      break;
    case 'N':
    case 'n':
      hasClubCard = false;
      break;
    default:
      hasClubCard = false;
  }

  basePrice = firstItemPrice + secondItemPrice;
  
  if (firstItemPrice < secondItemPrice) {
    priceAfterDiscounts = (firstItemPrice * 0.5) + secondItemPrice;
  } else {
    priceAfterDiscounts = firstItemPrice + (secondItemPrice * 0.5);
  }

  if (hasClubCard) {
    priceAfterDiscounts = priceAfterDiscounts * 0.90;
  }

  totalPrice = priceAfterDiscounts * (1 + (0.01 * taxRate));

  // setting prceision to properly format the output
  cout.setf(ios::fixed);
  cout.precision(1);

  cout<<"Base price: "<<basePrice<<endl;
  cout<<"Price after discounts: "<<priceAfterDiscounts<<endl;

  // setting precision to properly format the end total to 5 decimal places like the example
  cout.precision(5);
  cout<<"Total price: "<<totalPrice<<endl;

  return 0;
}
