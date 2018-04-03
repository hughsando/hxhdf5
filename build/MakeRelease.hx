package build;

import sys.FileSystem;
import sys.io.File;
import haxe.zip.Entry;
import haxe.zip.Writer;

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

   static function zipRecurse(src:String, dest:String, entries:List<Entry>)
   {
      if (!FileSystem.exists(src))
         throw 'File does not exist : $src';

      if (FileSystem.isDirectory(src))
      {
         for(file in FileSystem.readDirectory(src))
           zipRecurse(src+"/"+file, dest+"/"+file, entries);
      }
      else
      {
         Sys.print('$dest -> ');

          var bytes = sys.io.File.getBytes(src);
          var zipped = haxe.zip.Compress.run(bytes,9);
          zipped = zipped.sub(2,zipped.length-6);
          if (zipped.length > bytes.length*0.9)
             zipped = null;
          entries.add( {
             fileName : dest,
             fileSize : bytes.length,
             fileTime : Date.now(),
             compressed : zipped!=null,
             dataSize : zipped==null ? 0 : zipped.length,
             data : zipped==null ? bytes : zipped,
             crc32 : haxe.crypto.Crc32.make(bytes),
             extraFields : new List()
          } );
         Sys.println( zipped==null ? bytes.length : zipped.length );
      }
   }



   public static function main()
   {
      var version:String = haxe.Json.parse( File.getContent("haxelib.json") ).version;
      var releaseDir = "hxhdf5-" + version;
      var releaseName = releaseDir + ".zip";
      if (FileSystem.exists(releaseName))
         FileSystem.deleteFile(releaseName);

      var entries:List<Entry> = new List();

      for(file in files)
      {
         zipRecurse(file, releaseDir + "/" + file,entries);
      }

      var bytesOutput = new haxe.io.BytesOutput();
      var writer = new Writer(bytesOutput);
      writer.write(entries);
      // Grab the zipped file from the output stream
      var zipfileBytes = bytesOutput.getBytes();
      // Save the zipped file to disc
      var file = File.write(releaseName, true);
      file.write(zipfileBytes);
      file.close();
   }
}
