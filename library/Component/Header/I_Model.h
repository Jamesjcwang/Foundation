
#ifndef __I_Model_h__
#define __I_Model_h__

#include "library\Component\Header\I_DataStruct.h"
#include "library\Component\Header\I_CRC.h"
#include <stdbool.h>
#include <stdint.h>
typedef enum
{
  successful_model,
  busy_model,
  overflow_model,
  lastbyte_model,
  failure_model,
  notvalid_model

} resultofaccess;

typedef enum
{
    None,
    successful,
    failure

} Enum_result;
typedef enum
{
  CmdUartTest=0x00,
  CmdGetDeviceID=0x02,
  CmdI2Creset=0x03,
  CmdGetShaSN=0x04,
  CmdGetProtectionICcellvalue=0x05,
  CmdGetFlashID=0x06,
  CmdInttest=0x08,
  CmdVBAT=0x09,
  Cmdsteerlock=0x0A,
  Cmdprecharge=0x0B,
  Cmdtricklecharge=0x0C,
  CmdSkuID=0x0D,
  CmdSleep=0x0E,
  CmdMcuon=0x10,
  CmdPt=0x11,
  Cmd09=0x12,
  CmdVBAT2=0x13,
  CmdDischarge=0x14,
  CmdReset=0x15,
  CmdInttest2=0x16,
  CmdInttest3=0x17,
  CmdVBAT3=0x18,
  CmdSoftreset=0x19,

  Cmdtotal

} enum_CmdID;

typedef enum
{
    subcmdprotection,
    subcmdsha,
    subcmdflash

}enum_SubCmdID;



typedef struct
{

  bool validbit;

  enum_CmdID cmdname;
  uint8_t i;
  uint8_t length;
  uint8_t rawdata[50];


} ComDataStru;




typedef struct
{

  uint32_t (*NewModel)(void);
  resultofaccess(* Get)(uint32_t modelindex,enum_CmdID* cmd,
                     uint8_t* length, uint8_t* value,uint8_t index,bool release );
  // crccheck is true for checking the crc bytes
  // crccheck is false for adding the crc bytes
  resultofaccess (* Set)(uint32_t modelindex,enum_CmdID cmd,
               uint32_t* dataptr,uint32_t length);
 // ComDataStru flashdata;
 // ComDataStru shadata;

} ModelDevice;


ListStruct_uint8 modellist;
ListCollection* model_listcomp;
CRCDevice* model_crccomp;





extern void CreateModelDevice(ModelDevice* model,
                        CRCDevice* crccomp,
                        ListCollection* Delay_listcomp);


#endif

