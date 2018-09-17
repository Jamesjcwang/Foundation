#include <stdbool.h>
#include <stdint.h>
#include "library\Component\Header\I_CRC.h"
ListStruct_uint8 crclist;


bool crc_16bit(uint32_t index,uint8_t length,
               uint8_t *data,uint8_t* result,uint32_t* resultlength)
{
   //  SEGGER_RTT_printf(0,"crc %d\r\n",000);
    uint8_t* tempdata;
    uint32_t _tempmaindata;
    uint8_t _temps1[8];

    uint8_t** _temps;
    uint8_t _i,_j,_bitcount;
    uint8_t _length;
    uint8_t tempresult[2];
    uint8_t tempdata1[2];

    _length=length+1;
    uint8_t* _data;
   SEGGER_RTT_printf(0,"crc %d\r\n",3);
     CRCParameter* para;
     para=(CRCParameter*)CRC_listcomp->GetAt(&crclist,index);

   // SEGGER_RTT_printf(0,"crc %d\r\n",para);

    _data=malloc(_length*sizeof(uint8_t));

    _bitcount=para->bitcount;
    *resultlength=_bitcount;

       *(_data)=length+_bitcount;



    for (_i=1;_i<_length;_i++)
    {
      *(_data+_i)=*(data+_i-1);
    }



    _temps=malloc(_bitcount*sizeof(uint8_t*));

    for (_i=0;_i<_bitcount;_i++)
    { *(result+_i)=0;

      *(_temps+_i)=malloc(8*sizeof(uint8_t));

    }

  // SEGGER_RTT_printf(0,"crc %d\r\n",02);
    tempdata=malloc((_length+_bitcount)*sizeof(uint8_t));

    for (_i=0;_i<_bitcount;_i++)
    {
      *(_temps+_i)=malloc(8*sizeof(uint8_t));

    }

     for (_i=0;_i<_length;_i++)
     {
         *(tempdata+_i)=*(_data+_i);
     }
   for (_i=0;_i<_bitcount;_i++)
    {
        *(tempdata+_length+_i)=0;
    }



   if (para->inbitReverse==true)
   {

     for (_i=0;_i<_length;_i++)
     {  *(tempdata+_i)=0;

      for (_j=0;_j<8;_j++)
       {
         *(_temps1+_j)=*(_data+_i)&(1<<_j);

         if ((7-(_j<<1))>0)
         {
           *(tempdata+_i)= *(tempdata+_i)|(_temps1[_j]<<(7-(_j<<1)));
         }
         else
         {
            *(tempdata+_i)= *(tempdata+_i)|(_temps1[_j]>>((_j<<1)-7));
         }

       }

     }
   }
 //SEGGER_RTT_printf(0,"crc %d\r\n",03);
 _tempmaindata=0;

   for (_i=0;_i<_bitcount;_i++)
   {


    if ((_bitcount-2-_i)>=0)
    {
        _tempmaindata=_tempmaindata|
         (((uint32_t)*(tempdata+_i))<<(8<<(_bitcount-2-_i)));
    }
    else
    {
         _tempmaindata=_tempmaindata|((uint32_t)*(tempdata+_i));
    }
   }
 //SEGGER_RTT_printf(0,"crc %d\r\n",04);

 //SEGGER_RTT_printf(0,"crc %d\r\n",_length);
    for (_j=_bitcount;_j<(_length+_bitcount);_j++)
    {
      for (_i=0;_i<8;_i++)
      {
         if ((_tempmaindata>>(_bitcount*8-1))&1==1)
          {
            _tempmaindata=_tempmaindata<<1;
            _tempmaindata=_tempmaindata|((*(tempdata+_j)&(1<<(7-_i)))>>(7-_i));
            _tempmaindata=_tempmaindata^(uint32_t)(para->polynom);

          }

         else
          {
            _tempmaindata=_tempmaindata<<1;
            _tempmaindata=_tempmaindata|((*(tempdata+_j)&(1<<(7-_i)))>>(7-_i));
          }

      }


    }
    // SEGGER_RTT_printf(0,"crc %d\r\n",05);
    for (_i=0;_i<_bitcount;_i++)
    {
      if ((_bitcount-2-_i)>=0)
      {
        *(result+_i)=(_tempmaindata&(((uint32_t)(0xFF)<<(8<<(_bitcount-2-_i)))))
          >>(8<<(_bitcount-2-_i)) ;
      }
      else
      {
          *(result+_i)=_tempmaindata&((uint32_t)(0xFF));
      }


    }

   if (para->outbitReverse==true)
    {

    for (_i=0;_i<_bitcount;_i++)
    {


      for (_j=0;_j<8;_j++)
       {
         *(*(_temps+_i)+_j)= *(result+_i)&(1<<_j);
       }

          *(result+_i)=0;

    }

    for (_i=0;_i<_bitcount;_i++)
    {
      for (_j=0;_j<8;_j++)
       {
          if ((7-(_j<<1))>0)
         {
           *(result+_i)= *(result+_i)|
           ((*(*(_temps+(_bitcount-1-_i))+_j))<<(7-(_j<<1)));
         }
         else
         {
           *(result+_i)= *(result+_i)|
           ((*(*(_temps+(_bitcount-1-_i))+_j))>>((_j<<1)-7));

         }
       }

     }
    }
 //SEGGER_RTT_printf(0,"crc %d\r\n",05);


   SEGGER_RTT_printf(0,"crc %d\r\n",1);
     free(tempdata);
      for (_i=0;_i<_bitcount;_i++)
     {
         free(*(_temps+_i));

     }
     free(_temps);
     free(_data);

   // SEGGER_RTT_printf(0,"crc %d\r\n",*(result));
//SEGGER_RTT_printf(0,"crc %d\r\n",*(result+1));
tempresult[0]= *(result);
tempdata1[0]=*(data+length);
     for (_i=1;_i<_bitcount;_i++)
     {     if( *(result+_i)!=*(data+length+_i))
       {
           SEGGER_RTT_printf(0,"crc %d\r\n",4);
          return(false);
       }

     }
      // SEGGER_RTT_printf(0,"crc %d\r\n",*(tempresult));
//SEGGER_RTT_printf(0,"crc %d\r\n",*(tempdata1));

SEGGER_RTT_printf(0,"crc %d\r\n",2);
     return (true);

}

uint32_t _CRC_ParameterInitial(enum_crckind bitcount, uint32_t polynom,
                               bool inbitreverse,bool outbitreverse)
{
     ListStruct_uint8 tempdata;

    tempdata.value=(uint32_t)malloc(sizeof(CRCParameter));

    ((CRCParameter*)(tempdata.value))->bitcount=bitcount;
    ((CRCParameter*)(tempdata.value))->polynom=polynom;
    ((CRCParameter*)(tempdata.value))->inbitReverse=inbitreverse;
    ((CRCParameter*)(tempdata.value))->outbitReverse=outbitreverse;

    return(CRC_listcomp->Insert(&crclist,&tempdata));



}
void CreateCRCDevice(CRCDevice* device,ListCollection* listcomp)
{
    device->crc=crc_16bit;
    device->ParameterInitial=_CRC_ParameterInitial;
    CRC_listcomp=listcomp;

}
