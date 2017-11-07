#define IMPLEMENT_API
#include <hx/CffiPrime.h>
#include <vector>
#include <string>
#include "hdf5.h"


vkind fileKind;
vkind dataKind;


std::string h5LastError;

herr_t h5WalkFunc(unsigned n, const H5E_error2_t *err_desc, void *)
{
   if (h5LastError!="")
      h5LastError += "\n";
   h5LastError += err_desc->desc;
   return 0; //?
}

herr_t h5SetLastError(hid_t estack, void *)
{
   return H5Ewalk2(estack,H5E_WALK_DOWNWARD, h5WalkFunc, 0);
}

extern "C" void InitIDs()
{
   kind_share(&fileKind,"h5File");
   kind_share(&dataKind,"data");

   H5Eset_auto(H5E_DEFAULT,h5SetLastError,0);
}

DEFINE_ENTRY_POINT(InitIDs)

extern "C" int tensorflux_register_prims()
{
   InitIDs();
   return 0;
}


void ClearGc(value inValue)
{
   val_gc(inValue,0);
}

value idToVal(hid_t id, vkind k, void (*destroy)(value inVal))
{
   value result = alloc_abstract(k, (void *)(size_t)id );
   val_gc(result, destroy);
   return result;
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
   if (!val_is_kind(inFile,fileKind)) val_throw(alloc_string("object not a file")); \
   hid_t file = (hid_t)(size_t)val_data(inFile);

void destroyFile(value inFile)
{
   TO_FILE
   if (file)
      H5Fclose(file);
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
}
DEFINE_PRIME1v(fileClose)






