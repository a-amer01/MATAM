#include "matamikya_product.h"

struct product_t{
 char* name;
 unsigned int id;
 MatamikyaAmountType unit; 
 MtmProductData custom_data;
 MtmFreeData free_f;
 MtmCopyData copy_f;
 MtmGetProductPrice prodPrice;
};


Product productCopy(Product source)
{
    if(source==NULL){
       return NULL;
    }

    Product copy=(Product)malloc(sizeof(*copy));
                 if(copy==NULL){
                     return NULL;
                 }

      char* copy_name=(char*)malloc(sizeof(char)*strlen(source->name)+1);
                     if (copy_name==NULL){
                        productFree(copy);
                        return NULL;
                    }
      strcpy(copy_name,source->name);
      copy->name=copy_name;

      copy->id=source->id;
      copy->unit=source->unit;
      copy->copy_f=source->copy_f;
      copy->free_f=source->free_f;
      copy->prodPrice=source->prodPrice;
      copy->custom_data=source->copy_f(source->custom_data);
                if(copy->custom_data==NULL){
                   productFree(copy);
                   return NULL;
                }
       return copy;
}



void productFree( Product todelete)
{
       if (todelete==NULL) {
          return;
       }
       
     free(todelete->name);
     todelete->free_f(todelete->custom_data);
     free(todelete);
}


int productCompare(Product first,Product second){
   return (first->id)-(second->id);
}


Product productCreate(const unsigned int id, const char *name, const MatamikyaAmountType amountType,
const MtmProductData customData, MtmCopyData copyData, MtmFreeData freeData, MtmGetProductPrice prodPrice)
{
      Product new_product=(Product)malloc(sizeof(*new_product));
               if(new_product==NULL){
                  return NULL;
               }
      
                       char* copy_name=(char*)malloc(sizeof(char)*strlen(name)+1);
                     if (copy_name==NULL){
                        productFree(new_product);
                        return NULL;
                    }
       strcpy(copy_name,name);
       new_product->name=copy_name;

   new_product->id=id;
   new_product->unit=amountType; 
   new_product->copy_f=copyData;
   new_product->free_f=freeData;
   new_product->prodPrice=prodPrice;
   new_product->custom_data=(MtmProductData)copyData(customData);
                if(new_product->custom_data==NULL){
                   productFree(new_product);
                   return NULL;
                }
       return new_product;




}


Product productGet(AmountSet as,int id)
{
  if (as==NULL) {
   return NULL;
  }

 AS_FOREACH(Product, iterator, as) {
    if (iterator->id==id) {
       return iterator;
    }   
 }   
     return NULL;
}


MatamikyaAmountType porductGetAmountType(Product requested){
   return requested->unit;
}

double calcProfit(Product product ,double amount){
  return product->prodPrice(product->custom_data,amount);
}

void productGetData(int* id,double*price,Product product,double amount){  
 (*id)=product->id;
 (*price)=product->prodPrice(product->custom_data,amount);
}

char* productGetName(Product product){
 return product->name;
}

int productGetID(Product product){
 return product->id;
}


