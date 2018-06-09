#include <eossmartcity.hpp>
#include <eosiolib/asset.hpp>
#include <eosiolib/action.hpp>
#include <iostream>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <time.h>       /* time */

using namespace std;

void eossmartcity::addcitizen (const account_name    account,
                   const string&         citizen_name,
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

void eossmartcity::citizenvote (const account_name    account,
                   const string&         citizen_name,
                   const string&         project_name) {

  require_auth (account);

/*
TO BE DONE
*/

}

void eossmartcity::govapprove (const account_name    account,
                   const string&         goverment_name,
                   const string&         project_name) {

  require_auth (account);

/*
TO BE DONE
*/

}

void eossmartcity::projectstat (const account_name    account,
                   const string&         project_name) {

  require_auth (account);

/*
TO BE DONE
*/

}

void eossmartcity::projectdone (const account_name    account,
                   const string&         project_name) {

  require_auth (account);

/*
TO BE DONE
*/

}