#include "matamikya_orders.h"


struct Order_t{
 unsigned int id;
 AmountSet cart;
};

Order orderCopy(Order source)
{
    if (source==NULL) {
     return NULL;
    }

        Order copy=(Order)malloc(sizeof(*copy));
             if (copy==NULL){
                 return NULL;
             }
    
    copy->id=source->id;
    copy->cart=asCopy(source->cart);
                if (copy->cart==NULL){
                       orderFree(copy);
                       return NULL;
                }
               
    return copy;
}

void orderFree(Order todelete)
{
     if(todelete==NULL){
         return;
     }

    asDestroy(todelete->cart);
    free(todelete);
}


int orderCompare(Order first ,Order second){
  return first->id -second->id;
}

void orderProductDelete(Order order,Product todelete)
{
    if (order==NULL){
      return ;
    }

    asDelete(order->cart,todelete);
    return;
}

Order  orderCreate(unsigned int order_id)
 {

     Order new_order =(Order)malloc(sizeof(*new_order));
        if (new_order==NULL){
             return NULL;
        }
       
         
         new_order->id=order_id;
         new_order->cart=asCreate((CopyASElement)productCopy,(FreeASElement)productFree,
          (CompareASElements)productCompare);
                               if (new_order->cart==NULL){
                                   orderFree(new_order);
                                  return NULL;
                               }
            return  new_order;                           

 }


 Order orderGet(Set set,unsigned int id)
{
     if (set==NULL) {
      return NULL;
     }

      SET_FOREACH(Order, iterator, set) {
          if (iterator->id==id) {
            return iterator;
          }   
      }
       
     return NULL;
}


AmountSet OrderProdSet(Order order)
{
    if (order==NULL){
      return NULL;
    }

    return order->cart;
}

int orderGetID(Order order){
 return order->id;
}
