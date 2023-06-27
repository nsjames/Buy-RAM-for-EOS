#include <eosio/eosio.hpp>
#include <eosio/asset.hpp>
using namespace eosio;

CONTRACT buyramforeos : public contract {
public:
    using contract::contract;

    ACTION none(){}
    
    [[eosio::on_notify("eosio.token::transfer")]]
    void handle_notify(name from, name to, asset quantity, std::string memo) {
        if (to != get_self()) return;
        if (from == get_self()) return;
        if (quantity.symbol != symbol("EOS", 4)) check(false, "this contract only accepts EOS");

        name to_account = name(memo);
        if(!is_account(to_account)) check(false, "you must specify a recipient for the RAM");
        
        action(
            permission_level{get_self(), "active"_n},
            "eosio"_n,
            "buyram"_n,
            std::make_tuple(get_self(), to_account, quantity)
        ).send();
    }
};
