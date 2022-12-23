
#ifndef GUI_SERVICE_HPP
#define GUI_SERVICE_HPP

#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <boost/date_time.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include "soa.hpp"
#include "bondpricingservice.h"

class GUIServiceConnector;

class PriceWithTime : public Price<Bond> {
private:
    boost::posix_time::ptime timeStamp;

public:
    PriceWithTime(boost::posix_time::ptime _timeStamp, Price<Bond> _price) : Price<Bond>(_price) {
        timeStamp = _timeStamp;
    }

    boost::posix_time::ptime GetTimeStamp() {
        return timeStamp;
    }

};


/**
 * GUI Service to provide GUI service.
 */
class GUIService : public PricingService<Bond> {

private:
    GUIServiceConnector* connector;
    boost::posix_time::ptime lastTime;
    boost::posix_time::time_duration throtteTime;
    vector<ServiceListener<Price<Bond> >*> listenersList;
    map<string, Price<Bond> > dataMap;

public:
    //ctor
    GUIService(GUIServiceConnector* _connector);

    //override all virtual functions
    virtual Price<Bond>& GetData(string key) override { return dataMap[key]; };
    virtual void OnMessage(Price<Bond>& tradeData) override {};
    virtual void AddListener(ServiceListener<Price<Bond>>* listener) override {};
    virtual const vector< ServiceListener<Price<Bond>>*>& GetListeners() const override { return listenersList; };

    void SendToThrotte(Price<Bond>& data);
};


GUIService::GUIService(GUIServiceConnector* _connector) {
    connector = _connector;
    throtteTime = boost::posix_time::millisec(3);
    lastTime = boost::posix_time::microsec_clock::local_time();
    listenersList = vector<ServiceListener<Price<Bond> >*>();
    dataMap = map<string, Price<Bond> >();
}

#endif