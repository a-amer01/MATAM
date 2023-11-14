#include "matamikya.h"
#include "matamikya_print.h"
#include  <string.h>
#include  <stdlib.h>
#include  "set.h"
#include  "amount_set.h"
#include  "matamikya_product.h"
#include  "matamikya_orders.h"

struct Matamikya_t{

  AmountSet wh_products;
  Set wh_orders;
  AmountSet product_profits;
  int number_of_orders;//field for having an order unique id,no true meaning 
};

Matamikya matamikyaCreate()
{
    Matamikya warehouse=(Matamikya)malloc(sizeof(*warehouse));
      if(warehouse==NULL){
                     return NULL;
      }

    warehouse->wh_products=asCreate((CopyASElement)productCopy,(FreeASElement)productFree,
    (CompareASElements)productCompare); 
                                           if(warehouse->wh_products==NULL){
                                              free(warehouse);
                                              return NULL;
                                           }
          
    warehouse->wh_orders=setCreate((copySetElements)orderCopy,(freeSetElements)orderFree,
    (compareSetElements)orderCompare);
                                          if(warehouse->wh_orders==NULL){
                                            free(warehouse->wh_products);
                                            free(warehouse);return NULL;
                                          }

    warehouse->product_profits=asCreate((CopyASElement)productCopy,(FreeASElement)productFree,
    (CompareASElements)productCompare);
                                        if(warehouse->product_profits==NULL){
                                           asDestroy(warehouse->wh_products);
                                           setDestroy(warehouse->wh_orders);;
                                           free(warehouse);return NULL;
                                      }
    warehouse->number_of_orders=1;
    return warehouse;
    
}

void matamikyaDestroy(Matamikya matamikya)
{
    if(matamikya==NULL){
        return;
    }
     
     asDestroy(matamikya->wh_products);
     setDestroy(matamikya->wh_orders);
     asDestroy(matamikya->product_profits);
     free(matamikya);
}

static bool checkName(const char *name);
static bool checkAmount(const double amount,const MatamikyaAmountType amountType); 

MatamikyaResult mtmNewProduct(Matamikya matamikya, const unsigned int id,const char *name,const double amount,
const MatamikyaAmountType amountType,const MtmProductData customData,MtmCopyData copyData,MtmFreeData freeData,
MtmGetProductPrice prodPrice)
 {      

  if (matamikya==NULL ||name==NULL||customData==NULL||copyData==NULL||freeData==NULL||prodPrice==NULL){
       return MATAMIKYA_NULL_ARGUMENT;
  }

   bool valid=true;

                valid=checkName(name);
                      if (valid!=true) {
                         return MATAMIKYA_INVALID_NAME;
                      }

                 valid=checkAmount(amount,amountType);  
                      if (valid!=true) {
                         return MATAMIKYA_INVALID_AMOUNT;
                      }  
         
  Product new_product=productCreate(id,name,amountType,customData,copyData,freeData,prodPrice);
            
             if(new_product==NULL){
                return MATAMIKYA_OUT_OF_MEMORY;
              }

                  valid =asContains(matamikya->wh_products,new_product);
                         if (valid==true) {
                             productFree(new_product);
                             return MATAMIKYA_PRODUCT_ALREADY_EXIST;
                         } 
                   

      AmountSetResult result= asRegister(matamikya->wh_products,new_product);
      if (result==AS_SUCCESS){
          result=asChangeAmount(matamikya->wh_products,new_product,amount);
          AmountSetResult product_in_profits=asRegister(matamikya->product_profits,new_product);
    
      if (product_in_profits==AS_OUT_OF_MEMORY){
          asDelete(matamikya->wh_products,new_product);
          productFree(new_product);
          return MATAMIKYA_OUT_OF_MEMORY;
      }

         productFree(new_product);
         return MATAMIKYA_SUCCESS;     

      }else{//allocation faliure
            productFree(new_product);
            return MATAMIKYA_OUT_OF_MEMORY;
                                            }  

}


static bool checkName(const char *name)
{
     int len=strlen(name);
     if (len<2)/*"/0" is empty*/ {
         return false;
     }
      
      char first_letter=*name;
       if((first_letter>='A' && first_letter<='Z')|| (first_letter>='a' && first_letter<='z')||
         (first_letter>='0' && first_letter<='9')){
          return true;
       }
    
    return false;
     
}

static bool checkAmount(const double amount,const MatamikyaAmountType amountType)
{
      int down_value=(int)amount;
      double margin=amount-down_value;
      margin=margin*1000;

      if(amount<0){//to check if equal is also nesseray
        return false;
      }
       if (amountType==MATAMIKYA_INTEGER_AMOUNT){
            if (margin>1 && margin<999){
                 return false;
            }
        }

        if (amountType==MATAMIKYA_HALF_INTEGER_AMOUNT){
               if ((!(margin>=0 && margin<=1)) && (!(margin>=499 && margin<=501))&&
                    (!(margin>=999 && margin<=1000)))
               {
                 return false;
               }
               

            }
            
           if(amountType==MATAMIKYA_ANY_AMOUNT){
             return true;
           }
       
       return true;
           

 } 


MatamikyaResult mtmChangeProductAmount(Matamikya matamikya, const unsigned int id, const double amount)
{ 
       
       if (matamikya==NULL) {
         return MATAMIKYA_NULL_ARGUMENT;
       }


      Product requested=productGet(matamikya->wh_products,id);
               if (requested==NULL){
                    return MATAMIKYA_PRODUCT_NOT_EXIST;
                }

                        
       MatamikyaAmountType amountType=porductGetAmountType(requested);
       bool legal_add=true;
       double current_amount=0,legal_amount=true;
       asGetAmount(matamikya->wh_products,productGet(matamikya->wh_products,id),&current_amount);
        double new_amount = amount+current_amount;
          if(new_amount<0){
            legal_add = checkAmount((-new_amount),amountType); 

            }else{
           legal_add = checkAmount(new_amount,amountType); 
            }


          if(amount<0){
            legal_amount = checkAmount((-amount),amountType); 

            }else{
           legal_amount = checkAmount(amount,amountType); 
            }

          
              
                 if (legal_add!=true || legal_amount!=true){
                       return MATAMIKYA_INVALID_AMOUNT;
                 }

        AmountSetResult state=asChangeAmount(matamikya->wh_products,requested,amount);
           if (state==AS_INSUFFICIENT_AMOUNT){
               return MATAMIKYA_INSUFFICIENT_AMOUNT;
           }else{
                                     return MATAMIKYA_SUCCESS;
           }
                     
}


MatamikyaResult mtmClearProduct(Matamikya matamikya, const unsigned int id)
{
    if(matamikya==NULL){
      return MATAMIKYA_NULL_ARGUMENT;
    }


       Product requested=productGet(matamikya->wh_products,id);
                  if (requested==NULL){
                       return MATAMIKYA_PRODUCT_NOT_EXIST;
                  }

       Product copy =productCopy(requested);
                 if (copy==NULL){
                     return MATAMIKYA_OUT_OF_MEMORY;
                 }
                  
       asDelete(matamikya->product_profits,requested);
       asDelete(matamikya->wh_products,requested);

        SET_FOREACH(Order,iterator,matamikya->wh_orders){
          orderProductDelete(iterator,copy);
        }
         
  productFree(copy);
  return MATAMIKYA_SUCCESS;
     
                            
}



unsigned int mtmCreateNewOrder(Matamikya matamikya)
{

     if (matamikya==NULL){
         return 0;
     }
       
  Order new_order=orderCreate(matamikya->number_of_orders);
  (matamikya->number_of_orders)++;

     if (new_order==NULL){
         return 0;
     }

 SetResult result=setAdd(matamikya->wh_orders,new_order);
       if (result==SET_SUCCESS){
          unsigned int order_number = orderGetID(new_order);
          orderFree(new_order);
          return order_number;
     }else {
             orderFree(new_order);
              return 0;
           }
      
}


MatamikyaResult mtmChangeProductAmountInOrder(Matamikya matamikya, const unsigned int orderId,
                                     const unsigned int productId, const double amount)
{

     if (matamikya==NULL){
      return MATAMIKYA_NULL_ARGUMENT;
     }

  AmountSetResult state; double new_amount=0;


     Order requested=orderGet(matamikya->wh_orders,orderId);
         if (requested==NULL){
            return MATAMIKYA_ORDER_NOT_EXIST;
         }

     //the requested product in the warehouse
     Product product=productGet(matamikya->wh_products,productId);
             if (product==NULL){
                return MATAMIKYA_PRODUCT_NOT_EXIST;
             }

     MatamikyaAmountType amountType = porductGetAmountType(product);
     bool valid_amount=true;
     if(amount<0){    
       valid_amount = checkAmount((-amount),amountType);
     }else{
        valid_amount = checkAmount(amount,amountType);
     }
     
          if(!valid_amount){
          return MATAMIKYA_INVALID_AMOUNT;
         }

         if (amount==0){
           return MATAMIKYA_SUCCESS;
         }
         
            

   AmountSet prod_list= OrderProdSet(requested);//the list of products in the order.
   Product to_change=productGet(prod_list,productId);//the requested product inside the cart.

    if (to_change!=NULL)//the product is already in the cart
      {
        state=asChangeAmount(prod_list,to_change,amount);
        asGetAmount(prod_list,to_change,&new_amount);
        
        if (state==AS_SUCCESS && (new_amount)!=0){
                return MATAMIKYA_SUCCESS;
        }

        if (state==AS_INSUFFICIENT_AMOUNT||new_amount==0){
            asDelete(prod_list,to_change);
        }
    
     }


     if (to_change==NULL)//the product is not in the cart
     {
        asRegister(prod_list,product);

        to_change=productGet(prod_list,productId);
        state=asChangeAmount(prod_list,to_change,amount);
          
           if (state==AS_SUCCESS){
           return MATAMIKYA_SUCCESS;
           }

           if (state==AS_INSUFFICIENT_AMOUNT){
               asDelete(prod_list,to_change);
               return MATAMIKYA_SUCCESS;
           }
      }

        return MATAMIKYA_SUCCESS;
     
}


 MatamikyaResult mtmShipOrder(Matamikya matamikya, const unsigned int orderId)
 {
      if (matamikya==NULL) {
        return MATAMIKYA_NULL_ARGUMENT;
      }

         Order order=orderGet(matamikya->wh_orders,orderId);
               if (order==NULL){
                   return MATAMIKYA_ORDER_NOT_EXIST;
               }


      AmountSet prod_list= OrderProdSet(order);
      double amount_in_order=0, amount_in_wh=0; 

   //can do this becasue the iterator state is an-changed after calling the function
        AS_FOREACH(Product, iterator, prod_list){
         asGetAmount(prod_list,iterator,&amount_in_order);
         asGetAmount(matamikya->wh_products,iterator,&amount_in_wh);
          if (amount_in_order>amount_in_wh){
              return MATAMIKYA_INSUFFICIENT_AMOUNT;
          }
                                 
        }

        double amount=0;
        AS_FOREACH(Product, iterator, prod_list) {
         asGetAmount(prod_list,iterator,&amount);
         asChangeAmount(matamikya->wh_products,iterator,(-amount));
         double profit=calcProfit(iterator,amount);
         asChangeAmount(matamikya->product_profits,iterator,profit);                      
        }

        setRemove(matamikya->wh_orders,order);
        return MATAMIKYA_SUCCESS;

      
 }


 MatamikyaResult mtmCancelOrder(Matamikya matamikya, const unsigned int orderId)
 {
      if (matamikya==NULL){
         return MATAMIKYA_NULL_ARGUMENT;
      }

      Order order=orderGet(matamikya->wh_orders,orderId);
                if (order==NULL){
                    return MATAMIKYA_ORDER_NOT_EXIST;
                }

      setRemove(matamikya->wh_orders,order);
      return MATAMIKYA_SUCCESS;   
 }


 
MatamikyaResult mtmPrintInventory(Matamikya matamikya, FILE *output)
{
    if (matamikya==NULL || output==NULL){
        return MATAMIKYA_NULL_ARGUMENT;
    }

    fprintf(output,"Inventory Status:\n");
    
    char* name;   int id=0 ; double amount=0,price=0;
     
    AS_FOREACH(Product, iterator, matamikya->wh_products){
      productGetData(&id,&price,iterator,1.0);
      name=productGetName(iterator);
      asGetAmount(matamikya->wh_products,iterator,&amount);
      mtmPrintProductDetails(name,id,amount,price,output);    
    }

   return MATAMIKYA_SUCCESS;
}


MatamikyaResult mtmPrintOrder(Matamikya matamikya, const unsigned int orderId, FILE *output)
{
   if (matamikya==NULL|| output==NULL){
     return MATAMIKYA_NULL_ARGUMENT;
   }
    
   Order order=orderGet(matamikya->wh_orders,orderId);
         if (order==NULL){
             return MATAMIKYA_ORDER_NOT_EXIST;
         }

        int ord_id=orderGetID(order);
        mtmPrintOrderHeading(ord_id,output);
        AmountSet prod_list= OrderProdSet(order);
        char* name;   int id=0 ; double amount=0,price=0,total=0; 

       AS_FOREACH(Product, iterator, prod_list){
         asGetAmount(prod_list,iterator,&amount);
         productGetData(&id,&price,iterator,amount);
         name=productGetName(iterator);
         total=total+price;
         mtmPrintProductDetails(name,id,amount,price,output); 
        }
                  
        mtmPrintOrderSummary(total,output);

        return MATAMIKYA_SUCCESS;

   
    
}


MatamikyaResult mtmPrintBestSelling(Matamikya matamikya, FILE *output)
{
     if (matamikya==NULL || output==NULL){
      return MATAMIKYA_NULL_ARGUMENT;
     }

    fprintf(output,"Best Selling Product:\n");

    double max=-1; char* name; int id=0; double amount=0;
     
     AS_FOREACH(Product,iterator, matamikya->product_profits){
      asGetAmount(matamikya->product_profits,iterator,&amount);
          if (amount>max && amount>0){
              max=amount;
          }
     }
    
            if (max==-1){
               fprintf(output,"none\n");
               return MATAMIKYA_SUCCESS;
            }
   
    AS_FOREACH(Product,iterator, matamikya->product_profits){
      asGetAmount(matamikya->product_profits,iterator,&amount);
        if (amount==max){
            id=productGetID(iterator);
            name=productGetName(iterator);
            mtmPrintIncomeLine(name,id,max,output);
            break;   
        }
    }     
     return MATAMIKYA_SUCCESS;
     
}

