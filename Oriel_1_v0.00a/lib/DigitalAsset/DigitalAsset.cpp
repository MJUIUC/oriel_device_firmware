#include <DigitalAsset.h>

DigitalAsset::DigitalAsset(){
  this->next = NULL;
}
DigitalAsset::DigitalAsset(const char * contract_address, const char * token_id){
   this->contract_address = contract_address;
   this->token_id = token_id;
   this->next = NULL;
}