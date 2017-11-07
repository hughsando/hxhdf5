package hdf5;

class File implements DatasetContainer
{
   var handle:Dynamic;

   function new(inHandle:Dynamic) handle = inHandle;

   public function close()
   {
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
   static var fileCreate = Loader.load("fileOpen","sbo");
}

