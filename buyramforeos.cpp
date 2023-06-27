#include <eosio/eosio.hpp>
#include <eosio/asset.hpp>
using namespace eosio;

CONTRACT system : public contract {
public:
    ACTION buyram(const name from, const name to, const asset quantity) {}
    using buyram_action = eosio::action_wrapper<"buyram"_n, &system::buyram>;
};


CONTRACT buyramforeos : public contract {
public:
    using contract::contract;

    [[eosio::on_notify("eosio.token::transfer")]]
    void handle_notify(const name from, const name to, const asset quantity, const std::string memo) {
        if (to != get_self()) return;

        name to_account = name(memo);
        if (!is_account(to_account)) to_account = from;

        system::buyram_action buyram( "eosio", { get_self(), "active"_n });
        buyram.send(get_self(), to_account, quantity);
    }
};
