#ifndef MATAMIKYA_ORDERS_H_
#define MATAMIKYA_ORDERS_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "matamikya.h"
#include "set.h"
#include "amount_set.h"
#include "matamikya_product.h"


/* Type for representing a product in a Matamikya warehouse */
typedef struct Order_t *Order;



/**
 * orderCopy:create a copy of the product sent
 *
 * @param source - the Order to copy
 * 
 * @return 
 * -null if a null pointer was sent or a failed allocation
 * -a copy of the source product otherwise
 *    
 */
Order orderCopy(Order source);



/**
 * orderFree:frees the memory allocated for the sent product
 *
 * @param todelete - the Order to free
 * 
 * nothing if a NULL pointer was sent otherwise frees the product sent
 */
void orderFree(Order todelete);




/**
 * orderCompare:compares to products based on their id
 *
 * @param first - the first Order in the compartion
 * @param second - the second Order in the compartion
 * 
 * @return a positve intreger if the first Order id is "bigger"
 * than the first ,zero in case of equality, a negative intreger otherwise
 */
int orderCompare(Order first ,Order second);






/**
*orderProductDelete:deletes a product from a given order
*
* @param order - the order to delete the product from
* @param  todelete - the product to delete from the order
*
* @return  .
*/
void orderProductDelete(Order order,Product todelete);



/**
 * create_order=creates a new empty order with a uniqe id
 * @return -null if an allocation failed a new empty order otherwise
 */ 
Order orderCreate(unsigned int order_id);


/**
 * orderGet:return the Orders with a matching id in the amount set
 *
 * @param as - the  set to look in for 
 * @param id - the id of the wanted product
 * 
 * @return NULL-if a null argument was sent or the product doesn't exist in the amount set
 *         the product with the matching id otherwise
 */
 Order orderGet(Set set,unsigned int id);






/**
 * OrderProdSet:return the product list of the givin order
 *
 * @param order -the order to get the list form
 * 
 * @return NULL-if a null argument was sent otherise the shopping list
 */
AmountSet OrderProdSet(Order order);



/**
 * OrderProdSet:return the product list of the givin order
 *
 * @param order -the order to return the id of
 * 
 * @return the id of the order
 */
int orderGetID(Order order);



#endif
