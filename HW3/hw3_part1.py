#function adds product's information into the dictionary if the proudct
#wasn't there and it's price and amount are postive numbers
def addProduct(dict,list,name_current_selling):
    product= list[2]
    price= float(list[3])
    amount= float(list[4])
    if ((product in dict) or (price<0) or (amount<0)):
        return
    dict[product]= (price,amount)
    name_current_selling[product]= 0

#function changes product's amount in the dictionary if the proudct was there
def changeAmount(dict,list_1):
    product= list_1[2]
    added_amount= float(list_1[3])
    amount= 1
    if ((product in dict)== False):
        return
    value= list(dict[product])
    value[amount]= value[amount] + added_amount
    dict[product]= tuple(value)

#function updates our inventory if the proudct was there, if by updating
#we cause the product's amount to decline beneath 0, then we cancel only
#that proudct's order
def updateInventory(dict,list_1,name_current_selling):
    for key in range(2, len(list_1), 2):
        product= list_1[key]
        order_amount= float(list_1[key+1])
        amount= 1
        price= 0
        if ((product in dict)== False):
            continue
        value= list(dict[product])
        if value[amount] - order_amount <0:
            continue
        name_current_selling[product]+= value[price] * order_amount
        value[amount]= value[amount] - order_amount
        dict[product]= tuple(value)

#function finds best selling product, if file was  empty we return a tuple
#with an empty string and 0, otherwise we return a tuple with the best 
#selling product and it's cumulative sellings
def find_best_selling_product(file_name):
    import os
    if os.path.getsize(file_name) == 0:
        return ('',0)
    file= open(file_name,'r')
    dict= {}
    name_current_selling= {}
    for line in file:
        list= line.split()
        if list[0]== "add":
            addProduct(dict,list,name_current_selling)
        if list[0]== "change":
            changeAmount(dict,list)
        list= line.replace(',','').replace('--','').split()
        if list[0]== "ship":
            updateInventory(dict,list,name_current_selling)
    file.close()
    max_value = max(name_current_selling.values())
    max_key = [k for k,v in name_current_selling.items() if v == max_value]
    if len(max_key)>1:
        max_key.sort()
        return (max_key[0],max_value)
    return (max_key[0],max_value)

#function adds product and it's price into the dictionary if the proudct
#wasn't there and it's price and amount are postive numbers
#we know it's similar to the addProduct function, but the difference here
#is that we create a different kind of dictionary, one with only price as a value
#which would we ease our implementation for find_k_most_expensive_products function
def addProductAndPrice(dict,list):
    product= list[2]
    price= float(list[3])
    amount= float(list[4])
    if ((product in dict) or (price<0) or (amount<0)):
        return
    dict[product]= price

#function find k most expensive products, if file was empty or k<=0 we return an empty list
#otherwise we return a list of k most expensive products, the list order goes like this
#in a value descending order and if two have the same value  in a key lexicographical ascending order
def find_k_most_expensive_products(file_name, k):
    import os
    if ((os.path.getsize(file_name)== 0) or (k<=0)):
        return []
    file= open(file_name,'r')
    dict_products= {}
    sorted_k_list=[]
    for line in file:
        list= line.split()
        if list[0]== "add":
            addProductAndPrice(dict_products,list)
    file.close()
    sorted_key_values_list= sorted(dict_products.items(), key=lambda x: (-x[1], x[0]))
    sorted_k_list= [i[0] for i in sorted_key_values_list]
    if (k > len(sorted_k_list)):
        return sorted_k_list
    sorted_k_list= sorted_k_list[:k]
    return sorted_k_list