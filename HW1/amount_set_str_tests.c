#include <stdlib.h>
#include <stdio.h>
#include "tests/test_utilities.h"
#include "amount_set_str.h"
#include <string.h>


/*not much here*/
bool testasCreateDestroy()
{
    printf("testing asCreate \n");
    AmountSet test_set = asCreate();
          if(test_set==NULL){
             printf("failed to allocate a new empty amount set\n");
             return false;
          }
   /*looking for an undefined behavior*/
       asDestroy(test_set);

   AmountSet test_set2 = asCreate();
          if(test_set2==NULL){
             printf("failed to allocate a new empty amount set\n");
             return false;
          }
          asDestroy(test_set2);
         

    AmountSet test_set3 = asCreate();
          if(test_set3==NULL){
             printf("failed to allocate a new empty amount set\n");
             return false;
          }
           asDestroy(test_set3);
           asDestroy(NULL);
           return true;
    
             
}


bool testasRegister()
{
    AmountSet test_set = asCreate();
       if (test_set==NULL){
           printf("allocation faluire");
           return false;
       }
 AmountSetResult condtion;
/*checking each return value of the function and special cases for each one*/
/*we are starting with very basic tests,which failing means there is a huge problem*/
   condtion = asRegister(test_set,NULL);
          if (condtion!=AS_NULL_ARGUMENT){
               asDestroy(test_set);
              return false;
          }
          
    condtion = asRegister(NULL,"we passed a NULL");
             if (condtion!=AS_NULL_ARGUMENT){
              asDestroy(test_set);
              return false;
          }
   /* AmountSet test_set1= asCreate();
    asDestroy(test_set1);

    condtion = asRegister(test_set1,"doesnt matter whats here");
            if (condtion!=AS_NULL_ARGUMENT){
               asDestroy(test_set);
              return false;
          }*/
    
    condtion = asRegister(test_set,"Apples");
            if (condtion!=AS_SUCCESS){
                 asDestroy(test_set);
              return false;
          }

    condtion = asRegister(test_set,"!");
            if (condtion!=AS_SUCCESS){
                 asDestroy(test_set);
              return false;
          }

    condtion = asRegister(test_set,"@@$#$@$#$#$#");
            if (condtion!=AS_SUCCESS){
                 asDestroy(test_set);
              return false;
          }
        
    condtion = asRegister(test_set,"254dv3##CD");
            if (condtion!=AS_SUCCESS){
                 asDestroy(test_set);
              return false;
          }



    condtion = asRegister(test_set,"chairs");
            if (condtion!=AS_SUCCESS){
                 asDestroy(test_set);
              return false;
          }
    condtion = asRegister(test_set,"smart tv");
            if (condtion!=AS_SUCCESS){
                 asDestroy(test_set);
              return false;
          }
    condtion = asRegister(test_set,"smartphone");
            if (condtion!=AS_SUCCESS){
                 asDestroy(test_set);
              return false;
          }
    condtion = asRegister(test_set,"Headphones");
            if (condtion!=AS_SUCCESS){
                 asDestroy(test_set);
              return false;
          }
    condtion = asRegister(test_set,"i dont know");
            if (condtion!=AS_SUCCESS){
                 asDestroy(test_set);
              return false;
          }
    
    condtion = asRegister(test_set,"");
            if (condtion!=AS_SUCCESS){
                 asDestroy(test_set);
              return false;
          }
    condtion = asRegister(test_set,"smartphone");
            if (condtion!=AS_ITEM_ALREADY_EXISTS){
                 asDestroy(test_set);
              return false;
          }

    condtion = asRegister(test_set,"Headphones");
            if (condtion!=AS_ITEM_ALREADY_EXISTS){
                 asDestroy(test_set);
              return false;
          }

    asDestroy(test_set);//looking for leaked memorey in as destroy
    return true;
/*we will add a test for both asRemove and asRegister afte making each one works fine on their on*/      
}


static void createString(AmountSet set)
{
    asRegister(set,"apples");
    asRegister(set,"Apples");
    asRegister(set,"water");
    asRegister(set,"chargers");
    asRegister(set,"packbags");
    asRegister(set,"cases");
    asRegister(set,"tables");
    asRegister(set,"windows");
    asRegister(set,"computers");
    asRegister(set,"ABC's");
}


bool testasDelete()
{
    AmountSet test_set =asCreate();
           if(test_set==NULL){
             printf("failed to allocate a new empty amount set\n");
             return false;
          }

    createString(test_set);
    AmountSetResult condtion;

     condtion = asDelete(test_set,NULL);
          if (condtion!=AS_NULL_ARGUMENT){
               asDestroy(test_set);
              return false;
          }
          
    condtion = asDelete(NULL,"we passed a NULL");
             if (condtion!=AS_NULL_ARGUMENT){
                  asDestroy(test_set);
              return false;
          }

   /* AmountSet test_set1= asCreate();
    asDestroy(test_set1);

    condtion = asDelete(test_set1,"doesnt matter whats here");
            if (condtion!=AS_NULL_ARGUMENT){
                 asDestroy(test_set);
              return false;
          }*/
    
    condtion = asDelete(test_set,"apples");
            if (condtion!=AS_SUCCESS){
                 asDestroy(test_set);
              return false;
          }
    condtion = asDelete(test_set,"Apples");
            if (condtion!=AS_SUCCESS){
                 asDestroy(test_set);
              return false;
          }
    condtion = asDelete(test_set,"chargers");
            if (condtion!=AS_SUCCESS){
                 asDestroy(test_set);
              return false;
          }
    condtion = asDelete(test_set,"packbags");
            if (condtion!=AS_SUCCESS){
                 asDestroy(test_set);
              return false;
          }
    
    condtion = asDelete(test_set,"cases");
            if (condtion!=AS_SUCCESS){
                 asDestroy(test_set);
              return false;
          }
    condtion = asDelete(test_set,"tables");
            if (condtion!=AS_SUCCESS){
                 asDestroy(test_set);
              return false;
          }

    condtion = asDelete(test_set,"!");
            if (condtion!=AS_ITEM_DOES_NOT_EXIST){
                 asDestroy(test_set);
              return false;
          }

    condtion = asDelete(test_set,"@@$#$@$#$#$#");
            if (condtion!=AS_ITEM_DOES_NOT_EXIST){
                 asDestroy(test_set);
              return false;
          }
        
    condtion = asDelete(test_set,"254dv3##CD");
            if (condtion!=AS_ITEM_DOES_NOT_EXIST){
                 asDestroy(test_set);
              return false;
          }

    condtion = asDelete(test_set,"chairs");
            if (condtion!=AS_ITEM_DOES_NOT_EXIST){
                 asDestroy(test_set);
              return false;
          }
    condtion = asDelete(test_set,"smart tv");
            if (condtion!=AS_ITEM_DOES_NOT_EXIST){
                 asDestroy(test_set);
              return false;
          }
    condtion = asDelete(test_set,"smartphone");
            if (condtion!=AS_ITEM_DOES_NOT_EXIST){
                 asDestroy(test_set);
              return false;
          }
    condtion = asDelete(test_set,"Headphones");
            if (condtion!=AS_ITEM_DOES_NOT_EXIST){
                 asDestroy(test_set);
              return false;
          }
    condtion = asDelete(test_set,"i dont know");
            if (condtion!=AS_ITEM_DOES_NOT_EXIST){
                 asDestroy(test_set);
              return false;
          }

    condtion = asRegister(test_set,"i dont know");
            if (condtion!=AS_SUCCESS){
              printf("failed to register a new element into tothe set");
               asDestroy(test_set);
              return false;
          }

    condtion = asDelete(test_set,"i dont know");
            if (condtion!=AS_SUCCESS){
                 asDestroy(test_set);
              return false;
          }
    
    
    condtion = asDelete(test_set,"");
            if (condtion!=AS_ITEM_DOES_NOT_EXIST){
                 asDestroy(test_set);
              return false;
          }
    condtion = asDelete(test_set,"smartphone");
            if (condtion!=AS_ITEM_DOES_NOT_EXIST){
                 asDestroy(test_set);
              return false;
          }

    condtion = asDelete(test_set,"Headphones");
            if (condtion!=AS_ITEM_DOES_NOT_EXIST){
                 asDestroy(test_set);
              return false;
          }

    asDestroy(test_set);//looking for leaked memorey in as destroy
    return true;
}


void fillnames(char *names_arr[])
{
    names_arr[0]="apples";
    names_arr[1]="Apples";
    names_arr[2]="water";
    names_arr[3]="chargers";
    names_arr[4]="packbags";
    names_arr[5]="cases";
    names_arr[6]="tables";
    names_arr[7]="windows";
    names_arr[8]="computers";
    names_arr[9]="ABC's";
}


bool testAmountandSize()
{  
    double amount=0;
    AmountSet test_set=asCreate();
          if(test_set==NULL){
             printf("failed to allocate a new empty amount set\n");
             return false;
          }

        if (asGetSize(NULL)!=-1){
            asDestroy(test_set);
            return false;
        }

       /* AmountSet test_set1 = asCreate();
             if (test_set1==NULL){
             printf("failed to allocate a new empty amount set\n");
             asDestroy(test_set);
             return false;  
             }

        asDestroy(test_set1);

        if (asGetSize(test_set1)!=-1){
            asDestroy(test_set);
            return false;
        }*/

             
        if(asGetSize(test_set)!=0){
           asDestroy(test_set);
           return false; 
        }
         
    
    createString(test_set);//puts 10 new strings in the set
           if(asGetSize(test_set)!=10){
              asDestroy(test_set);
              return false;
            }
    char* names_arr[10];
    fillnames(names_arr);
          
          for (int i = 0; i < 10; i++){
            asGetAmount(test_set,names_arr[i],&amount); 
              if (amount!=0){
                asDestroy(test_set);
                return false;
              }
              
          }

    AmountSetResult condtion;
    
    for (int i = 0; i < 10; i++){
       double amount_change=5.55;
       asChangeAmount(test_set,names_arr[i],amount_change); 
       condtion= asGetAmount(test_set,names_arr[i],&amount);
         if(condtion!=AS_SUCCESS){
               asDestroy(test_set);
               return false;
         }

         if (amount!=amount_change){
             asDestroy(test_set);
             return false;
         }
            amount_change+=i;
    }

        
    for (int i = 0; i < 10; i++){    
       condtion = asChangeAmount(test_set,names_arr[i],-100000);
           if (condtion!=AS_INSUFFICIENT_AMOUNT){
                  asDestroy(test_set);
                  return false;          
            }

       double correct_amount=5.55;
       asGetAmount(test_set,names_arr[i],&amount);
          if (amount!=correct_amount){
              asDestroy(test_set);
              return false;
          }
         correct_amount+=i;


        asDelete(test_set,names_arr[i]);
          if (asGetAmount(test_set,names_arr[i],&amount)!=AS_ITEM_DOES_NOT_EXIST){
               asDestroy(test_set);
                    return false;
          }

          if (asGetSize(test_set)!=(10-i-1)){
              asDestroy(test_set);
               return false;
        }
    }

        
    for (int i = 0; i < 10; i++){
        condtion = asChangeAmount(test_set,names_arr[i],100000);
             if (condtion!=AS_ITEM_DOES_NOT_EXIST){
                       asDestroy(test_set);
                       return false;
             }
        
        if (asGetSize(test_set)!=0){
            asDestroy(test_set);
            return false;
        }
    }          
    asDestroy(test_set);
    return true;
}


bool testasContains()
{
    AmountSet test_set = asCreate();
           if(test_set==NULL){
              printf("failed to allocate a new empty set");
              return false;
           }

        char* names_arr[10];
        fillnames(names_arr);
            
            for (int i = 0; i < 10; i++){
              AmountSetResult condtion = asRegister(test_set,names_arr[i]);
                  if (condtion!=AS_SUCCESS){
                      printf("a problem with as register");
                      asDestroy(test_set);
                      return false;
                  } 
            }

                for (int i = 0; i < 10; i++){
                     if (asContains(test_set,names_arr[i])!=true){
                         asDestroy(test_set);
                         return false;
                     }

                    asDelete(test_set,names_arr[i]);

                    if (asContains(test_set,names_arr[i])!=false){
                         asDestroy(test_set);
                         return false;
                     }
                }



            for (int i = 0; i < 10; i++){
              AmountSetResult condtion = asRegister(test_set,names_arr[i]);
                  if (condtion!=AS_SUCCESS){
                      printf("a problem with as register");
                      asDestroy(test_set);
                      return false;
                  } 
            }

/*not needed extra tests*/
            if (asContains(test_set,"Appels")!=false){// not apples
               asDestroy(test_set);
               return false;
            }

            if (asContains(test_set,"Apples")!=true){
               asDestroy(test_set);
               return false;
            }
            
    asDestroy(test_set);
    return true;
}



bool testasCopy()
{
  AmountSet test_set=asCreate();
     if (test_set==NULL){
        printf("failed to allocate new empty set");
        return false;
    }

    char* names_arr[10];
    fillnames(names_arr);
    createString(test_set);

   
           AmountSet copy_test_set = asCopy(test_set);
                    if (copy_test_set==NULL){
                        printf("failed to allocate a copy set");
                        asDestroy(test_set);
                        return false;
                    }
                    
    /*here e check manually that every sing string have been copied with the amount */
           if (asGetSize(copy_test_set)!=10){
                asDestroy(test_set);
                return false;
            }
     
         for(int i=0;i<10;i++){
            if (asContains(copy_test_set,names_arr[i])!=true){
                 asDestroy(test_set);
                 asDestroy(copy_test_set);
                 return false;
            }
                 
         }


           for(int i=0;i<10;i++){
            double org_amount=0,cp_amount=0;
            asGetAmount(test_set,names_arr[i],&org_amount);
            asGetAmount(copy_test_set,names_arr[i],&cp_amount);
                      
                      if (org_amount!=cp_amount){
                          asDestroy(copy_test_set);
                          asDestroy(test_set);
                          return false;
                      }
           }
/*at this point these amount sets are equal,our work here is done*/
      asDestroy(copy_test_set);
      asDestroy(test_set);
      return true;                

}


static void fillnamesInOrder(char* names_arr[])
{

    names_arr[2]="apples";
    names_arr[1]="Apples";
    names_arr[8]="water";
    names_arr[4]="chargers";
    names_arr[6]="packbags";
    names_arr[3]="cases";
    names_arr[7]="tables";
    names_arr[9]="windows";
    names_arr[5]="computers";
    names_arr[0]="ABC's";
}
  






bool testIterator()
{
    AmountSet test_set = asCreate();
              if (test_set==NULL){
                  printf("failed to allocate a new emoty set");
                  return false;
              }
    char* names_arr[10];
    fillnamesInOrder(names_arr);
    createString(test_set);
    int i=0;
        
       AS_FOREACH(char*,Iterator,test_set){
           if (strcmp(Iterator,names_arr[i])!=0){
               asDestroy(test_set);
               return false;
           }
           i++;   
       }
      
      i=0;
        AS_FOREACH(char*,Iterator,test_set){
            double amount=0;
            asGetAmount(test_set,names_arr[i],&amount);
            asChangeAmount(test_set,names_arr[i],0);
            if(asGetSize(test_set)!=10){
                printf("somthing is very wrong");
                asDestroy(test_set);
                return false;
            }
            if (asContains(test_set,names_arr[i])!=true){
                printf("somthing is very wrong");
                asDestroy(test_set);
                return false;
            }
            
           if (strcmp(Iterator,names_arr[i])!=0){
               asDestroy(test_set);
               return false;
           }
           i++;   
       }

    /*no way to check if an undefined state of the iterator is acutally NULL*/
    asDestroy(test_set);
    return true;
}

bool testasClear()
{
    AmountSet test_set = asCreate();
       if (test_set==NULL){
           printf("failed to allocate a new empty set");
           return false;
       }

       char* names_arr[10];
       fillnames(names_arr);
       createString(test_set);
        AmountSetResult condtion = asClear(NULL);
               if (condtion!=AS_NULL_ARGUMENT){
                  asDestroy(test_set);
                  return false;
               }
               

         asClear(test_set);
         if (asGetSize(test_set)!=0){
             asDestroy(test_set);
             return false;
         }
         
       asDestroy(test_set);
       return true;
}













