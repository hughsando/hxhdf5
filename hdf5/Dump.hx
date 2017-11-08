package hdf5;

class Dump
{
   public static function run(inArgs:Array<String>) : Int
   {
      return h5DumpMain(inArgs);
   }
   static var h5DumpMain = Loader.load("h5DumpMain","oi");
}


