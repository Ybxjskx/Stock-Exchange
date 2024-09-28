#include <mutex>
#include <string>
#include "shortcuts.h"

namespace yaniv
{

class RegisteredUser
{
// Implement this class with locks.
private:
    vector<CompanySymbol, stock_amount> stocks; 
    unsigned int id;
    std::mutex lock;
    currency_amount money;
    StockExchange * stock_exchange;
    void add_money(unsigned int money,unsigned int card_pay);
    void take_money(unsigned int money, unsigned int card_id);

    RegisteredUser(unsigned int id):id(id), money(0) {}
    void start_transaction(){}

public:
    currency_amount get_money();
   // have to add option to hold stocks 
    InternalOrder& make_order(enum order_type type_of_the_order,const stock_amount amount,const currency_amount max_amount_money_per);
    void bid_market(CompanySymbol& company_symbol,stock_amount stocks_num, currency_amount total_money);
    void ask_market(CompanySymbol& company_symbol,stock_amount stocks_num);
    void buy_in_price(CompanySymbol& company_symbol,stock_amount stocks_num,currency_amount money_per_stock);
    void sale_in_price(CompanySymbol& company_symbol,stock_amount stocks_num,currency_amount money_per_stock);
};

}