class Test
{
  public static function main()
  {
     var args = Sys.args();

     var file = hdf5.File.open(args[0]);
     trace(file);
     file.close();
  }
}

