#ifndef RESTAURANT_MANAGER_H
#define RESTAURANT_MANAGER_H

#include<vector>
#include<string>
#include<algorithm>
#include"../models/Restaurant.h"

class RestauranManager {
    private:
      vector<Restaurant*>restaurants;
      static Restaurantmanager * instance;

      Restaurantmanager() {
        // private constructor
      }

    public:
      static RestaurantManager * getInstance(){
        if(!instance){
            instance = new Restaurantmanager();
        }
        return instance;
      }

      void addRestaurant(Restaurant*r){
        restaurants.push_back(r);
      }

      vector<Restaurant*> searchByLocation(string loc){
        vector<Restaurant*> result;
        transform(loc.begin(),loc.end(),loc.begin(),::tolower);
        for(auto r : restaurants){
            string rl = r->getLocation();
            transorm(rl.begin(),rl.end(),rl.begin(),::tolower);
            i(rl == loc){
                result.push_back(r);
            }
        }
        return result;
      }
};

RestaurantManager* RestaurantManager::instance = nullptr;

#endif //RESTAURANT_MANAGER_H