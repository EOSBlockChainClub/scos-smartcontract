#include <eosiolib/eosio.hpp>
#include <eosiolib/print.hpp>

#include <string>

using namespace eosio;
using std::string;

class eossmartcity: public contract {
public:
  eossmartcity(account_name self) : contract (self) {}

  // @abi action addcitizen
  void addcitizen (const account_name    account,
                   const string&         citizen_name,
                   uint32_t              projectsvoted,
                   uint32_t              projectsverified,
                   uint32_t              projectsimpactvalue,
                   uint32_t              age,
                   uint32_t              govermentid);
  // @abi action addvendor
  void addvendor (const account_name    account,
                   const string&         vendor_name,
                   uint32_t              ratingoutoffive,
                   uint32_t              projectssubmitted,
                   uint32_t              projectsfunded,
                   uint32_t              projectscompleted,
                   uint32_t              taxidbygov);
  // @abi action addproject
  void addproject (const account_name    account,
                   const string&         project_name,
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
  // @abi action citizenvoteforproject
  void citizenvoteforproject (const account_name    account,
                   const string&         citizen_name,
                   const string&         project_name);
  // @abi action govapprovingproject
  void govapprovingproject (const account_name    account,
                   const string&         goverment_name,
                   const string&         project_name);
  // @abi action checkprojectstatus
  void checkprojectstatus (const account_name    account,
                   const string&         project_name);
  // @abi action onprojectcomplete
  void onprojectcomplete (const account_name    account,
                   const string&         project_name);
private:

    // @abi table citizen i64
    struct citizen {
      account_name    account;
      string          citizen_name;
      uint32_t        projectsvoted;
      uint32_t        projectsverified;
      uint32_t        projectsimpactvalue;
      uint32_t        age;
      uint32_t        govermentid;

      account_name primary_key() const { return account; }

      EOSLIB_SERIALIZE(citizen, (account)(citizen_name)(projectsvoted)(projectsverified)(projectsimpactvalue)(age)(govermentid))
    };

    typedef eosio::multi_index<N(citizen), citizen> citizen_table;

    // @abi table vendor i64
    struct vendor {
      account_name    account;
      string          vendor_name;
      uint32_t        ratingoutoffive;
      uint32_t        projectssubmitted;
      uint32_t        projectsfunded;
      uint32_t        projectscompleted;
      uint32_t        taxidbygov;

      account_name primary_key() const { return account; }

      EOSLIB_SERIALIZE(vendor, (account)(vendor_name)(ratingoutoffive)(projectssubmitted)(projectsfunded)(projectscompleted)(taxidbygov))
    };

    typedef eosio::multi_index<N(vendor), vendor> vendor_table;

    // @abi table project i64
    struct project {
      account_name    account;
      string          project_name;
      uint32_t        totaldelivercostvalue;
      uint32_t        progresstatus;
      uint32_t        votedcitizentotal;
      uint32_t        votedcitizenpositive;
      bool        isapprovedbygoverment;

      account_name primary_key() const { return account; }

      EOSLIB_SERIALIZE(project, (account)(project_name)(totaldelivercostvalue)(progresstatus)(votedcitizentotal)(votedcitizenpositive)(isapprovedbygoverment))
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

EOSIO_ABI(eossmartcity, (addcitizen)(addvendor)(addproject)(addgoverment)(citizenvoteforproject)(govapprovingproject)(checkprojectstatus)(onprojectcomplete))
