#include <eossmartcity.hpp>
#include <eosiolib/asset.hpp>
#include <eosiolib/action.hpp>
#include <iostream>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <time.h>       /* time */

using namespace std;
using namespace eosio;
using eosio::permission_level;

void eossmartcity::addcitizen (const account_name    account,
                   const string&         citizen_name,
                   const asset&         citizen_bal,
                   uint32_t              projectsvoted,
                   uint32_t              projectsverified,
                   uint32_t              projectsimpactvalue,
                   uint32_t              age,
                   uint32_t              govermentid) {

  require_auth (account);

  citizen_table citizen(_self, _self);

  auto itr = citizen.find(account);
  eosio_assert(itr == citizen.end(), "citizen already exists");

  citizen.emplace(account, [&](auto& t) {
    t.account         = account;
    t.citizen_name        = citizen_name;
    t.citizen_bal        = citizen_bal;
    t.projectsvoted        = projectsvoted;
    t.projectsverified       = projectsverified;
    t.projectsimpactvalue    = projectsimpactvalue;
    t.age  = age;
    t.govermentid       = govermentid;
  });

  print (name{account}, " citizen created.");
}

void eossmartcity::citizenupdate (const account_name    account,
                   const string&         citizen_name,
                   const asset&         citizen_bal,
                   uint32_t              projectsvoted,
                   uint32_t              projectsverified,
                   uint32_t              projectsimpactvalue,
                   uint32_t              age,
                   uint32_t              govermentid) {

  require_auth (account);

  citizen_table citizen(_self, _self);

  auto itr = citizen.find(account);
  eosio_assert(itr != citizen.end(), "citizen for account not found");

  citizen.modify(itr, account, [&](auto& t) {
    t.account         = account;
    t.citizen_name        = citizen_name;
    t.citizen_bal        = citizen_bal;
    t.projectsvoted        = projectsvoted;
    t.projectsverified       = projectsverified;
    t.projectsimpactvalue    = projectsimpactvalue;
    t.age  = age;
    t.govermentid       = govermentid;
  });

  print (name{account}, " citizen updated.");
}

void eossmartcity::addvendor (const account_name    account,
                   const string&         vendor_name,
                   const asset&         vendor_bal,
                   uint32_t              ratingoutoffive,
                   uint32_t              projectssubmitted,
                   uint32_t              projectsfunded,
                   uint32_t              projectscompleted,
                   uint32_t              taxidbygov) {

  require_auth (account);

  vendor_table vendor(_self, _self);

  auto itr = vendor.find(account);
  eosio_assert(itr == vendor.end(), "vendor already exists");

  vendor.emplace(account, [&](auto& t) {
    t.account         = account;
    t.vendor_name        = vendor_name;
    t.vendor_bal        = vendor_bal;
    t.ratingoutoffive        = ratingoutoffive;
    t.projectssubmitted       = projectssubmitted;
    t.projectsfunded    = projectsfunded;
    t.projectscompleted  = projectscompleted;
    t.taxidbygov       = taxidbygov;
  });

  print (name{account}, " vendor created.");
}

void eossmartcity::vendorupdate (const account_name    account,
                   const string&         vendor_name,
                   const asset&         vendor_bal,
                   uint32_t              ratingoutoffive,
                   uint32_t              projectssubmitted,
                   uint32_t              projectsfunded,
                   uint32_t              projectscompleted,
                   uint32_t              taxidbygov) {

  require_auth (account);

  vendor_table vendor(_self, _self);

  auto itr = vendor.find(account);
  eosio_assert(itr != vendor.end(), "vendor not found");

  vendor.modify(itr, account, [&](auto& t) {
    t.account         = account;
    t.vendor_name        = vendor_name;
    t.vendor_bal        = vendor_bal;
    t.ratingoutoffive        = ratingoutoffive;
    t.projectssubmitted       = projectssubmitted;
    t.projectsfunded    = projectsfunded;
    t.projectscompleted  = projectscompleted;
    t.taxidbygov       = taxidbygov;
  });

  print (name{account}, " vendor updated.");
}

void eossmartcity::addproject (const account_name    account,
                   const string&         project_name,
                   const asset&         project_bal,
                   const string&         project_imagurl,
                   uint32_t              totaldelivercostvalue,
                   uint32_t              progresstatus,
                   uint32_t              votedcitizentotal,
                   uint32_t              votedcitizenpositive,
                   bool              isapprovedbygoverment) {

  require_auth (account);

  project_table project(_self, _self);

  auto itr = project.find(account);
  eosio_assert(itr == project.end(), "project already exists");

  project.emplace(account, [&](auto& t) {
    t.account         = account;
    t.project_name        = project_name;
    t.project_bal        = project_bal;
    t.project_imagurl        = project_imagurl;    
    t.totaldelivercostvalue        = totaldelivercostvalue;
    t.progresstatus       = progresstatus;
    t.votedcitizentotal    = votedcitizentotal;
    t.votedcitizenpositive  = votedcitizenpositive;
    t.isapprovedbygoverment       = isapprovedbygoverment;
  });

  print (name{account}, " project created.");
}

void eossmartcity::projectupdate (const account_name    account,
                   const string&         project_name,
                   const asset&         project_bal,
                   const string&         project_imagurl,
                   uint32_t              totaldelivercostvalue,
                   uint32_t              progresstatus,
                   uint32_t              votedcitizentotal,
                   uint32_t              votedcitizenpositive,
                   bool              isapprovedbygoverment) {

  require_auth (account);

  project_table project(_self, _self);

  auto itr = project.find(account);
  eosio_assert(itr != project.end(), "project not found");

  project.modify(itr, account, [&](auto& t) {
    t.account         = account;
    t.project_name        = project_name;
    t.project_bal        = project_bal;
    t.project_imagurl        = project_imagurl;  
    t.totaldelivercostvalue        = totaldelivercostvalue;
    t.progresstatus       = progresstatus;
    t.votedcitizentotal    = votedcitizentotal;
    t.votedcitizenpositive  = votedcitizenpositive;
    t.isapprovedbygoverment       = isapprovedbygoverment;
  });

  print (name{account}, " project updated.");
}

void eossmartcity::addgoverment (const account_name    account,
                   const string&         goverment_name,
                   uint32_t              projectsviewed,
                   uint32_t              projectsapproved,
                   uint32_t              partygovid) {

  require_auth (account);

  goverment_table goverment(_self, _self);

  auto itr = goverment.find(account);
  eosio_assert(itr == goverment.end(), "goverment already exists");

  goverment.emplace(account, [&](auto& t) {
    t.account         = account;
    t.goverment_name        = goverment_name;
    t.projectsviewed        = projectsviewed;
    t.projectsapproved    = projectsapproved;
    t.partygovid  = partygovid;
  });

  print (name{account}, " goverment created.");
}

void eossmartcity::govupdate (const account_name    account,
                   const string&         goverment_name,
                   uint32_t              projectsviewed,
                   uint32_t              projectsapproved,
                   uint32_t              partygovid) {

  require_auth (account);

  goverment_table goverment(_self, _self);

  auto itr = goverment.find(account);
  eosio_assert(itr != goverment.end(), "goverment not found");

  goverment.modify(itr, account, [&](auto& t) {
    t.account         = account;
    t.goverment_name        = goverment_name;
    t.projectsviewed        = projectsviewed;
    t.projectsapproved    = projectsapproved;
    t.partygovid  = partygovid;
  });

  print (name{account}, " goverment updated.");
}

void eossmartcity::citizenvote (const account_name    citizen_account,
                   const account_name   project_account,
                   uint32_t             tokenquantity,
                   const asset&         citizen_bal,
                   const asset&         project_bal) {

  require_auth (citizen_account);

  //Check if citizen exists
  citizen_table citizen(_self, _self);

  auto itr = citizen.find(citizen_account);
  eosio_assert(itr == citizen.end(), "citizen found");

  //Check if project exists
  project_table project(_self, _self);

  auto itr2 = project.find(project_account);
  eosio_assert(itr2 == project.end(), "project found");

  action(
      permission_level{ citizen_account, N(active) },
      N(eosio.token), N(transfer),
      std::make_tuple(citizen_account, project_account, tokenquantity, std::string("ONE TOKEN TRANSFERED ON VOTE to PROJECT"))
   ).send();

  citizen.modify(itr, citizen_account, [&](auto& t) {
    t.citizen_bal        = citizen_bal;
  });

  print (name{citizen_account}, "citizen balance is reduced by one");

  project.modify(itr2, project_account, [&](auto& t2) {
    t2.project_bal        = project_bal;
  });

  print (name{project_account}, "project balance is increased by one");

}


void eossmartcity::govapprove (const account_name    project_account,
                   const account_name    gov_account,
                   bool              isapprovedbygoverment) {

  require_auth (gov_account);

  goverment_table goverment(_self, _self);

  auto itr = goverment.find(gov_account);
  eosio_assert(itr == goverment.end(), "goverment found");

  project_table project(_self, _self);

  auto itr2 = project.find(project_account);
  eosio_assert(itr2 == project.end(), "project found");

  project.modify(itr2, project_account, [&](auto& t) {
    t.isapprovedbygoverment         = isapprovedbygoverment;
  });

  print (name{gov_account}, " goverment has approved the project.");
  print (name{project_account}, " project has approved by the goverment.");

}

void eossmartcity::projectdone (const account_name    vendor_account,
                   const account_name   project_account,
                   uint32_t             tokenquantity,
                   const asset&         vendor_bal,
                   const asset&         project_bal) {

  require_auth (project_account);

  //Check if vendor exists
  vendor_table vendor(_self, _self);

  auto itr = vendor.find(vendor_account);
  eosio_assert(itr == vendor.end(), "vendor found");

  //Check if project exists
  project_table project(_self, _self);

  auto itr2 = project.find(project_account);
  eosio_assert(itr2 == project.end(), "project found");

  action(
      permission_level{ project_account, N(active) },
      N(eosio.token), N(transfer),
      std::make_tuple(project_account, vendor_account, tokenquantity, std::string("ALL TOKEN TRANSFERED FROM PROJECT TO VENDOR AFTER DELIVERY"))
   ).send();

  vendor.modify(itr, vendor_account, [&](auto& t) {
    t.vendor_bal        = vendor_bal;
  });

  print (name{vendor_account}, "vendor balance is updated");

  project.modify(itr2, project_account, [&](auto& t2) {
    t2.project_bal        = project_bal;
  });

  print (name{project_account}, "project balance is increased by one");

}