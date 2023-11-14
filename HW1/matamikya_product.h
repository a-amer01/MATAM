#ifndef MATAMIKYA_PRODUCT_H_
#define MATAMIKYA_PRODUCT_H_

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "matamikya.h"
#include  "amount_set.h"


/* Type for representing a product in a Matamikya warehouse */
typedef struct product_t *Product;



/**
 * productCopy:create a copy of the product sent
 *
 * @param source - the product to copy
 * 
 * @return 
 * -null if a null pointer was sent or a failed allocation
 * -a copy of the source product otherwise
 *    
 */
Product productCopy(Product source);



/**
 * productFree:frees the memory allocated for the sent product
 *
 * @param todelete - the product to free
 * 
 * nothing if a NULL pointer was sent otherwise frees the product sent
 */
void productFree(Product todelete);




/**
 * productCompare:compares to products based on their id
 *
 * @param first - the first product in the compartion
 * @param second - the second product in the compartion
 * 
 * @return a positve intreger if the first product id is "bigger"
 * than the first ,zero in case of equality, a negative intreger otherwise
 */
int productCompare(Product first,Product second);


/**
 * productCreate: creates a new product
 *
 * @param id - new product id.
 * @param name - name of the product, e.g. "apple".
 * @param amount - the initial amount of the product when added to the warehouse.
 * @param amountType - defines what are valid amounts for this product.
 * @param customData - pointer to product's additional data
 * @param copyData - function pointer to be used for copying product's additional 
 *      data.
 * @param freeData - function pointer to be used for free product data.
 * @param prodPrice - function pointer to be used for getting the price of some 
 *      product.
 * @return
 *     NULL - if an allocation failed.
 *     a new product otherwise.
 */

Product productCreate(const unsigned int id, const char *name,/*const double amount,*/ const MatamikyaAmountType amountType,
const MtmProductData customData, MtmCopyData copyData, MtmFreeData freeData, MtmGetProductPrice prodPrice);




/**
 * productGet:return the product with a matching id in the amount set
 *
 * @param as - the amount set to look in for 
 * @param id - the id of the wanted product
 * 
 * @return NULL-if a null argument was sent or the product doesn't exist in the amount set
 *         the product with the matching id otherwise
 */
Product productGet(AmountSet as,int id);


/**
 * porductGetAmountType:return the amounttype of agiven product
 *
 * @param requested - the product to return the amounttype of
 * 
 * @return  the amount of the product given
 */
MatamikyaAmountType porductGetAmountType(Product requested);



/**
 * calcProfit:return the product's profit made in shipping 
 *
 * @param product -the product to buy
 * @param amount - the amount bought of the product
 * @return  the profit made of the purchaes
 */
double calcProfit(Product product ,double amount);




/**
 * productGetData:puts the id of a product and the cost of a given amount of the product
 *
 * @param id-the id of the product
 * @param  price - the price of unit of product
 * @param  product - the product which info is requested
 * @param  p_amount - the amonut of the product to get
 */
void productGetData(int* id,double*price,Product product,double amount);





/**
 * productGetName:return the name of given product
 *
 * @param product -the product to buy
 * 
 * @return  the name of the product.
 */
char* productGetName(Product product);


/**
 * productGetID:return the product's profit made in shipping 
 *
 * @param product -the product to buy
 * 
 * @return the id of the product
 */
int productGetID(Product product);


#endif
