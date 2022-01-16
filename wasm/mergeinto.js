mergeInto( LibraryManager.library, {
  sosicon_done: function( resultFiles ) {
    const files = UTF8ToString( resultFiles ).split( ";" ).filter( ( item => { return item.length > 0 } ) )
    sosiconResult(files.length);
    for( let i = 0; i < files.length; i++ ) {
      const fileLength = Module['_sosicon_get_file_length']([files[i]]);
      if( fileLength == -1 ) {
        continue;
      }
      const fileContent = Module['FS_readFile'](files[i]);
      const URL = self.URL || self.webkitURL;
      const blob = new Blob( [ fileContent ], { type: "" } );
      const downloadUrl = URL.createObjectURL( blob );
      sosiconResultFile(files[i], fileContent.length, downloadUrl);
    }
  }
})
