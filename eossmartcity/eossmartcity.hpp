#include <eosiolib/eosio.hpp>
#include <eosiolib/asset.hpp>
#include <eosiolib/print.hpp>

#include <string>

using namespace eosio;
using eosio::asset;
using std::string;

class eossmartcity: public contract {
public:
  eossmartcity(account_name self) : contract (self) {}

  // @abi action addcitizen
  void addcitizen (const account_name    account,
                   const string&         citizen_name,
                   const asset&         citizen_bal,
                   uint32_t              projectsvoted,
                   uint32_t              projectsverified,
                   uint32_t              projectsimpactvalue,
                   uint32_t              age,
                   uint32_t              govermentid);
  // @abi action addvendor
  void addvendor (const account_name    account,
                   const string&         vendor_name,
                   const asset&         vendor_bal,
                   uint32_t              ratingoutoffive,
                   uint32_t              projectssubmitted,
                   uint32_t              projectsfunded,
                   uint32_t              projectscompleted,
                   uint32_t              taxidbygov);
  // @abi action addproject
  void addproject (const account_name    account,
                   const string&         project_name,
                   const asset&         project_bal,
                   const string&         project_imagurl,
                   uint32_t              totaldelivercostvalue,
                   uint32_t              progresstatus,
                   uint32_t              votedcitizentotal,
                   uint32_t              votedcitizenpositive,
                   bool              isapprovedbygoverment);
  // @abi action addgoverment
  void addgoverment (const account_name    account,
                   const string&         goverment_name,
                   uint32_t              projectsviewed,
                   uint32_t              projectsapproved,
                   uint32_t              partygovid);
  // @abi action citizenupdate
  void citizenupdate (const account_name    account,
                   const string&         citizen_name,
                   const asset&         citizen_bal,
                   uint32_t              projectsvoted,
                   uint32_t              projectsverified,
                   uint32_t              projectsimpactvalue,
                   uint32_t              age,
                   uint32_t              govermentid);
  // @abi action vendorupdate
  void vendorupdate (const account_name    account,
                   const string&         vendor_name,
                   const asset&         vendor_bal,
                   uint32_t              ratingoutoffive,
                   uint32_t              projectssubmitted,
                   uint32_t              projectsfunded,
                   uint32_t              projectscompleted,
                   uint32_t              taxidbygov);
  // @abi action projectupdate
  void projectupdate (const account_name    account,
                   const string&         project_name,
                   const asset&         project_bal,
                   const string&         project_imagurl,
                   uint32_t              totaldelivercostvalue,
                   uint32_t              progresstatus,
                   uint32_t              votedcitizentotal,
                   uint32_t              votedcitizenpositive,
                   bool              isapprovedbygoverment);
  // @abi action govupdate
  void govupdate (const account_name    account,
                   const string&         goverment_name,
                   uint32_t              projectsviewed,
                   uint32_t              projectsapproved,
                   uint32_t              partygovid);
  // @abi action citizenvote
  void citizenvote (const account_name    citizen_account,
                   const account_name   project_account,
                   uint32_t             tokenquantity,
                   const asset&         citizen_bal,
                   const asset&         project_bal);
  // @abi action govapprove
  void govapprove (const account_name    project_account,
                   const account_name    gov_account,
                   bool              isapprovedbygoverment);
  // @abi action projectstat
  void projectstat (const account_name    account,
                   const string&         project_name);
  // @abi action projectdone
  void projectdone (const account_name    vendor_account,
                   const account_name   project_account,
                   uint32_t             tokenquantity,
                   const asset&         vendor_bal,
                   const asset&         project_bal);
private:

    // @abi table citizen i64
    struct citizen {
      account_name    account;
      string          citizen_name;
      asset           citizen_bal;
      uint32_t        projectsvoted;
      uint32_t        projectsverified;
      uint32_t        projectsimpactvalue;
      uint32_t        age;
      uint32_t        govermentid;

      account_name primary_key() const { return account; }

      EOSLIB_SERIALIZE(citizen, (account)(citizen_name)(citizen_bal)(projectsvoted)(projectsverified)(projectsimpactvalue)(age)(govermentid))
    };

    typedef eosio::multi_index<N(citizen), citizen> citizen_table;

    // @abi table vendor i64
    struct vendor {
      account_name    account;
      string          vendor_name;
      asset           vendor_bal;
      uint32_t        ratingoutoffive;
      uint32_t        projectssubmitted;
      uint32_t        projectsfunded;
      uint32_t        projectscompleted;
      uint32_t        taxidbygov;

      account_name primary_key() const { return account; }

      EOSLIB_SERIALIZE(vendor, (account)(vendor_name)(vendor_bal)(ratingoutoffive)(projectssubmitted)(projectsfunded)(projectscompleted)(taxidbygov))
    };

    typedef eosio::multi_index<N(vendor), vendor> vendor_table;

    // @abi table project i64
    struct project {
      account_name    account;
      string          project_name;
      asset           project_bal;
      string          project_imagurl;
      uint32_t        totaldelivercostvalue;
      uint32_t        progresstatus;
      uint32_t        votedcitizentotal;
      uint32_t        votedcitizenpositive;
      bool        isapprovedbygoverment;

      account_name primary_key() const { return account; }

      EOSLIB_SERIALIZE(project, (account)(project_name)(project_bal)(project_imagurl)(totaldelivercostvalue)(progresstatus)(votedcitizentotal)(votedcitizenpositive)(isapprovedbygoverment))
    };

    typedef eosio::multi_index<N(project), project> project_table;

    // @abi table goverment i64
    struct goverment {
      account_name    account;
      string          goverment_name;
      uint32_t        projectsviewed;
      uint32_t        projectsapproved;
      uint32_t        partygovid;

      account_name primary_key() const { return account; }

      EOSLIB_SERIALIZE(goverment, (account)(goverment_name)(projectsviewed)(projectsapproved)(partygovid))
    };

    typedef eosio::multi_index<N(goverment), goverment> goverment_table;

};

EOSIO_ABI(eossmartcity, (addcitizen)(addvendor)(addproject)(addgoverment)(citizenupdate)(vendorupdate)(projectupdate)(govupdate)(citizenvote)(govapprove)(projectstat)(projectdone))
