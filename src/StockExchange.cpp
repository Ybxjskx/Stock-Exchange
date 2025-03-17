#include "StockExchange.hpp"
#include "shortcuts.hpp"
#include <format>
#include <string>
#include "internals/OrderBook.hpp"
#include <stdexcept>
#include <iostream>
namespace yaniv
{

void StockExchange::add_company(CompanySymbol& company_symbol,double price, int amount_stocks)
{
	if(this->book_orders_by_company_symbol.find(company_symbol) != std::end(this->book_orders_by_company_symbol))
	{
		throw std::invalid_argument("The company " + std::string(company_symbol) + " already exists");
	}

	this->book_orders_by_company_symbol[company_symbol] = new OrderBook(company_symbol);

	const std::function<void(currency_amount, stock_amount)> notify =
	[](currency_amount amount, stock_amount stocks_take)
	{
		std::cout << "The original stock sold " << stocks_take
				  << " stocks for " << amount << " currency units." << std::endl;
	};

	// יצירת הזמנה עם notify שהוגדרה
	InternalOrder order(amount_stocks, company_symbol, this->name, 0, price, 0, notify);

	// קריאה לפונקציה שמבצעת את המכירה ומדפיסה את ההודעה
	this->book_orders_by_company_symbol[company_symbol]->ask_in_price(order);
	// TODO: Add all stocks to comapny
}void StockExchange::check_correct(InternalOrder&  order)
{
	if(this->book_orders_by_company_symbol.find(order.company_symbol) == std::end(this->book_orders_by_company_symbol))
	{
		std::cout<<"The company"+ order.company_symbol+ "is not exists";
		throw std::invalid_argument("The company"+ order.company_symbol+ "is not exists");
	}
}

double StockExchange::bid_market(InternalOrder&  internal_order)
{   
	// check input

	check_correct(internal_order);

	OrderBook * book_order = this -> book_orders_by_company_symbol[internal_order.company_symbol];
	// freeze money

	double money_to_give_back = book_order->bid_market(internal_order);
    return money_to_give_back;
}
int StockExchange::ask_market(InternalOrder& internal_order)
{
	check_correct(internal_order);

	OrderBook * book_order = this -> book_orders_by_company_symbol[internal_order.company_symbol];

    int stocks_to_return = book_order->ask_market(internal_order);

	return stocks_to_return;

}

void StockExchange::bid_in_price(InternalOrder& internal_order)
{	// check input

    check_correct(internal_order);

	OrderBook * book_order = this->book_orders_by_company_symbol[internal_order.company_symbol];

	book_order -> bid_in_price(internal_order);
}
void StockExchange::ask_in_price(InternalOrder& internal_order)
{
	// check input

	this->check_correct(internal_order);

	OrderBook* book_order = this->book_orders_by_company_symbol[internal_order.company_symbol];
    
    book_order->ask_market(internal_order);
}


}