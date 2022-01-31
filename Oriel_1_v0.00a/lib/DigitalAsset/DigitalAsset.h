#ifndef DIGITAL_ASSET_h
#define DIGITAL_ASSET_h

#include <Arduino.h>

class DigitalAsset {
  public:
    DigitalAsset();
    DigitalAsset(const char * contract_address, const char * token_id);
    DigitalAsset *next;
    const char * contract_address;
    const char * token_id;
};

class DigitalAssetList {
  public:
    DigitalAssetList();
    DigitalAsset *head;
    int number_of_assets;
    void addAssetToList(DigitalAsset *digitalAsset);
};

#endif /* _DIGITAL_ASSET_H_ */