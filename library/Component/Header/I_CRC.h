#ifndef __I_CRC_h__
#define __I_CRC_h__


#include "library\Component\Header\I_DataStruct.h"
typedef enum
{
    _8bit=1,
    _16bit=2,
    _32bit=4
} enum_crckind;


typedef struct
{
    enum_crckind bitcount;
    uint32_t polynom;
    bool inbitReverse;
    bool outbitReverse;


} CRCParameter;

typedef struct
{

// length:length of data not including crc value
//

bool (*crc)(uint32_t index,uint8_t length,
               uint8_t  *data, uint32_t * result,uint32_t* resultlength);

uint32_t(*ParameterInitial)(enum_crckind bitcount, uint32_t polynom,
                            bool inbitreverse, bool outbitreverse);

} CRCDevice;
ListCollection* CRC_listcomp;



extern void CreateCRCDevice(CRCDevice* device,ListCollection* listcomp);

#endif
