#include "hdf5.h"
#include "H5public.h"
#include "h5tools.h"

#define IMPLEMENT_API
#include <hx/CffiPrime.h>
#include <vector>
#include <string>
#include <algorithm>


vkind fileKind;
vkind dataKind;
vkind datasetKind;
vkind groupKind;

enum DataType
{
   SignedInteger   = 0x01000000,
   UnsignedInteger = 0x02000000,
   Floating        = 0x04000000,
   AsciiString     = 0x08000000,

   BitsMask        = 0x00ffffff,

   Float32        = Floating | 32,
   Float64        = Floating | 64,
   UInt8          = UnsignedInteger | 8,
   UInt16         = UnsignedInteger | 16,
   UInt32         = UnsignedInteger | 32,
   UInt64         = UnsignedInteger | 64,
   Int8           = SignedInteger | 8,
   Int16          = SignedInteger | 16,
   Int32          = SignedInteger | 32,
   Int64          = SignedInteger | 64,
};

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
   kind_share(&datasetKind,"h5Dataset");

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

// ------ Tools -----------------------

extern "C" { int h5dump_main(int argc, const void *); }

int h5DumpMain(value inCommands)
{
   int commandCount = val_is_null(inCommands) ? 0 :  val_array_size(inCommands);
   std::vector<const char *> args(commandCount+2);
   args[0] = "h5dump";
   for(int i=0;i<commandCount;i++)
      args[i+1] = val_string( val_array_i(inCommands,i) );
   args[commandCount+1] = 0;

   typedef const char *Arg_t[];

   return h5dump_main( commandCount+1, &args[0] );
}
DEFINE_PRIME1(h5DumpMain)



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
      ClearGc(inFile);
      CheckError();
   }
   else
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


herr_t h5GetAttrs(hid_t location_id, const char *attr_name, const H5A_info_t *ainfo, void *op_data)
{
   value result = (value)op_data;
   hid_t               attr = -1;

   if((attr = H5Aopen(location_id, attr_name, H5P_DEFAULT)))
   {
      hid_t type = H5Aget_type(attr);
      hid_t space = H5Aget_space(attr);
      hid_t p_type = h5tools_get_native_type(type);

      int cls = H5Tget_class(type);

      hsize_t     size[64];
      hsize_t     nelmts = 1;
      int ndims = H5Sget_simple_extent_dims(space, size, NULL);
      for(int i = 0; i < ndims; i++)
         nelmts *= size[i];
      #undef max
      hsize_t alloc_size = nelmts * std::max(H5Tget_size(type), H5Tget_size(p_type));

      /*
      if (cls==H5T_INTEGER &&  H5Tget_size(type) == 1 )
         printf("  -> char string\n");
      else
      */
         switch(cls)
         {
            case H5T_INTEGER:
               {
               int value = 0;
               H5Aread(attr, p_type, &value);
               alloc_field(result, val_id(attr_name), alloc_int(value) );
               }
               break;
            case H5T_FLOAT:
               {
               double value = 0;
               H5Aread(attr, H5T_NATIVE_DOUBLE, &value);
               alloc_field(result, val_id(attr_name), alloc_float(value) );
               }
               break;
            case H5T_STRING:
               {
               char *ptr = 0;
               H5Aread(attr, p_type, &ptr);
               alloc_field(result, val_id(attr_name), alloc_string(ptr) );
               }
               break;
            /*
            case H5T_TIME:
               printf("  ->time\n");
               break;
            */
            default:
               //printf("  ->unknown\n");
               break;
         }

      H5Tclose(p_type);
      H5Sclose(space);
      H5Tclose(type);
      H5Aclose(attr);
   }

   return 0;
}

value groupGetAttributes(value inGroup, HxString path)
{
   TO_GROUP

   value result = alloc_empty_object();

   hsize_t idx = 0;
   H5Aiterate_by_name(group, path.c_str(), H5_INDEX_CRT_ORDER, H5_ITER_NATIVE, &idx,
       h5GetAttrs, (void *)result, H5P_DEFAULT);

   CheckError();

   return result;
}
DEFINE_PRIME2(groupGetAttributes)


// --- Dataset ----

#define TO_DATASET \
   if (val_kind(inDataset)!=datasetKind) val_throw(alloc_string("object not a dataset")); \
   hid_t dataset = valToId(inDataset);

void destroyDataset(value inDataset)
{
   TO_DATASET
   if (dataset>=0)
      H5Dclose(dataset);
   FreeAbstract(inDataset);
}


value groupOpenDataset(value inGroup, HxString path)
{
   TO_GROUP

   hid_t dataset = H5Dopen2(group, path.c_str(), H5P_DEFAULT);

   CheckError();

   return idToVal(dataset, datasetKind, destroyDataset);
}


DEFINE_PRIME2(groupOpenDataset)

void datasetClose(value inDataset)
{
   TO_DATASET

   if (dataset>=0)
   {
      H5Dclose(dataset);
      ClearGc(inDataset);
      CheckError();
   }
   else
      ClearGc(inDataset);
}

DEFINE_PRIME1v(datasetClose)




value datasetGetShape(value inDataset)
{
   TO_DATASET

   hid_t type = H5Dget_type(dataset);

   value result = alloc_array(0);

   hid_t space = H5Dget_space(dataset);

   hsize_t     size[64];
   hsize_t     nelmts = 1;

   int ndims = H5Sget_simple_extent_dims(space, size, NULL);
   for(int i = 0; i < ndims; i++)
      val_array_push(result, alloc_int( (int)size[i] ) );

   H5Sclose(space);
   H5Tclose(type);

   CheckError();

   return result;
}

DEFINE_PRIME1(datasetGetShape)


int datasetGetType(value inDataset)
{
   TO_DATASET

   hid_t type = H5Dget_type(dataset);

   int result = 0;

   int cls = H5Tget_class(type);

   switch(cls)
   {
      case H5T_INTEGER:
         {
            result = H5Tget_sign(type)==H5T_SGN_NONE ? UnsignedInteger : SignedInteger;
            int sz = H5Tget_size(type);
            result |= (sz<<3);
         }
         break;
      case H5T_FLOAT:
         {
            result = Floating;
            int sz = H5Tget_size(type);
            result |= (sz<<3);
         }
         break;
      case H5T_STRING:
         {
            result = AsciiString;
         }
         break;

      default:
         //printf("  ->unknown\n");
         break;
   }

   H5Tclose(type);

   CheckError();

   return result;
}

DEFINE_PRIME1(datasetGetType)

