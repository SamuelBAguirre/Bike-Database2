/*
* bike.h
*
*  Created on: Feb 20, 2015
*  Author: Vladimir
*/

#ifndef _BIKES_H_
#define _BIKES_H_

using namespace std;



enum class status { NO_STATUS, NOT_RENTED, RENTED, ALL };
enum class order { NO_ORDER, ID, MANUF };
struct Bike
{
    
    char manufact[25];
    int id_num;
    status rented_code;     //RENTED/NOT_RENTED
    char to_whom[25];   //to whom bike is rented
    int size;
    float cost_per_day;
    bool deleted;     //to mark bike as deleted in the list.
    
};

void readBike(fstream&, list<shared_ptr<Bike>>&);
void addBike(list<shared_ptr<Bike>>&, shared_ptr<Bike>);
void printBikes(list<shared_ptr<Bike>>, status, order);
void do_transact(fstream&, list<shared_ptr<Bike>>&, status);
void del_id_bike(fstream&, list<shared_ptr<Bike>>&);
void del_manuf(fstream&, list<shared_ptr<Bike>>&);
bool comp_id(shared_ptr<Bike>& , shared_ptr<Bike>& );
bool comp_manuf(shared_ptr<Bike>& , shared_ptr<Bike>& );
void init(shared_ptr<Bike>);
#endif /* _BIKES_H_*/
