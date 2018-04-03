package build;

import sys.FileSystem;
import sys.io.File;

class MakeRelease
{
   static var files = [
       "README.md",
       "haxelib.json",
       "api",
       "build/Build.hx",
       "build/Detect.xml",
       "build/Hdf5.xml",
       "build/MakeRelease.hx",
       "build/Settings.xml",
       "configs/H5pubconf.h",
       "hdf5",
       "src",
       "test/Test.hx",
       "tools",
       "ndll/Windows64/hxhdf5.ndll",
   ];

   static function copyRecurse(src:String, dest:String)
   {
      if (!FileSystem.exists(src))
         throw 'File does not exist : $src';

      if (FileSystem.isDirectory(src))
      {
         if (!FileSystem.exists(dest))
            FileSystem.createDirectory(dest);
         for(file in FileSystem.readDirectory(src))
           copyRecurse(src+"/"+file, dest+"/"+file);
      }
      else
      {
         Sys.println('$dest');
         File.copy(src, dest);
         /*
         var path = dest.split("/");
         var file = path.pop();
         var dir = path.join("/");
         Sys.println('$src -> $dir  +  $file');
         */
      }
   }

   static function deleteRecurse(dir:String)
   {
      if (FileSystem.exists(dir))
      {
         for(file in FileSystem.readDirectory(dir))
         {
            var path = dir + "/" + file;
            Sys.println("rm " + path);
            if (FileSystem.isDirectory(path))
               deleteRecurse(path);
            else
               FileSystem.deleteFile(path);
         }
         FileSystem.deleteDirectory(dir);
      }
   }

   public static function main()
   {
      var version:String = haxe.Json.parse( File.getContent("haxelib.json") ).version;
      var releaseDir = "hxhdf5-" + version ;
      deleteRecurse(releaseDir);
      FileSystem.createDirectory(releaseDir);

      for(file in files)
      {
         if (!FileSystem.isDirectory(file))
         {
            var path = file.split("/");
            path.pop();
            var dir = path.join("/");
            FileSystem.createDirectory(releaseDir + "/" +dir);
         }
         copyRecurse(file, releaseDir + "/" + file);
      }
   }
}
