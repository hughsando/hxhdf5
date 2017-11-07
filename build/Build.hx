import sys.FileSystem;

class Build
{
   static var haxelibExtra:Array<String> = [ ];
   static var builds = ["detect", "settings", "hdf5" ];
   static var toolExt = Sys.systemName()=="Windows" ? ".exe" : "";
   static var debugExt = "";
   static var debugFlag = [];
   static var commandError = false;

   public static function command(exe:String, args:Array<String>)
   {
      if (exe=="haxelib")
         args = args.concat(haxelibExtra);

      Sys.println(exe +" " + args.join(' '));
      if (Sys.command(exe,args)!=0)
         commandError = true;
   }

   public static function readStdout(command:String,args:Array<String>)
   {
      var result = new Array<String>();
      var proc = new sys.io.Process(command,args);
      try
      {
         while(true)
         {
            var out = proc.stdout.readLine();
            result.push(out);
         }
      } catch(e:Dynamic){}
      //proc.exitCode();
      proc.close();
      return result;
   }

   public static function detectBuild()
   {
      command("haxelib", ["run","hxcpp","Detect.xml" ] );
      var lines = readStdout('./obj/detect$toolExt',[]);
      sys.io.File.saveContent("../configs/gen_detect.c", lines.join("\n"));
   }


   public static function settingsBuild()
   {
      command("haxelib", ["run","hxcpp","Settings.xml" ] );
      var lines = readStdout('./obj/settings$toolExt',[]);
      sys.io.File.saveContent("../configs/gen_settings.c", lines.join("\n"));
   }


   public static function hdf5Build()
   {
      command("haxelib", ["run","hxcpp","Hdf5.xml" ] );
   }


/*
   public static function testBuild()
   {
      var here = Sys.getCwd();
      Sys.setCwd("../test/smoke");

      command("haxe", ["compile.hxml" ].concat(debugFlag) );
      if (!commandError)
         command('cpp/Test$debugExt$toolExt', [] );
      Sys.setCwd(here);
   }
*/

   static function deleteDirRecurse(dir:String)
   {
      for(file in FileSystem.readDirectory(dir))
      {
         var path = dir + "/" + file;
         if (FileSystem.isDirectory(path))
            deleteDirRecurse(path);
         else
            FileSystem.deleteFile(path);
      }
      FileSystem.deleteDirectory(dir);
   }


   public static function cleanBuild()
   {
      for(gen in ["gen_detect.c", "gen_settings.c"])
         try {
            FileSystem.deleteFile('../config/$gen');
         }
         catch(e:Dynamic)  { }
      for(dir in ["obj"])
      {
         try {
            deleteDirRecurse(dir);
         } catch(d:Dynamic) { }
      }
   }

   public static function main()
   {
      // haxelibExtra.push("-DHXCPP_M64");

      var option:String = null;
      var args = Sys.args();
      var a = 0;
      while(a<args.length)
      {
         var arg = args[a];
         if (arg.substr(0,1)=='-')
         {
            if (arg=="-debug")
            {
               debugFlag = ["-debug"];
               debugExt = "-debug";
            }
            else if (arg=="-dirty")
            {
               haxelibExtra.push(arg);
               a++;
               haxelibExtra.push(args[a]);
            }
            else
               haxelibExtra.push(arg);
         }
         else if (option==null)
            option = arg;
         else
         {
            option = "help";
            break;
         }
         a++;
      }

      if (option=="all")
      {
         for(build in builds)
         {
            Sys.println('$build...');
            Reflect.field(Build, build + "Build")();
            if (commandError)
            {
               Sys.println('There were errors building $build');
               Sys.exit(-1);
            }
         }
      }
      else if (option=="clean")
      {
         cleanBuild();
      }
      else
      {
         if (builds.indexOf(option)<0)
         {
            Sys.println("Usage: haxe --run Build.hx target [-arg1 -arg2 ...]");
            Sys.println(' target = one of :$builds or "all" or "clean"');
            Sys.exit(-1);
         }

         Reflect.field(Build, option + "Build")();
      }
   }
}
