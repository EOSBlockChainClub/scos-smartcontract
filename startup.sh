#!/bin/sh

alias cleos='docker exec eosio /opt/eosio/bin/cleos --wallet-url http://localhost:8888'
alias eosiocpp='docker exec eosio eosiocpp'

WALLET_PASSWORD=$(cleos wallet create | tail -n 1)
cleos wallet unlock --password ${WALLET_PASSWORD} --unlock-timeout 3600

OWNER_ACCOUNT_KEY_PAIR=$(cleos create key |  grep -oE "[^:]+$")
OWNER_ACCOUNT_KEY_PAIR_ARR=($OWNER_ACCOUNT_KEY_PAIR)
OWNER_ACCOUNT_PRIVATE_KEY=${OWNER_ACCOUNT_KEY_PAIR_ARR[0]}
OWNER_ACCOUNT_PUBLIC_KEY=${OWNER_ACCOUNT_KEY_PAIR_ARR[1]}

OWNER_ACTIVE_KEY_PAIR=$(cleos create key |  grep -oE "[^:]+$")
OWNER_ACTIVE_KEY_PAIR_ARR=($OWNER_ACTIVE_KEY_PAIR)
OWNER_ACTIVE_PRIVATE_KEY=${OWNER_ACTIVE_KEY_PAIR_ARR[0]}
OWNER_ACTIVE_PUBLIC_KEY=${OWNER_ACTIVE_KEY_PAIR_ARR[1]}

cleos wallet import ${OWNER_ACCOUNT_PRIVATE_KEY}
cleos wallet import ${OWNER_ACTIVE_PRIVATE_KEY}

# Create first user account

TESTACC_OWNER_KEY_PAIR=$(cleos create key |  grep -oE "[^:]+$")
TESTACC_OWNER_KEY_PAIR_ARR=($TESTACC_OWNER_KEY_PAIR)
TESTACC_OWNER_PRIVATE_KEY=${OWNER_ACCOUNT_KEY_PAIR_ARR[0]}
TESTACC_OWNER_PUBLIC_KEY=${OWNER_ACCOUNT_KEY_PAIR_ARR[1]}

TESTACC_ACTIVE_KEY_PAIR=$(cleos create key |  grep -oE "[^:]+$")
TESTACC_ACTIVE_KEY_PAIR_ARR=($TESTACC_ACTIVE_KEY_PAIR)
TESTACC_ACTIVE_PRIVATE_KEY=${TESTACC_ACTIVE_KEY_PAIR_ARR[0]}
TESTACC_ACTIVE_PUBLIC_KEY=${TESTACC_ACTIVE_KEY_PAIR_ARR[1]}

cleos wallet import ${TESTACC_ACTIVE_PRIVATE_KEY}
cleos wallet import ${TESTACC_OWNER_PRIVATE_KEY}
cleos create account eosio testacc ${TESTACC_OWNER_PUBLIC_KEY} ${TESTACC_ACTIVE_PUBLIC_KEY}

# create keys, add keys to wallet, create new account 
add_new_account() {
	echo "Creating account for user: $1" 
	OWNER_KEY_PAIR=$(cleos create key |  grep -oE "[^:]+$")
	OWNER_KEY_PAIR_ARR=($OWNER_KEY_PAIR)
	OWNER_PRIVATE_KEY=${OWNER_KEY_PAIR_ARR[0]}
	OWNER_PUBLIC_KEY=${OWNER_KEY_PAIR_ARR[1]}

	ACTIVE_KEY_PAIR=$(cleos create key |  grep -oE "[^:]+$")
	ACTIVE_KEY_PAIR_ARR=($ACTIVE_KEY_PAIR)
	ACTIVE_PRIVATE_KEY=${ACTIVE_KEY_PAIR_ARR[0]}
	ACTIVE_PUBLIC_KEY=${ACTIVE_KEY_PAIR_ARR[1]}
	cleos wallet import ${OWNER_PRIVATE_KEY}
	cleos wallet import ${ACTIVE_PRIVATE_KEY}
	cleos create account eosio "$1" ${OWNER_PUBLIC_KEY} ${ACTIVE_PUBLIC_KEY}
}


# Add 100 citizen accounts
for number in {1..5} 
do
	add_new_account "citizen"$number
done

# Add 5 vendor
for number in {1..5} 
do
	add_new_account "vendor"$number
done

# Add 5 projects
for number in {1..5} 
do
	add_new_account "project"$number
done

# Add 1 government
add_new_account "govt"

# Add more smart contract accounts
add_new_account "eosio.token"

# Create smart contract

# Create WASM file
# eosiocpp -o /work/hello/hello.wasn /work/hello/hello.cpp

# Create ABI file
# eosiocpp -g /work/hello/hello.abi /work/hello/hello.cpp

# Deploy smart contract
# cleos set contract testacc /work/hello/ --permission testacc
cleos set contract eosio.token contracts/eosio.token -p eosio.token

# Issue tokens
cleos push action eosio.token create '{"issuer":"eosio", "maximum_supply":"1000000000.0000 HAK"}' -p eosio.token
cleos push action eosio.token issue '[ "testacc", "100.0000 HAK", "airdrop" ]' -p eosio
cleos push action eosio.token issue '[ "citizen1", "100.0000 HAK", "memo" ]' -p eosio
cleos push action eosio.token issue '[ "citizen2", "100.0000 HAK", "memo" ]' -p eosio
cleos push action eosio.token issue '[ "citizen3", "100.0000 HAK", "memo" ]' -p eosio
cleos push action eosio.token issue '[ "citizen4", "100.0000 HAK", "memo" ]' -p eosio
cleos push action eosio.token issue '[ "citizen5", "100.0000 HAK", "memo" ]' -p eosio
cleos push action eosio.token transfer '[ "citizen1", "project1", "25.0000 HAK", "voted"] ' -p citizen1

# Add more data models

