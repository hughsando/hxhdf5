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
        var file = hdf5.File.open(arg);

        for(i in 0...file.itemCount)
        {
           Sys.println("Top level " + file.getItem(i) );
        }

        for(item in file.getItemsRecurse())
        {
           switch(item.type)
           {
              case DatasetItem:
                 var dataset = item.openDataset();
                 Sys.println(dataset.name + ":" + dataset.shape + " x " + dataset.typename);
                 dataset.close();

              default:
           }
        }

        if (args[0]!=null)
        {
           var dataset = file.openDataset(args[0]);
           Sys.println(dataset.name + ":" + dataset.shape + " x " + dataset.typename);
           dataset.close();
        }


        if (args[1]!=null)
        {
           trace(file.getAttributes(args[0]));
        }

        file.close();
     }
  }
}

