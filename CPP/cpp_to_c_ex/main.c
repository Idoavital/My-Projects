
#include <stdio.h>
#include <stdlib.h>

enum
{
    DTOR,
    DISPLAY	
};	

typedef void (*VFUNC)(void * );
static int s_count = 0;

/**************************************************************/
/************** class Public_Transport ************************/

/************** struct body *******************************/
typedef struct 
{
    VFUNC *vtable_pt;
   int m_license_plate;

}Public_Transport;

/**************class functions******************************/
void pt_Ctor (Public_Transport* this);
void pt_Dtor (Public_Transport* this); /* virtual */
void pt_Copy_Ctor (Public_Transport* this ,const Public_Transport* other);    
void pt_Display(Public_Transport* this); /* virtual */
int GetID(Public_Transport* this); /* protected */

/************** virtual table  ******************************/

 VFUNC vtable_pt[] = {
             (VFUNC) pt_Dtor,
             (VFUNC) pt_Display
    
};
/************************************************************/
/************** class Public Minibus ************************/
typedef struct
{
  Public_Transport m_pt;  /*derived class*/
  int m_numSeats;
}Minibus;

/**************class functions*******************************/
void mini_Ctor (Minibus* this);
void mini_Dtor (Minibus* this); /* virtual */
void mini_Copy_Ctor (Minibus* this ,const Minibus* other);
void mini_Display(Minibus* this); /* virtual */
void Wash(Minibus* this); /* virtual */

/************** virtual table  ******************************/
VFUNC vtable_mini[] = {
             (VFUNC) mini_Dtor,
             (VFUNC) mini_Display,
             (VFUNC) Wash

};
/************************************************************/
/************** class Public Taxi **************************/
typedef struct
{
  Public_Transport m_pt;  /*derived class*/
}Taxi;
/**************class functions*******************************/
void taxi_Ctor (Taxi* this);
void taxi_Dtor (Taxi* this); /* virtual */
void taxi_Copy_Ctor (Taxi* this ,const Taxi* other);
void taxi_Display(); /* virtual */

/************** virtual table  ******************************/

VFUNC vtable_taxi[] = {
             (VFUNC) taxi_Dtor,
             (VFUNC) taxi_Display,             
};
/*****************************************************************/
/************** class Public Special_Taxi ************************/
typedef struct
{
    Taxi m_t1 ; /*derived class*/
}Special_Taxi;

/**************class functions*******************************/
void sp_Ctor (Special_Taxi* this);
void sp_Dtor (Special_Taxi* this); /* virtual */
void sp_Copy_Ctor (Special_Taxi* this ,const Special_Taxi* other);
void sp_taxi_Display(); /* virtual */
/************** virtual table  ******************************/
VFUNC vtable_sp[] = {
             (VFUNC) sp_Dtor,
             (VFUNC) sp_taxi_Display,             
};

/******************************************************************/
/************** class Public Public_Convoy ************************/
typedef struct
{
  Public_Transport m_pt; /*derived class*/
  
  Public_Transport *m_pt1;
  Public_Transport *m_pt2;
  Minibus m_m;
  Taxi m_t;
}Public_Convoy;
/****************class functions*******************************/

void pc_Ctor (Public_Convoy* this);
void pc_Dtor (Public_Convoy* this); /* virtual */
void pc_Copy_Ctor (Public_Convoy* this ,const Public_Convoy* other);
void pc_Display(Public_Convoy* this); /* virtual */
/**************** virtual table  ******************************/
VFUNC vtable_pc[] = {
             (VFUNC) pc_Dtor,
             (VFUNC) pc_Display,             
};

/*****************global functions**********************/
static void PrintCount()
{ 
   printf( "s_count: %d\n",s_count );
}	
void PrintInfo() /*overload*/
{
    PrintCount();
}
void PrintInfo_1(Public_Transport *a) /*overload*/
{
    a->vtable_pt[1](a);
}
Public_Transport* PrintInfo_2(Public_Transport* pt_ret , int i) /*overload*/
{
    	Minibus ret;
        
        
        mini_Ctor(&ret);
        printf("PrintInfo(int i) \n");
	ret.m_pt.vtable_pt[1](&ret);
        
        pt_Copy_Ctor(pt_ret ,(Public_Transport*) &ret);
        
        mini_Dtor(&ret);
	return pt_ret;
}

void TaxiDisplay(Taxi s) 
{
    /* */
    s.m_pt.vtable_pt[1](&s);
    taxi_Dtor(&s);
    
}

/*template<class T>                           ?????????
inline T maxFunc(const T &t1, const T &t2)
{
	return ((t1 > t2)? t1: t2);
}
*/

/*****************************************************************/

/**************class  Public_Transport functions definition**********************/
void pt_Ctor (Public_Transport* this)
{
    this->vtable_pt = vtable_pt;
    this->m_license_plate = ++s_count;
    printf("Public_Transport::Ctor()%d\n",  this->m_license_plate);
}
void pt_Dtor (Public_Transport* this) /* virtual */
{
    --s_count;
    printf("Public_Transport::Dtor()%d\n",  this->m_license_plate);
   
}
void pt_Copy_Ctor (Public_Transport* this ,const Public_Transport* other)
{
    
    this->vtable_pt = vtable_pt;
    this->m_license_plate = ++s_count;
    printf("Public_Transport::CCtor() %d\n", this->m_license_plate);
}
void pt_Display(Public_Transport* this) /* virtual */
{
     printf("Public_Transport::Display(): %d\n",  this->m_license_plate);
} 
int GetID(Public_Transport* this) /* protected */
{
    return this->m_license_plate;
}

/**************class  Minibus functions definition**********************/

void mini_Ctor (Minibus* this)
{
    pt_Ctor(&this->m_pt);
    this->m_pt.vtable_pt = vtable_mini;
    this->m_numSeats=20;
    printf("Minibus::Ctor()\n");
}

void mini_Dtor (Minibus* this) /* virtual */
{
     printf("Minibus::dtor()\n");
     pt_Dtor(&this->m_pt);
    
} 
void mini_Copy_Ctor (Minibus* this ,const Minibus* other)
{
    
    pt_Copy_Ctor(&this->m_pt, &other->m_pt);
    this->m_pt.vtable_pt = vtable_mini;
    this->m_numSeats = other->m_numSeats;
  
    printf("Minibus::CCtor() \n");
}
void mini_Display(Minibus* this) /* virtual */
{
    printf ("Minibus::Display() ID:%d " , GetID(&this->m_pt) );
    printf ("num seats:%d\n", this->m_numSeats ); 
}

void Wash(Minibus* this) /* virtual */
{
      printf ("Minibus::Wash() ID: %d \n" , GetID(&this->m_pt) );
}

/**************class  Taxi functions definition**********************/

void taxi_Ctor (Taxi* this)
{
    pt_Ctor(&this->m_pt);
    this->m_pt.vtable_pt = vtable_taxi;
    printf("Taxi::Ctor()\n");
}
void taxi_Dtor (Taxi* this) /* virtual */
{
   printf("Taxi::dtor()\n");
   pt_Dtor(&this->m_pt);
 
}
void taxi_Copy_Ctor (Taxi* this ,const Taxi* other)
{
    
    pt_Copy_Ctor(&this->m_pt, &other->m_pt);
    this->m_pt.vtable_pt = vtable_taxi;
    printf("Taxi::CCtor()\n");
}
void taxi_Display(Taxi* this) /* virtual */
{
       printf ("Taxi::Display() ID:%d\n" , GetID(&this->m_pt) );
}

/**************class  Special_Taxi functions definition**********************/
void sp_Ctor (Special_Taxi* this)
{
    taxi_Ctor(&this->m_t1);
    this->m_t1.m_pt.vtable_pt = vtable_sp;
    printf("Special_Taxi::Ctor()\n");
}

void sp_Dtor (Special_Taxi* this) /* virtual */
{
    printf("Special_Taxi::Dtor() \n");
    taxi_Dtor(&this->m_t1);
}
void sp_Copy_Ctor (Special_Taxi* this ,const Special_Taxi* other)
{
    this->m_t1.m_pt.vtable_pt = vtable_sp;
    printf("Taxi::CCtor() \n");
}
void sp_taxi_Display(Special_Taxi* this) /* virtual */
{
     printf ("Special_Taxi::Display() ID:%d\n" , GetID(&this->m_t1.m_pt) );
}

/**************class  Public_Convoy functions definition**********************/

void pc_Ctor (Public_Convoy* this)
{
    pt_Ctor(&this->m_pt);
    this->m_pt.vtable_pt = vtable_pc;
    
    this->m_pt1 = malloc(sizeof(Minibus));
    mini_Ctor((Minibus*)this->m_pt1);
    this->m_pt2 = malloc(sizeof(Taxi));
    taxi_Ctor((Taxi*)this->m_pt2);
    
    mini_Ctor(&this->m_m);
    taxi_Ctor(&this->m_t);
   
}
void pc_Dtor (Public_Convoy* this) /* virtual */
{
    
    this->m_pt1->vtable_pt[DTOR](this->m_pt1);
    free(this->m_pt1);
    this->m_pt2->vtable_pt[DTOR](this->m_pt2);
    free(this->m_pt2);
    taxi_Dtor(&this->m_t);
    mini_Dtor(&this->m_m);
    

    pt_Dtor(&this->m_pt);
    
}
void pc_Copy_Ctor (Public_Convoy* this ,const Public_Convoy* other)
{
    pt_Copy_Ctor((Public_Transport*)this, (Public_Transport*)other);
    this->m_pt.vtable_pt = vtable_pc;
    /* m_pt1(new Minibus (static_cast <Minibus&> (*other.m_pt1))), */
    this->m_pt1 = malloc( sizeof(Minibus)); 
    mini_Copy_Ctor((Minibus*)this->m_pt1 , (Minibus*)other->m_pt1);

    /*m_pt2(new Taxi (static_cast <Taxi&> (*other.m_pt2))), */
    this->m_pt2 = malloc(sizeof(Taxi)); 
    taxi_Copy_Ctor((Taxi*)this->m_pt2 , (Taxi*)other->m_pt2);
    
    
    mini_Copy_Ctor(&this->m_m , &other->m_m);
    taxi_Copy_Ctor(&this->m_t ,&other->m_t);

}
void pc_Display(Public_Convoy* this ) /* virtual */
{
    this->m_pt1->vtable_pt[DISPLAY]((Minibus*) this->m_pt1);
    this->m_pt2->vtable_pt[DISPLAY]( (Taxi*)this->m_pt2);
    
    mini_Display( &this->m_m);
    taxi_Display( &this->m_t);
    
}

/*************************** MAIN ************************************************/

int main(int argc, char *argv[])
{
 	Minibus m;
        Minibus m2;             /**/
        Public_Transport temp ;
        Public_Transport *array[3];
        int i = 0;
        Public_Transport arr2[3];
        Minibus arr3[4];
        Taxi *arr4[4];
        Special_Taxi st;   /**/
        Taxi taxi_tamp;
        Public_Convoy *ts1;
        Public_Convoy *ts2;
        /*Public_Convoy  pc_temp;*/
        
        mini_Ctor(&m);
	PrintInfo_1((Public_Transport*)&m);
  
	/*PrintInfo_2(3);.Display();*/ 
        PrintInfo_2(&temp , 3);
        temp.vtable_pt[1](&temp);
        pt_Dtor(&temp);
        
        /*
        Public_Transport *array[] = 
	{
		new Minibus(),
		new Taxi(),
		new Minibus()
	};
        */
       
        array[0] = malloc (sizeof(Minibus));
        mini_Ctor((Minibus*)array[0]);
        array[1] = malloc (sizeof(Taxi));
        taxi_Ctor((Taxi*)array[1]);
        array[2] = malloc (sizeof(Minibus));
        mini_Ctor((Minibus*)array[2]);
        
        /*for(int i = 0; i < 3; ++i) array[i]->Display();*/
        for( i = 0; i < 3; ++i)
        {
            array[i]->vtable_pt[1](array[i]);
        }
	/*for(i = 0; i < 3; ++i) delete array[i];*/
        for( i = 0; i < 3; ++i)
        {
            array[i]->vtable_pt[DTOR](array[i]);
        }

        
       /* Public_Transport arr2[] =
	{
		Minibus(),
		Taxi(),
		Public_Transport()
	}; */ 
        mini_Ctor((Minibus*)&temp);
        pt_Copy_Ctor(&arr2[0] ,(Public_Transport*)& temp);
        mini_Dtor((Minibus*)&temp);     
      
        taxi_Ctor((Taxi*)&temp);
        pt_Copy_Ctor(&arr2[1] ,(Public_Transport*)& temp);
        taxi_Dtor((Taxi*)&temp);
        
        pt_Ctor(&arr2[2] );
        
        /*for(int i = 0; i < 3; ++i) 
	{
            arr2[i].Display();
	}*/
         for( i = 0; i < 3; ++i)
        {
            arr2[i].vtable_pt[DISPLAY](&arr2[i]);
        }
          
        PrintCount();   /*Public_Transport::PrintCount();*/
        mini_Ctor(&m2);  /*Minibus m2;*/
        PrintCount();    /*m2.PrintCount();*/
        
      /* Minibus arr3[4];
        Taxi *arr4 = new Taxi[4];
	delete [] arr4;*/
        
        for( i = 0; i < 4; ++i) 
	{
            mini_Ctor(&arr3[i]);
	}
         for( i = 0; i < 4; ++i) 
	{
            arr4[i]= malloc(sizeof(Taxi));
            taxi_Ctor(arr4[i]);         
	}
     
        for( i = 3; i >= 0; --i) 
	{
            taxi_Dtor(arr4[i]);         
	}
        
       /* std::cout<<maxFunc<int>(1,2)<<std::endl;*/
        printf(" %d \n", 1 > 2 ? 1 : 2);  
        
        /* Special_Taxi st;
	   TaxiDisplay(st); */
        
        sp_Ctor(&st);
        taxi_Copy_Ctor(&taxi_tamp, (Taxi*)&st );
        taxi_tamp.m_pt.vtable_pt[DISPLAY](&taxi_tamp);
        taxi_tamp.m_pt.vtable_pt[DTOR](&taxi_tamp);
        
        /*
        Public_Convoy *ts1 = new Public_Convoy();
	Public_Convoy *ts2 = new Public_Convoy(*ts1); */
        
        ts1 = malloc(sizeof (Public_Convoy));
        pc_Ctor(ts1);
        
        ts2 = malloc(sizeof (Public_Convoy));       
        pc_Copy_Ctor( ts2, ts1);
   
        ts1->m_pt.vtable_pt[DISPLAY](ts1);
        ts2->m_pt.vtable_pt[DISPLAY](ts2);
        
      /*delete ts1;
	ts2->Display(); // this crashes. fix the bug!
	delete ts2; */
        
        pc_Dtor (ts1);
        ts2->m_pt.vtable_pt[DISPLAY](ts2);
        pc_Dtor (ts2);
        
        /***** delete temp **/
        
        sp_Dtor(&st);
        for( i = 3; i >= 0; --i) 
	{
            mini_Dtor(&arr3[i]);         
	}
        mini_Dtor(&m2);
         
        for( i = 2; i >= 0; --i) 
	{
            pt_Dtor(&arr2[i]);         
	}
        
        mini_Dtor(&m);
         
  return 0;
}



