#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int num_of_aisles = 5 ;

typedef struct item_tag
{
    int aisle_num ;
    int item_id ;
    int quantity ;
    int expiry_date;
    int threshold ;
    struct item_tag * next_item;
    char item_name[50] ;

}item_node ;

typedef struct aisle_tag
{

    int aisle_number ;
    struct aisle_tag* next_aisle;
    item_node * item_list ; 
    char aisle_name[50] ;

} aisle_node ;


typedef struct bill_tag
{
    int bill_number ;
    int aisle_num ;
    int item_id ;
    int qty;   
    struct bill_tag* next_bill;

}bill_node;

void search_and_insert(item_node* new,aisle_node* lptr)
{
    
    aisle_node* nptr;
    item_node* temp,* item_nptr;
    nptr = lptr;

    while((nptr->aisle_number != new->aisle_num) && (nptr != NULL))
    {
        nptr = nptr->next_aisle ;
    }
    item_nptr = nptr->item_list ;
    if(item_nptr == NULL)
    {
        
        nptr->item_list = new;
        new->next_item = NULL;
    }
    else if(item_nptr->next_item == NULL)
    {
        if(item_nptr->item_id < new->item_id)
        {
            
            item_nptr->next_item = new ;
        }
        else
        {
            new->next_item = item_nptr;
            nptr->item_list = new ;
        }
    }
    else
    {
        while((item_nptr->next_item != NULL) && (item_nptr->next_item->item_id < new->item_id) )
        {
          item_nptr = item_nptr->next_item ;
        }
        if(item_nptr->next_item != NULL)
        {
            
            temp = item_nptr->next_item;
            item_nptr->next_item = new ;
            new->next_item = temp ;
        }
        else
        {
            item_nptr->next_item= new ;

        }
    }

}

void update_item(aisle_node* lptr )
{
    int id,aisle_num;
    aisle_node* nptr;
    item_node* temp,* item_nptr;
    printf("enter item id :");
    scanf("%d",&id);
    printf("enter aisle number :");
    scanf("%d",&aisle_num);
   
    nptr = lptr;

    while(nptr->aisle_number != aisle_num)
    {
        nptr = nptr->next_aisle ;
    }
    item_nptr = nptr->item_list ;

    while(item_nptr->item_id != id)
    {
        item_nptr = item_nptr->next_item;
    }
    printf("enter the item name :");
    scanf("%s",item_nptr->item_name);
    printf("enter the threshold:");
    scanf("%d",&item_nptr->threshold);
    printf("enter the expiry date:");
    scanf("%d",&item_nptr->expiry_date);
    printf("enter the quantity:");
    scanf("%d",&item_nptr->quantity);
}

void add_item(aisle_node* lptr)
{
    int num,var;
    item_node* new;
    new =(item_node *) malloc(sizeof(item_node));
    printf("enter the aisle number :");
    scanf("%d",&new->aisle_num);
    printf("enter the item name :");
    scanf("%s",new->item_name);
    printf("enter the item_id:");
    scanf("%d",&new->item_id );
    printf("enter the threshold:");
    scanf("%d",&new->threshold);
    printf("enter the expiry date:");
    scanf("%d",&new->expiry_date);
    printf("enter the quantity:");
    scanf("%d",&new->quantity);
    search_and_insert(new,lptr);  
}

void delect_item(aisle_node* lptr)
{
    int aisle_num,id;
    aisle_node* nptr;
    item_node* temp,* item_nptr;
    printf("enter aisle_number :");
    scanf("%d",&aisle_num);
    printf("enter item id:");
    scanf("%d",&id);
    nptr = lptr;

    while(nptr->aisle_number != aisle_num)
    {
        nptr = nptr->next_aisle ;
    }
    item_nptr = nptr->item_list ;

    while(item_nptr->next_item->item_id != id)
    {
        item_nptr = item_nptr->next_item;
    }
    temp = item_nptr->next_item ;
    item_nptr->next_item = temp->next_item;
    free(temp);
}

void add_aisle(aisle_node* lptr)
{
    int i,flag=0;
    item_node* item_nptr ;
    aisle_node* new ,* nptr,*temp;
    new = (aisle_node*)malloc(sizeof(aisle_node));
    printf("enter the aisle number :");
    scanf("%d",&new->aisle_number);
    printf("enter the aisle name :");
    scanf("%s",new->aisle_name);
    new->aisle_number-- ;
    nptr = lptr ;
    
    for(i=1;i< new->aisle_number;i++)
    {
        nptr = nptr->next_aisle ;
    }
    num_of_aisles ++;
    temp = nptr ->next_aisle ;
    nptr->next_aisle = new ;
    new->next_aisle = temp ;
    new->item_list = NULL;
    do
    {
        printf("enter 1 to add a item in the list or enter key to exist:");
        scanf("%d",&flag);
        if(flag == 1)
        {
            add_item(lptr);
        }
    }
    while(flag == 1) ;
    for(i=new->aisle_number;i<num_of_aisles;i++)
    {
        nptr = nptr->next_aisle ;
        nptr->aisle_number ++ ;
        item_nptr = nptr->item_list;
        while(item_nptr != NULL)
        {
            item_nptr->aisle_num ++;
            item_nptr = item_nptr->next_item ;
        }
 }


}

void update_aisle(aisle_node * lptr)
{
    int i,aisle_num,opt;
    aisle_node* nptr;
    item_node* item_nptr ;
    nptr = lptr ;
    printf("enter the aisle number to be updated :");
    scanf("%d",&aisle_num);

    for(i=1;i< aisle_num;i++)
    {
        nptr = nptr->next_aisle ;
    }

    printf("enter 1 to update name :");
    printf("enter 2 to add item :");
    printf("enter 3 to update item :");
    scanf("%d",&opt);
    if(opt == 1)
    {
        printf("enter new aisle name :");
        scanf("%s",nptr->aisle_name);
    }
    else if(opt == 2)
    {
        add_item(lptr);
    }
    else
    {
        update_item(lptr);
    }

}

void free_items(item_node* nptr)
{
    item_node * temp;
    while(nptr != NULL)
    {
        temp = nptr ;
        nptr = nptr->next_item ;
        free(temp);
    }
}

void free_aisles(aisle_node * lptr)
{
    aisle_node* temp;
    while(lptr != NULL)
    {
        temp = lptr ;
        free_items(temp->item_list);
        lptr = lptr->next_aisle;
        free(temp);
    }
}

aisle_node* delete_aisle(aisle_node* lptr) 
{
    int a_num;
    aisle_node* nptr,*temp ;
    printf("aisle number to delected \n");
    scanf("%d",&a_num);
    if(lptr->aisle_number == a_num)
    {
        free_items(lptr->item_list);
        temp = lptr ;
        lptr = lptr->next_aisle ;
        free(temp);
    }
    else
    {
        nptr = lptr ;
        while((nptr->next_aisle->aisle_number != a_num) && (nptr->next_aisle != NULL))
        {
            nptr = nptr->next_aisle;
        }
        if(nptr->next_aisle == NULL)
        {
            printf("given aisle is not found");
        }
        else
        {
            temp = nptr->next_aisle ;
            free_items(temp->item_list) ;
            nptr->next_aisle = temp->next_aisle;
            free(temp);
        }
    }
}

item_node *merging(item_node *lptr1, item_node *lptr2)
{
    item_node *ptr1, *ptr2, *result, *tail;
    if (lptr1 == NULL)
    {
        result = lptr2;
    }
    else if (lptr2 == NULL)
    {
        result = lptr1;
    }
    else
    {
        ptr1 = lptr1;
        ptr2 = lptr2;
        if (lptr1->item_id < lptr2->item_id)
        {
            result = lptr1;
            ptr1 = ptr1->next_item;
        }
        else
        {
            result = lptr2;
            ptr2 = ptr2->next_item;
        }
        tail = result;
        while (ptr1 != NULL && ptr2 != NULL)
        {
            if (ptr1->item_id < ptr2->item_id)
            {
                tail->next_item = ptr1;
                tail = tail->next_item;
                ptr1 = ptr1->next_item;
            }
            else
            {
                tail->next_item = ptr2;
                tail = tail->next_item;
                ptr2 = ptr2->next_item;
            }
        }
        if (ptr1 != NULL)
        {
            tail->next_item = ptr1;
        }
        else
        {
            tail->next_item= ptr2;
        }
    }
    return result;
}




void merge_aisle(aisle_node * lptr)
{
    int t,n1,n2;
    aisle_node* nptr1 , *nptr2,* temp_aisle;
    item_node* item_nptr,* temp;
    printf("enter the aisle number of two to be merged : \n");
    scanf("%d%d",&n1,&n2);
    if(n1 == n2)
    {
        printf("enter two diffrent aisle numbers \n");
    }
    else

    {
        if(n1 > n2)
        {
            t = n1;
            n1= n2;
            n2= t;
        }
        nptr1= nptr2 = lptr ;

        

        while( (nptr1->aisle_number != n1) && (nptr1 != NULL) )
        {
            
            nptr1 = nptr1->next_aisle;
        }

        while(nptr2->next_aisle->aisle_number != n2)
        {
            
            nptr2 = nptr2->next_aisle;
        }
        strcat(nptr1->aisle_name," and ");
        strcat(nptr1->aisle_name,nptr2->next_aisle->aisle_name);

        nptr1->item_list = merging(nptr1->item_list,nptr2->next_aisle->item_list);

        temp_aisle = nptr2->next_aisle ;
        nptr2->next_aisle = temp_aisle->next_aisle;
        free(temp);
        
        
    }

}


aisle_node*  save_aisle_data(aisle_node* lptr)
{
    aisle_node * dummy,*nptr,*retval;
    FILE * fptr;
   
    fptr= fopen("aisle_data.txt","r");
    dummy = (aisle_node*)malloc(sizeof(aisle_node));
    retval = dummy;
    while(!feof(fptr))
    {
        
        nptr = (aisle_node*)malloc(sizeof(aisle_node));
        fscanf(fptr,"%d,%s",&nptr->aisle_number,nptr->aisle_name);
        dummy->next_aisle = nptr ;
        nptr->next_aisle = NULL;
        nptr->item_list = NULL;
        dummy = nptr;
    }
    dummy->next_aisle= NULL;
    nptr = retval;
    retval =retval->next_aisle;
    free(nptr);
    fclose(fptr);
    return retval;
}

void save_item_data(aisle_node* lptr)
{
    item_node* new;
    FILE * fptr;
    fptr = fopen("store_data.txt","r");
    while(!feof(fptr))
    {
        new = (item_node*)malloc(sizeof(item_node));
        fscanf(fptr,"%d",&new->aisle_num);
        fscanf(fptr,"%d",&new->item_id);
        fscanf(fptr,"%s",new->item_name);
        fscanf(fptr,"%d",&new->threshold);
        fscanf(fptr,"%d",&new->expiry_date);
        fscanf(fptr,"%d",&new->quantity);
        new->next_item = NULL;
        search_and_insert(new,lptr);
    }
    fclose(fptr);
}

item_node* search(int id, int a_num,aisle_node* lptr)
{
    aisle_node* nptr;
    item_node* retval,* item_nptr;
    nptr = lptr;

    while((nptr->aisle_number != a_num) && (nptr != NULL))
    {
        nptr = nptr->next_aisle ;
    }
    if(nptr == NULL)
    {
        retval = NULL;
    }
   else
   {
      item_nptr = nptr->item_list ;
      while((item_nptr->item_id != id) && (item_nptr != NULL))
       {
          item_nptr = item_nptr->next_item ;
       } 
       retval = item_nptr;
   }

    return retval;

}


void check_availbility(int id,int qty,int exp,aisle_node* lptr)
{
    int i=1;
    item_node* nptr ;
   do
   {
      nptr = search(id,i,lptr);       // assumption only exiting items are searched
      i++;
   } while (nptr == NULL);
   if( (nptr->quantity > qty) && ( nptr->expiry_date > exp) )
   {
      printf("%d qty of %d are avialible before %d \n",qty,id,exp);
   }
   else
   {
      printf("%d qty of %d are  not avialible before %d \n",qty,id,exp);
   }
   
}


void check_dairy(int date,aisle_node* lptr)
{
    aisle_node *nptr = lptr;
    item_node *item_nptr ;
    int exp_year,exp_day,exp_mon,year,day,mon,num_days,total_days,flag =0;
    while(strcmp(nptr->aisle_name,"dairy") != 0)
    {
        nptr = nptr->next_aisle ;
    }
    item_nptr = nptr->item_list;
    year = date /10000 ;
    mon = (date %1000) /100 ;
    day =  date %100 ;
    num_days = year*360 + mon*30 + day ;

    while(item_nptr!= NULL)
    {
        exp_year = item_nptr->expiry_date / 10000;
        exp_mon= (item_nptr->expiry_date % 1000) / 100;
        exp_day = item_nptr->expiry_date % 100;
        total_days = exp_year*360 + exp_mon*30 + exp_day ;
        if(num_days   == total_days  +1)
        {
            printf("%s expires tommorow \n",item_nptr->item_name);
            flag =1 ;
        }
       item_nptr = item_nptr->next_item ;
    }

    if(flag == 0)
    {
        printf("no dairy product expries by tommorow \n");
    }

}

void check_ready_to_eat(int date,aisle_node* lptr)
{
    aisle_node *nptr = lptr;
    item_node *item_nptr ;
    int exp_year,exp_day,exp_mon,year,day,mon,num_days,total_days,n,flag =0;
    while(strcmp(nptr->aisle_name,"ready_to_eat") != 0)
    {
        nptr = nptr->next_aisle ;
    }
    item_nptr = nptr->item_list;
    year = date /10000 ;
    mon = (date %1000) /100 ;
    day =  date %100 ;
    num_days = year*360+ mon*30 + day ;
    
    while(item_nptr!= NULL)
    {
        exp_year = item_nptr->expiry_date / 10000;
        exp_mon= (item_nptr->expiry_date % 1000) / 100;
        exp_day = item_nptr->expiry_date % 100;
        total_days = exp_year*360 + exp_mon*30 + exp_day ;
        n = total_days - num_days ;
        if( n < 7 && n > 0 )
        {
            printf("%s expires in %d days \n",item_nptr->item_name,total_days - num_days);
            flag =1 ;
        }
         if( n < 0 )
        {
            printf("%s expired  %d days ago \n",item_nptr->item_name,-1*n);
            
        }
       item_nptr = item_nptr->next_item ;
    }

    if(flag == 0)
    {
        printf("no ready_to_eat product expries by tommorow \n");
    }
}

void check_for_threshold(aisle_node* lptr)
{
    aisle_node* nptr;
    item_node* item_nptr ;
    nptr = lptr;
    while(nptr != NULL)
    {
        item_nptr = nptr->item_list ;
        while(item_nptr != NULL)
        {
            if(item_nptr->threshold > item_nptr->quantity)
            {
                printf("%s reached its threshold limit \n",item_nptr->item_name);
            }
            item_nptr = item_nptr->next_item ;
        }
        nptr = nptr ->next_aisle ;
    }


}

bill_node* save_bills_data()
{
    bill_node* new,*prev,*retval;
    prev = (bill_node*)malloc(sizeof(bill_node));
    retval = prev ;
    FILE* fptr ;
    fptr = fopen("bills_data.txt","r");
    while(!feof(fptr))
    {
       
        new =(bill_node*)malloc(sizeof(bill_node));
        fscanf(fptr,"%d,%d,%d,%d",&new->bill_number,&new->aisle_num,&new->item_id,&new->qty);
        prev->next_bill = new ;
        new->next_bill = NULL;
        prev = new; 
    }
    prev = retval;
    retval = retval ->next_bill ;
    free(prev);
    return retval;
}

void billing(bill_node* bptr,aisle_node* lptr)
{
    int i=1;
    bill_node* nptr;
    item_node* item_nptr ;
    nptr = bptr ;
    while(nptr != NULL )
    {
        item_nptr = search(nptr->item_id,nptr->aisle_num,lptr) ;
        item_nptr->quantity = item_nptr->quantity - nptr->qty ;
        nptr = nptr->next_bill ;  
        check_for_threshold(lptr); 
    }
}

item_node* foo(int id,bill_node* mark,bill_node*bptr,item_node* lptr)
{
    
    int flag = 0 ;
    item_node* new,* prev,*nptr;
    int bill;
    bill = mark->bill_number;
    
    if(lptr == NULL)
    {
        
        new = (item_node*)malloc(sizeof(item_node));
        if(mark->item_id != id)
        new->item_id = mark->item_id;
        else
        new->item_id = mark->next_bill->item_id;
        mark = mark->next_bill ;
        new->next_item = NULL;
        lptr =new;
        mark = mark->next_bill ;
        
    }
    while(mark->bill_number == bill)
    {
       
        prev = nptr = lptr; 
        
        while(nptr != NULL && flag == 0 )
        {
            
            if(nptr->item_id == mark->item_id)
            {
                
                nptr->quantity += mark->qty ;
                nptr = nptr->next_item ;
                flag = 1;
            }
            prev = nptr;
            nptr = nptr->next_item;
        }
        if(nptr == NULL)
        {
            new = (item_node*)malloc(sizeof(item_node));
            if(mark->item_id != id)
            new->item_id = mark->item_id;
            else
            mark = mark->next_bill;
            new->item_id = mark->item_id;
            new->quantity = mark->qty;
            prev->next_item = new ;
            new->next_item = NULL ;
        }

        mark = mark->next_bill;   
    }
    return lptr;
}

void free_bills(bill_node* bptr)
{
    bill_node* temp;
    while(bptr != NULL)
    {
        temp = bptr;
        bptr = bptr->next_bill ;
        free(temp);

    }
}

void most_frequntly_bought(int id,bill_node* bptr)
{
    bill_node* mark,*nptr;
    item_node* lptr,* item_nptr,* ans;
    lptr = NULL ;
    mark = nptr = bptr ;
    while(nptr != NULL)
    {
        
        
        if(mark->bill_number != nptr->bill_number)
        {
            
            mark = nptr ;
        }
        if(nptr->item_id == id)
        {
           lptr = foo(id,mark,bptr,lptr);
        }

        nptr = nptr->next_bill;

    }
    item_nptr =  ans = lptr;
    while( item_nptr != NULL)
    {
       
        if(ans->quantity < item_nptr->quantity)
        {
            ans = item_nptr;
        }
        item_nptr = item_nptr->next_item;

    }

    printf("%d is the product purshed more often with %d",ans->item_id,id);

}

void ask_user(aisle_node* lptr,bill_node* bptr)
{
    int opt,var ;
    int id,qty,exp;

    do
    {
    printf("----------------------------------------------------------------------");
    printf("enter 1  to add item : \n");
    printf("enter 2  to update item : \n");
    printf("enter 3  to add aisle : \n");
    printf("enter 4  to update aisle : \n");
    printf("enter 5  to delect item : \n");
    printf("enter 6  to merge aisle : \n");
    printf("enter 7  to delect aisle : \n");
    printf("enter 8  to check dairy  expiry : \n");
    printf("enter 9  to check ready to eat foods expiray : \n");
    printf("enter 10 to threshold : \n");
    printf("enter 11 to check availibility : \n");
    printf("enter 12 to check most frequnlty bought : \n");
    printf("---------------------------------------------------------------------- \n");
    printf("enter option ");
    scanf("%d",&opt); 
    switch (opt)
    {
    case 1:
        add_item(lptr) ;
        break;
    case 2:
        update_item(lptr);
        break ;
    case 3:
        add_aisle(lptr);
        break ;
    case 4:
        update_aisle(lptr);
        break ;
    case 5:
         delect_item(lptr);
         break ;
    case 6:
        merge_aisle(lptr);
        break ;
    case 7:
        lptr =delete_aisle(lptr);
         break ;
    case 8:
        printf("enter to date in yymmdd format :");
        scanf("%d",&var);
        check_dairy(var,lptr);
        break ;
    case 9:
        printf("enter to date in yymmdd format :");
        scanf("%d",&var);
        check_ready_to_eat(var,lptr);

    case 10:
        check_for_threshold(lptr);
        break ;
    case 11:
        printf("enter id quantity and expiry date :");
        scanf("%d%d%d",&id,&qty,&exp);
        check_availbility(id,qty,exp,lptr);
        break ;
    case 12:
          printf("enter id to be checked :");
          scanf("%d",&var);
          most_frequntly_bought(var,bptr);
          break ;    
    default:
        break;
    }
    } while (opt >= 1 && opt <= 12);
    
}

void update_aisle_data(aisle_node* lptr)
{
    aisle_node* nptr;
    nptr = lptr ;
    FILE * fptr = fopen("u_aisle.txt","w");
    while(nptr != NULL)
    {
        fprintf(fptr,"%d,",nptr->aisle_number);
        fprintf(fptr,"%s\n",nptr->aisle_name);
        nptr= nptr->next_aisle;
    }
}

void update_item_data(aisle_node* lptr)
{
    FILE* fptr = fopen("u_store_data.txt","w");
    aisle_node* nptr;
    item_node* item_nptr;
    nptr = lptr;
    while(nptr!= NULL)
    {
        item_nptr = nptr->item_list;
        while(item_nptr !=NULL)
        {
            fprintf(fptr,"%d,%d,%s,%d,%d,%d\n",item_nptr->aisle_num,item_nptr->item_id,item_nptr->item_name,item_nptr->threshold,item_nptr->expiry_date,item_nptr->quantity);
            item_nptr = item_nptr->next_item;
        }
        nptr = nptr->next_aisle;

    }
}




int main()
{
    int i=0;
    aisle_node* lptr,*temp;
    item_node* nptr;
    lptr = save_aisle_data(lptr);
    save_item_data(lptr);
    bill_node* bptr;
    bptr = save_bills_data();
    ask_user(lptr,bptr);
    update_aisle_data(lptr);
    update_item_data(lptr);
    free_aisles(lptr);
    free_bills(bptr);

    return 0;

}