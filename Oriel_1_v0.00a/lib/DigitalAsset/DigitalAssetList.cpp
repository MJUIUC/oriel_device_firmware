#include <DigitalAsset.h>

DigitalAssetList::DigitalAssetList(){
  this->head = NULL;
  this->number_of_assets = 0;
}

void DigitalAssetList::addAssetToList(DigitalAsset *digitalAsset){
  // Serial.printf("asset: %s\n", digitalAsset->contract_address);
  DigitalAsset *tmp = this->head;
  if (tmp == NULL) {
    this->head = digitalAsset;
    this->number_of_assets++;
    return;
  }

  while(tmp != NULL) {
    if (tmp->next == NULL) {
      tmp->next = digitalAsset;
      this->number_of_assets++;
      break;
    }
    tmp = tmp->next;
  }
};