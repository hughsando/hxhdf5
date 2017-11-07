#define IMPLEMENT_API
#include <hx/CffiPrime.h>
#include <vector>
#include <string>
#include "hdf5.h"


vkind fileKind;
vkind dataKind;
vkind groupKind;


std::string h5LastError;

herr_t h5WalkFunc(unsigned n, const H5E_error2_t *err_desc, void *)
{
    if (h5LastError!="")
      h5LastError += "\n";
   h5LastError += std::string(err_desc->func_name) + ":" + err_desc->desc;
   return 0; //?
}

herr_t h5SetLastError(hid_t estack, void *)
{
   return H5Ewalk2(estack,H5E_WALK_DOWNWARD, h5WalkFunc, 0);
}

static int _id_name;
static int _id_type;

extern "C" void InitIDs()
{
   kind_share(&fileKind,"h5File");
   kind_share(&dataKind,"data");
   kind_share(&groupKind,"h5Group");

   _id_name = val_id("name");
   _id_type = val_id("type");

   H5Eset_auto(H5E_DEFAULT,h5SetLastError,0);
}

DEFINE_ENTRY_POINT(InitIDs)


extern "C" int hxhdf5_register_prims()
{
   InitIDs();
   return 0;
}


value idToVal(hid_t id, vkind inKind, void (*destroy)(value inVal))
{
   value result;
   if (sizeof(void *)==8)
   {
      result = alloc_abstract(inKind, (void *)(size_t)id );
   }
   else
   {
      hid_t *ptr = (hid_t *)malloc(sizeof(hid_t));
      *ptr = id;
      result = alloc_abstract(inKind, ptr );
   }
   val_gc(result, destroy);
   return result;
}


hid_t valToId(value inValue)
{
   if (sizeof(void *)==8)
   {
      return (hid_t)(size_t)val_data(inValue);
   }

   return *(hid_t *)val_data(inValue);
}
void FreeAbstract(value inValue)
{
   if (sizeof(void *)!=8)
      free(val_data(inValue));
}

void ClearGc(value inValue)
{
   val_gc(inValue,0);
   FreeAbstract(inValue);
}

void CheckError()
{
   if (h5LastError!="")
   {
      value msg = alloc_string(h5LastError.c_str());
      h5LastError = "";
      val_throw( msg );
   }
}



// ------ File -----------------------



#define TO_FILE \
   if (val_kind(inFile)!=fileKind) val_throw(alloc_string("object not a file")); \
   hid_t file = valToId(inFile);

void destroyFile(value inFile)
{
   TO_FILE
   if (file>=0)
      H5Fclose(file);
   FreeAbstract(inFile);
}


value fileOpen(HxString inFilename, bool inReadOnly)
{
   hid_t file = H5Fopen(inFilename.c_str(), inReadOnly ? H5F_ACC_RDONLY : H5F_ACC_RDWR, H5P_DEFAULT );
   CheckError();
   return idToVal(file, fileKind, destroyFile);
}
DEFINE_PRIME2(fileOpen)


value fileCreate(HxString inFilename, bool inAllowOverwrite)
{
   hid_t file = H5Fcreate(inFilename.c_str(), inAllowOverwrite ?  H5F_ACC_TRUNC : H5F_ACC_EXCL, H5P_DEFAULT, H5P_DEFAULT );
   CheckError();
   return idToVal(file, fileKind, destroyFile);
}
DEFINE_PRIME2(fileCreate)


void fileClose(value inFile)
{
   TO_FILE

   if (file>=0)
   {
      H5Fclose(file);
      CheckError();
   }
   ClearGc(inFile);
}
DEFINE_PRIME1v(fileClose)





#define TO_GROUP \
   if (val_kind(inGroup)!=fileKind && val_kind(inGroup)!=groupKind) val_throw(alloc_string("object not a group")); \
   hid_t group = valToId(inGroup);


herr_t h5IterFunc(hid_t obj, const char *name, const H5O_info_t *info, void *op_data)
{
   value array = (value)op_data;

   value result = alloc_empty_object();
   alloc_field(result, _id_name, alloc_string(name));
   alloc_field(result, _id_type, alloc_int((int)info->type) );

   val_array_push(array,result);
   return 0;
}



value groupGetAllChildren(value inGroup)
{
   TO_GROUP

   // H5_INDEX_NAME/H5_INDEX_CRT_ORDER
   value array = alloc_array(0);
   hsize_t idx = 0;

   H5Ovisit( group, H5_INDEX_NAME, H5_ITER_INC, h5IterFunc, (void *)array );

   //H5Literate( group, H5_INDEX_NAME, H5_ITER_INC, &idx, h5GroupIterate, (void *)array )
   CheckError();
   return array;
}
DEFINE_PRIME1(groupGetAllChildren)

int groupGetItemCount(value inGroup)
{
   TO_GROUP

   H5G_info_t  info;
   H5Gget_info( group, &info );
   CheckError();
   return (int)info.nlinks;
}
DEFINE_PRIME1(groupGetItemCount)


value groupGetItemAt(value inGroup,int inIdx)
{
   TO_GROUP

   ssize_t nameLen = H5Gget_objname_by_idx(group, inIdx, 0, 0 );
   CheckError();

   std::vector<char> buffer(nameLen+1);
   H5Gget_objname_by_idx(group, inIdx, &buffer[0], nameLen );

   H5G_obj_t type = H5Gget_objtype_by_idx(group, inIdx);
   CheckError();

   value result = alloc_empty_object();
   alloc_field(result, _id_name, alloc_string(&buffer[0]) );
   alloc_field(result, _id_type, alloc_int((int)type) );

   return result;
}
DEFINE_PRIME2(groupGetItemAt)







