#include <string>
#include "soa.hpp"
#include "BondTradeBookingService.h"
#include "BondExecutionService.h"
#include "executionservice.hpp"

/**
 * BondTradeBookingServiceListener to listen data passing to BondTradeBooking Servicing
 * from BondExecutionService
 */
class BondTradeBookingServiceListener : public ServiceListener<ExecutionOrder<Bond> > {

private:
    BondTradeBookingService* btbs;

public:
    //ctor
    BondTradeBookingServiceListener(BondTradeBookingService* _btbs) {
        btbs = _btbs;
    }

    //override pure virtual functions
    virtual void ProcessAdd(ExecutionOrder<Bond>& data) override {
        auto bond = data.GetProduct();
        auto tradeID = "Execution";
        auto price = data.GetPrice();
        string book;
        switch (rand() % 3) {
        case 0: book = "TRSY1";break;
        case 1: book = "TRSY2";break;
        case 2: book = "TRSY3";break;
        }
        auto quantity = data.GetVisibleQuantity();
        auto side = data.GetSide() == BID ? SELL : BUY;
        Trade<Bond> trade(bond, tradeID, price, book, quantity, side);

        btbs->BookTrade(trade);
    }

    virtual void ProcessRemove(ExecutionOrder<Bond>& data) override {}
    virtual void ProcessUpdate(ExecutionOrder<Bond>& data) override {}


};