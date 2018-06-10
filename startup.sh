#!/bin/sh

alias cleos='docker exec eosio /opt/eosio/bin/cleos --wallet-url http://localhost:8888'
alias eosiocpp='docker exec eosio eosiocpp'

WALLET_PASSWORD=$(cleos wallet create | tail -n 1)
echo "\"wallet_password\" : \"$WALLET_PASSWORD\"," >> keyfile.json

cleos wallet unlock --password ${WALLET_PASSWORD} --unlock-timeout 36000

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

	echo "\""$1"\" : \""$OWNER_PRIVATE_KEY"\"," >> keyfile.json

	cleos wallet import ${OWNER_PRIVATE_KEY}
	cleos wallet import ${ACTIVE_PRIVATE_KEY}
	cleos create account eosio "$1" ${OWNER_PUBLIC_KEY} ${ACTIVE_PUBLIC_KEY}
	cleos push action eosio updateauth "{\"account\":\"$1\",\"permission\":\"active\",\"parent\":\"owner\",\"auth\":{\"keys\":[{\"key\":\"${OWNER_PUBLIC_KEY}\", \"weight\":1}],\"threshold\":1,\"accounts\":[{\"permission\":{\"actor\":\"eosio.token\",\"permission\":\"eosio.code\"},\"weight\":1}],\"waits\":[]}}" -p $1
}

# Add more smart contract accounts
add_new_account "eosio.token"
add_new_account "eossmartcity"

# Create smart contract
SMART_CONTRACT_NAME="eossmartcity"
# Create WASM file
eosiocpp -o /work/${SMART_CONTRACT_NAME}/${SMART_CONTRACT_NAME}.wasm /work/${SMART_CONTRACT_NAME}/${SMART_CONTRACT_NAME}.cpp

# Create ABI file
eosiocpp -g /work/${SMART_CONTRACT_NAME}/${SMART_CONTRACT_NAME}.abi /work/${SMART_CONTRACT_NAME}/${SMART_CONTRACT_NAME}.cpp

# Deploy smart contract
# cleos set contract testacc /work/hello/ --permission testacc
cleos set contract eosio.token contracts/eosio.token -p eosio.token
cleos set contract ${SMART_CONTRACT_NAME} /work/${SMART_CONTRACT_NAME} -p ${SMART_CONTRACT_NAME}
cleos push action eosio.token create '{"issuer":"eosio", "maximum_supply":"1000000000.0000 HAK"}' -p eosio.token


add_new_citizen() {
	# cleos push action ${smartContractName} ${functionName} '["account_name", "citizen_name", balance, "projectsVoted", "projectsVerified", "projectsImpactValue", "age", "governmentId"]'
	cleos push action eossmartcity addcitizen "[\"$1\", \"$2\", $3, $4, $5, $6, $7, $8]" -p "$1"
	cleos push action eosio.token issue "[ \"$1\", \"100.0000 HAK\", \"airdrop\" ]" -p eosio
}

add_new_vendor() {
	cleos push action eossmartcity addvendor "[\"$1\", \"$2\", \"100.0000 HAK\", $4, $5, $6]" -p "$1"
}

add_new_govt() {
	cleos push action eossmartcity addgovernment "[\"$1\", \"$2\", $3, $4, $5]" -p "$1"
}

add_new_project() {
	cleos push action eossmartcity addproject "[\"$1\", \"$2\", \"100.0000 HAK\", \"$4\", $5, $6, $7, $8, $9]" -p "$1"
}

# Add 5^4 = 625 citizen accounts
for n1 in {1..5}
do
	for n2 in {1..5}
	do
		for n3 in {1..2}
		do
			for n4 in {1..2}
			do			
				add_new_account "c"$n1$n2$n3$n4
				add_new_citizen "c"$n1$n2$n3$n4 "c"$n1$n2$n3$n4 "\"100 HAK\"" "$((RANDOM%100))" "$((RANDOM%100))" "$((RANDOM%100))" "$((RANDOM%80+20))" "$n1$n2$n3$n4"
			done
		done
	done
done

# Add 5 vendor
for number in {1..5} 
do
	add_new_account "vendor"$number
done
# Add 5 vendors
# account_name, vendor_name, vendor_bal, ratingoutoffive, projectssubmitted, projectedfunded projectscomplete, taxidbygov
add_new_vendor "vendor1" "vendor1" "100 HAK" 4 2 2 7 1234
add_new_vendor "vendor2" "vendor2" "100 HAK" 7 2 5 12 1235
add_new_vendor "vendor3" "vendor3" "100 HAK" 3 1 2 8 1236
add_new_vendor "vendor4" "vendor4" "100 HAK" 4 2 4 21 1237
add_new_vendor "vendor5" "vendor5" "100 HAK" 1 2 3 4 1238

# Add 5 projects
for number in {1..5} 
do
	add_new_account "project"$number
done
# account_name, project_name, project_bal, project_imagurl, totaldelivercostvalue, progressstatus votedcitizentotal, votedcitizenpostive, isapprovedbygovernment
add_new_project "project1" "Wind Turbines" "0 HAK" "https://images.pexels.com/photos/414807/pexels-photo-414807.jpeg?auto=compress&cs=tinysrgb&h=650&w=940" 0 0 0 0 0
add_new_project "project2" "Smart Homes" "0 HAK" "https://images.pexels.com/photos/186077/pexels-photo-186077.jpeg?auto=compress&cs=tinysrgb&h=650&w=940" 0 0 0 0 0
add_new_project "project3" "Drinking Water" "0 HAK" "https://images.pexels.com/photos/66090/pexels-photo-66090.jpeg?auto=compress&cs=tinysrgb&h=650&w=940" 0 0 0 0 0
add_new_project "project4" "Universal Healthcare" "https://images.pexels.com/photos/905874/pexels-photo-905874.jpeg?auto=compress&cs=tinysrgb&h=650&w=940" 0 0 0 0 0
add_new_project "project5" "Education" "https://images.pexels.com/photos/301926/pexels-photo-301926.jpeg?auto=compress&cs=tinysrgb&h=650&w=940" 0 0 0 0 0

# Add 1 government
add_new_account "govt"
# account_name, government_name, projectsviewed, projectsapproved, partygovid
add_new_govt "govt" "govt" 0 0 0 1234


# Issue tokens
# cleos push action eosio.token issue '[ "c1111", "100.0000 HAK", "memo" ]' -p eosio
# cleos push action eosio.token issue '[ "c1112", "100.0000 HAK", "memo" ]' -p eosio
# cleos push action eosio.token issue '[ "c1113", "100.0000 HAK", "memo" ]' -p eosio
# cleos push action eosio.token issue '[ "citizen4", "100.0000 HAK", "memo" ]' -p eosio
# cleos push action eosio.token issue '[ "citizen5", "100.0000 HAK", "memo" ]' -p eosio
# cleos push action eosio.token transfer '[ "c1111", "project1", "1.0000 HAK", "voted"] ' -p c1111

# Add more data models

# cleos push action eosio updateauth '{"account":"citizen2","permission":"active","parent":"owner","auth":{"keys":[{"key":"EOS5rpP47YcPQRfGBWcMwW5Xcd9hK7e6i8n4LBqDkTYuYMzGuhqkz", "weight":1}],"threshold":1,"accounts":[{"permission":{"actor":"eosio.token","permission":"eosio.code"},"weight":1}],"waits":[]}}' -p citizen2