class Test
{
  public static function main()
  {
     var args = Sys.args();
     var arg = args.shift();

     if (arg==null || arg=="-help" || arg=="-h")
     {
        Sys.println("Usage test [filename.h5 | h5dump | h5dump ..<h5dump args>.. ]");
     }
     else if (arg=="h5dump")
     {
        hdf5.Dump.run(args);
     }
     else
     {
        var file = hdf5.File.open(args[0]);

        for(i in 0...file.itemCount)
           trace(file.getItem(i));

        for(item in file.getItemsRecurse())
        {
           switch(item)
           {
              case DatasetItem(i): Sys.println("Found data " + i);
              default:
           }
        }

        file.close();
     }
  }
}

