#include "library\Component\Header\I_Model.h"





 static resultofaccess _Get(uint32_t modelindex,enum_CmdID* cmd,
                     uint8_t* length, uint8_t* value,uint8_t index,
                     bool release)
 {

   ComDataStru* data;

   data=(ComDataStru*)model_listcomp->GetAt(&modellist,modelindex);


   if (data->validbit==true)
   {
     if (release==true)
     {
       data->validbit=false;
     }

    if (index<(data->length-1))
     {

      *cmd=data->cmdname;
      *length=data->length;
      *value=*(data->rawdata+index);

      return(successful_model);
     }
    else if (index==data->length-1)
     {

       *cmd=data->cmdname;
       *length=data->length;
       *value=*(data->rawdata+data->length-1);
       return(lastbyte_model);

     }
    else
     {

       *cmd=data->cmdname;
       *length=data->length;
       *value=0xff;
        return(overflow_model);
     }
   }
   else
   {
       // SEGGER_RTT_printf(0,"Times %d\r\n",4);
       return (notvalid_model);
   }



 }
 static resultofaccess _Set(uint32_t modelindex,enum_CmdID cmd,
                            uint8_t* dataptr,uint32_t length)
 {

   ComDataStru* data;

   data=(ComDataStru*)model_listcomp->
                           GetAt(&modellist,modelindex);


   if (data->validbit==false)
   {
     data->cmdname=cmd;
     data->length=length;
     for (data->i=0;data->i<length;data->i++)
     {
      *(data->rawdata+data->i)=*(dataptr+data->i);
     SEGGER_RTT_printf(0,"model %d\r\n", *(data->rawdata+data->i));
     }



         data->validbit=true;


     return (successful_model);

   }
   else
   {
       return (busy_model);
   }


 }
static uint32_t _NewModel(void)
{
      ListStruct_uint8 tempdata;

    tempdata.value=(uint32_t)malloc(sizeof(ComDataStru));

    ((ComDataStru*)(tempdata.value))->validbit=false;
    ((ComDataStru*)(tempdata.value))->length=0;
    ((ComDataStru*)(tempdata.value))->cmdname=Cmdtotal;
    return(model_listcomp->Insert(&modellist,&tempdata));

}




void CreateModelDevice(ModelDevice* model,CRCDevice* crccomp,
                       ListCollection* listcomp)
{
    model->NewModel=_NewModel;
    model->Get=_Get;
    model->Set=_Set;
    model_crccomp=crccomp;
    model_listcomp=listcomp;



}
