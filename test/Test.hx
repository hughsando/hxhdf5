class Test
{
  public static function main()
  {
     var args = Sys.args();

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

