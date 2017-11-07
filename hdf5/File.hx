package hdf5;

class File extends Group
{
   function new(inHandle:Dynamic) super(inHandle);

   public function close()
   {
      if (handle!=null)
         fileClose(handle);
      handle = null;
   }

   public static function open(inFilename:String, inReadOnly:Bool = true) : File
   {
      return new File( fileOpen(inFilename, inReadOnly) );
   }

   public static function create(inFilename:String, inAllowOverwite:Bool = true) : File
   {
      return new File( fileCreate(inFilename, inAllowOverwite) );
   }


   static var fileClose = Loader.load("fileClose","ov");
   static var fileOpen = Loader.load("fileOpen","sbo");
   static var fileCreate = Loader.load("fileCreate","sbo");
}

