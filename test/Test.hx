import hdf5.DataType;

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

           var data = dataset.readData(DataType.Float32);
           Sys.println("Data size:" + data.length);
           Sys.print("[ ");
           for(i in 0...dataset.elementCount)
              Sys.print(data.getFloat(i<<2) + " ");
           Sys.println(" ]");
           #if cpp
           var floats:Array<cpp.Float32> = cpp.NativeArray.create(dataset.elementCount);
           dataset.fillData(floats, DataType.Float32);
           Sys.println("floats = " + floats );
           #end

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

