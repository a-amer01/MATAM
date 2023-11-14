#include "amount_set_str.h"
#include <stdlib.h>
#include <string.h>


typedef struct product
{
   char* product_name ;
   double  product_amount;
   struct product *next ;

}*Product;



struct AmountSet_t
{
    Product products_in_store;
    int size;
    Product iterator;
};


AmountSet asCreate()
{
    AmountSet new_as_set=malloc(sizeof (*new_as_set));
     if (!new_as_set){
          return NULL;
      }

        new_as_set->size=0;
        new_as_set->iterator=NULL;
        new_as_set->products_in_store=NULL;

        return new_as_set;

}


void asDestroy(AmountSet set)
{

  if (set == NULL){
    return;
  }

   while (set->products_in_store)
   {
     Product temp =set->products_in_store;
     set->products_in_store=set->products_in_store->next;
     free(temp->product_name);
     free(temp);
   }

    free(set);
}

AmountSet asCopy(AmountSet set)
{

  if(set==NULL) {
     return NULL;
  }

   AmountSet copy_as_set=asCreate();
     if(copy_as_set==NULL){
       return NULL;
     }

    Product set_iter=set->products_in_store;

    while (set_iter!=NULL){
     AmountSetResult result = asRegister(copy_as_set,set_iter->product_name);
        if (result !=AS_SUCCESS){
            asDestroy(copy_as_set);
            return NULL;
        }
       asChangeAmount(copy_as_set,set_iter->product_name,set_iter->product_amount);
       set_iter=set_iter->next;
    }

      return copy_as_set;

}



int asGetSize(AmountSet set)
{
  if (set==NULL){
      return -1;
    }
  return set->size;
}



bool asContains(AmountSet set, const char* element)
{
  if(set==NULL || set->size==0)
      return false;

  Product temp_inner_iter=set->products_in_store;

     while(temp_inner_iter){

     if(!(strcmp(temp_inner_iter->product_name,element))){
          return true;
      }
            temp_inner_iter=temp_inner_iter->next;
     }

    return false;
}


AmountSetResult asGetAmount(AmountSet set, const char* element, double* outAmount)
{
  if(set==NULL || element==NULL || outAmount==NULL){
    return AS_NULL_ARGUMENT;
  }

      Product temp_inner_iter=set->products_in_store;


         while(temp_inner_iter){
           if(!(strcmp(temp_inner_iter->product_name,element))) {
                *outAmount=temp_inner_iter->product_amount;
                return AS_SUCCESS;
              }
            temp_inner_iter=temp_inner_iter->next;
         }
       return  AS_ITEM_DOES_NOT_EXIST;

}

//for lack of adueqate function names that are'nt to long(i.e addToEmptySet),the 2-4 functions are for adding a product to
//an amount set in diffrent special cases.addProduct being a non-special case.
static Product createProduct(const char* element);
static AmountSetResult emptySet(AmountSet set, const char* element);
static AmountSetResult firstProduct(AmountSet set,const char* element);
static AmountSetResult addProduct(Product temp_inner_iter,const char* element);


AmountSetResult asRegister(AmountSet set, const char* element)
{
   if(set==NULL || element==NULL){
    return AS_NULL_ARGUMENT;
   }

          Product temp_inner_iter=set->products_in_store;

          if(asGetSize(set)==0) {
            return emptySet(set,element);
          }

           if (strcmp(temp_inner_iter->product_name,element)==0){
          return AS_ITEM_ALREADY_EXISTS;
          }


          if (strcmp(temp_inner_iter->product_name,element)>0){
          return firstProduct(set,element);
          }

        while(temp_inner_iter->next){

          int x=strcmp(temp_inner_iter->product_name,element);
          int y=strcmp(temp_inner_iter->next->product_name,element);

                if(x==0 || y==0){
                  return AS_ITEM_ALREADY_EXISTS;
                }

           if(x<0 && y>0){
               (set->size)++;
                return addProduct( temp_inner_iter,element);
           }

            temp_inner_iter=temp_inner_iter->next;
        }



        (set->size)++;
        return addProduct( temp_inner_iter,element);



}

static AmountSetResult addProduct(Product temp_inner_iter,const char* element)
{
     Product new_product=createProduct(element);
             if(new_product==NULL){
                 return AS_OUT_OF_MEMORY;
             }


      new_product->next=temp_inner_iter->next;
      temp_inner_iter->next=new_product;

       return AS_SUCCESS;

}

/*starting the list of product*/
static AmountSetResult emptySet(AmountSet set, const char* element)
{
           Product new_product=createProduct(element);
                      if(!new_product){
                          return AS_OUT_OF_MEMORY;
                      }

              set->products_in_store=new_product;
              new_product->next=NULL;
              (set->size)++;
              return AS_SUCCESS;


}

/* the special cas of adding the product to the start of the list,alphapitacly*/
static AmountSetResult firstProduct(AmountSet set,const char* element)
{

  Product new_product=createProduct(element);
            if(!new_product){
               return AS_OUT_OF_MEMORY;
            }

          new_product->next=set->products_in_store;
          set->products_in_store=new_product;
          (set->size)++;

          return AS_SUCCESS;

}

static  Product createProduct(const char* element)
{


           Product new_product=malloc(sizeof(*new_product));
                      if(!new_product)
                          return NULL;


              char* copy_name=malloc(strlen(element)+1);
                       if(!copy_name)
                          return NULL;

                strcpy(copy_name,element);

              new_product->product_name=copy_name;
              new_product->product_amount=0;
              new_product->next=NULL;

      return new_product;

}




AmountSetResult asChangeAmount(AmountSet set, const char* element, double amount)
{

   if (set==NULL || element==NULL) {
     return AS_NULL_ARGUMENT;
   }


   if(!(asContains(set,element))){
      return AS_ITEM_DOES_NOT_EXIST;
   }

       Product temp_inner_iter=set->products_in_store;
       Product wanted;

         while(temp_inner_iter){
           if(!(strcmp(temp_inner_iter->product_name,element))){
               wanted=temp_inner_iter;
           }
               temp_inner_iter=temp_inner_iter->next;
         }


          if((wanted->product_amount)+amount<0){
            return AS_INSUFFICIENT_AMOUNT;
          }


        (wanted->product_amount)=(wanted->product_amount)+amount;
        return AS_SUCCESS;


}


AmountSetResult asDelete(AmountSet set, const char* element)
{
  if(set==NULL || element==NULL){
       return AS_NULL_ARGUMENT;
  }

    if(!(asContains(set,element))){
       return AS_ITEM_DOES_NOT_EXIST;
    }


       Product temp_inner_iter=set->products_in_store;
       Product wanted;

       if(!(strcmp(set->products_in_store->product_name,element))){
                 wanted=temp_inner_iter;
                 set->products_in_store= set->products_in_store->next;
                 free(wanted->product_name);
                 free(wanted);
                 (set->size)--;
                 return AS_SUCCESS;
              }


         while(temp_inner_iter->next)
         {
           if(!(strcmp(temp_inner_iter->next->product_name,element))){
                 wanted=temp_inner_iter->next;
                 temp_inner_iter->next= temp_inner_iter->next->next;
                 free(wanted->product_name);
                 free(wanted); (set->size)--;
                 return AS_SUCCESS;

              }

            temp_inner_iter=temp_inner_iter->next;
         }
//the set contains the element(we checked) so it is the last one.
         free(temp_inner_iter->next->product_name);
         free(temp_inner_iter->next);
         (set->size)--;
         temp_inner_iter->next=NULL;
         return AS_SUCCESS;

}


AmountSetResult asClear(AmountSet set)
{
    if (set==NULL){
     return AS_NULL_ARGUMENT;
    }

   Product temp=set->products_in_store;
   Product temp2;

   while (temp)
   {
     free(temp->product_name);
     temp2=temp;
     temp=temp->next;
     free(temp2);
   }

   set->products_in_store=NULL;
   set->size=0;
   return AS_SUCCESS;
}

char* asGetFirst(AmountSet set)
{

   if(set==NULL || set->products_in_store==NULL){
       return NULL;
     }

  set->iterator=set->products_in_store;
   return set->iterator->product_name;

}


char* asGetNext(AmountSet set)
{
   if(set==NULL || set->products_in_store==NULL){
       return NULL;
   }

      if(set->iterator->next==NULL){
         return NULL;
      }

     set->iterator=set->iterator->next;
     return set->iterator->product_name;


}